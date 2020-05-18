//
// Created by lsc on 20-05-18.
//

#include "Lsc/Scripture/TokenData.h"

static const char *fmt = "'%s'(%d,%d) %s[%s]";

namespace Lsc
{

std::string TokenData::LocationData::operator()()
{
    // line y, col x: `attribute`
    return Text();
}

std::string TokenData::LocationData::Text()
{
    if(Begin == nullptr)
        return std::string();
    
    std::string str;
    const char  *ptr = Begin;
    
    str += *ptr++;
    if(!End)
    {
        while(*ptr)
            str += *ptr++;
        return str;
    }
    while(ptr <= End)
        str += *ptr++;
    return str;
}

std::string TokenData::LocationData::Position()
{
    String Str = "%d,%d";
    Str << L << C;
    return Str();
}

TokenData SCRIPTURE_LIB TokenData::mNull = TokenData();

TokenData::TokenData(Mnemonic aCode, Type::T aType, Type::T aSem, Type::Delta::T aDelta, Lexem::T aLexem, int8_t aFlags)
{
    M      = aCode;
    T      = aType;
    S      = aSem;
    D      = aDelta;
    mLoc   = {aLexem, 0, 0, 0, -1};
    mFlags = {aFlags, 0, 0};
    
}

TokenData::TokenData(Mnemonic aCode, Type::T aType, Type::T aSem, Type::Delta::T aDelta, TokenData::LocationData aLoc, TokenData::Flag aFlag, void *aPtr)
{
    M      = aCode;
    T      = aType;
    S      = aSem;
    D      = aDelta;
    mLoc   = aLoc;
    mFlags = aFlag;
    mData  = aPtr;
}

TokenData::TokenData(const TokenData &aToken) // Consider using "default" ...
{
    M      = aToken.M     ;
    T      = aToken.T     ;
    S      = aToken.S     ;
    D      = aToken.D     ;
    mLoc   = aToken.mLoc  ;
    mFlags = aToken.mFlags;
    mData  = aToken.mData ;
}

TokenData::TokenData(TokenData &&aToken) noexcept
{
    std::swap(M      , aToken.M      );
    std::swap(T      , aToken.T      );
    std::swap(S      , aToken.S      );
    std::swap(D      , aToken.D      );
    std::swap(mLoc   , aToken.mLoc   );
    std::swap(mFlags , aToken.mFlags );
    std::swap(mData  , aToken.mData  );
    
}

TokenData &TokenData::operator=(TokenData &&aToken) noexcept
{
    std::swap(M      , aToken.M      );
    std::swap(T      , aToken.T      );
    std::swap(S      , aToken.S      );
    std::swap(D      , aToken.D      );
    std::swap(mLoc   , aToken.mLoc   );
    std::swap(mFlags , aToken.mFlags );
    std::swap(mData  , aToken.mData  );
    return *this;
}

TokenData &TokenData::operator=(const TokenData &aToken)
{
    M      = aToken.M     ;
    T      = aToken.T     ;
    S      = aToken.S     ;
    D      = aToken.D     ;
    mLoc   = aToken.mLoc  ;
    mFlags = aToken.mFlags;
    mData  = aToken.mData ;
    return *this;
}

std::string TokenData::Mark()
{
    String   str;
    const char *B  = mLoc.Begin - mLoc.I;
    //std::string str;
    int        l   = 1;
    const char *cc = mLoc.Begin;
    // localiser le debut de la ligne;
    while(*cc && (cc > B) && (*cc != '\n') && (*cc != '\r'))
        --cc;
    // debut de la ligne ou de la source:
    if(cc >= B)
    {
        if((*cc == '\n') || (*cc == '\r'))
            ++cc;
        while(*cc && (*cc != '\n') && (*cc != '\r'))
            str += *cc++;
    }
    String tstr;
    
    tstr << str << '\n';
    for(int x = 1; x < mLoc.C; x++)
        tstr << ' ';
    tstr << '^';
    //std::cerr << tstr() << '\n';
    return tstr();
}




std::string TokenData::SemanticTypes()
{
    std::string Str;
    return Str << S;
}


std::string TokenData::TypeName()
{
    std::string Str;
    return Str << T;
}

static TokenData::Collection tokens_table = {{Mnemonic::Knull,        Type::Keyword,     0x000040000,  Type::Delta::Identifier, Lexem::Knull,        1},
                                             {Mnemonic::Lshift,       Type::Binary,      0x000C00000,  Type::Delta::Shift,      Lexem::Lshift,       1},
                                             {Mnemonic::Openabs,      Type::OpenPair,    0x080C00000,  Type::Delta::Par,        Lexem::Openabs,      1},
                                             {Mnemonic::Closeabs,     Type::ClosePair,   0x080C00000,  Type::Delta::Par,        Lexem::Closeabs,     1},
                                             {Mnemonic::Radical,      Type::Binary,      0x000C00000,  Type::Delta::Exponent,   Lexem::Radical,      1},
                                             {Mnemonic::Exponent,     Type::Binary,      0x000C00000,  Type::Delta::Exponent,   Lexem::Exponent,     1},
                                             {Mnemonic::Rshift,       Type::Binary,      0x000400000,  Type::Delta::Shift,      Lexem::Rshift,       1},
                                             {Mnemonic::Bitxor,       Type::Binary,      0x000C00000,  Type::Delta::Bits,       Lexem::Bitxor,       1},
                                             {Mnemonic::Decr,         Type::Unary,       0x000580000,  Type::Delta::Unary,      Lexem::Decr,         1},
                                             {Mnemonic::Incr,         Type::Unary,       0x000580000,  Type::Delta::Unary,      Lexem::Incr,         1},
                                             {Mnemonic::Assignadd,    Type::Assign,      0x100C40000,  Type::Delta::Assign,     Lexem::Assignadd,    1},
                                             {Mnemonic::Assignsub,    Type::Assign,      0x100C40000,  Type::Delta::Assign,     Lexem::Assignsub,    1},
                                             {Mnemonic::Assignmul,    Type::Assign,      0x100C40000,  Type::Delta::Assign,     Lexem::Assignmul,    1},
                                             {Mnemonic::Assigndiv,    Type::Assign,      0x100C40000,  Type::Delta::Assign,     Lexem::Assigndiv,    1},
                                             {Mnemonic::Assignmod,    Type::Assign,      0x100C40000,  Type::Delta::Assign,     Lexem::Assignmod,    1},
                                             {Mnemonic::Assignand,    Type::Assign,      0x100C40000,  Type::Delta::Assign,     Lexem::Assignand,    1},
                                             {Mnemonic::Assignor,     Type::Assign,      0x100C40000,  Type::Delta::Assign,     Lexem::Assignor,     1},
                                             {Mnemonic::Assignxor,    Type::Assign,      0x100C40000,  Type::Delta::Assign,     Lexem::Assignxor,    1},
                                             {Mnemonic::Assignx1,     Type::Assign,      0x100C40000,  Type::Delta::Assign,     Lexem::Assignx1,     1},
                                             {Mnemonic::Assignlshift, Type::Assign,      0x100C40000,  Type::Delta::Assign,     Lexem::Assignlshift, 1},
                                             {Mnemonic::Assignrshift, Type::Assign,      0x100C40000,  Type::Delta::Assign,     Lexem::Assignrshift, 1},
                                             {Mnemonic::Leq,          Type::Binary,      0x200C00000,  Type::Delta::Less,       Lexem::Lteq,         1},
                                             {Mnemonic::Geq,          Type::Binary,      0x200C00000,  Type::Delta::Less,       Lexem::Gteq,         1},
                                             {Mnemonic::Eq,           Type::Binary,      0x200C00000,  Type::Delta::Less,       Lexem::Eq,           1},
                                             {Mnemonic::Neq,          Type::Binary,      0x200C00000,  Type::Delta::Less,       Lexem::Neq,          1},
                                             {Mnemonic::Add,          Type::Binary,      0x000C00000,  Type::Delta::Add,        Lexem::Add,          1},
                                             {Mnemonic::Sub,          Type::Binary,      0x000C00000,  Type::Delta::Add,        Lexem::Sub,          1},
                                             {Mnemonic::Mul,          Type::Binary,      0x000C00000,  Type::Delta::Product,    Lexem::Mul,          1},
                                             {Mnemonic::Cppcomment,   Type::Punctuation, 0x00000,      Type::Delta::Noop,       Lexem::Cppcomment,   0},
                                             {Mnemonic::Modulo,       Type::Binary,      0x000C00000,  Type::Delta::Product,    Lexem::Modulo,       1},
                                             {Mnemonic::Lt,           Type::Binary,      0x200C00000,  Type::Delta::Less,       Lexem::Lt,           1},
                                             {Mnemonic::Gt,           Type::Binary,      0x200C00000,  Type::Delta::Less,       Lexem::Gt,           1},
                                             {Mnemonic::Assign,       Type::Assign,      0x100C40000,  Type::Delta::Assign,     Lexem::Assign,       1},
                                             {Mnemonic::Binand,       Type::Binary,      0x000C00000,  Type::Delta::Bits,       Lexem::Binand,       1},
                                             {Mnemonic::Binor,        Type::Binary,      0x000C00000,  Type::Delta::Bits,       Lexem::Binor,        1},
                                             {Mnemonic::X2,           Type::Prefix,      0x000580000,  Type::Delta::Prefix,     Lexem::X2,           1},
                                             {Mnemonic::X1,           Type::Prefix,      0x000580000,  Type::Delta::Prefix,     Lexem::X1,           1},
                                             {Mnemonic::Bitnot,       Type::Unary,       0x000580000,  Type::Delta::Prefix,     Lexem::Bitnot,       1},
                                             {Mnemonic::Booland,      Type::Binary,      0x200C00000,  Type::Delta::Logand,     Lexem::Booland,      1},
                                             {Mnemonic::Boolor,       Type::Binary,      0x200C00000,  Type::Delta::Logor,      Lexem::Boolor,       1},
                                             {Mnemonic::Openpar,      Type::OpenPair,    0x880C00000,  Type::Delta::Par,        Lexem::Openpar,      1},
                                             {Mnemonic::Closepar,     Type::ClosePair,   0x1080C00000, Type::Delta::Par,        Lexem::Closepar,     1},
                                             {Mnemonic::Openindex,    Type::Binary,      0x2080C00000, Type::Delta::Par,        Lexem::Openindex,    1},
                                             {Mnemonic::Closeindex,   Type::Binary,      0x4080C00000, Type::Delta::Par,        Lexem::Closeindex,   1},
                                             {Mnemonic::Openbrace,    Type::Binary,      0x880C00000,  Type::Delta::Par,        Lexem::Openbrace,    1},
                                             {Mnemonic::Closebrace,   Type::Binary,      0x1080C00000, Type::Delta::Par,        Lexem::Closebrace,   1},
                                             {Mnemonic::Bcomment,     Type::Punctuation, 0x00000,      Type::Delta::Noop,       Lexem::Bcomment,     0},
                                             {Mnemonic::Ecomment,     Type::Punctuation, 0x00000,      Type::Delta::Noop,       Lexem::Ecomment,     0},
                                             {Mnemonic::Division,     Type::Binary,      0x000C00000,  Type::Delta::Product,    Lexem::Division,     1},
                                             {Mnemonic::Comma,        Type::Binary,      0x080C00000,  Type::Delta::Comma,      Lexem::Comma,        1},
                                             {Mnemonic::Scope,        Type::Binary,      0x080C00000,  Type::Delta::Scope,      Lexem::Scope,        1},
                                             {Mnemonic::Semicolon,    Type::Punctuation, 0x080000000,  Type::Delta::Noop,       Lexem::Semicolon,    0},
                                             {Mnemonic::Colon,        Type::Binary,      0x080C00000,  Type::Delta::Noop,       Lexem::Colon,        0},
                                             {Mnemonic::Range,        Type::Binary,      0x080C00000,  Type::Delta::Scope,      Lexem::Range,        1},
                                             {Mnemonic::Factorial,    Type::Postfix,     0x000580000,  Type::Delta::Unary,      Lexem::Factorial,    1},
                                             {Mnemonic::Positive,     Type::Prefix,      0x000580020,  Type::Delta::Unary,      Lexem::Positive,     1},
                                             {Mnemonic::Negative,     Type::Prefix,      0x000580020,  Type::Delta::Unary,      Lexem::Negative,     1},
                                             {Mnemonic::Squote,       Type::Text,        0x000000012,  Type::Delta::Identifier, Lexem::Squote,       1},
                                             {Mnemonic::Dquote,       Type::Text,        0x000000012,  Type::Delta::Identifier, Lexem::Dquote,       1},
                                             {Mnemonic::Kternary,     Type::Keyword,     0x000C40000,  Type::Delta::Unary,      Lexem::Kternary,     1},
                                             {Mnemonic::Hash,         Type::Prefix,      0x000580000,  Type::Delta::Unary,      Lexem::Hash,         1},
                                             {Mnemonic::Dollard,      Type::Prefix,      0x000580000,  Type::Delta::Unary,      Lexem::Dollard,      1},
                                             {Mnemonic::Dot,          Type::Binary,      0x080C00000,  Type::Delta::Scope,      Lexem::Dot,          1},
                                             {Mnemonic::Kreturn,      Type::Keyword,     0x000040000,  Type::Delta::Identifier, Lexem::Kreturn,      0},
                                             {Mnemonic::Kif,          Type::Keyword,     0x000040000,  Type::Delta::Identifier, Lexem::Kif,          0},
                                             {Mnemonic::Kpi,          Type::Keyword,     0x000044011,  Type::Delta::Identifier, Lexem::Kpi,          1},
                                             {Mnemonic::Knumber,      Type::Prefix,      0x000540001,  Type::Delta::Identifier, Lexem::Knumber,      1},
                                             {Mnemonic::Ku8,          Type::Prefix,      0x000540400,  Type::Delta::Identifier, Lexem::Ku8,          1},
                                             {Mnemonic::Ku16,         Type::Prefix,      0x000540800,  Type::Delta::Identifier, Lexem::Ku16,         1},
                                             {Mnemonic::Ku32,         Type::Prefix,      0x000541000,  Type::Delta::Identifier, Lexem::Ku32,         1},
                                             {Mnemonic::Ku64,         Type::Prefix,      0x000542000,  Type::Delta::Identifier, Lexem::Ku64,         1},
                                             {Mnemonic::Ki8,          Type::Prefix,      0x000540040,  Type::Delta::Identifier, Lexem::Ki8,          1},
                                             {Mnemonic::Ki16,         Type::Prefix,      0x000540080,  Type::Delta::Identifier, Lexem::Ki16,         1},
                                             {Mnemonic::Ki32,         Type::Prefix,      0x000540100,  Type::Delta::Identifier, Lexem::Ki32,         1},
                                             {Mnemonic::Ki64,         Type::Prefix,      0x000540200,  Type::Delta::Identifier, Lexem::Ki64,         1},
                                             {Mnemonic::Kreal,        Type::Prefix,      0x000544000,  Type::Delta::Identifier, Lexem::Kreal,        1},
                                             {Mnemonic::Kstring,      Type::Prefix,      0x000540002,  Type::Delta::Identifier, Lexem::Kstring,      1},
                                             {Mnemonic::Kthen,        Type::Keyword,     0x000040000,  Type::Delta::Identifier, Lexem::Kthen,        0},
                                             {Mnemonic::Kelse,        Type::Keyword,     0x000040000,  Type::Delta::Identifier, Lexem::Kelse,        0},
                                             {Mnemonic::Kconst,       Type::Keyword,     0x000040000,  Type::Delta::Identifier, Lexem::Kconst,       0},
                                             {Mnemonic::Kinclude,     Type::Keyword,     0x000040000,  Type::Delta::Identifier, Lexem::Kinclude,     0},
                                             {Mnemonic::Kmodule,      Type::Keyword,     0x000040000,  Type::Delta::Identifier, Lexem::Kmodule,      0},
                                             {Mnemonic::Kat,          Type::Prefix,      0x000580000,  Type::Delta::Unary,      Lexem::Kat,          1},
                                             {Mnemonic::Kprime,       Type::Prefix,      0x000580000,  Type::Delta::Unary,      Lexem::Kprime,       1},
                                             {Mnemonic::Kdo,          Type::Keyword,     0x000040000,  Type::Delta::Noop,       Lexem::Kdo,          0},
                                             {Mnemonic::Kwhile,       Type::Keyword,     0x000040000,  Type::Delta::Noop,       Lexem::Kwhile,       0},
                                             {Mnemonic::Kfor,         Type::Keyword,     0x000040000,  Type::Delta::Noop,       Lexem::Kfor,         0},
                                             {Mnemonic::Kuntil,       Type::Keyword,     0x000040000,  Type::Delta::Noop,       Lexem::Kuntil,       0},
                                             {Mnemonic::Krepeat,      Type::Keyword,     0x000040000,  Type::Delta::Noop,       Lexem::Krepeat,      0},
                                             {Mnemonic::Kswitch,      Type::Keyword,     0x000040000,  Type::Delta::Noop,       Lexem::Kswitch,      0},
                                             {Mnemonic::Kcase,        Type::Keyword,     0x000040000,  Type::Delta::Noop,       Lexem::Kcase,        0},
                                             {Mnemonic::Ktype,        Type::Keyword,     0x000040000,  Type::Delta::Noop,       Lexem::Ktype,        0},
                                             {Mnemonic::Khex,         Type::Hex,         0x000040011,  Type::Delta::Noop,       Lexem::Khex,         1},
                                             {Mnemonic::KHex,         Type::Hex,         0x000040011,  Type::Delta::Noop,       Lexem::KHex,         1},
                                             {Mnemonic::Kcos,         Type::Prefix,      0x000580000,  Type::Delta::Unary,      Lexem::Kcos,         1},
                                             {Mnemonic::Kacos,        Type::Prefix,      0x0005C0000,  Type::Delta::Unary,      Lexem::Kacos,        1},
                                             {Mnemonic::Ktan,         Type::Prefix,      0x0005C0000,  Type::Delta::Unary,      Lexem::Ktan,         1},
                                             {Mnemonic::Katan,        Type::Prefix,      0x0005C0000,  Type::Delta::Unary,      Lexem::Katan,        1},
                                             {Mnemonic::Ksin,         Type::Prefix,      0x0005C0000,  Type::Delta::Unary,      Lexem::Ksin,         1},
                                             {Mnemonic::Kasin,        Type::Prefix,      0x0005C0000,  Type::Delta::Unary,      Lexem::Kasin,        1},
                                             {Mnemonic::Kobject,      Type::Keyword,     0x000040000,  Type::Delta::Identifier, Lexem::Kobject,      0},
                                             {Mnemonic::Kstatic,      Type::Keyword,     0x000040000,  Type::Delta::Identifier, Lexem::Kstatic,      0},
                                             {Mnemonic::Kme,          Type::Keyword,     0x000040000,  Type::Delta::Identifier, Lexem::Kme,          1}};



// It was the right one ... duh...
TokenData TokenData::Scan(const char *C_)
{
    int unicode = 0;
    int index = 0;
    
    for(auto Tok : tokens_table) {
        const char *crs = C_;
        const char *rtxt = Tok.mLoc.Begin;
        std::size_t sz = std::strlen(rtxt);
        if(*crs != *Tok.mLoc.Begin) {
            ++index;
            continue;
        }
        ++index;
        /*
         * I arbitrary assume that the UNICODE UNIT is a signed 16 bits AND THAT THE VALUE OF FIRST BYTE IS NEGATIVE.
         * Then I take the next byte to determine the unicode ...code...
         */
        while((*crs && *rtxt) && (*crs == *rtxt))
        {
            ////std::cout << *crs <<  *rtxt << ">>>";
            if(*crs < 0)
                ++unicode;
            ++crs;
            ++rtxt;
            ////std::cout << *crs << *rtxt << ','; sin0x4A
        }
        
        if(*rtxt == 0)
        {
            if(*crs && !isspace(*crs))
            {
                if(isalnum(*crs) || (*crs == '_')) continue;
            }
            
            Tok.mLoc.Begin = C_;
            Tok.mLoc.End = crs - 1;
            return Tok;
        }
    }
    return TokenData::mNull;
    
}



TokenData TokenData::operator[](Mnemonic CC)
{
    for(TokenData T : tokens_table)
    {
        if(CC == T.M)
            return T;
    }
    return TokenData::mNull;
}


std::string TokenData::Details(bool Mark_)
{
    String Str = "Details: '%s': Pos(%d,%d), %s::{%s}";
    Str << Attr() << mLoc.L << mLoc.C << TypeName() << SemanticTypes();
    if(Mark_)
        Str << '\n' << Mark();
    return Str();
}


}
