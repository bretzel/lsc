//
// Created by slussier on 21-01-02.
//

//#ifndef LSC_AST_H
//#define LSC_AST_H
#pragma once

#include <Lsc/Scripture/Interpreter/Compiler/Grammar.h>

namespace Lsc::Ast
{





class SCRIPTURE_LIB Parser
{
    Grammar _G;
    TokenData::Collection* _Tokens = nullptr;

    
};

class SCRIPTURE_LIB Node
{
    TokenData::Collection::iterator _Token; ///< Le tokens stream ne changera pas.

};

}
//#endif //LSC_AST_H
