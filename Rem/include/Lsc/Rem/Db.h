#pragma once

#include <Lsc/Rem/Rem.h>
#include <sqlite3.h>
namespace Lsc
{



class REM_LIB Db
{
    sqlite3*    mHandle = nullptr;
    std::string mDbName;
public:
    
    using Return = Expect<sqlite3*>;
    
    Db()          = default;
    Db(Db&&)      = default;
    Db(const Db&) = default;

    Db(std::string DbName_);
    
    std::string Filename();
    
    Return Open();
    Return Close();
    Return Create();
    

};

}

