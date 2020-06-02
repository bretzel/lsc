//
// Created by lsc on 20-05-18.
//

#include "App.h"



auto main(int arc, char**argv) -> int
{
    Lsc::App mApp;
    mApp();
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

    Rem::Clear([](Rem& R) {
        std::cout << R() << '\n';
        });
    return Rem::Int::Ok;
}



Return App::LscObject()
{
    Object Obj;
    
    return Rem::Int::Ok;
}


}