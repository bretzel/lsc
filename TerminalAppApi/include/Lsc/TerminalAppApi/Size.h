//
// Created by lsc on 20-08-23.
//

//#ifndef ui_SIZE_H
//#define ui_SIZE_H

#pragma once


#include <Lsc/Rem/Rem.h>

namespace Lsc::TAA
{


struct  Size
{
    float DX = 0.0f;
    float DY = 0.0f;
    

    uint32_t MinX=0;
    uint32_t MinY=0;
    uint32_t MaxX=0;
    uint32_t MaxY=0;
    Lsc::Rem::Int  St = Lsc::Rem::Int::Null;
    
// ------------ Trivial Copy and Move -----------------------------
    Size() = default;
    ~Size()  = default;
    Size(const Size&) = default;

    Size(Size&&) noexcept = default;
// -----------------------------------------------------------------

    Size(float DX_, float DY_);

    Size& operator=(const Size&) = default;
    Size& operator=(Size&&) noexcept = default;

    Size operator+(const Size&);
    Size operator+(float);
    Size operator-(const Size&);
    Size operator-(float);

    Size& operator+=(const Size&);
    Size& operator+=(float);
    Size& operator-=(const Size&);
    Size& operator-=(float);


    explicit operator bool() const {
        return DX * DY > 0;
    }
    
    [[nodiscard]] float Width()  const;
    [[nodiscard]] float Height() const;
    [[nodiscard]] float R();
    
    Lsc::String ToString() const ;

};


}

//#endif //ui_SIZE_H