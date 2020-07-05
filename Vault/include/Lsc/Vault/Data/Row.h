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

class Entity;

class Row
{
    Entity* mModel = nullptr;
    String::Collection mRow;
    using FColumn = std::vector<Field*>::iterator;
    String::Collection::iterator _C;
    FColumn mColumn;
    
    // NOTE (Sous reserve):
    using RCursor = std::pair<Row::FColumn, String::Collection::iterator>;
    // -------------------------------------------------------------------
public:
    
    Row() = default;
    Row(const Row&) = default;
    Row(Row&&) noexcept = default;
    
    ~Row();
    
    explicit Row(Entity* E_);
    void Reset();
    Row::FColumn Begin();
    bool End();
    Expect<std::string&> operator[](const std::string& ColumnName_);
    
};
}
//#endif //LSC_ROW_H
