//
// Created by bretzel on 20-04-18.
//

//#ifndef TEXT_REM_H
//#define TEXT_REM_H

#pragma once
//#pragma clang diagnostic push
//#pragma ide diagnostic ignored "google-explicit-constructor"

#include <Lsc/Rem/String.h>
#include <stack>
//#include <functional> // Already loaded from String.h
#include <any>  // Used by the Expect template class.
#include <Lsc/Rem/RemColor.h>

namespace Lsc
{

class REM_LIB Rem
{
    
    std::string        mText;
    String::Collection mVerticalData;
    
public:
    
    enum class Int : uint8_t
    {
        Ok = 0,
        Fail,
        Eof,
        Eos,
        Eot,
        UnExpected,
        Expected,
        Null,
        Bad,
        Good,
        Unknown,
        Known,
        Unset,
        UnInit,
        Implement,
        Accepted,
        Rejected,
        Unterminated
    };
    
    enum class Type : uint8_t
    {
        None = 0,
        Info,
        Internal,
        Error,
        SyntaxError,
        Warning,
        Fatal,
        Success,
        Message,
        Return,
        Value,
        State,
        Debug,
        Event,
        System,
        Application,
        Network,
        Exception
        
    };
private:
    
    Type mType = Rem::Type::None;
    static Type sType;
    Int  mCode = Rem::Int::Unknown;
    
    using Collection = std::vector<Rem>;
    static Collection _Array;
    
    static Rem _Null;
    
public:
    enum Prefix{
        Clr,
        FuncName,
        FullName,
        HoroData
    };
    Rem() = default;
    ~Rem();
    
    Rem(const Rem &R) = default;
    Rem(Rem &&R) noexcept;
    
    Rem &operator=(const Rem &R) = default;
    Rem &operator=(Rem &&R) noexcept;
    
    std::string Text();
    std::string operator()();
    
    explicit operator bool() const;
    
    static Rem &Push();
    static Rem &Pop();
    
    static Rem &Debug();
    
    static Rem &Info();
    static Rem &Internal();
    static Rem &Error();
    static Rem &SyntaxError();
    static Rem &Warning();
    static Rem &Fatal();
    static Rem &Success();
    static Rem &Message();
    static Rem &Return();
    static Rem &Value();
    static Rem &State();
    static Rem &Event();
    static Rem &System();
    static Rem &Application();
    static Rem &Network();
    static Rem &Exception();
    
    static Rem &Null();
    
/*    static*/ std::string ToStr(Rem::Type T);
/*    static*/ std::string ToStr(Rem::Int C);
    
    Rem &operator<<(Rem::Type T);
    Rem &operator<<(Rem::Int C);
    Rem &operator<<(Ansi::Color C);
    Rem &operator<<(Rem::Prefix P);
    
    template<typename T> Rem &operator<<(const T &Arg)
    {
        String Str = mText;
        Str << Arg;
        mVerticalData.push_back(Str());
        return *this;
    }
    
    static std::size_t Clear(const std::function<void(Rem &)>& LambdaFN = nullptr);
    
private:
    Rem::Prefix mPrefix=Rem::Clr;
};

template<typename T = Rem::Int> class Expect
{
    std::any mVal;
    bool     mF = false;

public:
    Expect() = default;
    
    Expect(Rem &R)
    {
        mVal = R;
        mF   = false;
    }
    
    Expect(const T &V)
    {
        mVal = V; // Must remove const ?
        mF   = true;
    }
    
    Expect(Expect &&E) noexcept
    {
        mVal = std::move(E.mVal);
        mF   = E.mF;
    }
    
    Expect(const Expect &E)
    {
        mF   = E.mF;
        mVal = E.mVal;
    }
    
    Expect &operator=(Rem &R)
    {
        mVal.reset();
        mF   = false;
        mVal = R;
        return *this;
    }
    
    Expect &operator=(Expect &&E) noexcept
    {
        mVal.reset();
        mVal = std::move(E.mVal);
        mF   = std::move(E.mF);
        
        return *this;
    }
    
    Expect &operator=(const Expect &E)
    {
        if(&E == this)
            return *this;
        mVal.reset();
        mVal = E.mVal;
        mF   = E.mF;
        return *this;
    }
    
    Expect &operator=(const T &V)
    {
        //        /if(mF)
        mVal.reset();
        mVal = V;
        mF   = true;
        return *this;
    }
    
    explicit operator bool() const
    { return mF; }
    
    Rem &operator()()
    {
        if(mF)
            return Rem::Null();
        return std::any_cast<Rem &>(mVal);
    }
    
    auto &operator*()
    {
        if(!mF)
        {
            Rem::Push() << Rem::Type::Error << ": " << __PRETTY_FUNCTION__ << " - Expected value was not returned. >>\n >> " << std::any_cast<Rem>(mVal).operator()();
            
            mVal.reset();
            mVal = T(); // Yep... T must be default-constructible...
        }
        return std::any_cast<T &>(mVal);
    }
    
    //    auto &operator()()
    //    {
    //        if(!f)
    //        {
    //            _a = notification::push(), "expect: expected value on a false state.";
    //            return std::any_cast<notification &>(_a);
    //        }
    //        return std::any_cast<T &>(_a);
    //    }
    
    void Reset()
    {
        mVal.reset();
        mF = false;
    }
    
    ~Expect()
    {
        //Reset();
    }
    /*!
        @brief  to be verified.
    */
    std::string Text(std::function<std::string(const T &)> textify_ = nullptr)
    {
        if(*this)
        {
            String      Str;
            std::string rr;
            T           &v = *(*this);
            if(textify_)
                return textify_(v);
            else
            {
                Str << __PRETTY_FUNCTION__;
                rr  = Str.ExtractSurrounded("T =", ";");
                Str = " No method given, for textifying this instance of Expect<T>:[";
                Str << rr << ']';
            }
            return Str();
        }
        return std::any_cast<Rem &>(mVal)();
    }
};

using Return = Expect<>;
}

//#endif //TEXT_REM_H

//#pragma clang diagnostic pop