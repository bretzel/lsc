//
// Created by lsc on 20-08-23.
//

#include <Lsc/TerminalAppApi/Size.h>


namespace Lsc::TAA{


Size Size::operator+(const Size & s) {
    Size sz;
    sz = *this;

    // cancel (discard) operation if any of the limits are passed (any overflow/underflow).
    if(MinX > (DX + s.DX) || (MinY > (DY + s.DY))|| (MaxX < (DX + s.DX))|| (MaxY < (DY + s.DY))) return sz;
    
    sz = *this;
    sz.DX += s.DX;
    sz.DY += s.DY;
    
    return sz;
}


Size Size::operator+(float q) {
    Size sz;
    sz = *this;

    // cancel (discard) operation if any of the limits are passed (any overflow/underflow).
    if(MinX > (DX + q) || (MinY > (DY + q))|| (MaxX < (DX + q))|| (MaxY < (DY + q))) return sz;
    
    sz.DX += q;
    sz.DY += q;
    
    
    return sz;
}

Size Size::operator-(const Size & s) {
    Size sz;
    sz = *this;

    // cancel (discard) operation if any of the limits are passed (any overflow/underflow).
    if(MinX > (DX - s.DX) || (MinY > (DY - s.DY))|| (MaxX < (DX - s.DX))|| (MaxY < (DY - s.DY))) return sz;
    
    sz.DX -= s.DX;
    sz.DY -= s.DY;

    return sz;

}

Size Size::operator-(float q) {
    Size sz;
    sz = *this;

    // cancel (discard) operation if any of the limits are passed (any overflow/underflow).
    if(MinX > (DX - q) || (MinY > (DY - q))|| (MaxX < (DX - q))|| (MaxY < (DY - q))) return sz;
    
    sz.DX -= q;
    sz.DY -= q;

    return sz;

}

Size &Size::operator+=(const Size & s)
{
    if(MinX > (DX + s.DX) || (MinY > (DY + s.DY))|| (MaxX < (DX + s.DX))|| (MaxY < (DY + s.DY))) return *this;
    
    DX += s.DX;
    DY += s.DY;

    return *this;
}


Size &Size::operator-=(const Size & s)
{
    if(MinX > (DX - s.DX) || (MinY > (DY - s.DY))|| (MaxX < (DX - s.DX))|| (MaxY < (DY - s.DY))) return *this;
    
    DX += s.DX;
    DY += s.DY;
    return *this;
}

Size &Size::operator-=(float s)
{
    if(MinX > (DX - s) || (MinY > (DY - s))|| (MaxX < (DX - s))|| (MaxY < (DY - s))) return *this;
    
    DX -= s;
    DY -= s;

    return *this;

}

Size &Size::operator+=(float s)
{
    // cancel (discard) operation if any of the limits are passed (any overflow/underflow).
    if(MinX > (DX + s) || (MinY > (DY + s))|| (MaxX < (DX + s))|| (MaxY < (DY + s))) return *this;
    
    DX += s;
    DY += s;
    return *this;
}

float Size::Width() const
{
    return DX;
}

float Size::Height() const
{
    return DY;
}



float Size::R()
{
    return DX * DY;
}
Size::Size(float DX_, float DY_):DX(DX_),DY(DY_)
{

}

Lsc::String Size::ToString() const
{
    Lsc::String Str = "%.02f,%.02f";
    Str << DX << DY;
    return Str;
    
}

}
