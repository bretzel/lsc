//
// Created by lsc on 20-07-16.
//

//#ifndef LSC_QUERY_H
//#define LSC_QUERY_H

#pragma once

#include <Lsc/Vault/Vault.h>
#include <Lsc/Rem/Rem.h>

namespace Lsc::Vault
{

class VAULT_LIB Query
{
    Vault* mVault = nullptr;
    String mSql;
public:
    Query() = default;
    Query(Query&& ) noexcept = default;
    
    Query(Vault* Vault_);
    ~Query();
    
    Query& Select();
    Query& Delete();
    Query& Update();
    Query& Create();
    Query& Alter();
    
    Query& operator << (const std::string& Content_);
    Query& operator << (const Field* F_);
    Query& operator << (const Table* T_);
    
    Query& Where();
    Query& And();
    Query& Or();
    Query& Date();
    Query& EQ();
    Query& NEQ();
    
    Query& SQL(const std::string& Sql_);
    
//
//    // Testing the Overloaded arithmetic and boolean operators here.
//    // Subject to be cancelled because RHS can be sub-objects into a building graph-tree.
//    #pragma region TestOperators
//
//    Query& operator == (const std::string& Data_);
//    Query& operator = (const std::string& Data_);
//    Query& operator || (Query& RHS_);
//    Query& operator && (Query& RHS_);
//    Query& operator != (Query& RHS_);
//    Query& operator <= (Query& RHS_);
//    Query& operator >= (Query& RHS_);
//    Query& operator < (Query& RHS_);
//    Query& operator > (Query& RHS_);
//
//    #pragma endregion TestOperators
//
    
};



}
//#endif //LSC_QUERY_H
