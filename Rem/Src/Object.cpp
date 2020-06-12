#include <Lsc/Rem/Object.h>
#include <Lsc/Rem/Rem.h>

#include <iostream>

#include <algorithm>

namespace Lsc
{

CLASSNAME_IMPL(Object)



Object::Object(Object* Parent_) : mParent(Parent_) 
{
    if (mParent)
        mParent->AppendChild(this);
}




std::size_t Object::AppendChild(Object* Object_)
{
    Rem::Debug() << __PRETTY_FUNCTION__ << ":";
    mChildren.push_back(Object_);
    return mChildren.size();
}



void Object::SetParent(Object* Object_)
{
    if(mParent)
        return;
    
    if(Object_)
        Object_->AppendChild(this);
    
}

Object::~Object()
{
    Rem::Debug() << __PRETTY_FUNCTION__ << ": \\O/!";
    if(!mChildren.empty())  mChildren.clear();
}


bool Object::Detach()
{
    if(!mParent)
        return false;
    
    return mParent->RemoveChild(this);
}



bool Object::RemoveChild(Object* Child_)
{
    auto I = std::find(mChildren.begin(), mChildren.end(), Child_);
    if(I!=mChildren.end())
    {
        mChildren.erase(I);
        return true;
    }
    return false;
}


} // namespace Lsc
