//
// Created by lsc on 20-07-07.
//

#include <Lsc/Scripture/Interpreter/ExIO.h>

namespace Lsc
{

ExIO::~ExIO()
{

}




ExIO::ExIO(ExIO::Shared&& ExIO_, TokenData *Token_, Alu::Shared&& Alu_):
mParent(std::move(ExIO_)),
mToken(Token_)
{
    if(!Alu_)
        mAlu = std::make_shared<Alu>();
    else
        mAlu = std::move(Alu_);
    
    
}

}