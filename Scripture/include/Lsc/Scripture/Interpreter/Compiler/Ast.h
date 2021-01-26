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

    


#pragma region ExprInput
// First : declare associatibn pair:
    using InputType = std::pair<Type::T, Type::T>;
    using InputFn = Return(Node::*)(Node*);        ///< callable Node tree input function ptr
    using InputPair = std::pair < Node::InputType, Node::InputFn>;

    using InputTable = std::vector<InputPair>;
    static InputTable _InputTable;

    Return Input(TokenData* Token_, Node::Maker Maker_);
    
    Return InputBinary(Node* x);
    Return InputLeaf(Node* x);
    Return SetLeft(Node* x);
    Return SetRight(Node* x);
    Return SetRightToOper(Node* x);

    InputFn Associate(Node* a_lhs, Node* a_rhs);

    Return InputLeftParBinary(Node* x);

    Return InputRPar(Node*);
    Return InputLPar(Node*);
    Return ClosePar(Node*);
    Return RParInputPostfix(Node*);
    Return RParInputLeaf(Node*);
    Return RParRPar(Node*);

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
