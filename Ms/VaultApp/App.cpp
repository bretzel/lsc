//
// Created by lsc on 20-05-18.
//

#include "App.h"
#include <Lsc/Vault/Data/Row.h>
#include <Lsc/Vault/Vault.h>
#include <Lsc/Vault/Model/Entity.h>

auto main(int arc, char **argv)->int
{
    Lsc::VaultApp mApp;
    mApp();
    Lsc::Rem::Clear([](Lsc::Rem &R) {
        std::cout << R() << '\n';
    });
    return 0;
}

namespace Lsc
{

VaultApp::~VaultApp()
{
    mString.Clear();
}

Return VaultApp::operator()()
{
    //...
    mString = "Hello, Testing Vault:\n------------------------------------------------\n";
    std::cout << mString();
    
    Rem::Message() << " First thing first: Test the Field: ";
    
    try
    {
        Field();
        Rem::Message() << " Now the Entity:";
        Vault::Vault Vault("lab");
        Vault.Open();
        Vault::Entity E = Vault::Entity("User", &Vault);
        
        E += "User:UserName,A,Name, Mode:Name,Begin,End";
        std::cout << "\n--------------------------------------------------------------------\n";
        return Rem::Int::Ok;
    }
    catch(Rem &R)
    {
        return R;
    }
}


// if(Expect<std::string&> R; R = Row["Username"]) *R = "lussier.serge";

Return VaultApp::Field()
{
    using Vault::Field;
    Field F = {"ParentID", Vault::Field::Type::INTEGER};
    F.SetReference("Parent", "ID");
    String Str = F.Serialize();
    
    Rem::Debug() << __PRETTY_FUNCTION__ << ": [" << Str << "] ...";
    return Rem::Int::Ok;
}

/*!
 * @brief Pour l'instant c'est juste pour tester si ça compile :) ...
 * @return
 */
Return VaultApp::Row()
{
    Vault::Vault Vault("lab");
    if(Return    R; !(R = Vault.Open()))
        return R();
    
    // We create Entity's In the Open Databse phase. Shall I do callbacks ? - no! Because Entities are made from already existing tables and from NEW
    // Tabeless Fields. So they are created manually, systematically:
    
    return Rem::Int::Ok;
}

} // namespace [Lsc::]Type
