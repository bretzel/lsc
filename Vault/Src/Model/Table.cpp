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
        Field::SchemaInfo Infos;
        for(int i=0; i<argc; i++)
        {
            Rem::Debug() << "[" << azColName[i] << "]: " << argv[i];
            Infos.push_back({azColName[i], argv[i]});
        }
        This->mFields.push_back({This, Infos});
        Rem::Debug() << "Field: "  << This->mFields.back().Serialize();
        Rem::Debug() << "------------------------------------";
        Infos.clear();
        return SQLITE_OK;
    };
    
    if(SQLITE_OK != sqlite3_exec(mVault->Handle(), sql.c_str(), Lm, this, &ErrMsg))
    {
        Expect<std::size_t> R = Rem::Error() << "Table::PullSchema: sqlite3: " << sqlite3_errmsg(mVault->Handle());
        sqlite3_free(ErrMsg);
        return R;
    }
    
    return mFields.size();
}


sqlite3 *Lsc::Vault::Table::DB()
{
     return mVault->Handle();
}

