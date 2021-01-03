//
// Created by lsc on 20-05-18.
//

#include "App.h"
#include "../../Scripture/App/App.h"

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
    return Rem::Int::Ok;
}


//Return App.App::Log()
//{
//
//    App::Config() = {
//        "Lsc::Rem",     // Title
//        "",     // Filename (path)
//        App::Mode::Ansi,      // Mode
//        "Passwd",     // Db Passwd.  ?? sqlite3 ?? duh!
//    };
//    App::Init();
//    App::Log& mLog = App::Begin(App::Debug);
//    mLog << "Testing debug log ..." << TextCtl::Eol;
//    mLog << "Second log entry [";
//    mLog << "third entry on the same line ?]" << TextCtl::Eol;
//    mLog << "Fourth entry..." << TextCtl::Eol;
//    mLog << "Ok, On met App sur la glace... Il faut continuer à travailler sur Lsc::Object!";
//    mLog.End();
//
//
//    App::End([](const std::string& Txt) {
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

}
