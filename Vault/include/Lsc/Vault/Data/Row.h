//
// Created by lsc on 20-07-01.
//
//
//#ifndef LSC_ROW_H
//#define LSC_ROW_H

#pragma once

#include <Lsc/Vault/Model/Field.h>
#include <utility>

namespace Lsc::Vault
{

class Entity; ///< External definition because it will creates mutual dependancy on Entity<->Field

class VAULT_LIB Row
{
    Entity* mModel = nullptr;
    String::Collection           mStrData;
    String::Collection::iterator mStrCursor;
    
    using FieldCursor = std::vector<Field*>::iterator;
    FieldCursor mFieldCursor; ///< Internal;
    
    // NOTE (Likely Unused) (Sous reserve):
    using RowCursor = std::pair<Row::FieldCursor, String::Collection::iterator>;
    // -------------------------------------------------------------------
public:
    
    Row() = default;
    Row(const Row&) = default;
    Row(Row&&) noexcept = default;
    
    ~Row();
    
    explicit Row(Entity* E_);
    void Reset();
    Row::FieldCursor Begin();
    bool End(Row::FieldCursor Cursor_);
    Expect<std::string&> operator[](const std::string& FieldName_);
    
    /*!
     * @brief Input Data at the current column into the Row.
     * @tparam T
     * @param Data_
     * @return Self.
     */
    template<typename T> Row& operator << (const T& Data_)
    {
        if(End(mFieldCursor))
        {
            ///@todo throw or return failure.
            return *this;
        }
        
        String StrData; // Stringify(serializes?) and hold data.
        ///@todo Check input data type VS Schema Column/Field's data type.
        //...
        StrData << Data_;
        (*mStrCursor) = StrData();
        ++mFieldCursor;
        return *this;
    }
};
}
//#endif //LSC_ROW_H
