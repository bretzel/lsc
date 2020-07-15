//#include <Lsc/Vault/Model/Field.h>
#include <Lsc/Vault/Model/Table.h>
#include <Lsc/Vault/Model/Field.h>
#include <map>

namespace Lsc::Vault
{

CLASSNAME_IMPL(Field)

Field::Field(Table *Table_, std::string Name_) : mName(std::move(Name_))
{

}

Field::Field(std::string Name_, Field::Type Type_, Field::Attr Attr_) : mName(std::move(Name_)), mType(Type_), mAttr(Attr_)
{

}

//Field::Field(std::string Name_, Field::Type Type_):
//mName(Name_),
//mType(Type_)
//{
//
//}

Field::Attr Field::SetAttributes(uint8_t Attr_)
{
    mAttr            = {0};
    String StrDebug = "%08b -> %08b";
    if(Attr_ & Field::PKAUTO)
    {
        mAttr.Primary = 1;
        mAttr.Auto    = 1;
    }
    if(Attr_ & Field::Unique)
        mAttr.Unique = 1;
    if(Attr_ & Field::Null)
        mAttr.Null   = 1;
    if(Attr_ & Field::Index)
        mAttr.Index  = 1;
    if(Field::FK & Attr_)
        mAttr.FK     = 1;
    
    Field::Attr AA = {Attr_};
    StrDebug << *(uint8_t*)&AA << *(uint8_t*)&mAttr;
    
    Rem::Debug() << __PRETTY_FUNCTION__ << " :Test:  {" << StrDebug() << "}:";
    return mAttr;
}


String Field::Serialize()
{
    std::map<Field::Type, const char *> Types = {{Field::Type::NUL,      "NULL"},
                                                 {Field::Type::TEXT,     "TEXT"},
                                                 {Field::Type::NUMERIC,  "NUMERIC"},
                                                 {Field::Type::INTEGER,  "INTEGER"},
                                                 {Field::Type::REAL,     "REAL"},
                                                 {Field::Type::RAW,      "BLOB"},
                                                 {Field::Type::CHAR,     "TEXT"},
                                                 {Field::Type::DATE,     "INTEGER"},
                                                 {Field::Type::TIME,     "INTEGER"},
                                                 {Field::Type::STAMP,    "INTEGER"},
                                                 {Field::Type::STRING,   "TEXT"},
                                                 {Field::Type::CURRENCY, "NUMERIC"}
        
    };
    
    String Str = mName;
    Str << ' ' << Types[mType];
    
    String Debug = "%08b";
    Debug << *(uint8_t*)&mAttr;
    Rem::Debug() << __PRETTY_FUNCTION__ << ": Attr: {" << Debug() << '}';
    if(mLen > 0)
        Str << '(' << mLen << ") ";
    else
        Str << ' ';
    
    if(mAttr.FK)
    {
        Str.Clear(); /// vider le contenu de la String...
        Str << "FOREIGN KEY(" << mName << ") REFERENCES " << mFkTableName << '(' << mFkFieldName << ')';
        return Str;
    }
    
    Str << (mAttr.Primary ? "PRIMARY KEY " : mAttr.Unique ? "UNIQUE " : "");
    
    if(mAttr.Auto)
        Str << "AUTOINCREMENT ";
    else
    {
        if(mAttr.Null)
            Str << "NULL ";
    }
    
    return Str;
}

/*!
 * @brief Construct a Field from the Table::PullSchema()
 *
 * @param Table_ Table instance this Field belongs.
 * @param SI_    SchemaInfo set.
 */
Field::Field(Table *Table_, const Field::SchemaInfo &SI_) : mTable(Table_)
{
    String Txt = SI_[0].second;
    Txt >> CID;
    mName = SI_[1].second;
    Txt   = SI_[2].second; // Type
    std::map<std::string, Field::Type> _ = {{"TEXT",    Field::Type::TEXT},
                                            {"NUMERIC", Field::Type::NUMERIC},
                                            {"INTEGER", Field::Type::INTEGER},
                                            {"REAL",    Field::Type::REAL},
                                            {"BLOB",    Field::Type::RAW}};
    
    mType = _[Txt()];
    _.clear();
    
    mAttr.Null = (SI_[3].second[0] != '1' ? 1 : 0);
    mDflt = SI_[4].second;
    mAttr.Primary = (SI_[5].second[0] == '1' ? 1 : 0);
    
    //sqlite3* H = mTable->DB();
    
}
Field::~Field()
{
    String Str;
    Str << '[';
    if(mTable)
        Str << mTable->Name() << ':';
    Str << mName << ']';
    Rem::Debug() << __PRETTY_FUNCTION__ << Str;
    mName.Clear();
    mDflt.Clear();
    mDesc.Clear();
}
Return Field::SetReference(const String &Table_, const String &Field_)
{
    mAttr.FK = 1;
    mFkFieldName = Field_;
    mFkTableName = Table_;
    return Rem::Int::Ok;
    ///@note Pour l'instant on se contente de ca...
}
Field::Field(Table *Table_, std::string&& Name_, Field::Type Type_, uint8_t AttrBits_)
{
    mAttr  = {AttrBits_};
    mName  = std::move(Name_);
    mTable = Table_;
    mType  = Type_;
}

}

