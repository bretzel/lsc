//
// Created by lsc on 20-07-07.
//

#include <Lsc/Scripture/Interpreter/Xio.h>

namespace Lsc
{






Xio::ExeTable Xio::_ExeTable = {
    {Mnemonic::Lshift,      &Xio::Lshift },
    {Mnemonic::Radical,     &Xio::Radical },
    {Mnemonic::Exponent,    &Xio::Exponent },
    {Mnemonic::Rshift,      &Xio::Rshift },
    {Mnemonic::Decr,        &Xio::Decr },
    {Mnemonic::Incr,        &Xio::Incr },
    {Mnemonic::Assignadd,   &Xio::Assignadd },
    {Mnemonic::Assignsub,   &Xio::Assignsub },
    {Mnemonic::Assignmul,   &Xio::Assignmul },
    {Mnemonic::Assigndiv,   &Xio::Assigndiv },
    {Mnemonic::Assignmod,   &Xio::Assignmod },
    {Mnemonic::Assignand,   &Xio::Assignand },
    {Mnemonic::Assignor,    &Xio::Assignor },
    {Mnemonic::Assignxor,   &Xio::Assignxor },
    {Mnemonic::Assignx1,    &Xio::Assignx1 },
    {Mnemonic::Assignlshift,&Xio::Assignlshift },
    {Mnemonic::Assignrshift,&Xio::Assignrshift },
    {Mnemonic::Leq,         &Xio::Leq },
    {Mnemonic::Geq,         &Xio::Geq },
    {Mnemonic::Eq,          &Xio::Eq },
    {Mnemonic::Neq,         &Xio::Neq},
    {Mnemonic::Add,         &Xio::Add },
    {Mnemonic::Sub,         &Xio::Sub },
    {Mnemonic::Mul,         &Xio::Mul },
    {Mnemonic::Modulo,      &Xio::Modulo },
    {Mnemonic::Lt,          &Xio::Lt },
    {Mnemonic::Gt,          &Xio::Gt },
    {Mnemonic::Assign,      &Xio::Assign },
    {Mnemonic::Binand,      &Xio::Binand },
    {Mnemonic::Binor,       &Xio::Binor },
    {Mnemonic::Bitxor,      &Xio::Bitxor },
    {Mnemonic::X1,          &Xio::X1},
    {Mnemonic::X2,          &Xio::X2 },
    {Mnemonic::Bitnot,      &Xio::Bitnot},
    {Mnemonic::Booland,     &Xio::Booland },
    {Mnemonic::Boolor,      &Xio::Boolor },
    {Mnemonic::Division,    &Xio::Division },
    {Mnemonic::Factorial,   &Xio::Factorial },
    {Mnemonic::Positive,    &Xio::Positive },
    {Mnemonic::Negative,    &Xio::Negative },
    {Mnemonic::Hash,        &Xio::Hash},
    {Mnemonic::Dollard,     &Xio::Dollard },
    {Mnemonic::Dot,         &Xio::Dot },
    {Mnemonic::Kpi,         &Xio::Kpi },
    {Mnemonic::Kcos,        &Xio::Kcos },
    {Mnemonic::Kacos,       &Xio::Kacos },
    {Mnemonic::Ktan,        &Xio::Ktan },
    {Mnemonic::Katan,       &Xio::Katan },
    {Mnemonic::Ksin,        &Xio::Ksin },
    {Mnemonic::Kasin,       &Xio::Kasin },
    {Mnemonic::Noop,        &Xio::Noop }

};






Xio::~Xio()
{
    Rem::Debug(__PRETTY_FUNCTION__ ) << "\\O/;";
}




Xio::Xio(Xio::Shared Xio, TokenData *Token_, Alu::Shared Alu_):
_Parent(std::move(Xio)),
_T(Token_)
{
    if(!Alu_)
        _A = std::make_shared<Alu>();
    else
        _A = Alu_;
    
    
}
Xio::Shared Xio::New(Xio::Shared Parent_, TokenData *Token_, Alu::Shared Alu_)
{
    Xio::Shared X = std::make_shared<Xio>(Parent_,Token_,Alu_);
    return X;
}
Alu Xio::Exe()
{
    return *_A;
}


// Arithmetic --------------------------------------------------------------------------------------------------------

Alu Xio::Lshift()
{
    return *_A;
}
Alu Xio::Radical()
{
    return *_A;
}
Alu Xio::Exponent()
{
    return *_A;
}
Alu Xio::Rshift()
{
    return *_A;
}
Alu Xio::Decr()
{
    return *_A;
}
Alu Xio::Incr()
{
    return *_A;
}
Alu Xio::Assignadd()
{
    return *_A;
}
Alu Xio::Assignsub()
{
    return *_A;
}
Alu Xio::Assignmul()
{
    return *_A;
}
Alu Xio::Assigndiv()
{
    return *_A;
}
Alu Xio::Assignmod()
{
    return *_A;
}
Alu Xio::Assignand()
{
    return *_A;
}
Alu Xio::Assignor()
{
    return *_A;
}
Alu Xio::Assignxor()
{
    return *_A;
}
Alu Xio::Assignx1()
{
    return *_A;
}
Alu Xio::Assignlshift()
{
    return *_A;
}
Alu Xio::Assignrshift()
{
    return *_A;
}
Alu Xio::Leq()
{
    return *_A;
}
Alu Xio::Geq()
{
    return *_A;
}
Alu Xio::Eq()
{
    return *_A;
}
Alu Xio::Neq()
{
    return *_A;
}
Alu Xio::Add()
{
    return *_A;
}
Alu Xio::Sub()
{
    return *_A;
}
Alu Xio::Mul()
{
    return *_A;
}
Alu Xio::Modulo()
{
    return *_A;
}
Alu Xio::Lt()
{
    return *_A;
}
Alu Xio::Gt()
{
    return *_A;
}
Alu Xio::Assign()
{
    return *_A;
}
Alu Xio::Binand()
{
    return *_A;
}
Alu Xio::Binor()
{
    return *_A;
}
Alu Xio::Bitxor()
{
    return *_A;
}
Alu Xio::X1()
{
    return *_A;
}
Alu Xio::X2()
{
    return *_A;
}
Alu Xio::Bitnot()
{
    return *_A;
}
Alu Xio::Booland()
{
    return *_A;
}
Alu Xio::Boolor()
{
    return *_A;
}
Alu Xio::Division()
{
    return *_A;
}
Alu Xio::Factorial()
{
    return *_A;
}
Alu Xio::Positive()
{
    return *_A;
}
Alu Xio::Negative()
{
    return *_A;
}
Alu Xio::Hash()
{
    return *_A;
}
Alu Xio::Dollard()
{
    return *_A;
}
Alu Xio::Dot()
{
    return *_A;
}
Alu Xio::Kpi()
{
    return *_A;
}
Alu Xio::Kcos()
{
    return *_A;
}
Alu Xio::Kacos()
{
    return *_A;
}
Alu Xio::Ktan()
{
    return *_A;
}
Alu Xio::Katan()
{
    return *_A;
}
Alu Xio::Ksin()
{
    return *_A;
}
Alu Xio::Kasin()
{
    return *_A;
}

Alu Xio::Noop()
{
    return *_A;
}

}