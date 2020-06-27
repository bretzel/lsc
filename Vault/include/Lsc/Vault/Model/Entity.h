#pragma once

#include <Lsc/Vault/Lib.h>
#include <Lsc/Vault/Model/Field.h>

namespace Lsc::Vault
{

class Vault;

class VAULT_LIB  Entity
{
    Vault*  mVault = nullptr;
    using Fields = std::vector<Field&>; ///< J'ai besoin de restreindre la copie donc ici on ne prend que l'adresse ( ou la r&eacute;f&eacute;rence) .
    
public:

//...
};

}
