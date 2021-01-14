//
// Created by slussier on 21-01-02.
//

#include <Lsc/Scripture/Interpreter/Compiler/Ast.h>



namespace Lsc
{

    
    



Ast::Shared Ast::New(Ast::Shared Parent_)
{
    Ast::Shared A = std::make_shared<Ast>();
    A->_Parent = Parent_;
    Parent_->_Children.push_back(A);
    return A;
}


Return Ast::Build()
{
    return Rem::Int::Implement;
}


Ast::Node::Shared Ast::Node::New(TokenData* Token_)
{
    Shared N = std::make_shared<Ast::Node>(Token_);
}


Ast::Node::~Node()
{

}
Ast::Node::Node(TokenData *Info_)
{
    Info = Info_;
}

}