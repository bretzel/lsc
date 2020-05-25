
#pragma once
#include <Lsc/Rem/Lib.h>
#include <vector>


namespace Lsc
{

class REM_LIB Object
{
    
    Object* mParent= nullptr;

    DECLOBJ_ID

public:
    using Collection = std::vector<Object*>; // NE SE COPIE PAS !!!

    Object() = default;
    explicit Object(Object* Parent_);

    virtual ~Object();

    Object(const Object& ) = delete;
    Object(Object&& ) = delete;

    template<typename T> T* IsClass() { return dynamic_cast<T*>(this); }
    template<typename T=Object> T* Parent() { return (mParent? dynamic_cast<T*>(mParent):nullptr); }
    
    bool Detach();
    bool RemoveChild(Object*);
    
private:
    virtual std::size_t AppendChild(Object* Object_);
    virtual void SetParent(Object* Object_);
    
protected:
    Collection mChildren;
};



}