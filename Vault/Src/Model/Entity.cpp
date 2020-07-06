#include <Lsc/Vault/Model/Entity.h>

#include <Lsc/Vault/Vault.h>

namespace Lsc::Vault
{



Entity::Parsers Entity::EParsers = {
    {':', &Entity::ParseTableName },
    {',', &Entity::ParseFieldName }
};


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
Entity &Entity::operator+=(const String& FieldName_)
{
    try
    {
        String::Word::Collection Words;
        std::size_t              count = FieldName_.Words(Words, ":,", true);
        if(!count)
            return *this; ///@todo handle empty result.
        //..
        Expect<Table *> Tbl = nullptr;
        Expect<Field *> F   = nullptr;
        int Idx = 0;
        for(auto S: Words)
        {
            Rem::Debug() << __PRETTY_FUNCTION__ << " Word: [" << *S << "]:";
            if(Idx == 0 )
            {
                Tbl = (*mVault)[*S];
                Rem::Debug() << __PRETTY_FUNCTION__ << ": Tablename: '" << (*Tbl)->Name() << '\'';
                ++Idx;
                continue;
            }
            
            if(*S == "*")
            {
                // All fields except CID=0:
                Rem::Debug() << "'*': All fields except 'CID':" << (*Tbl)->Fields().size();
                int Fid = 0;
                for(auto& Fi : (*Tbl)->Fields())
                {
                    if(!Fid)
                    {
                        ++Fid;
                        Rem::Debug() << " Bypass Column:['" << Fi.Name() << "']";
                        continue;
                    }
                    Rem::Debug() << " Column:['" << Fi.Name() << "']";
                    (*this) << &Fi;
                    ++Fid;
                }
                return *this;
            }
            if(S() == "**")
            {
                // All fields including CID=0:
                Rem::Debug() << "'**': All fields including 'CID':" << (*Tbl)->Fields().size();
                for(auto& Fi : (*Tbl)->Fields())
                {
                    (*this) << &Fi;
                }
                return *this;
            }
            F = (*(*Tbl))[*S];
            (*this) << *F;
        }
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
int Entity::operator[](const std::string &Name_)
{
    int I=0;
    for(const auto* F : mModel)
    {
        if(F->Name()() == Name_) return I;
    }
    return -1;
}


Return Entity::Parse(const String &Text_)
{
    String Str;
    String::Word::Collection Words;
    
    return Lsc::Return();
}
Return Entity::QueryTableName(const String &Text_)
{
    return Lsc::Return();
}
Return Entity::QueryFieldName(const String &Text_)
{
    return Lsc::Return();
}

}