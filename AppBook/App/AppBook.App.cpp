//
// Created by lsc on 20-07-07.
//

#include "./AppBook.App.h"
#include <Lsc/Vault/Vault.h>
#include <Lsc/Vault/Model/Table.h>

auto main(int argc, char **argv)->int
{
    
    using Lsc::Rem;
    try
    {
        if(argc > 1)
        {
            Lsc::String Str = argv[1];
            if((Str == "--init") || (Str == "-i"))
            {
                Lsc::Return R = Lsc::AppBookApp::InitAndCreateDatabase();
            }
            else
                throw Rem::Exception() << __PRETTY_FUNCTION__ << ": Invalid argument '" << Str << '\'';
        }
        Rem::Application() << __PRETTY_FUNCTION__ << ": Nothing to do as of this version...";
    }
    catch(Rem &R)
    { ;
    }
    catch(std::exception &E)
    {
        Rem::Exception() << __PRETTY_FUNCTION__ << ':' << E.what();
    }
    
    Rem::Clear([](Rem &R) {
        std::cout << R() << "\n";
    });
    return 0;
}

namespace Lsc
{

Return AppBookApp::operator()()
{
    return Lsc::Return();
}

Return AppBookApp::InitAndCreateDatabase()
{
    //throw Rem::Internal() << __PRETTY_FUNCTION__ << ": Not yet implemented... Doh!";
    Vault::Vault Vault;
    Vault::Table T = {"Color", &Vault};
    T << Vault::Field {&T, "ID", Vault::Field::Type::INTEGER, Vault::Field::PKAUTO}
    << Vault::Field {&T, "Name", Vault::Field::Type::TEXT, Vault::Field::Unique};
    
    (*T["ID"])->SetAttributes(Vault::Field::PKAUTO);
    
    return Rem::Debug() << __PRETTY_FUNCTION__ <<": " << T.Serialize()();
}

}
