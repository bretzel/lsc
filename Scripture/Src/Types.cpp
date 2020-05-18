//
// Created by lsc on 20-05-18.
//

#include <Lsc/Scripture/Types.h>
#include <map>



namespace Lsc
{
namespace Type
{

std::map<T, std::string> T_STR = {{null,        "null"},
                                  {number,      "number"},
                                  {text,        "text"},
                                  {voidptr,     "voidptr"},
                                  {any,         "any"},
                                  {leaf,        "leaf"},
                                  {sign,        "sign"},
                                  {i8,          "i8"},
                                  {i16,         "i16"},
                                  {i32,         "i32"},
                                  {i64,         "i64"},
                                  {u8,          "u8"},
                                  {u16,         "u16"},
                                  {u32,         "u32"},
                                  {u64,         "u64"},
                                  {real,        "real"},
                                  {var,         "var"},
                                  {bloc,        "bloc"},
                                  {filo,        "filo"},
                                  {keyword,     "keyword"},
                                  {unary,       "unary"},
                                  {prefix,      "prefix"},
                                  {postfix,     "postfix"},
                                  {oper,        "operator"},
                                  {binary,      "binary"},
                                  {func,        "rtfn"},
                                  {funcptr,     "rtfn ptr"},
                                  {obj,         "object"},
                                  {pointer,     "pointer"},
                                  {type,        "t"},
                                  {id,          "identifier"},
                                  {ref,         "reference"},
                                  {punctuation, "punctuation"},
                                  {assign,      "assign"},
                                  {boolean,     "boolean"},
                                  {hex,         "hex"},
                                  {bin,         "bin"},
                                  {octal,       "oct"},
                                  {f32,         "f32"},
                                  {f64,         "f64"},
                                  {f128,        "f128"},
                                  {leftpar,     "leftpar"},
                                  {closepar,    "closepar"},
                                  {openabs,     "openabs"},
                                  {closeabs,    "closeabs"},
                                  {static_t,    "static"}};

std::map<std::string, T> STR_T = {{"null",         null},
                                  {"number",       number},
                                  {"text",         text},
                                  {"string",       text},
                                  {"voidptr",      voidptr},
                                  {"void-pointer", voidptr},
                                  {"any",          any},
                                  {"leaf",         leaf},
                                  {"sign",         sign},
                                  {"i8",           i8},
                                  {"i16",          i16},
                                  {"i32",          i32},
                                  {"i64",          i64},
                                  {"u8",           u8},
                                  {"u16",          u16},
                                  {"u32",          u32},
                                  {"u64",          u64},
                                  {"real",         real},
                                  {"var",          var},
                                  {"variable",     var},
                                  {"bloc",         bloc},
                                  {"filo",         filo},
                                  {"stack",        filo},
                                  {"keyword",      keyword},
                                  {"unary",        unary},
                                  {"prefix",       prefix},
                                  {"postfix",      postfix},
                                  {"oper",         oper},
                                  {"operator",     oper},
                                  {"binary",       binary},
                                  {"binary-op",    binary},
                                  {"func",         func},
                                  {"rtfn",         func},
                                  {"funcptr",      funcptr},
                                  {"rtfn-pointer", funcptr},
                                  {"obj",          obj},
                                  {"object",       obj},
                                  {"pointer",      pointer},
                                  {"t",            type},
                                  {"id",           id},
                                  {"identifier",   id},
                                  {"ref",          ref},
                                  {"reference",    ref},
                                  {"punctuation",  punctuation},
                                  {"assign",       assign},
                                  {"boolean",      boolean},
                                  {"hex",          hex},
                                  {"leftpar",      leftpar},
                                  {"closepar",     closepar},
                                  {"openabs",      openabs},
                                  {"closeabs",     closeabs}};
    
}
}


Lsc::String& operator << (Lsc::String& Str_, Lsc::Type::T T_)
{
    Lsc::Type::T tbm = T_;
    int a,c,b;
    
    
    for(const auto &t : Lsc::Type::T_STR) {
        if(!tbm)
            break;
        if(t.first & tbm) {
            Str_ << t.second;
            tbm &= ~t.first;
            if(tbm)
                Str_ << '/';
        }
    }
    if(Str_.Empty())
        Str_ << "null";
    return Str_;
}

std::string& operator << (std::string& Str_, Lsc::Type::T T_)
{
    Lsc::Type::T tbm = T_;
    int a,c,b;
    
    
    for(const auto &t : Lsc::Type::T_STR) {
        if(!tbm)
            break;
        if(t.first & tbm) {
            Str_ += t.second;
            tbm &= ~t.first;
            if(tbm)
                Str_ += '/';
        }
    }
    if(Str_.empty())
        Str_ += "null";
    return Str_;
}



/*!
 * @brief Overload input operator
 *
 * Provides building Semantic [Lsc::]Types from string:
 *
 * @code
 *   //...
 *   Lsc::Type::T Sem;
 *   Sem << "number/real";
 * @endcode
 * @param T_
 * @param TStr_
 * @return
 */
Lsc::Type::T &operator<<(Lsc::Type::T &T_, const std::string &TStr_)
{
    Lsc::String::Word::Collection Array;
    Lsc::String names = TStr_;
    
    T_ = 0;
    std::size_t count = names.Words(Array, "/", false);
    if(count > 0) {
        for(auto s : Array) {
            std::string txt = s();
            T_ |= Lsc::Type::STR_T[txt];
        }
    }
    
    return T_;
}
