//
// Created by lsc on 20-07-01.
//

#include <Lsc/Vault/Data/Row.h>
#include <Lsc/Vault/Model/Entity.h>



namespace Lsc::Vault
{

Row::~Row()
{
    mRow.clear();
}

Row::Row(Entity *E_) : mModel(E_)
{
    
}

void Row::Reset()
{
    mColumn = mModel->Begin();
    _C = mRow.begin();
}

Row::FColumn Row::Begin()
{
    mColumn = mModel->Begin();
    return mColumn;
}


bool Row::End()
{
    return mModel->End(mColumn);
}


std::string &Row::operator[](const std::string &ColumnName_)
{
    return mRow[0];
}
}