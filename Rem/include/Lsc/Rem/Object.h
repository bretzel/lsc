
#pragma once
#include <Lsc/Rem/Lib.h>
#include <vector>
#include <memory>


namespace Lsc
{

#pragma warning(disable: 4251)

class REM_LIB Object
{
    
    Object* mParent= nullptr;

    DECLOBJ_ID

    
public:
    using Shared = std::shared_ptr<Object>;

    using Collection = std::vector<Object*>; // NE SE COPIE PAS !!!

    Object() = default;
    explicit Object(Object* Parent_);
    explicit Object(Object::Shared Parent_);
    virtual ~Object();

    Object(const Object& ) = delete;
    Object(Object&& ) = delete;

    template<typename T> T* IsClass() { return dynamic_cast<T*>(this); }
    template<typename T=Object> T* Parent() { return (mParent? dynamic_cast<T*>(mParent):nullptr); }
    
    bool Detach();
    bool RemoveChild(Object*);
    

    static Object::Shared  Make(Object::Shared Parent_);
    Object::Shared Self() { return _Self; }

private:
    virtual std::size_t AppendChild(Object* Object_);
    virtual void SetParent(Object* Object_);

    Object::Shared _Self = nullptr; // Pas si certain ... 

protected:
    Collection mChildren;
};



}