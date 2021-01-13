//
// Created by slussier on 21-01-02.
//

//#ifndef LSC_AST_H
//#define LSC_AST_H
#pragma once

#include <Lsc/Scripture/Interpreter/Compiler/Grammar.h>

namespace Lsc
{

class SCRIPTURE_LIB Ast
{
    Grammar _G;
    TokenData* _Tokens = nullptr;
    using Shared = std::shared_ptr<Ast>;
    using Collection = std::vector<Ast::Shared>;
    Ast::Shared    _Parent      = nullptr;
    Collection     _Children;
    struct Node
    {
        using Shared = std::shared_ptr<Node>;

        using Collection = std::vector<Ast::Node::Shared>;
        Node* Parent    = nullptr; ///< Parent Node. 
        Node* Lhs       = nullptr; ///< Lef Hand Side Operand
        Node* Rhs       = nullptr; ///< Right Hand Side Operand
        Node* Child     = nullptr; ///< Child Node.
        TokenData* Token= nullptr; ///< TokenData (infos).

        static Node::Shared New(Ast::Shared&& Ast_, TokenData* Token_);

        ~Node();
    };
    
    Node::Shared _Root = nullptr;  ///< Root of this Ast;
    Node::Shared _IP    = nullptr; ///< Input Pointer;
    
    
public:
    Ast() = default;
    Ast(Ast&&) = default;

    ~Ast()  = default;
    static Ast::Shared New(Ast::Shared Parent_);
    
    
    Return Build();
    
};

}
//#endif //LSC_AST_H
