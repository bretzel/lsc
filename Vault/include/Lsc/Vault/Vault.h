#pragma once

#include <Lsc/Vault/Lib.h>
#include <Lsc/Rem/Rem.h>
#include <Lsc/Vault/Model/Table.h>

namespace Lsc::Vault
{

class VAULT_LIB Vault
{
    sqlite3* mDB = nullptr;
    std::string mName;

    Table::Collection mTables;
    Expect<std::size_t> PullSchema(); ///< Construire la liste des Tables de cette Vo&ucirc;te.
    
public:
    Vault() = default;
    Vault(Vault&&) = default;
    Vault(const Vault&) = default;

    ~Vault();
    Vault(std::string DbName_);
    sqlite3* Handle() { return mDB; }
    Return Open();
    Return Close();
    Return Create();
    
    
    //Return Query();
    
    
};

}
