//
// Created by lsc on 20-05-28.
//

#include <Lsc/Scripture/Interpreter/Alu.h>
#include <Lsc/Rem/Rem.h>

namespace Lsc
{

std::string  SCRIPTURE_LIB Alu::mNil = "";

#define UCTor(Rhs_) { T |= Type::Number|Type::Leaf; R = (Rhs_);}
#define SCTor(Rhs_) { T |= Type::Number|Type::Sign|Type::Leaf; R = (Rhs_);}
#define _assign_u T |= Type::Number|Type::Leaf; R.reset(); R = (Rhs_);
#define _assign_s T |= Type::Number|Type::Sign|Type::Leaf; R.reset(); R = (Rhs_);

Alu::Alu(int8_t Rhs_) : T(Type::I8)
SCTor(Rhs_)
Alu::Alu(int16_t Rhs_) : T(Type::I16)
SCTor(Rhs_)
Alu::Alu(int32_t Rhs_) : T(Type::I32)
SCTor(Rhs_)
Alu::Alu(int64_t Rhs_) : T(Type::I64)
SCTor(Rhs_)
Alu::Alu(uint8_t Rhs_) : T(Type::U8)
UCTor(Rhs_)
Alu::Alu(uint16_t Rhs_) : T(Type::U16)
UCTor(Rhs_)
Alu::Alu(uint32_t Rhs_) : T(Type::U32)
UCTor(Rhs_)
Alu::Alu(uint64_t Rhs_) : T(Type::U64)
UCTor(Rhs_)
Alu::Alu(bool Rhs_) : T(Type::Boolean)
SCTor(Rhs_)

#define cast(Rhs_)\
(Rhs_).T & Type::Boolean  ? std::any_cast<bool>((Rhs_).R) != false :\
(Rhs_).T & Type::I8       ? std::any_cast<int8_t>  ((Rhs_).R):\
(Rhs_).T & Type::I16      ? std::any_cast<int16_t> ((Rhs_).R):\
(Rhs_).T & Type::I32      ? std::any_cast<int32_t> ((Rhs_).R):\
(Rhs_).T & Type::I64      ? std::any_cast<int64_t> ((Rhs_).R):\
(Rhs_).T & Type::U8       ? std::any_cast<uint8_t> ((Rhs_).R):\
(Rhs_).T & Type::U16      ? std::any_cast<uint16_t>((Rhs_).R):\
(Rhs_).T & Type::U32      ? std::any_cast<uint32_t>((Rhs_).R):\
(Rhs_).T & Type::U64      ? std::any_cast<uint64_t>((Rhs_).R):\
(Rhs_).T & Type::Float    ? std::any_cast<double>((Rhs_).R) :0

Alu::Alu(double Rhs_)
{
    T = Type::Number | Type::Float | Type::Leaf;
    R = Rhs_;
    //    std::cout << __PRETTY_FUNCTION__ << ":" << types() << ": " << sizeof(a) << '\n';
}

Alu::Alu(float Rhs_)
{
    T = Type::Number | Type::Float | Type::Leaf;
    R = (double) Rhs_;
    //    std::cout << __PRETTY_FUNCTION__ << ":" << types() << ": " << sizeof(a) << '\n';
}

Alu::Alu(const std::string &Rhs_)
{
    T = Type::Text | Type::Leaf;
    R = Rhs_;
    //std::cout << __PRETTY_FUNCTION__ << ":" << types() << ": " << sizeof(a) << '\n';
}

Alu::Alu(const char *Rhs_)
{
    T = Type::Text | Type::Leaf;
    R = std::string(Rhs_);
}

Alu::Alu(void *Rhs_)
{
    T = Type::Any | Type::Voidptr;
    R = Rhs_;
}

//Alu::Alu(Alu &&Rhs_) noexcept
//{
//    std::swap(T<< Rhs_.T);
//    Rhs_.T = Type::null;
//    std::swap(a<< Rhs_.a);
//}

void Alu::Reset()
{
    R.reset();
    T = Type::Null;
}

bool Alu::TypeSize(const Alu &Rhs_)
{
    using namespace Type;
    Type::T me = T & (I8 | I16 | I32 | I64 | U8 | U16 | U32 | U64 | Float);
    Type::T r  = Rhs_.T & (I8 | I16 | I32 | I64 | U8 | U16 | U32 | U64 | Float);
    return me - r >= 0;
}

Alu::operator bool()
{
    if(!R.has_value())
        return false;
    if(!T)
        return false;
    if(T & Type::Text)
        return !Value<std::string>().empty();
    if(T & Type::Number)
        return Number<double>() != 0.0f;
    if(T & Type::Voidptr)
        return Value<void *>() != nullptr;
    return false;
}

#define lr_number(rv) if ((T&Type::Number) && ((rv).T&Type::Number))
#define lr_text(rv)   if ((T&Type::Text) && ((rv).T&Type::Text))
#define lr_any(rv)    if ((T&Type::Any)  && ((rv).T&Type::Any))
#define is_integrale(rv) if (!((rv).T&Type::Float))
#define is_text(i)    if((i).T & Type::Text)
#define is_number if (!(T&(Type::Float|Type::Number)))
// #define delstring_if(Rhs_) if ((T&Type::Text) && (!(Rhs_).T & Type::Text)) delete R.t;  Vieux stuff

Alu &Alu::operator=(const Alu &Rhs_)
{
    if(&Rhs_ != this)
    {
        T = Rhs_.T;
        R.reset();
        R = Rhs_.R;
    }
    return *this;
}

Alu &Alu::operator=(Alu &&Rhs_) noexcept
{
    //logdebugpfn << logger::HBlue << " Rhs_: " << Rhs_() << logger::Reset << Ends;
    std::swap(T, Rhs_.T);
    std::swap(R, Rhs_.R);
    return *this;
}

Alu Alu::operator==(const Alu &Rhs_)
{
    
    if(T & Type::Number)
        return Alu((bool) (((cast(*this)) == (cast(Rhs_)))));
    if(T & Type::Text)
        return Alu(std::any_cast<std::string>(R) == std::any_cast<std::string>(Rhs_.R));
    
    if(T & Type::Any)
        return Alu(std::any_cast<void *>(R) == std::any_cast<void *>(Rhs_.R));
    return Alu(false);
}

std::string Alu::Types() const
{
    std::string str;
    return str << T;
}

Alu Alu::operator+(const Alu &Rhs_)
{
    lr_text(Rhs_)
        return Alu(Value<std::string>() + Rhs_.Value<std::string>());
    else lr_number(Rhs_)
        return Alu(Number<double>() + Rhs_.Number<double>()); // Slow?
    std::string str;
    Rem::Warning() << " [" << (str << T) << "] and [" << (str << Rhs_.T) << "] are incompatible.";
    return Alu(false);
}

Alu Alu::operator[](Alu::CNV c)
{
    is_text(*this)
    {
        return Alu(0.0);
    }
    double d = Number<double>();
    Alu    a;
    switch(c)
    {
        case Alu::DEG:
            a = d * 180 / 3.141592653589793;
            break;
        case Alu::RAD:
            a = d * 3.141592653589793 / 180;
            break;
        default:
            a = 0.0;
            break;
    }
    return a;
}

Alu Alu::operator-(const Alu &rv)
{
    
    lr_text(rv)
    {
        Rem::Warning() << " substraction operator strings is not yet supported";
        //return remove_substr_copy(rv.Value<std::string>());
        return *this;
    }
    
    lr_number(rv)
        return Alu(Number<double>() - rv.Number<double>());
    lr_any(rv)
        return Alu(reinterpret_cast<uint64_t>(Value<void *>()) - reinterpret_cast<uint64_t>(rv.Value<void *>()));
    
    Rem::Warning() << "cannot apply sign on " <<  Type::Name(T);
    return Alu(false);
}


Alu Alu::operator*(const Alu &rv)
{
    Alu f;
    lr_text(rv)
    {
        std::size_t pos = std::any_cast<std::string>(rv.R).find(std::any_cast<std::string>(R));
        return Alu(pos != std::string::npos);
    }
    
    //else
    lr_number(rv)
        return Alu(Number<double>() * rv.Number<double>());
    
    Rem::Warning() <<  "cannot multiply"<< Type::Name(T)<< " and "<< Type::Name(rv.T)<< ".";
    return Alu();
}

Alu Alu::operator/(const Alu &rv)
{
    lr_text(rv)
    {
        Rem::Warning() <<  "cannot divide strings";
        return Alu();
    }
    //    f = Value<std::string>() + rv.Value<std::string>();
    //else
    lr_number(rv)
    {
        double vr = std::any_cast<double>(rv.R);
        double lr = std::any_cast<double>(R);
        
        if(vr == 0.0L)
        {
            Rem::Exception() <<  " In Alu operation: division by zero error. (" <<  (*this)() << " / " << rv() << ")";
            return Alu();
        }
        return Alu(lr / vr);
    }
    
    Rem::Warning() << "cannot divide " << Type::Name(T) << " and " <<  Type::Name(rv.T) << ".";
    return Alu();
}

Alu Alu::operator%(const Alu &rv)
{
    Alu f;
    lr_text(rv)
    {
        Rem::Warning() << "cannot modulo strings";
        return Alu();
    }
    lr_number(rv)
        return Alu(Number<uint64_t>() % rv.Number<uint64_t>());
    
    Rem::Warning() << "cannot modulo " << Type::Name(T) << " and " << Type::Name(rv.T) <<  ".";
    return Alu();
}

Alu Alu::operator^(const Alu &rv)
{
    Alu f;
    lr_text(rv)
    {
        Rem::Warning() <<  "cannot xor strings";
        return Alu();
    }
    
    lr_number(rv)
        return Alu(Number<uint64_t>() ^ rv.Number<uint64_t>());
    
    Rem::Warning() <<  "cannot xor " <<  Type::Name(T) << " and " << Type::Name(rv.T) << ".";
    return Alu();
}

Alu Alu::operator<<(const Alu &Rhs_)
{
    Alu f;
    lr_text(Rhs_)
    {
        String str = Value<std::string>();
        str << Rhs_.Value<std::string>();
        return Alu(str());
    }
    
    lr_number(Rhs_)
        return Alu(Number<uint64_t>() << Rhs_.Number<uint64_t>());
    
    Rem::Warning() <<  "cannot execute bitwise left-shift or insert with " << Type::Name(T) << " and " <<  Type::Name(Rhs_.T) << ".";
    return f;
}
Alu Alu::operator>>(const Alu &Rhs_)
{
    Alu f;
    lr_text(Rhs_)
    {
        Rem::Warning() <<  "cannot execute bitwise right-shift or extract/write/send string on string " << Type::Name(T) << " and " <<  Type::Name(Rhs_.T) << ".";
    }
    lr_number(Rhs_)
        return Alu(Number<uint64_t>() >> Rhs_.Number<uint64_t>());
    
    Rem::Warning() <<  "cannot execute bitwise right-shift or extract/write/send with "<< Type::Name(T)<< " and "<< Type::Name(Rhs_.T)<< ".";
    return f;
}

Alu Alu::operator|(const Alu &Rhs_)
{
    
    lr_text(Rhs_)
    {
        return Alu(Value<std::string>() + Rhs_.Value<std::string>());
    }
    lr_number(Rhs_)
        return Alu(Number<uint64_t>() | Rhs_.Number<uint64_t>());
    
    Rem::Warning() <<  "cannot execute bitwise or with "  <<  Type::Name(T) <<  " and " <<  Type::Name(Rhs_.T) << ".";
    return Alu();
}

Alu Alu::operator&(const Alu &Rhs_)
{
    lr_text(Rhs_)
    {
        Rem::Warning() <<  "cannot execute bitwise and on string ";
    }
    lr_number(Rhs_)
        return Alu(Number<uint64_t>() & Rhs_.Number<uint64_t>());
    
    Rem::Warning() <<  "cannot execute bitwise and between " << Type::Name(T) << " and "<< Type::Name(Rhs_.T) << ".";
    return Alu();
}

Alu Alu::operator~()
{
    is_text(*this)
    {
        Rem::Warning() <<  "cannot execute bitwise invert on string ";
    }
    
    is_number
        return Alu(~Number<uint64_t>());
    
    Rem::Warning() <<  "cannot execute bitwise invert on " << Type::Name(T);
    return Alu();
}

// Assign operators:
Alu &Alu::operator+=(const Alu &rv)
{
    lr_text(rv)
    {
        R = std::string(Value<std::string>() + rv.Value<std::string>());
        return *this;
    }
    
    lr_number(rv)
    {
        double r   = rv.Number<double>();
        double l   = Number<double>();
        R = l + r;
        return *this;
    }
    
    Rem::Warning() <<  "cannot execute assign add between " << Type::Name(T) << " and " << Type::Name(rv.T) << ".";
    return *this;
}

Alu &Alu::operator-=(const Alu &rv)
{
    lr_text(rv) return *this;
        //return remove_substr(rv.Value<std::string>());
    
    lr_number(rv)
    {
        R = Number<double>() - rv.Number<double>();
        return *this;
    }
    
    Rem::Warning() <<  "cannot execute assign substract between "<< Type::Name(T)<< " and "<< Type::Name(rv.T)<< ".";
    return *this;
}

Alu &Alu::operator*=(const Alu &rv)
{
    lr_text(rv)
    {
        Rem::Warning() <<  "cannot execute assign multiply on strings [" << (*this)() << " *= " << rv() << "].";
        return *this;
    }
    
    lr_number(rv)
    {
        R = Number<double>() * rv.Number<double>();
        return *this;
    }
    
    Rem::Warning() <<  "cannot execute assign multiply between "<< Type::Name(T)<< " and "<< Type::Name(rv.T)<< ".";
    return *this;
}

Alu &Alu::operator/=(const Alu &rv)
{
    lr_text(rv)
    {
        Rem::Warning() <<  "cannot execute assign divide on strings ["<< (*this)()<< " /= "<< rv()<< "].";
        return *this;
    }
    
    lr_number(rv)
    {
        double vr = rv.Number<double>();
        if(!vr)
        {
            Rem::Warning() <<  "Alu: cannot divide by zero.";
            R = 0.0;
            T = Type::Null;
            return *this;
        }
        R         = Number<double>() / rv.Number<double>();
        return *this;
    }
    Rem::Warning() <<  "cannot execute assign divide between "<< Type::Name(T)<< " and "<< Type::Name(rv.T)<< ".";
    return *this;
}

Alu::~Alu()
{
    R.reset();
}

Alu &Alu::operator%=(const Alu &rv)
{
    lr_text(rv) return *this;
        //return completely_remove_substr(rv.Value<std::string>());
    
    lr_number(rv)
    {
        R = Number<uint64_t>() % rv.Number<uint64_t>();
        return *this;
    }
    
    return *this;
}

Alu &Alu::operator|=(const Alu &rv)
{
    
    lr_text(rv)
    {
        Rem::Warning() <<  "cannot execute assign bitwise or on strings ["<< (*this)()<< " |= "<< rv()<< "].";
        return *this;
    }
    
    lr_number(rv)
    {
        R = Number<uint64_t>() | rv.Number<uint64_t>();
        return *this;
    }
    Rem::Warning() <<  "cannot execute assign bitwise or between "<< Type::Name(T)<< " and "<< Type::Name(rv.T)<< ".";
    return *this;
}

Alu &Alu::operator&=(const Alu &rv)
{
    lr_text(rv)
    {
        Rem::Warning() <<  "cannot execute assign bitwise and on strings ["<< (*this)()<< " &= "<< rv()<< "].";
        return *this;
    }
    //    a = std::string(Value<std::string>() + rv.Value<std::string>());
    //else
    lr_number(rv)
    {
        R = Number<uint64_t>() & rv.Number<uint64_t>();
        return *this;
    }
    Rem::Warning() <<  "cannot execute assign bitwise and between "<< Type::Name(T)<< " and "<< Type::Name(rv.T)<< ".";
    return *this;
}

Alu &Alu::operator^=(const Alu &rv)
{
    lr_text(rv)
    {
        Rem::Warning() <<  "cannot execute assign xor on strings ["<< (*this)()<< " ><= "<< rv()<< "].";
        return *this;
    }
    
    lr_number(rv)
    {
        R = Number<uint64_t>() ^ rv.Number<uint64_t>();
        return *this;
    }
    
    Rem::Warning() <<  "cannot execute assign xor between "<< Type::Name(T)<< " and "<< Type::Name(rv.T)<< ".";
    return *this;
}

// boolean operators:
Alu Alu::operator>(const Alu &rv)
{
    lr_text(rv)
        return Alu(Value<std::string>() > rv.Value<std::string>());
    
    lr_number(rv)
        return Alu(Number<double>() > rv.Number<double>());
    
    Rem::Warning() <<  "cannot execute relational operations between "<< Type::Name(T)<< " and "<< Type::Name(rv.T)<< ".";
    return Alu(false);
}

Alu Alu::operator<(const Alu &rv)
{
    lr_text(rv)
        return Alu(Value<std::string>() < rv.Value<std::string>());
    
    lr_number(rv)
        return Alu(Number<double>() < rv.Number<double>());
    
    Rem::Warning() <<  "cannot execute relational operations between "<< Type::Name(T)<< " and "<< Type::Name(rv.T)<< ".";
    return Alu(false);
    
}
Alu Alu::operator>=(const Alu &rv)
{
    lr_text(rv)
        return Alu(Value<std::string>() >= rv.Value<std::string>());
    
    lr_number(rv)
        return Alu(Number<double>() >= rv.Number<double>());
    
    Rem::Warning() <<  "cannot execute relational operations between "<< Type::Name(T)<< " and "<< Type::Name(rv.T)<< ".";
    return Alu(false);
    
}

Alu Alu::operator<=(const Alu &rv)
{
    lr_text(rv)
        return Alu(Value<std::string>() <= rv.Value<std::string>());
    
    lr_number(rv)
        return Alu(Number<double>() <= rv.Number<double>());
    
    Rem::Warning() <<  "cannot execute relational operations between "<< Type::Name(T)<< " and "<< Type::Name(rv.T)<< ".";
    return Alu(false);
    
}

Alu Alu::operator!=(const Alu &rv)
{
    lr_text(rv)
        return Alu(Value<std::string>() != rv.Value<std::string>());
    
    lr_number(rv)
        return Alu(Number<double>() != rv.Number<double>());
    
    Rem::Warning() <<  "cannot execute relational operations between "<< Type::Name(T)<< " and "<< Type::Name(rv.T)<< ".";
    return Alu(false);
}

Alu Alu::operator||(const Alu &rv)
{
    lr_text(rv)
        return Alu(!Value<std::string>().empty() || (!rv.Value<std::string>().empty()));
    
    lr_number(rv)
        return Alu(Number<double>() || rv.Number<double>());
    
    Rem::Warning() <<  "cannot execute relational operations between "<< Type::Name(T)<< " and "<< Type::Name(rv.T)<< ".";
    return Alu(false);
}

Alu Alu::operator&&(const Alu &rv)
{
    lr_text(rv)
        return Alu(!Value<std::string>().empty() && (!rv.Value<std::string>().empty()));
    
    lr_number(rv)
        return Alu(Number<bool>() && rv.Number<bool>());
    
    Rem::Warning() <<  "cannot execute relational operations between "<< Type::Name(T)<< " and "<< Type::Name(rv.T)<< ".";
    return Alu(false);
}

bool Alu::operator!()
{ return R.has_value(); }//T == Type::null; }
Alu Alu::operator-()
{
    is_text(*this)
    {
        Rem::Warning() <<  "cannot execute sign operator on string -(\""<< (*this)()<< "\").";
    }
    Rem::Warning() <<  "cannot execute relational operations on "<< Type::Name(T);
    return -Number<double>();
}

Alu Alu::operator+()
{
    is_text(*this)
    {
        Rem::Warning() <<  "cannot execute sign operator on string +(\""<< (*this)()<< "\").";
    }
    
    is_number
        if(Number<double>() < 0.0f)
            return Alu(Number<double>() * -1);
    
    Rem::Warning() <<  "cannot execute relational operations on "<< Type::Name(T);
    return Alu(false);
}

Alu Alu::operator++(int)
{
    
    is_text(*this)
    {
        Rem::Warning() <<  "cannot increment string (\""<< (*this)()<< "\")++.";
    }
    
    is_number
    {
        double f = Number<double>();
        Alu    ff(f);
        ++f;
        R = f;
        return ff;
    }
    Rem::Warning() <<  "cannot execute increment operations on "<< Type::Name(T);
    return Alu(false);
}

Alu Alu::operator++()
{
    is_text(*this)
    {
        Rem::Warning() <<  "cannot increment string ++(\""<< (*this)()<< "\").";
    }
    
    is_number
    {
        double f = Number<double>();
        ++f;
        R = f;
        return *this;
    }
    Rem::Warning() <<  "cannot execute increment operations on "<< Type::Name(T);
    return Alu(false);
}

Alu Alu::operator--()
{
    
    is_text(*this)
    {
        Rem::Warning() <<  "cannot decrement string --(\""<< (*this)()<< "\").";
    }
    
    is_number
    {
        double f = Number<double>();
        ++f;
        R = f;
        return *this;
    }
    Rem::Warning() <<  "cannot execute decrement operations on "<< Type::Name(T);
    return Alu(false);
}

Alu Alu::operator--(int)
{
    is_text(*this)
    {
        Rem::Warning() <<  "cannot decrement string (\""<< (*this)()<< "\")++."; // oops... What if long text string?
    }
    
    is_number
    {
        double f = Number<double>();
        Alu    ff(f);
        ++f;
        R = f;
        return ff;
    }
    Rem::Warning() <<  "cannot execute decrement operations on "<< Type::Name(T);
    return Alu(false);
}

Alu Alu::Radical(const Alu &Rhs_)
{
    Alu al;
    lr_number(Rhs_)
    {
        al = Alu(std::pow(Number<double>(),1 / Rhs_.Number<double>()));
        return al;
    }
    
    Rem::Warning() <<  "cannot execute radical operator on "<< Type::Name(T);
    return Alu(false);
}

Alu Alu::Factorial(const Alu &Rhs_)
{
    lr_number(Rhs_)
    {
        int fac = 1;
        int N   = Rhs_.Number<int>();
        if(N >= 10)
            return Alu();
        for(int j = 1; j <= N; j++)
            fac *= j;
        return Alu(fac);
    }
    Rem::Warning() <<  "cannot execute Factorial operator on "<< Type::Name(T);
    return Alu(false);
}

Alu &Alu::operator<<=(const Alu &rv)
{
    
    lr_text(rv)
    {
        Rem::Warning() <<  "cannot execute assign extraction/bitwise right-shift / output on strings.";
        return *this;
    }
    
    lr_number(rv)
    {
        R = Number<uint64_t>() << rv.Number<uint64_t>();
        return *this;
    }
    
    Rem::Warning() <<  "cannot execute assign bitwise left-shift or insert with " << Type::Name(T) << " and " << Type::Name(rv.T) << ".";
    return *this;
}

Alu &Alu::operator>>=(const Alu &rv)
{
    
    lr_text(rv)
    {
        Rem::Warning() <<  "cannot execute assign extraction/bitwise right-shift / output on strings.";
        return *this;
    }
    
    lr_number(rv)
    {
        R = Number<uint64_t>() << rv.Number<uint64_t>();
        return *this;
    }
    
    Rem::Warning() <<  "cannot execute assign bitwise right-shift or insert with "<< Type::Name(T)<< " and "<< Type::Name(rv.T)<< ".";
    return *this;
}

//Alu Alu::remove_substr_copy(const std::string &to_erase)
//{
//
//    // J'suis paresseux :: copy-paste here (from thispointer :: how to remove substr: )
//    auto   cp  = std::any_cast<std::string>(a);
//    size_t pos = cp.find(to_erase);
//
//    if(pos != std::string::npos)
//    {
//        // If found then erase it from string
//
//        cp.erase(pos<< to_erase.length());
//    }
//    return Alu(cp);
//}
//
//Alu Alu::remove_all_substr_copy(const std::string &to_erase)
//{
//    // J'suis paresseux :: copy-paste here (from thispointer :: how to remove substr: )
//
//
//    size_t pos = std::string::npos;
//    auto   cp  = std::any_cast<std::string>(a);
//    // Search for the substring in string in a loop untill nothing is found
//    while((pos = cp.find(to_erase)) != std::string::npos)
//    {
//        // If found then erase it from string
//        cp.erase(pos<< to_erase.length());
//    }
//
//    return Alu(cp);
//}
//
//Alu &Alu::remove_substr(const std::string &to_erase)
//{
//
//    // J'suis paresseux :: copy-paste here (from thispointer :: how to remove substr: )
//    auto   cp  = std::any_cast<std::string &>(a);
//    size_t pos = cp.find(to_erase);
//
//    if(pos != std::string::npos)
//    {
//        // If found then erase it from string
//
//        cp.erase(pos<< to_erase.length());
//    }
//    return *this;
//}

bool Alu::IsNumber()
{ return (T & (Type::Float | Type::Number)); }

//Alu &Alu::completely_remove_substr(const std::string &to_erase)
//{
//    // J'suis paresseux :: copy-paste here (from thispointer :: how to remove substr: )
//
//
//    size_t pos = std::string::npos;
//    auto   cp  = std::any_cast<std::string &>(a);
//    // Search for the substring in string in a loop untill nothing is found
//    while((pos = cp.find(to_erase)) != std::string::npos)
//    {
//        // If found then erase it from string
//        cp.erase(pos<< to_erase.length());
//    }
//
//    return *this;
//}

std::string Alu::ToStr()
{
    return (std::string) *this;
}

}

