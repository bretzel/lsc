#pragma once

#include <Lsc/Vault/Lib.h>
#include <Lsc/Vault/Model/Field.h>

namespace Lsc::Vault
{

class Vault;

class VAULT_LIB  Entity
{
    friend class Vault;
    Vault*  mVault = nullptr;
    using Fields = std::vector<Field*>; ///< J'ai besoin de restreindre la copie donc ici on ne prend que l'adresse ( ou la r&eacute;f&eacute;rence) .
    
    Field::Collection  mLocalFields; ///< Schema etendu ou locale
    Fields mModel;
    
    String mName;
public:
    Entity() = default;
    Entity(const Entity&) = default;
    Entity(Entity&&) noexcept = default;
    
    virtual ~Entity();
    
    Entity(std::string Name_, Vault* Vault_);
    Entity(std::string Name_);
    
    //--------------------Composition de l'Entity : -------------------------------
    #pragma region EntityCompose
    Entity& operator + (Field&);
    Entity& operator + (const String&);
    Entity& operator << (Field&&) noexcept;
    template<typename T=const std::string&> Entity& operator << (T D_)
    {
        
        return *this;
    }
    #pragma endregion EntityCompose
    //-----------------------------------------------------------------------------
    
//...
};

}