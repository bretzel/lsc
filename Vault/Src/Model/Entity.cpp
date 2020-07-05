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
    mModel.push_back(F);
    return *this;
}


/*!
 * @brief Insert existing Field From the given "Tablename:Fieldname"
 * @param FieldName_
 * @return Self for chaining operation;
 */
Entity &Entity::operator+(const String& FieldName_)
{
    String::Word::Collection Words;
    std::size_t count = FieldName_.Words(Words,":",false);
    if(!count)
        return *this; ///@todo handle empty result.
    //..
    Expect<Table*> Tbl = nullptr;
    Expect<Field*> F   = nullptr;
    if(count  == 2)
    {
        Tbl = (*mVault)[*Words[0]];
        if(!(mTable = *Tbl ? *Tbl : nullptr))
            return *this;
        F = (*(*Tbl))[(*F)->Name()];
    }
    else
    {
        if(mTable)
            F = (*mTable)[*Words[0]];
    }
    
    return *this;
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

}