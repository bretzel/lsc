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
    TokenData::Collection::iterator _Token; ///< Informations; @note Le tokens stream ne changera pas.

//  Exclusif aux expression arithm�tiques
    using Maker = std::function<Node*(Lsc::Ast::AstTree*, TokenData*)>;

    Node* Op = nullptr;
    Node* L = nullptr;
    Node* R = nullptr;
// ---------------------------------------
    AstTree* Tree = nullptr;

    Node() = default;
    Node(Node&&) = delete;
    Node(const Node&) = delete;
    Node(AstTree* Tree_, TokenData* Token_);

    ~Node() = default;

    Return Input(TokenData*, Ast::Node::Maker Maker_);


#pragma region ExprInput
// First : declare associatibn pair:
    using InputType = std::pair<Type::T, Type::T>;
    using InputFn = Return(Node::*)(Node*);        ///< callable Node tree input function ptr
    using InputPair = std::pair < Node::InputType, Node::InputFn>;

    using InputTable = std::vector<InputPair>;
    static InputTable _InputTable;

#pragma endregion ExprInput
};


struct AstTree
{
    Node*    Root = nullptr;
    AstTree* Parent = nullptr;
    using List = std::vector<AstTree*>;

    AstTree::List Children;



};


}
//#endif //LSC_AST_H
