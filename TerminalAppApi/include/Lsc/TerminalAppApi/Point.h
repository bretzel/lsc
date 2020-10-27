

#pragma once
//#include <ConIO++/Lib.h>
#include <Lsc/Rem/Rem.h>

namespace Lsc::TAA
{

struct  Point
{
    float X = -1.0f;
    float Y = -1.0f;

    using collection    = std::vector<Point>;
    
    Point() = default;
    Point(float aX, float aY) noexcept;
    Point(Point&& aPt) noexcept  = default;
    Point(const Point& aPt) = default ;
    ~Point() = default;

    
    Point& operator=(Point&& Pt_) noexcept  = default;
    Point& operator=(const Point& Pt_) = default;
    Point& operator+=(const Point& Pt_);
    Point& operator-=(const Point& Pt_);

    Point operator + (const Point& Pt_)const;
    Point operator - (const Point& Pt_)const;

    bool operator == (const Point& Pt_)const ;
    bool operator <= (const Point& Pt_)const ;
    bool operator >= (const Point& Pt_)const ;
    bool operator != (const Point& Pt_)const ;
    bool operator < (const Point& Pt_) const;
    bool operator > (const Point& Pt_) const;
    Point operator[](const Point& Pt_);
    [[nodiscard]] std::string ToString() const;
};

}
