//#include <Lsc/Vault/Model/Field.h>
#include <Lsc/Vault/Model/Table.h>
#include <Lsc/Vault/Model/Field.h>

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



}

