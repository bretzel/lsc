//
// Created by lsc on 20-08-23.
//

#include <Lsc/TerminalAppApi/Rect.h>

namespace Lsc::TAA{


Rect::operator bool() const {
    return ( (WH.DX > 0.f) && (WH.DY > 0.f));
}

float Rect::Width() const {
    return WH.DX;
}

float Rect::Height() const {
    return WH.DY;
}

float Rect::R() const {
    return WH.DX * WH.DY;
}


Rect Rect::Null;


Rect::Rect (float x1, float y1, float w, float h )
{
    A = {x1, y1};
    B = {x1 + w -1, y1 + h -1} ;
    WH = {w,h};
}

Rect::Rect (const Point& a, float w, float h )
{
    A = { a.X, a.Y };
    B = { A.X + w -1, A.Y + h - 1 };
    WH = {w,h};
}

Rect::Rect (const Point& a, const Size& _size )
{
    A = a;
    A = {a.X + _size.DX -1, a.Y + _size.DY - 1};
    WH = _size;
}




Rect Rect::Intersect (const Rect& rec ) const
{
    // intersect self with <r>
    Rect r = Rect::Null;
    Point a,b;
    a = { A.X <= rec.A.X ? rec.A.X : A.X, A.Y <= rec.A.Y ? rec.A.Y : A.Y };
    b = { B.X <= rec.B.X ? B.X : rec.B.X, B.Y <= rec.B.Y ? B.Y : rec.B.Y };
    
    if ( !(Within ( a ) || Within ( b )) ) return r;
    r.Set ( a,b );
    return r;
}

/*!
 * @brief creates a Rect from the union between this Rect and the given one
 * @param rect r the given Rect to make the union with this Rect
 * @return new Rect as the result of the union
 */
Rect Rect::Un (const Rect& rr ) const
{
    float xx1,h,yy1,w;
    Rect rec;
    xx1 = rr.A.X < A.X ? rr.A.X : A.X;
    w = rr.WH.DX > WH.DX ? rr.WH.DX : WH.DX;
    yy1 = rr.A.Y < A.Y ? rr.A.Y : A.Y;
    h = rr.WH.DY > WH.DY ? rr.WH.DY : WH.DY;

    rec.Set ( xx1, yy1, w, h );
    return rec;
}




void Rect::Resize (const Size& S_ )
{
    WH = S_;
    B.X  = A.X + WH.DX -1;
    B.Y  = A.Y + WH.DY -1;
}


Lsc::String Rect::ToString() const
{
    Lsc::String s;
    s << '[' << A.X << ',' << A.Y << ',' << B.X << ',' << B.Y << "][" << WH.ToString() << ']';
    return s;
}


/*!
 * @brief  Check if the Point \c xy is inside this Rectangle.
 * @param xy  coodrinates at the same scale as this rectangle.
 * @return true, or false if xy is outside.
 */
bool Rect::operator&&(const Point& xy) const
{
    return ( xy.X >= A.X ) && ( xy.X <= B.X ) && (xy.Y >= A.Y ) && (xy.Y <= B.Y );
}


}
