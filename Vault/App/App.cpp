//
// Created by lsc on 20-05-18.
//

#include "App.h"
#include <Lsc/Vault/Data/Row.h>
#include <Lsc/Vault/Vault.h>
#include <Lsc/Vault/Model/Entity.h>

auto main(int arc, char**argv) -> int
{
    Lsc::AppBook mApp;
    mApp();
    Lsc::Rem::Clear([](Lsc::Rem& R) {
       std::cout << R() << '\n';
    });
    return 0;
}


namespace Lsc
{

AppBook::~AppBook()
{
    mString.Clear();
}

Return AppBook::operator()()
{
    //...
    Vault::Vault Vault("lab");
    Vault.Open();
    Vault::Entity E = Vault::Entity("User", &Vault);
    
    try{
        E += "User:UserName,A,Name, Mode:Name,Begin,End"; // Expect crash or ....
        std::cout << "\n--------------------------------------------------------------------\n";
        return Rem::Int::Ok;
    }
    catch(Rem& R)
    {
        return R;
    }
}


// if(Expect<std::string&> R; R = Row["Username"]) *R = "lussier.serge";

Expect<Vault::Field> AppBook::Field()
{
    using Vault::Field;
    Field F = {"ID", Vault::Field::Type::INTEGER};
    F.SetAttributes(Field::PKAUTO);
    
    return F;
}
Return AppBook::Row()
{
    Vault::Vault Vault("lab");
    if(Return R; !( R= Vault.Open()))
        return R();
     
    // We create Entity's In the Open Databse phase. Shall I do callbacks ? - no! Because Entities are made from already existing tables and from NEW
    // Tabeless Fields. So they are created manually, systematically:
    
    return Rem::Int::Ok;
}

} // namespace [Lsc::]Type
