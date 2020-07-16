//
// Created by lsc on 20-07-16.
//

#include <Lsc/Vault/Data/Query.h>



namespace Lsc::Vault
{

Query::~Query()
{
    mSql.Clear();
}

Query &Query::Select()
{
    return *this;
}
Query &Query::Delete()
{
    return *this;
}
Query &Query::Update()
{
    return *this;
}
Query &Query::Create()
{
    return *this;
}
Query &Query::Alter()
{
    return *this;
}
Query &Query::operator<<(const std::string &Content_)
{
    mSql << Content_ << ' ';
    return *this;
}
Query &Query::operator<<(const Field *F_)
{
    mSql += "%s.%s ";
    mSql << F_->TableName() << F_->Name();
    return *this;
}

Query &Query::operator<<(const Table *T_)
{
    mSql << T_->Name() << ' ';
    return *this;
}

Query &Query::Where()
{
    return *this;
}
Query &Query::And()
{
    return *this;
}
Query &Query::Or()
{
    return *this;
}
Query &Query::Date()
{
    return *this;
}

Query &Query::EQ()
{
    
    return *this;
}


Query &Query::NEQ()
{
    return *this;
}
Query &Query::SQL(const std::string &Sql_)
{
    return *this;
}
Query::Query(Vault *Vault_)
{
    mVault = Vault_;
}

}


