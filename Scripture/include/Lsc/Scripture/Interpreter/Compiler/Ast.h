//
// Created by slussier on 21-01-02.
//

//#ifndef LSC_AST_H
//#define LSC_AST_H
#pragma once

#include <Lsc/Scripture/Interpreter/Compiler/Grammar.h>
#include <Lsc/Scripture/Interpreter/Xio.h>

namespace Lsc
{



struct Ast
{
    using Shared = std::shared_ptr<Ast>;
    using List = std::vector<Ast::Shared>;
    
    
    static Ast::Shared New(Ast::Shared Parent_);
    
    Ast::Shared Operator = nullptr;
    Ast::Shared Rhs      = nullptr;
    Ast::Shared Lhs      = nullptr;
    
    Ast::List   Children;
#pragma region ExprInput
    
    // ----------------- TOKEN INFORMATIONS ----------------
    TokenData*  mInformations = nullptr;
    // -----------------------------------------------------
    
    // ---- Arithmetic Expression Binary Tree (#expression rule directive)--------------
    using TableItem = std::pair<Type::T, Type::T>;
    using InputFn   = Return(Ast::*)(Ast::Shared);
    //using InputPair = std::pair<Ast::TableItem, Ast::InputFn>;
    using ExpressionInputTable = std::map<TableItem, Ast::InputFn>;
    static Ast::ExpressionInputTable _EIT;
    

    
};


};

//#endif //LSC_AST_H
