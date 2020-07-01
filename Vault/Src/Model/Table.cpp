#include  <Lsc/Vault/Vault.h>
#include <Lsc/Vault/Model/Table.h>

Lsc::Vault::Table::Table(std::string Name_, Lsc::Vault::Vault *Vault_):
mName(std::move(Name_)),
mVault(Vault_)
{

}


Lsc::Expect<size_t> Lsc::Vault::Table::PullSchema()
{
    String sql = "PRAGMA table_info('%s')";
    sql << mName;
    
    char* ErrMsg = nullptr;
    auto Lm = [](void *this_, int argc, char **argv, char **azColName) -> int{
        auto* This = reinterpret_cast<Table*>(this_);
        Rem::Debug() << "------------------------------------";
        for(int i=0; i<argc; i++)
        {
            Rem::Debug() << "[" << azColName[i] << "]: " << argv[i];
        }
        Rem::Debug() << "------------------------------------";
        return SQLITE_OK;
    };
    
    sqlite3_exec(mVault->Handle(), sql.c_str(), Lm, this, &ErrMsg);
    
    return Rem::Warning() << __PRETTY_FUNCTION__ << "(" << sql() << "):" << Rem::Int::Implement;
}

