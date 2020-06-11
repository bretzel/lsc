
#pragma once
#include <Lsc/Rem/Lib.h>
#include <vector>
#include <memory>


namespace Lsc
{

#pragma warning(disable: 4251)

class REM_LIB Object: public std::enable_shared_from_this<Object>
{
    
    DECLOBJ_ID

    
public:
    
    using Shared = std::shared_ptr<Object>;
    using Collection = std::vector<Object::Shared>; // NE SE COPIE PAS !!!
    using Iterator = Collection::iterator;
    using ConstIterator = Collection::const_iterator;

    Object() = default;
    explicit Object(Object::Shared Parent_);
    virtual ~Object();

    Object(const Object& ) = delete;
    Object(Object&& ) = delete;

    template<typename T> Object::Shared IsClass() { return dynamic_cast<T*>(shared_from_this()); }
    template<typename T=Object> Object::Shared Parent() { return (mParent? dynamic_cast<T*>(mParent):nullptr); }
    
    bool Detach();
    bool RemoveChild(Object::Shared);
    
    static Object::Shared  Make(Object::Shared Parent_);
    Object::Shared Self() { return shared_from_this(); }

private:
    
    Object::Shared mParent = nullptr;

    virtual std::size_t AppendChild(Object::Shared Object_);
    virtual void SetParent(Object::Shared Object_);

    //Object::Shared _Self = nullptr; // Pas si certain ... 

protected:
    Collection mChildren;
};



}