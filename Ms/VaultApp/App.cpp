//
// Created by lsc on 20-05-18.
//

#include "App.h"



#include <Lsc/Vault/Vault.h>

auto main(int arc, char**argv) -> int
{
    Lsc::App mApp;
    mApp();
    Lsc::Rem::Clear([](Lsc::Rem& R) {
       std::cout << R() << '\n';
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
    Vault::Vault Vault("test");
    
    mString = "Hello, And welcome to the Lsc::Vault Tests!:\n--------------------------------------------------------------------\n";
    std::cout << mString();
    Vault.Create();
    std::cout << "\n--------------------------------------------------------------------\n";
    return Rem::Int::Ok;
}



} // namespace [Lsc::]Type