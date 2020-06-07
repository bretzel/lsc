#pragma once

#include <AppQD/Lib.h>
#include <AppQD/sqlite3.h>
#include <Lsc/Rem/Object.h>
#include <string>
namespace Lsc::QD
{


class APPQD_LIB SchemaItem : public Object
{
    std::string mName;

public:
    SchemaItem() = default;
    SchemaItem(const SchemaItem& ) = default;
    SchemaItem(SchemaItem&&) noexcept = default;
    virtual ~SchemaItem();

    SchemaItem(std::string Name_);

};


class APPQD_LIB AppQD
{

};

}