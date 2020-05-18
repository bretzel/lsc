//
// Created by lsc on 20-05-18.
//

//#ifndef LSC_TOKENDATA_H
//#define LSC_TOKENDATA_H

#pragma once

#include <Lsc/Scripture/Types.h>

namespace Lsc
{

struct SCRIPTURE_LIB TokenData
{
    Mnemonic       M = Mnemonic::Noop;
    Type::T        T = Type::Null;    ///< Primitive Type bit.
    Type::T        S = Type::Null;    ///< Semantic Type bits field
    Type::Delta::T D = Type::Delta::Noop;
    void *mData = nullptr;
    
    using Collection = std::vector<TokenData>;
    using Iterator = Collection::iterator;
    
    struct SCRIPTURE_LIB  LocationData
    {
        const char *Begin = nullptr;
        const char *End   = nullptr;
        int     L = -1; ///< line number
        int     C = -1; ///< Column number
        int64_t I = -1; ///< Absolute Offset from the beginning of the Source Text.
        std::string operator()();
        std::string Text();
        std::string Position();
    }    mLoc;
    
    struct SCRIPTURE_LIB Flag
    {
        int8_t V: 1; ///< Pre-parsed as a value ArgToken;
        int8_t S: 1; ///< Post parsed as assignable
        int8_t M: 1; ///< Virtual multiplication operator. (...4ac...)
    }    mFlags = {0, 0, 0};
    
    static TokenData mNull;
    
    TokenData() = default;
    ~TokenData() = default;
    
    TokenData(Mnemonic Code_, Type::T Type_, Type::T Sem_, Type::Delta::T Delta_, Lexem::T aLexem, int8_t V);
    TokenData(Mnemonic Code_, Type::T Type_, Type::T Sem_, Type::Delta::T Delta_, TokenData::LocationData LocationData_, TokenData::Flag Flags_, void *Ptr_ = nullptr);
    TokenData(const TokenData &Token_);
    TokenData(TokenData &&Token_) noexcept;
    
    TokenData &operator=(TokenData &&Token_) noexcept;
    TokenData &operator=(const TokenData &Token_);
    TokenData operator[](Mnemonic CC);
    //ArgToken* ptr() { return this; }
    std::string Mark();
    
    explicit operator bool() const
    { return mLoc.Begin != nullptr; }
    bool operator||(Type::T Sem_) const
    { return S || Sem_; }
    
    [[nodiscard]] std::string Attr()
    { return mLoc(); }
    [[nodiscard]] std::string SemanticTypes();
    [[nodiscard]] std::string TypeName();
    [[nodiscard]] std::string Details(bool Mark_ = false);
    
    static TokenData Scan(const char *C_);
    
    [[nodiscard]] bool IsBinary() const
    { return S & Type::Binary; }
    [[nodiscard]] bool IsUnary() const
    { return S & Type::Unary; }
    [[nodiscard]] bool IsIdentifier() const
    { return S & Type::Id; }
    [[nodiscard]] bool IsLeaf() const
    { return S & Type::Leaf; }
    [[nodiscard]] bool IsOperator() const
    { return S & Type::Operator; }
    [[nodiscard]] bool IsClosing_pair() const
    { return S & Type::ClosePair; }
    [[nodiscard]] bool IsPunctuation() const
    { return S & Type::Punctuation; }
    [[nodiscard]] bool IsNumber() const
    { return S & Type::Number; }
    [[nodiscard]] bool IsHexadecimal() const
    { return S & Type::Hex; }
    [[nodiscard]] bool IsPrefix() const
    { return S & Type::Prefix; }
    [[nodiscard]] bool IsPostfix() const
    { return S & Type::Postfix; }
    [[nodiscard]] bool IsInstruction() const
    { return !(S & (Type::Operator | Type::Leaf)); }
    
    
};

}
//#endif //LSC_TOKENDATA_H
