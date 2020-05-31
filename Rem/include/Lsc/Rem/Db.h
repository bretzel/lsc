#pragma once

#include <Lsc/Rem/String.h>
#include <sqlite3.h>
namespace Lsc
{

class REM_LIB Db
{
    sqlite3*    mHandle = nullptr;

public:
    Db()          = default;
    Db(Db&&)      = default;
    Db(const Db&) = default;

    Db(std::string DbName_);
    

};

}

