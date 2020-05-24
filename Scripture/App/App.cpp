//
// Created by lsc on 20-05-18.
//

#include "App.h"


#include <Lsc/Scripture/Lexer.h>


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
    mString = "Hello, And welcome to the Lsc::Scripture Tests!:\n--------------------------------------------------------------------\n";
    std::cout << mString();
    
    (void) App::Type("Binary/Operator/TypeId/Number/Float");
    (void) Tokens("<>;");
    (void) LexerScan("Abcdere = 0xbcda >< 0xabcd + -4.012ac(;");
    std::cout << "\n--------------------------------------------------------------------\n";
    return Rem::Int::Ok;
}



Return App::Type(std::string Txt_)
{
    Type::T T;
    T << Txt_;
    String Str_  = "[%08b]";
    Str_ << T;
    std::cout << "App::Type( [%08b]" << Txt_ << ") :" <<  Str_() << '\n';
    Str_.Clear();
    std::string Txt;
    Txt.clear();
    Txt << T;
    std::cout   << Txt << '\n';
    
    return Rem::Int::Ok;
}



Return App::Tokens(std::string Txt_)
{
    TokenData Token_ = TokenData::Scan(Txt_.c_str()); // => sin(+4) / 2a;
    
    std::cout <<
        "App::TokenScan(" << Txt_ << "):\n" <<
        Token_.Details() << '\n';
        
    TokenData::Collection Tokens(1);
    Token_ = Tokens.back();
    std::cout <<
        "App::TokenScan(From the head of an empty Tokens stream):\n" <<
        Token_.Details() << '\n';
    return Rem::Int::Ok;
}



Return App::LexerScan(std::string Txt_)
{
    std::cout << "App::LexerScan(" << Txt_ << "):\n";
    Lexer Lex;
    TokenData::Collection Tokens;
    Lex.Config() =
    {
        .Source = Txt_.c_str(),
        .Tokens = &Tokens
    };
    auto R = Lex();
    
    Lex.Flush([](TokenData Token_) {
       Rem::Debug() << Token_.Details();
    });
    return Rem::Int::Implement;
}

} // namespace [Lsc::]Type
