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
    
    struct Node
    {
        using Shared = std::shared_ptr<Node>;

        using Collection = std::vector<Ast::Node*>;
        Node* Parent    = nullptr; ///< Parent Node. 
        Node* Lhs       = nullptr; ///< Lef Hand Side Operand
        Node* Rhs       = nullptr; ///< Right Hand Side Operand
        Node* Child     = nullptr; ///< Child Node.
        TokenData* Token= nullptr; ///< TokenData (infos).

        static Node::Shared New(Ast::Shared&& Ast_, TokenData* Token_);

        ~Node();
    };
    
    Node*   _IP = nullptr; ///< Input Pointer;
    
    
public:
    Ast() = default;
    ~Ast()  = default;
    
    Return Build();
    
};

}
//#endif //LSC_AST_H
