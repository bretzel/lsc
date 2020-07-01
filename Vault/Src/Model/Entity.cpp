#include <Lsc/Vault/Model/Entity.h>


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

Entity &Entity::operator+(Field &F)
{
    mModel.push_back(&F);
    return *this;
}


Entity &Entity::operator<<(Field && F) noexcept
{
    mLocalFields.emplace_back(std::move(F));
    return *this;
}



Entity &Entity::operator+(const String& FieldName_)
{
    String::Word::Collection Words;
    std::size_t count = FieldName_.Words(Words,":",false);
    if(!count)
        return *this; ///@todo handle empty result.
    //..
    
    return *this;
}

bool Entity::End( Entity::Cursor C_)
{
    return C_ == mModel.end();
}


}