#pragma once

#include <Lsc/Vault/Lib.h>
#include <Lsc/Vault/Model/Field.h>
#include <Lsc/Vault/Model/Table.h>

namespace Lsc::Vault
{

class Vault;

class VAULT_LIB  Entity
{
    friend class Vault;
    Vault*  mVault = nullptr;
    using Fields = std::vector<Field*>; ///< J'ai besoin de restreindre la copie donc ici on ne prend que l'adresse ( ou la r&eacute;f&eacute;rence) .
    using Cursor = Fields::iterator;    ///< Current position;
    
    Field::Collection   mLocalFields; ///< Schema &eacute;tendu ou initiale.
    Cursor              mCursor;
    Fields              mModel;
    String              mName;
    Table*              mTable = nullptr;
public:
    Entity() = default;
    Entity(const Entity&) = default;
    Entity(Entity&&) noexcept = default;
    
    virtual ~Entity();
    
    Entity(std::string Name_, Vault* Vault_);
    Entity(std::string Name_);
    
    //--------------------Composition de l'Entity : -------------------------------
    #pragma region EntityCompose
    Entity& operator + (Field&&);
    Entity& operator + (const String&);
    Entity& operator << (Field*) noexcept;
    int     operator [](const std::string& Name_);
    
    bool End(Cursor C_);
    Entity::Cursor Begin() { mCursor = mModel.begin(); return mCursor;}
    
    /*!
     * @brief Temporaire...
     * @tparam T
     * @param D_
     * @return
     */
    template<typename T=const std::string&> Entity& operator << (T D_)
    {
        String Str;
        Str << D_;
        //... Selon la donnee versus le type de donnee de la colonne(field) courante,
        // on ne verifie que si le type est grossierement compatible.
        //...
        return *this;
    }
    
    #pragma endregion EntityCompose
    //-----------------------------------------------------------------------------
    
//...
};

}
