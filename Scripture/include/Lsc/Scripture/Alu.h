//
// Created by lsc on 20-05-28.
//

//#ifndef LSC_ALU_H
//#define LSC_ALU_H

#pragma once

#include <Lsc/Scripture/Lib.h>
#include <any>
#include <vector>
#include <Lsc/Scripture/Types.h>
#include <memory>

namespace Lsc
{

struct SCRIPTURE_LIB Alu
{
    using Collection = std::vector<Alu>;
    using LinkArray = std::vector<Alu *>;
    
    std::any R = .0;
    Type::T  T = Type::Float; ///< Default type.
    
    enum CNV {
        DEG,
        RAD
    };
    
    Alu() { R.reset(); }

    Alu(const Alu&) = default;
    Alu(double A_);
    Alu(float A_);
    //alu(token_t* rhs);

    Alu(const std::string& A_);
    Alu(const char* A_);
    Alu(void* A_);
    Alu(Alu&& ) noexcept = default;
    Alu(int8_t A_);
    Alu(int16_t A_);
    Alu(int32_t A_);
    Alu(int64_t A_);
    Alu(uint8_t A_);
    Alu(uint16_t A_);
    Alu(uint32_t A_);
    Alu(uint64_t A_);
    Alu(bool A_);

    void Reset();
    
};

}
//#endif //LSC_ALU_H
