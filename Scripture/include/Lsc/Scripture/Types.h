//
// Created by lsc on 20-05-18.
//

#pragma once

#include <Lsc/Scripture/Lib.h>
#include <Lsc/Rem/String.h>

namespace Lsc
{

namespace Type
{
using T = uint64_t;
constexpr T Null        = 0x1000000000000000;
constexpr T Number      = 0x000000001;
constexpr T Text        = 0x000000002;
constexpr T Voidptr     = 0x000000004;
constexpr T Any         = 0x000000008;
constexpr T Leaf     = 0x000000010;
constexpr T Sign     = 0x000000020;
constexpr T I8       = 0x000000040;
constexpr T I16      = 0x000000080; // 0x7F41
constexpr T I32      = 0x000000100;
constexpr T I64      = 0x000000200;
constexpr T U8       = 0x000000400;
constexpr T U16      = 0x000000800;
constexpr T U32      = 0x000001000;
constexpr T U64      = 0x000002000;
constexpr T Float    = 0x000004000; // real: f32, f64, f128... ^^
constexpr T Var      = 0x000008000; // Ne pas oublier d'ajouter ce type a toutes "variables"
constexpr T Bloc     = 0x000010000;
constexpr T Filo     = 0x000020000;
constexpr T Keyword  = 0x000040000;
constexpr T Unary    = 0x000080000;
constexpr T Prefix   = 0x000100000;
constexpr T Postfix  = 0x000200000;
constexpr T Operator = 0x000400000;
constexpr T Binary   = 0x000800000;
constexpr T Function = 0x001000000;
constexpr T FunctionPtr = 0x002000000;
constexpr T Object      = 0x004000000;
constexpr T Pointer     = 0x008000000;
constexpr T TypeId      = 0x010000000;
constexpr T Id          = 0x020000000;
constexpr T Ref         = 0x040000000;
constexpr T Punctuation = 0x080000000;
constexpr T Assign      = 0x100000000;
constexpr T Boolean     = 0x200000000;
constexpr T Hex         = 0x400000000;
constexpr T OpenPair    = 0x800000000;
constexpr T ClosePair   = 0x1000000000;
//constexpr T Openabs = 0x2000000000;
//constexpr T Closeabs = 0x4000000000;
constexpr T Static      = 0x8000000000; ///< Flag set at the parser phase when applicable.
constexpr T F32         = 0x10000000000;
constexpr T F64         = 0x20000000000;
constexpr T F128        = 0x40000000000;
constexpr T Octal       = 0x80000000000;
constexpr T Bin         = 0x100000000000;

//std::string Name(T T_);
}

enum class Mnemonic : uint16_t
{
    Knull = 0,
    Lshift,
    Radical,
    Exponent,
    Rshift,
    Decr,
    Incr,
    Assignadd,
    Assignsub,
    Assignmul,
    Assigndiv,
    Assignmod,
    Assignand,
    Assignor,
    Assignxor,
    Assignx1,
    Assignlshift,
    Assignrshift,
    Leq,
    Geq,
    Eq,
    Neq,  // != <>
    Add,
    Sub,
    Mul,
    Cppcomment,
    Modulo,
    Lt,
    Gt,
    Assign,
    Binand,
    Binor,
    Bitxor,
    X1,           // complement a 1
    X2,
    Bitnot,          //
    Booland,
    Boolor,
    Openabs,
    Closeabs,
    Openpar,
    Closepar,
    Openindex,
    Closeindex,
    Openbrace,
    Closebrace,
    Bcomment,
    Ecomment,
    Division,
    Comma,
    Scope,
    Semicolon,
    Colon,
    Range,
    Factorial,
    Positive,
    Negative,
    Squote, // '
    Dquote, // "
    Kternary, // ? :
    Hash, // #
    Dollard,
    Dot,
    Kreturn,
    Kif,
    Kpi,
    Knumber,
    Ku8,
    Ku16,
    Ku32,
    Ku64,
    Ki8,
    Ki16,
    Ki32,
    Ki64,
    Kreal,
    Kstring,
    Kthen,
    Kelse,
    Kconst,
    Kinclude,
    Kmodule,
    Kat,
    Kprime,
    Kdo,
    Kwhile,
    Kfor,
    Kuntil,
    Krepeat,
    Kswitch,
    Kcase,
    Ktype,
    Khex,
    KHex,
    Kcos,
    Kacos,
    Ktan,
    Katan,
    Ksin,
    Kasin,
    Kobject,
    Kstatic,
    Kme,
    Noop
};

namespace Type::Delta
{
using T = uint8_t;
constexpr T Scope      = 0;
constexpr T Assign_rs  = 1;
constexpr T Unary      = 2;
constexpr T Prefix     = 3;
constexpr T Deref      = 4;
constexpr T Par        = 5;
constexpr T Exponent   = 6;
constexpr T Product    = 7;
constexpr T Bits       = 8;
constexpr T Add        = 9;
constexpr T Shift      = 10;
constexpr T Less       = 11;
constexpr T Comp       = 12;
constexpr T Logand     = 13;
constexpr T Logxor     = 14;
constexpr T Logor      = 15;
constexpr T Boolean    = 16;
constexpr T Ternary    = 17;
constexpr T Comma      = 18;
constexpr T Identifier = 19;
constexpr T Assign     = 20; // a = b + c = 0 - 1
constexpr T Noop       = 21;
}

namespace Lexem
{

using T = const char *;
constexpr T Knull        = "null";
constexpr T Lshift       = "<<";
constexpr T Radical      = "^/";
constexpr T Exponent     = "^";
constexpr T Rshift       = ">>";
constexpr T Decr         = "--";
constexpr T Incr         = "++";
constexpr T Assignadd    = "+=";
constexpr T Assignsub    = "-=";
constexpr T Assignmul    = "*=";
constexpr T Assigndiv    = "/=";
constexpr T Assignmod    = "%=";
constexpr T Assignand    = "&=";
constexpr T Assignor     = "|=";
constexpr T Assignxor    = "><=";
constexpr T Assignx1     = "`=";
constexpr T Assignlshift = "<<=";
constexpr T Assignrshift = ">>=";
constexpr T Lteq         = "<=";
constexpr T Gteq         = ">=";
constexpr T Eq           = "==";
constexpr T Neq          = "!=";  // != <>
constexpr T Add          = "+";
constexpr T Sub          = "-";
constexpr T Mul          = "*";
constexpr T Cppcomment   = "//";
constexpr T Modulo       = "%";
constexpr T Bitxor       = "><";
constexpr T Lt           = "<";
constexpr T Gt           = ">";
constexpr T Assign       = "=";
constexpr T Binand       = "&";
constexpr T Binor        = "|";
constexpr T X1           = "`"; ///< compl&eacute;ment &agrave; 1
constexpr T X2           = "``";///< compl&eacute;ment &agrave; 2
constexpr T Bitnot       = "!";
constexpr T Booland      = "&&";
constexpr T Boolor       = "||";
constexpr T Openabs      = "|<";// |< expr >|
constexpr T Closeabs     = ">|";
constexpr T Openpar      = "(";
constexpr T Closepar     = ")";
constexpr T Openindex    = "[";
constexpr T Closeindex   = "]";
constexpr T Openbrace    = "{";
constexpr T Closebrace   = "}";
constexpr T Bcomment     = "/*";
constexpr T Ecomment     = "*/";
constexpr T Division     = "/";
constexpr T Comma        = ",";
constexpr T Scope        = "::";
constexpr T Semicolon    = ";";
constexpr T Colon        = ":";
constexpr T Range        = "..";
constexpr T Factorial    = "!";
constexpr T Positive     = "+";
constexpr T Negative     = "-";
constexpr T Squote       = "'";  // '
constexpr T Dquote       = "\""; // "
constexpr T Kternary     = "?";  // ? :
constexpr T Hash         = "#";  // #
constexpr T Dollard      = "$";
constexpr T Dot          = ".";
constexpr T Kreturn      = "return";
constexpr T Kif          = "if";
constexpr T Kpi          = "pi";
constexpr T Knumber      = "number";
constexpr T Ku8          = "u8";
constexpr T Ku16         = "u16";
constexpr T Ku32         = "u32";
constexpr T Ku64         = "u64";
constexpr T Ki8          = "i8";
constexpr T Ki16         = "i16";
constexpr T Ki32         = "i32";
constexpr T Ki64         = "i64";
constexpr T Kreal        = "real";
constexpr T Kstring      = "string";
constexpr T Kthen        = "then";
constexpr T Kelse        = "else";
constexpr T Kconst       = "const";
constexpr T Kinclude     = "include";
constexpr T Kmodule      = "module";
constexpr T Kat          = "@";
constexpr T Kprime       = "`";
constexpr T Kdo          = "do";
constexpr T Kwhile       = "while";
constexpr T Kfor         = "for";
constexpr T Kuntil       = "until";
constexpr T Krepeat      = "repeat";
constexpr T Kswitch      = "switch";
constexpr T Kcase        = "case";
constexpr T Ktype        = "type";
constexpr T Khex         = "0x";
constexpr T KHex         = "0X";
constexpr T Kcos         = "cos";
constexpr T Kacos        = "acos";
constexpr T Ktan         = "tan";// tan(4*a*c)  - sin(4ac) sina
constexpr T Katan        = "atan";
constexpr T Ksin         = "sin";
constexpr T Kasin        = "asin";
constexpr T Kobject      = "object";
constexpr T Kstatic      = "static";
constexpr T Kme          = "me";

}



}
std::string SCRIPTURE_LIB &operator<<(std::string &, Lsc::Type::T);
Lsc::Type::T SCRIPTURE_LIB  &operator<<(Lsc::Type::T &T_, const std::string &TStr_);
//#endif //LSC_TYPES_H
