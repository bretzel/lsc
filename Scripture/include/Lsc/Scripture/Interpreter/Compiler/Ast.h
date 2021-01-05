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
    
    
    struct Node
    {
        Node* Parent    = nullptr;
        Node* Lhs       = nullptr;
        Node* Rhs       = nullptr;
        Node* Child     = nullptr;
        TokenData* Token= nullptr;
        
    };
    
    Node*   _IP = nullptr; ///< Input Pointer;
    
    
public:
    Ast() = default;
    ~Ast()  = default;
    
    Return Build();
    
};
}
//#endif //LSC_AST_H
