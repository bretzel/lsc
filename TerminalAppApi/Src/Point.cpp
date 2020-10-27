

#include <Lsc/TerminalAppApi/Point.h>


namespace Lsc::TAA
{

Point::Point(float X_ , float Y_) noexcept:
X(X_), Y(Y_)
{
}

Point& Point::operator+=(const Point& Pt_)
{
    X += Pt_.X;
    Y += Pt_.Y;
    return *this;
}


Point& Point::operator-=(const Point& Pt_)
{
    X -= Pt_.X;
    Y -= Pt_.Y;
    return *this;
}

Point Point::operator + (const Point& Pt_)const
{
    return {X + Pt_.X, Y + Pt_.Y};
}

Point Point::operator - (const Point& Pt_)const
{
    return {X - Pt_.X, Y - Pt_.Y};
}

bool  Point::operator == (const Point& Pt_)const { return false;}
bool  Point::operator <= (const Point& Pt_)const { return false;}
bool  Point::operator >= (const Point& Pt_)const { return false;}
bool  Point::operator != (const Point& Pt_)const { return false;}
bool  Point::operator < (const Point& Pt_) const {return false;}
bool  Point::operator > (const Point& Pt_) const {return false;}


Point Point::operator[](const Point& Pt_)
{
    return {X - Pt_.X, Y - Pt_.Y};
}



std::string Point::ToString() const
{
    Lsc::String Str = "%f,%f";
    Str << X << Y;
    return Str();
}

}// naespace nui
