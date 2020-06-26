#pragma once

#include <Lsc/Vault/Lib.h>
#include <Lsc/Rem/Rem.h>


namespace Lsc::Vault
{

class VAULT_LIB Vault
{
    sqlite3* mDB = nullptr;
    std::string mName;


public:
    Vault() = default;
    Vault(Vault&&) = default;
    Vault(const Vault&) = default;

    Vault(const std::string& DbName_);
    

};

}
