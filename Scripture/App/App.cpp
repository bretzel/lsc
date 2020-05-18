//
// Created by lsc on 20-05-18.
//

#include "App.h"


#include <Lsc/Scripture/TokenData.h>


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
    mString = "Hello, And welcome to the Lsc::Scripture Tests!:\n--------------------------------------------------------------------\n";
    std::cout << mString();
    
    (void) App::Type();
    (void) Tokens();
    
    std::cout << "\n--------------------------------------------------------------------\n";
    return Rem::Int::Ok;
}



Return App::Type()
{
    Type::T T;
    std::string Txt = "Binary/Operator/TypeId/Number/Real";
    T << Txt;
    String Str_  = "[%08b]\n";
    Str_ << T;
    std::cout << __PRETTY_FUNCTION__  << Str_();
    Str_.Clear();
    Txt.clear();
    Txt << T;
    std::cout << __PRETTY_FUNCTION__  << Txt << '\n';
    //...
    
    return Rem::Int::Ok;
}
Return App::Tokens()
{
    TokenData Token_ = TokenData::Scan("sin(4/2a);");
    
    std::cout <<
        __PRETTY_FUNCTION__ << ":\n" <<
        Token_.Details();
    
    return Rem::Int::Ok;
}

} // namespace [Lsc::]Type
