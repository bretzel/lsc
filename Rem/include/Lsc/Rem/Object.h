
#pragma once
#include <Lsc/Rem/Lib.h>
#include <vector>


namespace Lsc
{

class Object
{
    
    Object* mParent= nullptr;

    DECLOBJ_ID

public:
    using Collection = std::vector<Object*>; // NE SE COPIE PAS !!!

    Object() = default;
    explicit Object(Object* Parent_);

    virtual ~Object() = default;

    Object(const Object& ) = delete;
    Object(Object&& ) = delete;


private:
    virtual std::size_t AppendChild(Object* Object_);
    virtual void SetParent(Object* Object_);
    
protected:
    Collection mChildren;
};



}