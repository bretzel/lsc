//
// Created by slussier on 21-01-02.
//

//#ifndef LSC_AST_H
//#define LSC_AST_H
#pragma once

#include <Lsc/Scripture/Interpreter/Compiler/Grammar.h>

namespace Lsc
{

class Ast
{
    Grammar _G;
    TokenData* _Tokens = nullptr;
    
public:
    Ast() = default;
    ~Ast()  = default;
    
    Return Build();
    
};
}
//#endif //LSC_AST_H
