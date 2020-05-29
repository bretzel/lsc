//
// Created by lsc on 20-05-28.
//

//#ifndef LSC_Alu_H
//#define LSC_Alu_H

#pragma once

#include <Lsc/Scripture/Lib.h>
#include <any>
#include <vector>
#include <Lsc/Scripture/Types.h>
#include <memory>

namespace Lsc
{

struct SCRIPTURE_LIB Alu
{
    using Collection = std::vector<Alu>;
    using LinkArray = std::vector<Alu *>;
    static std::string mNil;
    std::any R = .0;
    Type::T  T = Type::Float; ///< Default type.
    
    enum CNV {
        DEG,
        RAD
    };
    
    Alu() { R.reset(); }

    Alu(const Alu&) = default;
    Alu(double A_);
    Alu(float A_);
    //Alu(token_t* rhs);

    Alu(const std::string& A_);
    Alu(const char* A_);
    Alu(void* A_);
    Alu(Alu&& ) noexcept = default;
    Alu(int8_t A_);
    Alu(int16_t A_);
    Alu(int32_t A_);
    Alu(int64_t A_);
    Alu(uint8_t A_);
    Alu(uint16_t A_);
    Alu(uint32_t A_);
    Alu(uint64_t A_);
    Alu(bool A_);

    void Reset();
        Alu& operator =(const Alu& Lhs_);// { a = lf.a; T = lf.T; return *this; }

    Alu& operator =(Alu&& rhs) noexcept;

    Alu operator==(const Alu & lf);
    Type::T TypeOf() { return T; }

    template<typename OfType> OfType Value() const {

        if constexpr (std::is_same<OfType, std::string>::value)
            return (T & Type::Text ? std::any_cast<std::string>(R) : "");
        else
        if constexpr (std::is_same<OfType, const std::string&>::value)
            return (T & Type::Text ? std::any_cast<const std::string&>(R) : "");
        else
        if constexpr (std::is_same<OfType, const char*>::value)
            return (T & Type::Text ? std::any_cast<std::string>(R).c_str() : nullptr);
        else
        if constexpr (std::is_same<OfType, void*>::value)
            return std::any_cast<void*>(R);
        else
            return static_cast<OfType>(
                T & Type::I8 ?  std::any_cast<int8_t>(R) :
                T & Type::I16 ? std::any_cast<int16_t>(R) :
                T & Type::I32 ? std::any_cast<int32_t>(R) :
                T & Type::I64 ? std::any_cast<int64_t>(R) :
                T & Type::U8 ?  std::any_cast<uint8_t>(R) :
                T & Type::U16 ? std::any_cast<uint16_t>(R) :
                T & Type::U32 ? std::any_cast<uint32_t>(R) :
                T & Type::U64 ? std::any_cast<uint64_t>(R) :
                T & Type::Boolean ? std::any_cast<bool>(R) :
                T & Type::Float ? std::any_cast<double>(R) :0

            );
    }

    template<typename OfType> OfType Number() const
    {
        if constexpr (std::is_same<OfType, void*>::value)
            return std::any_cast<void*>(R);
        else
        if constexpr (std::is_same<OfType, std::string>::value)
            return (std::string)*this;
        else
            return static_cast<OfType>(
                T & Type::I8 ?  std::any_cast<int8_t>  (R) :
                T & Type::I16 ? std::any_cast<int16_t> (R) :
                T & Type::I32 ? std::any_cast<int32_t> (R) :
                T & Type::I64 ? std::any_cast<int64_t> (R) :
                T & Type::U8 ?  std::any_cast<uint8_t> (R) :
                T & Type::U16 ? std::any_cast<uint16_t>(R) :
                T & Type::U32 ? std::any_cast<uint32_t>(R) :
                T & Type::U64 ? std::any_cast<uint64_t>(R) :
                T & Type::Boolean ? std::any_cast<bool>(R) :
                T & Type::Float ? std::any_cast<double>(R) : 0
            );

    }


    template<Type::T T> bool is() {
        return T == T;
    }

    bool IsText() { return T&Type::Text;}
    std::string ToStr();
    bool IsNumber();
    std::string Types() const;
    virtual ~Alu();



    // Arithmetic operations overload between two Alus:

    // Binary operators:

    Alu operator +(const Alu& Rhs_);
    Alu operator -(const Alu& Rhs_);
    Alu operator *(const Alu& Rhs_);
    Alu operator [](Alu::CNV Cnv_);

    Alu operator /(const Alu& Rhs_);
    Alu operator %(const Alu& Rhs_);
    Alu operator ^(const Alu& Rhs_);
    Alu operator <<(const Alu& Lhs_);
    Alu operator >>(const Alu& Lhs_);
    Alu operator |(const Alu& Lhs_);
    Alu operator &(const Alu& Lhs_);
    Alu operator ~();
    // Assign operators:
    Alu& operator +=(const Alu& Rhs_);
    Alu& operator -=(const Alu& Rhs_);
    Alu& operator *=(const Alu& Rhs_);
    Alu& operator /=(const Alu& Rhs_);
    Alu& operator %=(const Alu& Rhs_);
    Alu& operator |=(const Alu& Rhs_);
    Alu& operator &=(const Alu& Rhs_);
    Alu& operator ^=(const Alu& Rhs_);

    Alu& operator <<=(const Alu& Rhs_);
    Alu& operator >>=(const Alu& Rhs_);


    // boolean operators:
    Alu operator >(const Alu& Rhs_);
    Alu operator <(const Alu& Rhs_);
    Alu operator >=(const Alu& Rhs_);
    Alu operator <=(const Alu& Rhs_);
    Alu operator !=(const Alu& Rhs_);
    Alu operator ||(const Alu& Rhs_);
    Alu operator &&(const Alu& Rhs_);

    bool operator !();
    bool IsSet() { return R.has_value(); }
    operator bool();

    Alu operator -();
    Alu operator +();

    Alu operator ++(int);
    Alu operator ++();
    Alu operator --();
    Alu operator --(int);

    Alu Radical(const Alu& Lhs_);
    Alu Factorial(const Alu& Lhs_);

    bool TypeSize(const Alu& Rhs_);
    std::string operator()()const { return (std::string)(*this); }
    operator std::string() const {
        String str;
        if (T &Type::Boolean)
            str << (Value<bool>() ? "true" : "false");
        else
        if (T&Type::Number)
            str << Number<double>();
        else
        if (T&Type::Text)
            return Value<std::string>();
        else
        if (T&Type::Voidptr) {
            str = "@[%ld]";
            str << Number<void*>();
        }
        else
        if (T&Type::Null)
            str << "null";
        return str();
    }

//    private:
//    Alu remove_substr_copy(const std::string& to_erase);
//    Alu completely_remove_substr_copy(const std::string& to_erase);
//    Alu& remove_substr(const std::string& to_erase);
//    Alu& completely_remove_substr(const std::string& to_erase);


};

}
//#endif //LSC_Alu_H
