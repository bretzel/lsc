//
// Created by lsc on 20-07-07.
//

#include <Lsc/Scripture/Interpreter/ExIO.h>

namespace Lsc
{






ExIO::ExeTable ExIO::_ExeTable = {
    {Mnemonic::Lshift,      &ExIO::Lshift },
    {Mnemonic::Radical,     &ExIO::Radical },
    {Mnemonic::Exponent,    &ExIO::Exponent },
    {Mnemonic::Rshift,      &ExIO::Rshift },
    {Mnemonic::Decr,        &ExIO::Decr },
    {Mnemonic::Incr,        &ExIO::Incr },
    {Mnemonic::Assignadd,   &ExIO::Assignadd },
    {Mnemonic::Assignsub,   &ExIO::Assignsub },
    {Mnemonic::Assignmul,   &ExIO::Assignmul },
    {Mnemonic::Assigndiv,   &ExIO::Assigndiv },
    {Mnemonic::Assignmod,   &ExIO::Assignmod },
    {Mnemonic::Assignand,   &ExIO::Assignand },
    {Mnemonic::Assignor,    &ExIO::Assignor },
    {Mnemonic::Assignxor,   &ExIO::Assignxor },
    {Mnemonic::Assignx1,    &ExIO::Assignx1 },
    {Mnemonic::Assignlshift,&ExIO::Assignlshift },
    {Mnemonic::Assignrshift,&ExIO::Assignrshift },
    {Mnemonic::Leq,         &ExIO::Leq },
    {Mnemonic::Geq,         &ExIO::Geq },
    {Mnemonic::Eq,          &ExIO::Eq },
    {Mnemonic::Neq,         &ExIO::Neq},
    {Mnemonic::Add,         &ExIO::Add },
    {Mnemonic::Sub,         &ExIO::Sub },
    {Mnemonic::Mul,         &ExIO::Mul },
    {Mnemonic::Modulo,      &ExIO::Modulo },
    {Mnemonic::Lt,          &ExIO::Lt },
    {Mnemonic::Gt,          &ExIO::Gt },
    {Mnemonic::Assign,      &ExIO::Assign },
    {Mnemonic::Binand,      &ExIO::Binand },
    {Mnemonic::Binor,       &ExIO::Binor },
    {Mnemonic::Bitxor,      &ExIO::Bitxor },
    {Mnemonic::X1,          &ExIO::X1},
    {Mnemonic::X2,          &ExIO::X2 },
    {Mnemonic::Bitnot,      &ExIO::Bitnot},
    {Mnemonic::Booland,     &ExIO::Booland },
    {Mnemonic::Boolor,      &ExIO::Boolor },
    {Mnemonic::Division,    &ExIO::Division },
    {Mnemonic::Factorial,   &ExIO::Factorial },
    {Mnemonic::Positive,    &ExIO::Positive },
    {Mnemonic::Negative,    &ExIO::Negative },
    {Mnemonic::Hash,        &ExIO::Hash},
    {Mnemonic::Dollard,     &ExIO::Dollard },
    {Mnemonic::Dot,         &ExIO::Dot },
    {Mnemonic::Kpi,         &ExIO::Kpi },
    {Mnemonic::Kcos,        &ExIO::Kcos },
    {Mnemonic::Kacos,       &ExIO::Kacos },
    {Mnemonic::Ktan,        &ExIO::Ktan },
    {Mnemonic::Katan,       &ExIO::Katan },
    {Mnemonic::Ksin,        &ExIO::Ksin },
    {Mnemonic::Kasin,       &ExIO::Kasin },
    {Mnemonic::Noop,        &ExIO::Noop }

};






ExIO::~ExIO()
{
    Rem::Debug(__PRETTY_FUNCTION__ ) << "\\O/;";
}




ExIO::ExIO(ExIO::Shared ExIO_, TokenData *Token_, Alu::Shared Alu_):
_Parent(std::move(ExIO_)),
_T(Token_)
{
    if(!Alu_)
        _A = std::make_shared<Alu>();
    else
        _A = Alu_;
    
    
}
ExIO::Shared ExIO::New(ExIO::Shared Parent_, TokenData *Token_, Alu::Shared Alu_)
{
    ExIO::Shared X = std::make_shared<ExIO>(Parent_,Token_,Alu_);
    return X;
}
Alu ExIO::Exe()
{
    return *_A;
}


// Arithmetic --------------------------------------------------------------------------------------------------------

Alu ExIO::Lshift()
{
    return *_A;
}
Alu ExIO::Radical()
{
    return *_A;
}
Alu ExIO::Exponent()
{
    return *_A;
}
Alu ExIO::Rshift()
{
    return *_A;
}
Alu ExIO::Decr()
{
    return *_A;
}
Alu ExIO::Incr()
{
    return *_A;
}
Alu ExIO::Assignadd()
{
    return *_A;
}
Alu ExIO::Assignsub()
{
    return *_A;
}
Alu ExIO::Assignmul()
{
    return *_A;
}
Alu ExIO::Assigndiv()
{
    return *_A;
}
Alu ExIO::Assignmod()
{
    return *_A;
}
Alu ExIO::Assignand()
{
    return *_A;
}
Alu ExIO::Assignor()
{
    return *_A;
}
Alu ExIO::Assignxor()
{
    return *_A;
}
Alu ExIO::Assignx1()
{
    return *_A;
}
Alu ExIO::Assignlshift()
{
    return *_A;
}
Alu ExIO::Assignrshift()
{
    return *_A;
}
Alu ExIO::Leq()
{
    return *_A;
}
Alu ExIO::Geq()
{
    return *_A;
}
Alu ExIO::Eq()
{
    return *_A;
}
Alu ExIO::Neq()
{
    return *_A;
}
Alu ExIO::Add()
{
    return *_A;
}
Alu ExIO::Sub()
{
    return *_A;
}
Alu ExIO::Mul()
{
    return *_A;
}
Alu ExIO::Modulo()
{
    return *_A;
}
Alu ExIO::Lt()
{
    return *_A;
}
Alu ExIO::Gt()
{
    return *_A;
}
Alu ExIO::Assign()
{
    return *_A;
}
Alu ExIO::Binand()
{
    return *_A;
}
Alu ExIO::Binor()
{
    return *_A;
}
Alu ExIO::Bitxor()
{
    return *_A;
}
Alu ExIO::X1()
{
    return *_A;
}
Alu ExIO::X2()
{
    return *_A;
}
Alu ExIO::Bitnot()
{
    return *_A;
}
Alu ExIO::Booland()
{
    return *_A;
}
Alu ExIO::Boolor()
{
    return *_A;
}
Alu ExIO::Division()
{
    return *_A;
}
Alu ExIO::Factorial()
{
    return *_A;
}
Alu ExIO::Positive()
{
    return *_A;
}
Alu ExIO::Negative()
{
    return *_A;
}
Alu ExIO::Hash()
{
    return *_A;
}
Alu ExIO::Dollard()
{
    return *_A;
}
Alu ExIO::Dot()
{
    return *_A;
}
Alu ExIO::Kpi()
{
    return *_A;
}
Alu ExIO::Kcos()
{
    return *_A;
}
Alu ExIO::Kacos()
{
    return *_A;
}
Alu ExIO::Ktan()
{
    return *_A;
}
Alu ExIO::Katan()
{
    return *_A;
}
Alu ExIO::Ksin()
{
    return *_A;
}
Alu ExIO::Kasin()
{
    return *_A;
}

Alu ExIO::Noop()
{
    return *_A;
}

}