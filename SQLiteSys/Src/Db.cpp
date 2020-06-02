

#include <Lsc/SQLiteSys/Db.h>
#include <Lsc/SQLiteSys/sqlite3.h>

#ifdef  _WIN32
#   include <Windows.h>
#   include <Shlwapi.h>
#else
# include <unistd.h>
#endif




namespace Lsc::Db
{

Db::Db(std::string DbName_)
{
   String Str_ = std::move(DbName_);
    mDbName    = Str_();
    Str_ << ".Db";

    Rem::Debug() << __FUNCTION__ << ": db file: [" << Str_() << "]";

}

Db::Return Db::Open()
{
    String Str_  = mDbName;
    Str_ << ".Db";
#ifdef  _WIN32
    if (!PathFileExistsA(Str_().c_str()))
        return Rem::Error()<< " -  creating database '"<< mDbName <<"' :"<< strerror(errno);
#else
    int ok = access(Str_().c_str(),F_OK) == 0; // Just check if the db file exists.
    if(!ok)
        return Rem::Error()<< " -  openning database '"<< mDbName <<"' :"<< strerror(errno);
    
#endif
    int res = sqlite3_open(Str_().c_str(), &mHandle);
    if (res != SQLITE_OK)
        return Rem::Error() <<  " Rem::Db open sqlite3 Database  file error(" << res << ") : " << sqlite3_errmsg(mHandle);
        

    Rem::Debug() << "(" << res << ")" << sqlite3_errmsg(mHandle) << "\n";
    
    return mHandle;
}

Db::Return Db::Close()
{
    std::cout << __FUNCTION__ << '\n';
    if(mHandle)
        sqlite3_close(mHandle);
    mDbName.clear();
    return nullptr;
}


Db::Return Db::Create()
{
    String str = Filename();
#ifdef  _WIN32
    if (PathFileExistsA(str().c_str()))
        return Rem::Error()<< " -  creating database '"<< mDbName <<"' : File already exists.";
#else
    int exists_ = access(str().c_str(),F_OK) == 0; // Just check if the db file exists.
    if(exists_)
        return Rem::Error()<< " -  creating database '"<< mDbName <<"' : File already exists";

#endif
    int res = sqlite3_open(str().c_str(), &mHandle);
    if (res != SQLITE_OK)
        return Rem::Error() << " sqlitedb open db error(" << res << ") - " << sqlite3_errmsg(mHandle);

    return mHandle;
}


std::string Db::Filename()
{
    return mDbName + ".Db";
}
void Db::SetName(std::string Name_)
{
    mDbName = std::move(Name_);
}

SchemaItem::~SchemaItem()
{
    mName.Clear();
}

SchemaItem::SchemaItem(Object *Parent_) : Object(Parent_){}


Schema::~Schema()
{
}

Expect<Schema *> Schema::Load(std::string DbName_)
{
    Db Temp = Db();
    Temp.SetName(DbName_);
    Db::Return R = Temp.Open();
    if(!R)
        return R();
    
    
    return nullptr;
}

Table::~Table()
{

}

Query::~Query()
{
    mText.Clear();
}

Query& Query::operator<<(std::string Obj_)
{
    String Str_;
    Str_ << "\"" << Obj_ << "\"";
    mStack.push(Str_());
    return *this;
}

Query& Query::Select(Query& Q_)
{
    mStack.push("SELECT");
    return *this;
}

Query& Query::Delete(Query& Q_)
{
    mStack.push("DELETE");
    return *this;

}

Query& Query::Update(Query& Q_)
{
    mStack.push("UPDATE");
    return *this;

}

Query& Query::Insert(Query& Q_)
{
    mStack.push("UPDATE");
    return *this;
}
std::string Query::Text()
{
    while(!mStack.empty())
    {
        mText << " " << mStack.top();
        mStack.pop();
    }
    return mText();
}

QueryItem::QueryItem(std::string ItemName_)
{
}

QueryItem::~QueryItem()
{
}

Field::~Field()
{
}

}