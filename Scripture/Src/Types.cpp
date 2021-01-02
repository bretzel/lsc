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
                                  {Leaf,        "Leaf"},
                                  {Sign,        "Sign"},
                                  {I8,          "I8"},
                                  {I16,         "I16"},
                                  {I32,         "I32"},
                                  {I64,         "I64"},
                                  {U8,          "U8"},
                                  {U16,         "U16"},
                                  {U32,         "U32"},
                                  {U64,         "U64"},
                                  {Float,       "Float"},
                                  {Var,         "Var"},
                                  {Bloc,        "Bloc"},
                                  {Filo,        "Filo"},
                                  {Keyword,     "Keyword"},
                                  {Unary,       "Unary"},
                                  {Prefix,      "Prefix"},
                                  {Postfix,     "Postfix"},
                                  {Operator,    "Operator"},
                                  {Binary,      "Binary"},
                                  {Function,    "Rtfn"},
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
                                  {"Leaf",         Leaf},
                                  {"Sign",         Sign},
                                  {"I8",           I8},
                                  {"I16",          I16},
                                  {"I32",          I32},
                                  {"I64",          I64},
                                  {"U8",           U8},
                                  {"U16",          U16},
                                  {"U32",          U32},
                                  {"U64",          U64},
                                  {"Float",        Float},
                                  {"Var",          Var},
                                  {"Variable",     Var},
                                  {"Bloc",         Bloc},
                                  {"Filo",         Filo},
                                  {"Stack",        Filo},
                                  {"Keyword",      Keyword},
                                  {"Unary",        Unary},
                                  {"Prefix",       Prefix},
                                  {"Postfix",      Postfix},
                                  {"Operator",     Operator},
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
 
std::string Name(T T_)
{
    std::string Str_;
    
    if(T_ >= Lsc::Type::Bin)
    {
        Str_ += "*.*";
        return Str_;
    }
    
    Lsc::Type::T tbm = T_;
    int          a, c, b;
    
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

T    SCRIPTURE_LIB FromStr(String Str)
{
    T types = 0;
    
}

}}

