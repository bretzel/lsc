//
// Created by lsc on 20-07-07.
//

#include "./AppBook.App.h"
#include <Lsc/Vault/Vault.h>
#include <Lsc/Vault/Model/Entity.h>
#include <Lsc/Vault/Data/Query.h>

auto main(int argc, char **argv)->int
{
    
    using Lsc::Rem;
    try
    {
        Lsc::String::Collection Args;
        for(int                 a = 0; a < argc; a++)
            Args.push_back(argv[a]);
        
        Lsc::AppBookApp App;
        App(Args);
        
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

Return AppBookApp::operator()(const String::Collection &Args_)
{
    if(Args_.size() != 3)
    {
        throw Rem::Exception() << __PRETTY_FUNCTION__ << ": This version strictly expects 2 arguments.";
    }
    if(Args_[1] == "--init")
        mDbName = Args_[2];
    Rem::Debug() << __PRETTY_FUNCTION__ << ": DbName: '" << mDbName << "' :";
    //throw Rem::Internal() << " -- STOP. Must Implement a Vault::Query.";
    return InitAndCreateDatabase();
}

Return AppBookApp::InitAndCreateDatabase()
{
    //throw Rem::Internal() << __PRETTY_FUNCTION__ << ": Not yet implemented... Doh!";
    Vault::Vault Vault(mDbName());
    Vault.Create(); // Throws on error.
    
//    Vault::Table TElement = {"Element", &Vault};
//    TElement
//    << Vault::Field {&TElement, "ID", Vault::Field::Type::INTEGER, Vault::Field::PKAUTO}
//    << Vault::Field {&TElement, "Name", Vault::Field::Type::TEXT, Vault::Field::Unique}
//    << Vault::Field {&TElement, "TagName", Vault::Field::Type::TEXT}
//    << Vault::Field {&TElement, "Prefix", Vault::Field::Type::TEXT}
//    << Vault::Field {&TElement, "Suffix", Vault::Field::Type::TEXT};
//
//    (*TElement["ID"])->SetAttributes(Vault::Field::PKAUTO);
//
//    //Vault::Table
//
    Vault::Entity E = {"Element", &Vault};
    E + Vault::Field {E.Model(), "ID", Vault::Field::Type::INTEGER, Vault::Field::PKAUTO} +
    Vault::Field {E.Model(), "Name", Vault::Field::Type::TEXT, Vault::Field::Unique} +
    Vault::Field {E.Model(), "TagName", Vault::Field::Type::TEXT} +
    Vault::Field {E.Model(), "Prefix", Vault::Field::Type::TEXT} +
    Vault::Field {E.Model(), "Suffix", Vault::Field::Type::TEXT};
    
    Vault::Query Q = Vault::Query {&Vault};
    Q.SQL(E.GenerateSchema());
    Vault.ExecuteQuery(Q);
    
    return Rem::Int::Ok;
}

}
