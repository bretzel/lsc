#pragma once

#include <Lsc/Vault/Lib.h>
#include <Lsc/Vault/Model/Field.h>

namespace Lsc::Vault
{


class Vault;

class VAULT_LIB  Table
{
    std::string mName;
    Field::Collection   mField;
    Vault*              mVault = nullptr;
public:

    Table() = default;
    Table(Table&&) noexcept = default;
    Table(const Table&) = default;
    
    Table(std::string Name_, Vault* Vault_);
};

}
