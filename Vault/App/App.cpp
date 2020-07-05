//
// Created by lsc on 20-05-18.
//

#include "App.h"
#include <Lsc/Vault/Data/Row.h>


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
    
    std::cout << "\n--------------------------------------------------------------------\n";
    return Rem::Int::Ok;
}


// if(Expect<std::string&> R; R = Row["Username"]) *R = "lussier.serge";

Expect<Vault::Field> App::Field()
{
    using Vault::Field;
    Field F = {"ID", Vault::Field::Type::INTEGER};
    F.SetAttributes(Field::PKAUTO);
    
    return F;
}
Return App::Row()
{
     Vault::Vault Vault("lab");
     if(Return R; !( R= Vault.Open()))
        return R();
     
     ;
    return Rem::Int::Ok;
}

} // namespace [Lsc::]Type
