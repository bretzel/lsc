//
// Created by lsc on 20-05-18.
//

#include <Lsc/Scripture/Types.h>
#include <map>



namespace Lsc
{

namespace Type
{

std::map<T, std::string> T_STR = {{Null,        "Null"},
                                  {Number,      "Number"},
                                  {Text,        "Text"},
                                  {Voidptr,     "Voidptr"},
                                  {Any,         "Any"},
                                  {Leaf,     "Leaf"},
                                  {Sign,     "Sign"},
                                  {I8,       "I8"},
                                  {I16,      "I16"},
                                  {I32,      "I32"},
                                  {I64,      "I64"},
                                  {U8,       "U8"},
                                  {U16,      "U16"},
                                  {U32,      "U32"},
                                  {U64,      "U64"},
                                  {Float,    "Float"},
                                  {Var,      "Var"},
                                  {Bloc,     "Bloc"},
                                  {Filo,     "Filo"},
                                  {Keyword,  "Keyword"},
                                  {Unary,    "Unary"},
                                  {Prefix,   "Prefix"},
                                  {Postfix,  "Postfix"},
                                  {Operator, "Operator"},
                                  {Binary,   "Binary"},
                                  {Function, "Rtfn"},
                                  {FunctionPtr, "Rtfn ptr"},
                                  {Object,      "Object"},
                                  {Pointer,     "Pointer"},
                                  {TypeId,      "TypeId"},
                                  {Id,          "Identifier"},
                                  {Ref,         "Reference"},
                                  {Punctuation, "Punctuation"},
                                  {Assign,      "Assign"},
                                  {Boolean,     "Boolean"},
                                  {Hex,         "Hex"},
                                  {Bin,         "Bin"},
                                  {Octal,       "Oct"},
                                  {F32,         "F32"},
                                  {F64,         "F64"},
                                  {F128,        "F128"},
                                  {OpenPair,    "OpenPair"},
                                  {ClosePair,   "ClosePair"},
                                  {Static,      "Static"}};

std::map<std::string, T> STR_T = {{"Null",         Null},
                                  {"Number",       Number},
                                  {"Text",         Text},
                                  {"String",       Text},
                                  {"Voidptr",      Voidptr},
                                  {"Void-pointer", Voidptr},
                                  {"Any",          Any},
                                  {"Leaf",     Leaf},
                                  {"Sign",     Sign},
                                  {"I8",       I8},
                                  {"I16",      I16},
                                  {"I32",      I32},
                                  {"I64",      I64},
                                  {"U8",       U8},
                                  {"U16",      U16},
                                  {"U32",      U32},
                                  {"U64",      U64},
                                  {"Float",     Float},
                                  {"Var",      Var},
                                  {"Variable", Var},
                                  {"Bloc",     Bloc},
                                  {"Filo",     Filo},
                                  {"Stack",    Filo},
                                  {"Keyword",  Keyword},
                                  {"Unary",    Unary},
                                  {"Prefix",   Prefix},
                                  {"Postfix",  Postfix},
                                  {"Operator", Operator},
                                  {"Binary",       Binary},
                                  {"Binary-op",    Binary},
                                  {"Func",         Function},
                                  {"Rtfn",         FunctionPtr},
                                  {"Funcptr",      FunctionPtr},
                                  {"Rtfn-pointer", FunctionPtr},
                                  {"Obj",          Object},
                                  {"Object",       Object},
                                  {"Pointer",      Pointer},
                                  {"TypeId",       TypeId},
                                  {"Id",           Id},
                                  {"Identifier",   Id},
                                  {"Ref",          Ref},
                                  {"Reference",    Ref},
                                  {"Punctuation",  Punctuation},
                                  {"Assign",       Assign},
                                  {"Boolean",      Boolean},
                                  {"Hex",          Hex},
                                  {"Leftpar",      OpenPair},
                                  {"Closepar",     ClosePair}};
    
}}



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
    if(count > 0)
    {
        for(auto s : Array)
        {
            std::string txt = s();
            T_ |= Lsc::Type::STR_T[txt];
        }
    }
    
    return T_;
    
}

std::string &operator<<(std::string &Str_, Lsc::Type::T T_)
{
    Lsc::Type::T tbm = T_;
    int a, c, b;
    
    for(const auto &t : Lsc::Type::T_STR)
    {
        if(!tbm)
            break;
        if(t.first & tbm)
        {
            Str_ += t.second;
            tbm &= ~t.first;  // Remove the Bit from the "Sem" field.
            if(tbm)
                Str_ += '/';
        }
    }
    if(Str_.empty())
        Str_ += "null";
    return Str_;
}
