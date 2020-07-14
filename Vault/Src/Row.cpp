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

Row::FieldCursor Row::Begin()
{
    mColumn = mModel->Begin();
    return mColumn;
}


bool Row::End(Row::FieldCursor Cursor_)
{
    return mModel->End(Cursor_);
}


Expect<std::string&> Row::operator[](const std::string &ColumnName_)
{
    int I =  (*mModel)[ColumnName_];
    if(I<0)
        return Rem::Error() << __PRETTY_FUNCTION__ << ": No Field named '" << ColumnName_ << "';";
    return mRow[I];
}

}