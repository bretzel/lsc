//
// Created by lsc on 20-05-18.
//

//#ifndef LSC_LEXER_H
//#define LSC_LEXER_H

#pragma once

#include <Lsc/Scripture/TokenData.h>
#include <Lsc/Rem/Rem.h>
#include <map>
namespace Lsc
{

class SCRIPTURE_LIB Lexer
{
    struct InternalCursor
    {
        const char *B  = nullptr; ///> Absolute Beginning of the source text.
        const char *E  = nullptr; ///> Absolute End of the soure text.
        const char *C  = nullptr;
        
        bool operator++();
        bool operator++(int);
        [[maybe_unused]] bool SkipWS();
        bool Eof(const char *P = nullptr) const;
        long Index() const;
        int        L   = -1;
        int        Col = -1;
        void Sync();
        std::string ScanToEol();
        std::string Line() const;
        std::string Mark() const;
        std::string Location() const;
        bool       _F  = false;
        Rem::Int ScanTo(const char *SubStr_);
        Expect<std::string> ScanString();
        
        InternalCursor() = default;
        InternalCursor(const char *Source_);
    } mCursor;
    
    struct NumScanner
    {
        const char *B   = nullptr;
        const char *E   = nullptr;
        const char *C   = nullptr;
        const char *Eos = nullptr;
        bool Real = false;
        
        bool Literal = true; ///< scan literal digits - do not validate hexadecimal...
        
        enum NumBase
        {
            None,
            Bin,
            Oct,
            Dec,
            Hex,/* ..., */ //  FUCK!!!
        }    Num     = None;
        
        NumScanner() = default;
        NumScanner(const char *_c, const char *_eos);
        
        ~NumScanner() = default;
        
        //bool operator++();
        bool operator++(int);
        
        explicit operator bool() const;
        Type::T operator()() const;
    };

public:
    struct SCRIPTURE_LIB ConfigData
    {
        const char *Source            = nullptr;
        TokenData::Collection *Tokens = nullptr;
        operator bool() const { return Source && Tokens; }
    };
    
    
    Lexer() = default;
    Lexer(const Lexer&) = default;
    Lexer(Lexer&&)      = default;
    
    ~Lexer()            = default;
    
    Lexer::ConfigData& Config();
    
    Return  Exec();
    Return  operator()();
    
    
    bool Empty() { return (mConfig.Tokens ? mConfig.Tokens->empty() : true); }
private:

    ConfigData mConfig;
    
    Return Append(TokenData& Token_) ;
    
    using ScannerFn = Return(Lexer::*)(TokenData&);
    using InputPair = std::pair<Type::T, Type::T>;
    static std::map<Lexer::InputPair , ScannerFn> _ProductionTable;
    
    using Scanner = Expect<Lexer::ScannerFn>;
    
    
    #pragma region Scanners
    Scanner GetScanner(InputPair && Pair);
    
    Return _InputBinaryOperator(TokenData&);
    Return _InputDefault(TokenData&);
    Return _InputUnaryOperator(TokenData&);
    Return _InputPunctuation(TokenData&);
    Return _InputKeyword(TokenData&);
    Return _InputString(TokenData&);
    Return _InputHex(TokenData&);
    
    Return ScanNumber(TokenData&);
    Return ScanIdentifier(TokenData&);
    Return ScanFactorNotation(TokenData&);
    Return ScanSignPrefix(TokenData&);
    Return ScanPrefix(TokenData&);
    Return ScanPostfix(TokenData&);
    
    
    #pragma endregion Scanners
};


}

uint64_t operator & (std::pair<Lsc::Type::T, Lsc::Type::T>, std::pair<Lsc::Type::T, Lsc::Type::T>);

//#endif //LSC_LEXER_H
