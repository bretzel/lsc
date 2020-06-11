#include <Lsc/Rem/Object.h>
#include <iostream>

#include <algorithm>

namespace Lsc
{

CLASSNAME_IMPL(Object)



Object::Object(Object::Shared Parent_) : mParent(Parent_)
{
    if(mParent)
        mParent->AppendChild(shared_from_this());

}



Object::Shared Object::Make(Object::Shared Parent_)
{
    Object::Shared So = std::make_shared<Object>(Parent_);
    // If I keep a Self Shared instance within this Object instance, 
    // Does it infinite recurse when std::shared_ptr ref count-- ? 
    // Or never reach 0 ? 
    So->shared_from_this() = So->shared_from_this();
    return So;
}

std::size_t Object::AppendChild(Object::Shared Object_)
{
    mChildren.push_back(Object_);
    return mChildren.size();
}



void Object::SetParent(Object::Shared Object_)
{
    if(mParent)
        return;
    
    if(Object_)
        Object_->AppendChild(shared_from_this());
    
}

Object::~Object()
{
    std::cout << __PRETTY_FUNCTION__ << ": \\O/!\n";
    //if (shared_from_this().use_count() == 1)
    //{

    //}
}


bool Object::Detach()
{
    if(!mParent)
        return false;
    
    return mParent->RemoveChild(shared_from_this());
}



bool Object::RemoveChild(Object::Shared Child_)
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
