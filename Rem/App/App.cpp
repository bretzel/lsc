//
// Created by lsc on 20-05-18.
//

#include "App.h"



auto main(int arc, char**argv) -> int
{
    Lsc::App mApp;
    mApp();
    Lsc::Rem::Clear([](Lsc::Rem& R) {
       std::cout <<  R() << '\n';
    });
    return 0;
}


namespace Lsc
{


App::~App()
{
    mString.Clear();
}



Return App::operator()()
{
    //...
    mString = "Hello, And welcome to the Lsc World!\n";
    std::cout << mString();
    LscObject();
    CreateDb();
    Query();
    //Log();
    return Rem::Int::Ok;
}


//Return App::Log()
//{
//
//    AppBook::Config() = {
//        "Lsc::Rem",     // Title
//        "",     // Filename (path)
//        AppBook::Mode::Ansi,      // Mode
//        "Passwd",     // Db Passwd.  ?? sqlite3 ?? duh!
//    };
//    AppBook::Init();
//    AppBook::Log& mLog = AppBook::Begin(AppBook::Debug);
//    mLog << "Testing debug log ..." << TextCtl::Eol;
//    mLog << "Second log entry [";
//    mLog << "third entry on the same line ?]" << TextCtl::Eol;
//    mLog << "Fourth entry..." << TextCtl::Eol;
//    mLog << "Ok, On met AppBook sur la glace... Il faut continuer à travailler sur Lsc::Object!";
//    mLog.End();
//
//
//    AppBook::End([](const std::string& Txt) {
//       std::cout << Txt << '\n';
//    });
//
//    return ( Rem::Push()  << Rem::Int::Implement << " : Not there yet." );
//}
//

Return App::LscObject()
{
    Object Obj;
    
    return Rem::Int::Ok;
}


Return App::CreateDb()
{
    Db::Db Db_ = Db::Db();
    Db_.SetName("Rem");
    Db::Db::Return Handle = Db_.Create();
    if(Handle)
    {
        Rem::Success() << " SQLite3 Database file" << Db_.Filename() << " Created";
        return Handle();
    }
    
    return Rem::Int::Ok;
}

Return App::Query()
{
    Db::Query Q;
    
    Q.Select(
        Q.Insert(
            Q.Delete(Q << "Start")
        )
    );
    
    Rem::Debug() << Q.Text();
    return Rem::Int::Ok;
}

}
