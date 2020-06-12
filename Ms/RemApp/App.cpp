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
    /// <summary>
    /// @todo TEST Shared PTR!!!
    /// </summary>
    /// <returns></returns>
    Rem::Clear([](Rem& R) {
        std::cout << R() << '\n';
        });
    return Rem::Int::Ok;
}



Return App::LscObject()
{
    Object* Obj = new Object;
    Object* C =  new Object(Obj);
    
    delete Obj;
    delete C;
    return Rem::Int::Ok;
}


}