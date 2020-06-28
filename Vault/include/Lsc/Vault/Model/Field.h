#pragma once
#include <Lsc/Vault/Lib.h>
#include <Lsc/Rem/Rem.h>

namespace Lsc::Vault
{


class Table;

/*!
    @brief  Renferme les informations sur la colonne du schema sqlite3 et du modele.

    
*/
class VAULT_LIB Field
{

DECLOBJ_ID

    String mName; ///< Nom de la colonne de la table du schema sqlite3 - ET - d'un item du Modele donne par le nom de la classe. ( CLASSNAME_IMPL )
    String mDesc; ///< Description de la colonne.
    Table* mTable = nullptr;

public:
    
    using Collection = std::vector<Field>;
    
    enum class Type : uint8_t
    {
        NUL = 0,
        TEXT,
        NUMERIC,
        INTEGER,
        REAL,
        RAW,
        CHAR,
        DATE = 100,
        TIME,
        STAMP,
        STRING,
        CURRENCY
    };
    uint32_t mLen = 0;
    /*!
     * @brief Not necessarely exclusive (merged) serial bit selections;
     */
    struct Attr
    {
        uint8_t Primary:1;
        uint8_t Unique :1;
        uint8_t Auto   :1;
        uint8_t Null   :1;
        uint8_t Index  :1;
        uint8_t FK     :1;
    }mAttr={0,0,0,0,0,0};
    
    static constexpr uint8_t PK     = 0x01;
    static constexpr uint8_t Unique = 0x02;
    static constexpr uint8_t PKAUTO = 0x05;
    static constexpr uint8_t Null   = 0x08;
    static constexpr uint8_t Index  = 0x10;
    static constexpr uint8_t FK     = 0x20;
    
    
    Field() = default;
    Field(const Field&) = default;
    Field(Field&&) noexcept = default;
    ~Field() = default;

    Field(Table* Table_, std::string Name_);
    Field(std::string Name_, Field::Type, Field::Attr Attr_);
    Field(std::string Name_, Field::Type Type_);
    String Name() { return mName; }
    
    Field::Attr SetAttributes(uint8_t Attr_);
    
    String Serialize();
private:
    Field::Type mType = Field::Type::INTEGER;
    
};

}
