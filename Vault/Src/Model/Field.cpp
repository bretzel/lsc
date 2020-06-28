//#include <Lsc/Vault/Model/Field.h>
#include <Lsc/Vault/Model/Table.h>
#include <Lsc/Vault/Model/Field.h>
#include <map>

namespace Lsc::Vault
{


CLASSNAME_IMPL(Field)



Field::Field(Table *Table_, std::string Name_): mName(std::move(Name_))
{

}

Field::Field(std::string Name_, Field::Type Type_, Field::Attr Attr_):
mName(std::move(Name_)),
mType(Type_),
mAttr(Attr_)
{}

Field::Field(std::string Name_, Field::Type Type_):
mName(Name_),
mType(Type_)
{

}
Field::Attr Field::SetAttributes(uint8_t Attr_)
{
    mAttr = {0};
    if(Attr_ & Field::PKAUTO)
    {
        mAttr.Primary = 1;
        mAttr.Auto    = 1;
    }
    if(Attr_ & Field::Unique)
        mAttr.Unique = 1;
    if(Attr_ & Field::Null)
        mAttr.Null = 1;
    if(Attr_ & Field::Index)
        mAttr.Index = 1;
    if(Field::FK & Attr_)
        mAttr.FK = 1;
        
    return mAttr;
}


String Field::Serialize()
{
    std::map<Field::Type, const char*> Types =
    {
        {Field::Type::NUL,       "NULL"},
        {Field::Type::TEXT,      "TEXT"},
        {Field::Type::NUMERIC,   "NUMERIC"},
        {Field::Type::INTEGER,   "INTEGER"},
        {Field::Type::REAL,      "REAL"},
        {Field::Type::RAW,       "BLOB"},
        {Field::Type::CHAR,      "TEXT"},
        {Field::Type::DATE,      "INTEGER"},
        {Field::Type::TIME,      "INTEGER"},
        {Field::Type::STAMP,     "INTEGER"},
        {Field::Type::STRING,    "TEXT"},
        {Field::Type::CURRENCY,  "NUMERIC"}
  
    };
    
    String Str = mName;
    Str << ' ' << Types[mType];
    if(mLen > 0)
        Str << '(' << mLen << ") ";
    else
        Str << ' ';
    
    Str << (mAttr.Primary ? "PRIMARY KEY " : mAttr.Unique ? "UNIQUE " : !mAttr.Null ? "NOT NULL " : mAttr.FK ? "FOREIGN KEY " :" ");
    if(mAttr.Auto)
        Str << " AUTOINCREMENT ";
    
    return Str;
}

}

