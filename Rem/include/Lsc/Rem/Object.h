
#pragma once
#include <Lsc/Rem/Lib.h>
#include <vector>



namespace Lsc
{

#pragma warning(disable: 4251)

class REM_LIB Object
{
    
    DECLOBJ_ID

    
public:
    
    using Collection = std::vector<Object*>; // NE SE COPIE PAS !!!
    using Iterator = Collection::iterator;
    using ConstIterator = Collection::const_iterator;

    Object() = default;
    explicit Object(Object* Parent_);
    virtual ~Object();

    Object(const Object& ) = delete;
    Object(Object&& ) = delete;

    template<typename T> T* IsClass() { return dynamic_cast<T*>(this); }
    template<typename T=Object> T* Parent() { return (mParent? dynamic_cast<T*>(mParent):nullptr); }
    
    bool Detach();
    bool RemoveChild(Object*);
    
    
    void Clear() { if (!mChildren.empty()) mChildren.clear(); }

private:
    
    Object* mParent = nullptr;

    virtual std::size_t AppendChild(Object* Object_);
    virtual void SetParent(Object* Object_);

    //Object* _Self = nullptr; // Pas si certain ... 

protected:
    Collection mChildren;
};



}