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
    Object::Shared Obj = Object::Make(nullptr);
    Object::Shared C = Object::Make(Obj);
    Rem::Debug() << "Object::Shared Obj.use_count() = " << Obj.use_count();
    Rem::Debug() << "Object::Shared Child.use_count() = " << C.use_count();
    //...
    Obj->Clear();
    return Rem::Int::Ok;
}


}