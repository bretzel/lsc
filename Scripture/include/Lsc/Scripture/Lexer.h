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
        const char *mSource = nullptr;
        TokenData::Collection *mTokensCollection = nullptr;
    };
    
    
    Lexer() = default;
    Lexer(const Lexer&) = default;
    Lexer(Lexer&&)      = default;
    
    ~Lexer()            = default;
    
    Lexer::ConfigData& Config();
    
    Return  Exec();
private:

    ConfigData mConfig;
    
    void Append(TokenData& Token_) ;
    
    
    /*
        (English text will follows after this)
        Il s'agit ici de pr&eacute;-analyser une expression arith&eacute;tique par association de paires de types pris dans la table des tokens/symboles de r&eacute;f&eacute;ce.
        En math&eacute;matiques, les op&eacute;rations et leurs pr&eacute;cedences sont universelles - donc on r&egrave;gle les erreurs de syntaxe
        aussit&ocirc;t qu'&agrave; la phase d'analyse lexicale du code source!
     */
    
    using ScannerPFn = Return(Lexer::*)(TokenData&);
    using InputPair = std::pair<Type::T, Type::T>;
    using AssocPair = std::map<Lexer::InputPair, Lexer::ScannerPFn>;
    static Lexer::AssocPair _AssocLexerTable;
    static std::map<Type::T, ScannerPFn> _ProdTable;

};


}


//#endif //LSC_LEXER_H
