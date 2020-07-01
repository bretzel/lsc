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
    Vault::Vault Vault("lab");
    
    mString = "Hello, And welcome to the Lsc::Vault Tests!:\n--------------------------------------------------------------------\n";
    std::cout << mString();
    
    Vault.Open();
    
    Expect<Vault::Field> F = Field();
    if(!F)
        std::cout << F()() << "\n";
    else
    {
        Rem::Success() << "Field:[" << (*F).Serialize()() << "]";
    }
    
    std::cout << "\n--------------------------------------------------------------------\n";
    return Rem::Int::Ok;
}

Expect<Vault::Field> App::Field()
{
    using Vault::Field;
    Field F = {"ID", Vault::Field::Type::INTEGER};
    F.SetAttributes(Field::PKAUTO);
    
    return F;
}


} // namespace [Lsc::]Type
