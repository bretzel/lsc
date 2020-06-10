#pragma once
#include <Lsc/Vault/Lib.h>
#include <Lsc/Rem/Rem.h>
#include <Lsc/Rem/Object.h>

namespace Lsc::Vault
{


/*!
    @brief  Renferme les informations sur la colonne du schema sqlite3 et du modele.

    
*/
class VAULT_LIB Field : public Object
{
    String mID; ///< Nom de la colonne de la table du schema sqlite3 - ET - d'un item du Modele donne par le nom de la classe. ( CLASSNAME_IMPL )
    
                
    // Test rapide pour verification. La veritable utilisation de la refelxion se fera dans l'implementation du "Modele".
    DECLOBJ_ID
    
public:
    Field() = default;
    Field(const Field&) = default;
    Field(Field&&) noexcept = default;
    ~Field() override;

    Field(std::string Id_);
    Field(Object::Shared Table_);


};

}
