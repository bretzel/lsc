//
// Created by slussier on 21-01-02.
//

//#ifndef LSC_AST_H
//#define LSC_AST_H
#pragma once

#include <Lsc/Scripture/Interpreter/Compiler/Grammar.h>

namespace Lsc::Ast
{


struct AstTree;

struct SCRIPTURE_LIB Node
{
    using Shared = std::shared_ptr<Lsc::Ast::Node>;
    TokenData::Collection::iterator _Token; ///< Informations; @note Le tokens stream ne changera pas.

//  Exclusif aux expression arithmétiques
    Node* Op = nullptr;
    Node* L = nullptr;
    Node* R = nullptr;
// ---------------------------------------
    AstTree* Tree = nullptr;

};


struct AstTree
{
    Node*    Root = nullptr;
    AstTree* Parent = nullptr;
    using List = std::vector<AstTree*>;

    AstTree::List Children;



};


class SCRIPTURE_LIB Parser
{
    Grammar _G;
    TokenData::Collection* _Tokens = nullptr;

    
};


}
//#endif //LSC_AST_H
