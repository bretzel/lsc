#include <Lsc/Vault/Model/Entity.h>

#include <Lsc/Vault/Vault.h>

namespace Lsc::Vault
{


Entity::~Entity()
{
    if(!mModel.empty())
        mModel.clear();
    if(!mLocalFields.empty())
        mLocalFields.clear();
    Rem::Debug() << __PRETTY_FUNCTION__ << "["<< mName << "]: \\O/!";
}


Entity::Entity(std::string Name_, Vault *Vault_):
mVault(Vault_),
mName(std::move(Name_))
{

}


Entity::Entity(std::string Name_):
mName(std::move(Name_))
{

}

Entity &Entity::operator+(Field&& F)
{
    mLocalFields.emplace_back(std::move(F));
    return *this;
}


Entity &Entity::operator<<(Field* F) noexcept
{
    Rem::Debug() << "Appending Field: '" << F->Name() << "' into Entity '" <<  mName << '\'';
    mModel.push_back(F);
    return *this;
}


/*!
 * @brief Insert existing Field From the given "Tablename:*;**;Fieldname;,..."
 *
 * Init Chaining operation.
 * @param FieldName_
 * Splits FieldName_ into Words separated by  TABLENAME:FIELD and comma:
 *       Words:0 Tablename - Mandatory
              :1+ Field(s) (Ex.: "User:UserName, Birth, Alias, Name")  ....
              :1->"*"  All fields except the CID==0.
              :1->"**" All fields including CID==0.
              
   Or TABLENAME alone for the default "*".
 *
 * @return Self for chaining operation;
 *
 * @todo Must work with exceptions(Rem&).
 */
Entity &Entity::operator+=(const String& Fields_)
{
    try
    {
        (void)Parse(Fields_);
    }
    catch(Rem& Msg)
    {
        // Just re-throw for now...
        throw(Msg);
    }
    return *this;
}



/*!
 * @brief Insert existing Field From the given "Tablename:Fieldname"
 *
 * Chaining operation.
 *
 * @param FieldName_
 * @return Self for chaining operation;
 */
Entity &Entity::operator+(const String& FieldName_)
{
    return (*this) += FieldName_;
}

bool Entity::End( Entity::Cursor C_)
{
    return C_ == mModel.end();
}


/*!
 * @brief Integer index overloaded operator
 * @param Name_ The name of the column/field;
 * @return index of the column for addressing the data row.
 */
int Entity::operator[](const std::string &Name_)
{
    int I=0;
    for(const auto* F : mModel)
    {
        if(F->Name()() == Name_) return I;
    }
    return -1;
}

/*!
 * @brief Parses the list of Table:Field separated by comma;
 * @param Text_
 * @return remark code.
 */
Return Entity::Parse(const String &Text_)
{
    //String Str;
    Rem::Debug() << __PRETTY_FUNCTION__ <<": '" << Text_ << '\'';
    String::Word::Collection Words;
    (void) Text_.Words(Words,":,", true);
    for(auto S: Words)
    {
        Return R;
        Rem::Debug() << __PRETTY_FUNCTION__ <<": Word '" << *S << '\'';
        switch((*S)[0])
        {
            case ':':
                R = SetTable(*S);
                //...
                break;
            case ',':
                R = ProcessField(*S);
                //...
                break;
            default:
                mStack.push(*S);
                break;
        }
    }
    
    if(!mStack.empty())
    {
        if(!mTable)
            return Rem::Error() << __PRETTY_FUNCTION__ <<": Failed processing Entity from '" << Text_ << "'";
        ProcessField(mStack.top());
    }
    if(!mStack.empty())
        Rem::Warning() << __PRETTY_FUNCTION__ <<": extra tokens not processed in Entity ('" << Text_ << "')";
    
    return Rem::Int::Ok;
}


Return Entity::SetTable(const String &Text_)
{
    std::string Str;
    if(mStack.empty())
        return Rem::Error() << __PRETTY_FUNCTION__ << " : Error Processing Entity from ('" << Text_ << "')";
    try
    {
        mTable = *(*mVault)[mStack.top()];
    }
    catch(Rem & R)
    {
        throw R;
    }
    
    mStack.pop();
    
    return Rem::Int::Ok;
}

Return Entity::ProcessField(const String &Text_)
{
    if(!mTable)
        return Rem::Error() << __PRETTY_FUNCTION__ << ": ";
    
    try
    {
        auto F = *(*mTable)[mStack.top()];
        (*this) << F;
    }
    catch(Rem& R)
    {
        throw R;
    }
    mStack.pop();
    return Rem::Int::Ok;
}


/*!
 * @brief Only creates a single table. Uses internal table storage
 * @return Rem::Int
 */
std::string Entity::GenerateSchema()
{
    if(!mVault)
        throw Rem::Exception() << __PRETTY_FUNCTION__ << ": Entity '" << mName << "' must be linked to a Vault prior to generate it's schema.";
    
    // Using mName as the Table name:
    Table TSqlTbl = {mName, mVault};
    for(auto const& F : mLocalFields)
    {
        TSqlTbl << Field{&TSqlTbl, F.Name(),F.mType, F.mAttr};
    }
    
    return TSqlTbl.Serialize()();
}

}