#include <Lsc/Vault/Vault.h>

#ifdef _WIN32
#include <shlwapi.h>
#else
    #include <unistd.h>
#endif




namespace Lsc::Vault
{

Vault::Vault::~Vault()
{
    Rem::Debug() << __PRETTY_FUNCTION__ << ": ";
    if(mDB)
        Close();
    else
        Rem::Debug() << __PRETTY_FUNCTION__ << ": Clear.";
}


Vault::Vault::Vault(std::string DbName_):
mName(std::move(DbName_))
{

}

/*!
 * @brief   Opens the sqlite3 database file.
 *
 * @note Do not let sqlite3_open auto-create the file automatically.
 * @return sqlitedb::code::ok.
*/

Return Vault::Open()
{
    String str = mName;
    str << ".sqlite3";
#ifdef  _WIN32
    if (!PathFileExistsA(str().c_str()))
        return Rem::Error() << " sqlite3 open db error(" << mName <<  ") - no such database file.\n";
    
#else
    if(access(str().c_str(), F_OK) == 0) // Just check if the db file exists.
        return Rem::Error() << "error openning database '" << mName << "' - database file not found.";
    
#endif
    int res = sqlite3_open(str().c_str(), &mDB);
    if (res != SQLITE_OK)
        return Rem::Error()<< " sqlitedb open db error(" << res << ") - " << sqlite3_errmsg(mDB);

    std::cout << "(" << res << ")" << sqlite3_errmsg(mDB) << "\n";

    return Rem::Int::Accepted;
}


Return Vault::Close()
{
    if(!mDB)
        return Rem::Warning() << "Vault::Close() : " << Rem::Int::Rejected;
    sqlite3_close(mDB);
    mDB = nullptr;
    return Rem::Int::Accepted;
}


Return Vault::Create()
{
    String str = mName;
    str << ".sqlite3";
#ifdef  _WIN32
    if (PathFileExistsA(str().c_str()))
        return Rem::Error() << " sqlitedb create db error - Database file exists.";

#else
    int exists = access(str().c_str(), F_OK) == 0; // Just check if the db file exists.
    if (exists)
        return Rem::Error() << "error creating database '" << mName << "' - database file already exists.";
        
    
#endif
    int res = sqlite3_open(str().c_str(), &mDB);
    if (res != SQLITE_OK)
        return Rem::Error() << " sqlite3 create db error(" << res <<  ") - " <<  sqlite3_errmsg(mDB);
    
    return Rem::Int::Accepted;
}

}
