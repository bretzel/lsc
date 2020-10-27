//
// Created by lsc on 20-10-17.
//
/*
#pragma once
#include <Lsc/Rem/Rem.h>

//#include <Lsc/Scripture/Types.h>
#include <Lsc/Scripture/TokenData.h>

namespace Lsc::Scripture
{



struct Rule;

struct  Attr
{
    int8_t Z : 1; ///< Zero or one (optional * )
    int8_t R : 1; ///< Repeat      (        + )
    int8_t L : 1; ///< List        (one of  ~ ?)
    int8_t X : 1; ///< directive    ( ast direcive )
    int8_t S : 8; ///< Litteral List Separator
    Attr &operator|(Attr const &A)
    {
        Z |= A.Z;
        R |= A.R;
        L |= A.L;
        X |= A.X;
        //S = A.S;
        return *this;
    }
    
    Attr &operator+()
    {
        R = 1;
        return *this;
    }
    Attr &operator*()
    {
        Z = 1;
        return *this;
    }
    Attr &operator!()
    {
        X = 1;
        return *this;
    }
    Attr &operator~()
    {
        L = 1;
        return *this;
    }
    void Reset() { Z = R = L = X = S = 0; }
    std::string operator()();
    bool IsOpt() const { return Z != 0; }
    bool IsOneOf() const { return L != 0; }
    bool IsStrict() const { return Z == 0 && L == 0 && R == 0; }
    bool IsRepeat() const { return R != 0; }
    bool IsAccepted() const { return X != 0; }
    void Accept() { X = 1; }
    void Reject() { X = 0; }
};

struct Term
{
    using List = std::vector<Term>;
    Attr _A  = {0, 0, 0, 0, 0}; ///< default : punctual, strict match
    
    enum class Type : uint8_t
    {
        //term,
        Rule = 0,
        Sem,
        Code,
        Nil
    };

    void Accept() { _A.Accept(); }
    void Reject() { _A.Reject(); }

    Term::Type _Type = Term::Type::Nil;
    union Mem {
        Rule *R;
        Lsc::Type::T Sem;
        Lsc::Lexem::T Code;
    } _Mem = {nullptr};
    
    using Iterator = Term::List::iterator;
    using CIterator = Term::List::const_iterator;

    // pas le choix... 'y faut un parser....

    Term();
    Term(Rule *R, Attr A_ = {0, 0, 0, 0, 0});
    Term(Lsc::Type::T Sem_, Attr A_ = {0, 0, 0, 0, 0});
    Term(Lsc::Mnemonic Code_, Attr A_ = {0, 0, 0, 0, 0});

    Term(const std::string &Lexem_);

    Term(Term && T_);
    Term(const Term & T_);

    Term &operator=(Term && T_);
    Term &operator=(const Term &T_);

    bool operator==(const Term &T_) const;
    bool operator==(const TokenData &T_) const;
    bool operator!=(const TokenData &T_) const;

    operator bool() { return _Type != Type::Nil; }
    ~Term();

    Term &operator*()
    {
        *_A;
        return *this;
    }
    Term &operator+()
    {
        +_A;
        return *this;
    }
    Term &operator!()
    {
        !_A;
        return *this;
    }
    Term &operator~()
    {
        ~_A;
        return *this;
    }

    std::string operator()() const;

    bool IsRule() const { return _Type == Term::Type::Rule; }
    bool IsSemantic() const { return _Type == Term::Type::Sem; }
    bool IsMnemonic() const { return _Type == Term::Type::Code; }
    bool IsNull() const { return _Type == Term::Type::Nil; }

    static Term Query(const char *);
    static Term Query(Lsc::Type::T);
    static Term Query(Lsc::Mnemonic);
};


struct TermSeq
{
    using List = std::vector<TermSeq>;
    
    Term::List _Terms;
    
};

struct Rule
{
    using List = std::vector<Rule*>;
    
    TermSeq::List _Sequences;
};



struct Grammar
{
    Rule::List _Rules;
    
};

}
 */
