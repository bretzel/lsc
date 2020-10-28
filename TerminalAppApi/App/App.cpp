//
// Created by lsc on 20-05-18.
//

#include "App.h"



auto main(int arc, char**argv) -> int
{
    Lsc::Terminal mApp;
    mApp();
    Lsc::Rem::Clear([](Lsc::Rem& R) {
       std::cout <<  R() << '\n';
    });
    return 0;
}


namespace Lsc
{


Terminal::~Terminal()
{

}



Return Terminal::operator()()
{
    //...
    TAA::Rect R = {0,0,150,150};
    Rem::Debug("TerminalAppApi Tests") << "Rect: " << R.ToString();
    _T = new TAA::Terminal ;
    _T->Init();
    getch();
    delete _T;
    return Rem::Int::Ok;
}


//Return Terminal.App::Log()
//{
//
//    Terminal::Config() = {
//        "Lsc::Rem",     // Title
//        "",     // Filename (path)
//        Terminal::Mode::Ansi,      // Mode
//        "Passwd",     // Db Passwd.  ?? sqlite3 ?? duh!
//    };
//    Terminal::Init();
//    Terminal::Log& mLog = Terminal::Begin(Terminal::Debug);
//    mLog << "Testing debug log ..." << TextCtl::Eol;
//    mLog << "Second log entry [";
//    mLog << "third entry on the same line ?]" << TextCtl::Eol;
//    mLog << "Fourth entry..." << TextCtl::Eol;
//    mLog << "Ok, On met Terminal sur la glace... Il faut continuer à travailler sur Lsc::Object!";
//    mLog.End();
//
//
//    Terminal::End([](const std::string& Txt) {
//       std::cout << Txt << '\n';
//    });
//
//    return ( Rem::Push()  << Rem::Int::Implement << " : Not there yet." );
//}
//



}
