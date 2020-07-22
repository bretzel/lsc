//
// Created by lsc on 20-07-01.
//

#include <Lsc/Vault/Data/Row.h>
#include <Lsc/Vault/Model/Entity.h>



namespace Lsc::Vault
{

Row::~Row()
{
    mStrData.clear();
}

Row::Row(Entity *E_) : mModel(E_)
{
    
}

void Row::Reset()
{
    mFieldCursor = mModel->Begin();
    mStrCursor   = mStrData.begin();
}

Row::FieldCursor Row::Begin()
{
    return (mFieldCursor = mModel->Begin());
    //return mFieldCursor;
}


bool Row::End(Row::FieldCursor Cursor_)
{
    return mModel->End(Cursor_);
}


Expect<std::string&> Row::operator[](const std::string &FieldName_)
{
    int I =  (*mModel)[FieldName_];
    if(I<0)
        return Rem::Error() << __PRETTY_FUNCTION__ << ": No Field named '" << FieldName_ << "';";
    return mStrData[I];
}

}