namespace Lsc
{

std::string MnemonicName(Mnemonic M)
{
    std::map<Mnemonic, std::string_view> _ = {{Mnemonic::Knull,        "Knull"},
                                              {Mnemonic::Lshift,       "Lshift,"},
                                              {Mnemonic::Radical,      "Radical,"},
                                              {Mnemonic::Exponent,     "Exponent,"},
                                              {Mnemonic::Rshift,       "Rshift,"},
                                              {Mnemonic::Decr,         "Decr"},
                                              {Mnemonic::Incr,         "Incr"},
                                              {Mnemonic::Assignadd,    "Assignadd"},
                                              {Mnemonic::Assignsub,    "Assignsub"},
                                              {Mnemonic::Assignmul,    "Assignmul"},
                                              {Mnemonic::Assigndiv,    "Assigndiv"},
                                              {Mnemonic::Assignmod,    "Assignmod"},
                                              {Mnemonic::Assignand,    "Assignand"},
                                              {Mnemonic::Assignor,     "Assignor"},
                                              {Mnemonic::Assignxor,    "Assignxor"},
                                              {Mnemonic::Assignx1,     "Assignx1"},
                                              {Mnemonic::Assignlshift, "Assignlshift"},
                                              {Mnemonic::Assignrshift, "Assignrshift"},
                                              {Mnemonic::Leq,          "Leq"},
                                              {Mnemonic::Geq,          "Geq"},
                                              {Mnemonic::Eq,           "Eq"},
                                              {Mnemonic::Neq,          "NEq"},
                                              {Mnemonic::Add,          "Add"},
                                              {Mnemonic::Sub,          "Sub"},
                                              {Mnemonic::Mul,          "Mul"},
                                              {Mnemonic::Cppcomment,   "Cppcomment"},
                                              {Mnemonic::Modulo,       "Modulo"},
                                              {Mnemonic::Lt,           "Lt"},
                                              {Mnemonic::Gt,           "Gt"},
                                              {Mnemonic::Assign,       "Assign"},
                                              {Mnemonic::Binand,       "Binand"},
                                              {Mnemonic::Binor,        "Binor"},
                                              {Mnemonic::Bitxor,       "Bitxor"},
                                              {Mnemonic::X1,           "X1,           // complement a 1"},// complement a 1
                                              {Mnemonic::X2,           "X2"},
                                              {Mnemonic::Bitnot,       "Bitnot,          //"},   //
                                              {Mnemonic::Booland,      "Booland"},
                                              {Mnemonic::Boolor,       "Boolor"},
                                              {Mnemonic::Openabs,      "Openabs"},
                                              {Mnemonic::Closeabs,     "Closeabs"},
                                              {Mnemonic::Openpar,      "Openpar"},
                                              {Mnemonic::Closepar,     "Closepar"},
                                              {Mnemonic::Openindex,    "Openindex"},
                                              {Mnemonic::Closeindex,   "Closeindex"},
                                              {Mnemonic::Openbrace,    "Openbrace"},
                                              {Mnemonic::Closebrace,   "Closebrace"},
                                              {Mnemonic::Bcomment,     "Bcomment"},
                                              {Mnemonic::Ecomment,     "Ecomment"},
                                              {Mnemonic::Division,     "Division"},
                                              {Mnemonic::Comma,        "Comma"},
                                              {Mnemonic::Scope,        "Scope"},
                                              {Mnemonic::Semicolon,    "Semicolon"},
                                              {Mnemonic::Colon,        "Colon"},
                                              {Mnemonic::Range,        "Range"},
                                              {Mnemonic::Factorial,    "Factorial"},
                                              {Mnemonic::Positive,     "Positive"},
                                              {Mnemonic::Negative,     "Negative"},
                                              {Mnemonic::Squote,       "Squote"},
                                              {Mnemonic::Dquote,       "Dquote"},
                                              {Mnemonic::Kternary,     "Kternary"},
                                              {Mnemonic::Hash,         "Hash"},
                                              {Mnemonic::Dollard,      "Dollard"},
                                              {Mnemonic::Dot,          "Dot"},
                                              {Mnemonic::Kreturn,      "Kreturn"},
                                              {Mnemonic::Kif,          "Kif"},
                                              {Mnemonic::Kpi,          "Kpi"},
                                              {Mnemonic::Knumber,      "Knumber"},
                                              {Mnemonic::Ku8,          "Ku8"},
                                              {Mnemonic::Ku16,         "Ku16"},
                                              {Mnemonic::Ku32,         "Ku32"},
                                              {Mnemonic::Ku64,         "Ku64"},
                                              {Mnemonic::Ki8,          "Ki8"},
                                              {Mnemonic::Ki16,         "Ki16"},
                                              {Mnemonic::Ki32,         "Ki32"},
                                              {Mnemonic::Ki64,         "Ki64"},
                                              {Mnemonic::Kreal,        "Kreal"},
                                              {Mnemonic::Kstring,      "Kstring"},
                                              {Mnemonic::Kthen,        "Kthen"},
                                              {Mnemonic::Kelse,        "Kelse"},
                                              {Mnemonic::Kconst,       "Kconst"},
                                              {Mnemonic::Kinclude,     "Kinclude"},
                                              {Mnemonic::Kmodule,      "Kmodule"},
                                              {Mnemonic::Kat,          "Kat"},
                                              {Mnemonic::Kprime,       "Kprime"},
                                              {Mnemonic::Kdo,          "Kdo"},
                                              {Mnemonic::Kwhile,       "Kwhile"},
                                              {Mnemonic::Kfor,         "Kfor"},
                                              {Mnemonic::Kuntil,       "Kuntil"},
                                              {Mnemonic::Krepeat,      "Krepeat"},
                                              {Mnemonic::Kswitch,      "Kswitch"},
                                              {Mnemonic::Kcase,        "Kcase"},
                                              {Mnemonic::Ktype,        "Ktype"},
                                              {Mnemonic::Khex,         "Khex"},
                                              {Mnemonic::KHex,         "KHex"},
                                              {Mnemonic::Kcos,         "Kcos"},
                                              {Mnemonic::Kacos,        "Kacos"},
                                              {Mnemonic::Ktan,         "Ktan"},
                                              {Mnemonic::Katan,        "Katan"},
                                              {Mnemonic::Ksin,         "Ksin"},
                                              {Mnemonic::Kasin,        "Kasin"},
                                              {Mnemonic::Kobject,      "Kobject"},
                                              {Mnemonic::Kstatic,      "Kstatic"},
                                              {Mnemonic::Kme,          "Kme"},
                                              {Mnemonic::Noop,         "Noop"}};
    return std::string(_[M]);
}
    
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
    Lsc::String                   names = TStr_;
    
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
    if(T_ >= Lsc::Type::Bin)
    {
        Str_ += "*.*";
        return Str_;
    }
    
    Lsc::Type::T tbm = T_;
    int          a, c, b;
    
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
