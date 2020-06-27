#include <Lsc/Vault/Model/Field.h>



namespace Lsc::Vault
{
CLASSNAME_IMPL(Field)

Field::~Field()
{
    mID.Clear(); //...
}

Field::Field(std::string Id_):Object(),
mName(std::move(Id_))
{
}

Field::Field(Object* Table_):Object(Table_)
{
}


}

