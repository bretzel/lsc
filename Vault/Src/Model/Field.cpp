//#include <Lsc/Vault/Model/Field.h>
#include <Lsc/Vault/Model/Table.h>
#include <Lsc/Vault/Model/Field.h>
#include <map>



/*
 int sqlite3_table_column_metadata(
  sqlite3 *db,                * Connection handle *
  const char *zDbName,        * Database name or NULL
  const char *zTableName,     * Table name *
  const char *zColumnName,    * Column name *
  char const **pzDataType,    * OUTPUT: Declared data type *
  char const **pzCollSeq,     * OUTPUT: Collation sequence name *
  int *pNotNull,              * OUTPUT: True if NOT NULL constraint exists *
  int *pPrimaryKey,           * OUTPUT: True if column part of PK *
  int *pAutoinc               * OUTPUT: True if column is auto-increment *
);
The sqlite3_table_column_metadata(X,D,T,C,....) routine returns information about column C of table T in database D on database connection X. The sqlite3_table_column_metadata() interface returns SQLITE_OK and fills in the non-NULL pointers in the final five arguments with appropriate values if the specified column exists. The sqlite3_table_column_metadata() interface returns SQLITE_ERROR if the specified column does not exist. If the column-name parameter to sqlite3_table_column_metadata() is a NULL pointer, then this routine simply checks for the existence of the table and returns SQLITE_OK if the table exists and SQLITE_ERROR if it does not. If the table name parameter T in a call to sqlite3_table_column_metadata(X,D,T,C,...) is NULL then the result is undefined behavior.

The column is identified by the second, third and fourth parameters to this function. The second parameter is either the name of the database (i.e. "main", "temp", or an attached database) containing the specified table or NULL. If it is NULL, then all attached databases are searched for the table using the same algorithm used by the database engine to resolve unqualified table references.

The third and fourth parameters to this function are the table and column name of the desired column, respectively.

Metadata is returned by writing to the memory locations passed as the 5th and subsequent parameters to this function. Any of these arguments may be NULL, in which case the corresponding element of metadata is omitted.

Parameter	Output
Type	Description
5th	const char*	Data type
6th	const char*	Name of default collation sequence
7th	int	True if column has a NOT NULL constraint
8th	int	True if column is part of the PRIMARY KEY
9th	int	True if column is AUTOINCREMENT
The memory pointed to by the character pointers returned for the declaration type and collation sequence is valid until the next call to any SQLite API function.

If the specified table is actually a view, an error code is returned.

If the specified column is "rowid", "oid" or "_rowid_" and the table is not a WITHOUT ROWID table and an INTEGER PRIMARY KEY column has been explicitly declared, then the output parameters are set for the explicitly declared column. If there is no INTEGER PRIMARY KEY column, then the outputs for the rowid are set as follows:

data type: "INTEGER"
collation sequence: "BINARY"
not null: 0
primary key: 1
auto increment: 0
This function causes all database schemas to be read from disk and parsed, if that has not already been done, and returns an error if any errors are encountered while loading the schema.
 */
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

uint8_t Field::SetAttributes(uint8_t Attr_)
{
    mAttr = Attr_;
    String StrDebug = "%08b -> %08b";
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
    //String DebugStr = "%08b";
    //DebugStr << *(uint8_t*)&mAttr;
    
    if(mLen > 0)
        Str << '(' << mLen << ") ";
    else
        Str << ' ';
    
    if(mAttr & Field::FK)
    {
        Str.Clear(); /// vider le contenu de la String...
        Str << "FOREIGN KEY(" << mName << ") REFERENCES " << mFkTableName << '(' << mFkFieldName << ')';
        return Str;
    }
    
    Str << (mAttr & Field::PK ? "PRIMARY KEY " : mAttr & Unique ? "UNIQUE " : "");
    
    if(mAttr & PKAUTO)
        Str << "AUTOINCREMENT ";
    else
    {
        if(mAttr & NotNull)
            Str << "NOT NULL ";
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
    mAttr = 0;
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
    
    mAttr |= (SI_[3].second[0] == '1' ? Field::NotNull : 0);
    mDflt = SI_[4].second;
    
    mAttr = mAttr | (SI_[5].second[0] == '1' ? Field::PK :0);
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
    mAttr |= Field::FK;
    mFkFieldName = Field_;
    mFkTableName = Table_;
    return Rem::Int::Ok;
    ///@note Pour l'instant on se contente de ca...
}


Field::Field(Table *Table_, std::string&& Name_, Field::Type Type_, uint8_t AttrBits_)
{
    mAttr  = AttrBits_;
    mName  = std::move(Name_);
    mTable = Table_;
    mType  = Type_;
}

std::string Field::TableName() const
{
    return mName();
}

}

