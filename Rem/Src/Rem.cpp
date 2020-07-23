//
// Created by bretzel on 20-04-18.
//

#include <Lsc/Rem/Rem.h>
#include <map>

using namespace Lsc;



Rem::Collection Rem::_Array;

Rem  Rem::_Null;
Rem::Type Rem::sType=Rem::Type::None;

Rem::Rem(Rem &&R) noexcept
{
    mText         = std::move(R.mText);
    mVerticalData = std::move(R.mVerticalData);
    mType         = R.mType;
    mCode         = R.mCode;
}

Rem &Rem::operator=(Rem &&R) noexcept
{
    mText         = std::move(R.mText);
    mVerticalData = std::move(R.mVerticalData);
    mType         = R.mType;
    mCode         = R.mCode;
    
    return *this;
}

std::string Rem::Text()
{
    return mText;
}

std::string Rem::operator()()
{
    mText.clear();
    if(mVerticalData.empty())
        return "empty"; // ?
    for(auto &R : mVerticalData)
        mText += R;
    return mText;
}

Rem::operator bool() const
{
    return mType != Type::None;
}

Rem &Rem::Push()
{
    Rem::_Array.push_back(Rem());
    return Rem::_Array.back();
}

Rem &Rem::Pop()
{
    if(Rem::_Array.empty())
        return Rem::_Null;
    
    Rem &R = Rem::_Array.back();
    Rem::_Array.erase(Rem::_Array.begin());
    return R;
}

Rem &Rem::Null()
{
    return Rem::_Null;
}

std::size_t Rem::Clear(std::function<void(Rem &)> LambdaFN)
{
    std::size_t Sz = Rem::_Array.size();
    if(!Sz)
        std::cout << " No Rem to clear.\n";
    for(auto &R : Rem::_Array)
    {
        if(LambdaFN)
            LambdaFN(R);
    }
    Rem::_Array.clear();
    return Sz;
}


/*!
 * @brief ...
 * @param T
 * @return
 */
std::string Rem::ToStr(Rem::Type T)
{
    std::map<Rem::Type, std::string> _ = {{Rem::Type::None,        "\033[0mNone"},
                                          {Rem::Type::Info,        "\033[38;5;12m⚫ Info\033[0m"},
                                          {Rem::Type::Internal,    "\033[38;5;247m⚑ Internal\033[0m"},
                                          {Rem::Type::Error,       "\033[38;5;124m✘ Error\033[0m"},
                                          {Rem::Type::SyntaxError, "\033[38;5;9m☠ Syntax Error\033[0m"},
                                          {Rem::Type::Warning,     "\033[38;5;106m⚠ Warning\033[0m"},
                                          {Rem::Type::Fatal,       "\033[38;5;12m☠ Fatal Error\033[0m"},
                                          {Rem::Type::Success,     "\033[38;5;12m✔ Success\033[0m"},
                                          {Rem::Type::Message,     "\033[38;5;70m@ Message\033[0m"},
                                          {Rem::Type::Return,      "\033[38;5;12m⏎ Return\033[0m"},
                                          {Rem::Type::Value,       "\033[38;5;12m  Value\033[0m"},
                                          {Rem::Type::State,       "\033[38;5;12m  Status\033[0m"},
                                          {Rem::Type::Debug,       "\033[38;5;130m➤ Debug\033[0m"},
                                          {Rem::Type::Event,       "\033[38;5;74m  Event\033[0m"},
                                          {Rem::Type::System,      "\033[38;5;12m  System\033[0m"},
                                          {Rem::Type::Application, "\033[38;5;12m⚫ Application\033[0m"},
                                          {Rem::Type::Network,     "\033[38;5;12m  Network\033[0m"},
                                          {Rem::Type::Exception,   "\033[38;5;57m☠ Exception\033[0m"}
        
    };
    
    String Str;
    switch(mPrefix)
    {
        case Rem::Clr: break;
        default:break;
    }
    
    Str += _[T];
    return Str();
}

std::string Rem::ToStr(Rem::Int C)
{
    std::map<Rem::Int, std::string> _ = {{Rem::Int::Ok,           "Ok"},
                                         {Rem::Int::Fail,         "Fail"},
                                         {Rem::Int::Eof,          "Eof"},
                                         {Rem::Int::Eos,          "Eos"},
                                         {Rem::Int::Eot,          "Eot"},
                                         {Rem::Int::UnExpected,   "UnExpected"},
                                         {Rem::Int::Expected,     "Expected"},
                                         {Rem::Int::Null,         "Null"},
                                         {Rem::Int::Bad,          "Bad"},
                                         {Rem::Int::Good,         "Good"},
                                         {Rem::Int::Unknown,      "Unknown"},
                                         {Rem::Int::Known,        "Known"},
                                         {Rem::Int::Unset,        "Unset"},
                                         {Rem::Int::UnInit,       "UnInit"},
                                         {Rem::Int::Implement,    "Not Implemented"},
                                         {Rem::Int::Accepted,     "Accepted"},
                                         {Rem::Int::Rejected,     "Rejected"},
                                         {Rem::Int::Unterminated, "Unterminated"},};
    
    return _[C];
}

