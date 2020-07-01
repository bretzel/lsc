#pragma once

#include <Lsc/Vault/Lib.h>
#include <Lsc/Vault/Model/Field.h>

namespace Lsc::Vault
{


class Vault;

class VAULT_LIB  Table
{
    std::string mName;
    Field::Collection   mFields;
    Vault*              mVault = nullptr;
    using Collection    = std::vector<Table>;
    friend class Vault;
    Expect<std::size_t> PullSchema(); ///< Construire la liste des Fields de cette table;
    
public:

    Table() = default;
    Table(Table&&) noexcept = default;
    Table(const Table&) = default;
    
    Table(std::string Name_, Vault* Vault_);
    
    sqlite3* DB();
};

}
