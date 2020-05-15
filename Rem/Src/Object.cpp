#include <Lsc/Rem/Object.h>



namespace Lsc
{

CLASSNAME_IMPL(Object)



Object::Object(Object *Parent_) : mParent(Parent_)
{
    if(mParent)
        mParent->AppendChild(this);
}


std::size_t Object::AppendChild(Object *Object_)
{
    mChildren.push_back(Object_);
    return mChildren.size();
}



void Object::SetParent(Object *Object_)
{

}

} // namespace Lsc
