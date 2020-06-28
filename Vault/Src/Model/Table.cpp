#include  <Lsc/Vault/Vault.h>
#include <Lsc/Vault/Model/Table.h>

Lsc::Vault::Table::Table(std::string Name_, Lsc::Vault::Vault *Vault_):
mName(std::move(Name_)),
mVault(Vault_)
{

}


Lsc::Expect<size_t> Lsc::Vault::Table::PullSchema()
{
    return Rem::Warning() << __PRETTY_FUNCTION__ << "(" << mName << "):" << Rem::Int::Implement;
}