Rem &Rem::operator<<(Rem::Type T)
{
    mVerticalData.push_back(ToStr(T));
    return *this;
}

Rem &Rem::operator<<(Rem::Int C)
{
    mVerticalData.push_back(ToStr(C));
    return *this;
}
Rem::~Rem()
{
    mVerticalData.clear();
    mText.clear();
}

Rem &Rem::Debug()
{
       Rem R;
    if(Rem::sType != Rem::Type::Debug)
    {
        R << Rem::Type::Debug << ": ";
        Rem::sType = Rem::Type::Debug;
    }
    else
    {
        R << "          ";
    }
    
    Rem::_Array.push_back(R);
    return Rem::_Array.back();
}

Rem &Rem::Info()
{
       Rem R;
    if(Rem::sType != Rem::Type::Info)
    {
        R << Rem::Type::Info << ": ";
        Rem::sType = Rem::Type::Info;
    }
    else
    {
        R << "          ";
    }
    
    Rem::_Array.push_back(R);
    return Rem::_Array.back();
}

Rem &Rem::Internal()
{
       Rem R;
    if(Rem::sType != Rem::Type::Internal)
    {
        R << Rem::Type::Internal << ": ";
        Rem::sType = Rem::Type::Internal;
    }
    else
    {
        R << "          ";
    }
    
    Rem::_Array.push_back(R);
    return Rem::_Array.back();
}

Rem &Rem::Error()
{
       Rem R;
    if(Rem::sType != Rem::Type::Error)
    {
        R << Rem::Type::Error << ": ";
        Rem::sType = Rem::Type::Error;
    }
    else
    {
        R << "          ";
    }
    
    Rem::_Array.push_back(R);
    return Rem::_Array.back();
}

Rem &Rem::SyntaxError()
{
    Rem R;
    if(Rem::sType != Rem::Type::SyntaxError)
    {
        R << Rem::Type::SyntaxError << ": ";
        Rem::sType = Rem::Type::SyntaxError;
    }
    else
    {
        R << "          ";
    }
    
    Rem::_Array.push_back(R);
    return Rem::_Array.back();
}

Rem &Rem::Warning()
{
   Rem R;
    if(Rem::sType != Rem::Type::Warning)
    {
        R << Rem::Type::Warning << ": ";
        Rem::sType = Rem::Type::Warning;
    }
    else
    {
        R << "          ";
    }
    
    Rem::_Array.push_back(R);
    return Rem::_Array.back();
}

Rem &Rem::Fatal()
{
    Rem R;
    R << Rem::Type::Fatal << ": ";
    Rem::_Array.push_back(R);
    return Rem::_Array.back();
}

Rem &Rem::Success()
{
    Rem R;
    R << Rem::Type::Success << ": ";
    Rem::_Array.push_back(R);
    return Rem::_Array.back();
}

Rem &Rem::Message()
{
    Rem R;
    R << Rem::Type::Message << ": ";
    Rem::_Array.push_back(R);
    return Rem::_Array.back();
}

Rem &Rem::Return()
{
    Rem R;
    R << Rem::Type::Return << ": ";
    Rem::_Array.push_back(R);
    return Rem::_Array.back();
}

Rem &Rem::Value()
{
    Rem R;
    R << Rem::Type::Value << ": ";
    Rem::_Array.push_back(R);
    return Rem::_Array.back();
}

Rem &Rem::State()
{
    Rem R;
    R << Rem::Type::State << ": ";
    Rem::_Array.push_back(R);
    return Rem::_Array.back();
}

Rem &Rem::Event()
{
    Rem R;
    R << Rem::Type::Event << ": ";
    Rem::_Array.push_back(R);
    return Rem::_Array.back();
}

Rem &Rem::System()
{
    Rem R;
    R << Rem::Type::System << ": ";
    Rem::_Array.push_back(R);
    return Rem::_Array.back();
}

Rem &Rem::Application()
{
    Rem R;
    R << Rem::Type::Application << ": ";
    Rem::_Array.push_back(R);
    return Rem::_Array.back();
}

Rem &Rem::Network()
{
    Rem R;
    R << Rem::Type::Network << ": ";
    Rem::_Array.push_back(R);
    return Rem::_Array.back();
}
Rem &Rem::Exception()
{
    Rem R;
    if(Rem::sType != Rem::Type::Exception)
    {
        R << Rem::Type::Exception << ": ";
        Rem::sType = Rem::Type::Exception;
    }
    else
    {
        R << "          ";
    }
    
    Rem::_Array.push_back(R);
    return Rem::_Array.back();
}

Rem &Rem::operator<<(Ansi::Color C)
{
    Rem R;
    R << "\033[38;5;" << static_cast<int>(C) << 'm';
    Rem::_Array.push_back(R);
    return *this;
}

Rem &Rem::operator<<(Rem::Prefix P)
{
    mPrefix = P;
    return *this;
}

