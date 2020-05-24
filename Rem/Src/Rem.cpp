//
// Created by bretzel on 20-04-18.
//

#include <Lsc/Rem/Rem.h>
#include <map>

using namespace Lsc;

Rem::Collection Rem::_Array;

Rem  Rem::_Null;

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

std::string Rem::ToStr(Rem::Type T)
{
    
    std::map<Rem::Type, std::string> _ = {{Rem::Type::None,        "None"},
                                          {Rem::Type::Info,        "Info"},
                                          {Rem::Type::Internal,    "Internal"},
                                          {Rem::Type::Error,       "Error"},
                                          {Rem::Type::SyntaxError, "Syntax Error"},
                                          {Rem::Type::Warning,     "Warning"},
                                          {Rem::Type::Fatal,       "Fatal Error"},
                                          {Rem::Type::Success,     "Success"},
                                          {Rem::Type::Message,     "Message"},
                                          {Rem::Type::Return,      "Return"},
                                          {Rem::Type::Value,       "Value"},
                                          {Rem::Type::State,       "State"},
                                          {Rem::Type::Debug,       "Debug"},
                                          {Rem::Type::Event,       "Event"},
                                          {Rem::Type::System,      "System"},
                                          {Rem::Type::Application, "Application"},
                                          {Rem::Type::Network,     "Network"}
        
    };
    return "Rem::" + _[T];
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
    R << Rem::Type::Debug << ": ";
    Rem::_Array.push_back(R);
    return Rem::_Array.back();
}

Rem &Rem::Info()
{
    Rem R;
    R << Rem::Type::Info << ": ";
    Rem::_Array.push_back(R);
    return Rem::_Array.back();
}

Rem &Rem::Internal()
{
    Rem R;
    R << Rem::Type::Internal << ": ";
    Rem::_Array.push_back(R);
    return Rem::_Array.back();
}

Rem &Rem::Error()
{
    Rem R;
    R << Rem::Type::Error << ": ";
    Rem::_Array.push_back(R);
    return Rem::_Array.back();
}

Rem &Rem::SyntaxError()
{
    Rem R;
    R << Rem::Type::SyntaxError << ": ";
    Rem::_Array.push_back(R);
    return Rem::_Array.back();
}

Rem &Rem::Warning()
{
    Rem R;
    R << Rem::Type::Warning << ": ";
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

