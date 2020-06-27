#include  <Lsc/Vault/Vault.h>

Lsc::Vault::Table::Table(std::string Name_, Lsc::Vault::Vault *Vault_):
mName(std::move(Name_)),
mVault(Vault_)
{

}

