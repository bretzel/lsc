//
// Created by lsc on 20-05-18.
//

#include "App.h"


#include <Lsc/Scripture/Lexer.h>
#include <Lsc/Scripture/Interpreter/Alu.h>
#include <Lsc/Scripture/Interpreter/Xio.h>
#include <Lsc/Scripture/Interpreter/Compiler/Grammar.h>

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
    //(void) Tokens("<>;");
    (void) LexerScan(
R"(
if A
{
    Abcdere = 0xb09AFcfdaghj >< 0xabcd + -4.012ac * 4ac(x^2+y+b);
}
else
{
   return .0001;
})"
);
    (void) ExIOCanUseShared();
    (void) TeaGrammar();
    std::cout << "\n---------------------------------------------------------------------\n";
    return Rem::Int::Ok;
}

Return App::Type(std::string Txt_)
{
    Type::T T;
    Type::FromStr( Txt_);
    String Str_  = "[%08b]";
    Str_ << T;
    std::cout << "App::Type( [%08b]" << Txt_ << ") :" <<  Str_() << '\n';
    Str_.Clear();
    std::string Txt;
    Txt.clear();
    Type::FromStr(Txt);
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
    
    Lex.Flush([](TokenData Token_) { // On s'en foutre que ce soit une (deep) copie ou une reference...
       Rem::Debug() << Token_.Details();
    });
    return Rem::Int::Implement;
}



Return App::ArithmeticLogicalUnit()
{
    Rem::Debug() << __PRETTY_FUNCTION__  << ":\n";
    Alu A = 1.1f;
    Alu B = .0f;
    Alu C = .00345f;
    Rem::Debug() << "A=" << A() << " => [" << Type::Name(A.TypeOf()) << "]";
    Rem::Debug() << "B=" << B() << " => [" << Type::Name(B.TypeOf()) << "]";
    Rem::Debug() << "A / B:"  << " => " << (A/B)() ;
    
    Rem::Debug() << "C=" << C.Number<double>() << " => [" << Type::Name(C.TypeOf()) << "]";
    Rem::Debug() << "A / C: => " << (A/C)() << "[" << Type::Name(C.TypeOf()) << "]";
    return Rem::Int::Good;
}

Return App::TeaGrammar()
{
    Grammar G;
    G.Build();
    //G.Dump();
    
    return Rem::Int::Accepted;
}


Return App::ExIOCanUseShared()
{
   Xio::Shared Xio = Xio::New(nullptr, nullptr, nullptr);
    
    return Lsc::Return();
}


} // namespace [Lsc::]Type
