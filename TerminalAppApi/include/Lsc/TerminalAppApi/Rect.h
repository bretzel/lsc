//
// Created by lsc on 20-08-23.
//

//#ifndef ui_RECT_H
//#define ui_RECT_H

#pragma once
#include <Lsc/TerminalAppApi/Point.h>
#include <Lsc/TerminalAppApi/Size.h>

namespace Lsc::TAA
{

struct Rect
{
    Point A;
    Point B;
    Size WH;
    bool IsNull = true;

    using Collection = std::vector<Rect>;
    using Iterator   = Collection::iterator;
    using CIterator  = Collection::const_iterator;

    //typedef std::map<int, Rect> int_hash_t;
public:
    Rect() = default;
    Rect(float X_, float Y_, float W_, float H_);
    Rect(const Point &A_, float W_, float H_);
    Rect(const Point &A_, const Size &S_);
    
    
    Rect (Rect && a_r) noexcept = default;
    Rect& operator=(Rect&& a_r) noexcept = default;
    Rect (const Rect & _r) = default;
    Rect& operator=(const Rect& _r) = default;
    
    ~Rect() = default;

    [[nodiscard]] explicit operator bool() const;

    [[nodiscard]] float Width() const;

    [[nodiscard]] float Height() const;

    [[nodiscard]] float R() const;

    void operator()(float a, float b, float c, float d) {
        Set(a, b, c, d);
    }

    bool operator[](const Point &A_) const {
        return Within(A_);
    }

    Rect operator+(const Rect &R_) {
        Rect rr = {A.X + R_.A.X, A.Y + R_.A.Y, B.X + R_.B.X, B.Y + R_.B.Y};
        return rr;
    }

    Rect operator+(Point A_) const {
        return {A.X + A_.X, A.Y + A_.Y, Width(), Height()};
    }

    bool operator[](const Rect &R_) {
        // calling a(&b) is to verify if the entire b is inside this Rect boundaries.
        return Within(R_.A) && Within(R_.B);
    }

    bool operator!=(const Rect &R_) const {
        return R() != R_.R();
    }

    Rect operator-(Point P_) {
        return {A.X - P_.X, A.Y - P_.Y, Width(), Height()};
    }

    bool operator>=(const Rect &R_) const {
        return R() >= R_.R();
    }
    
    bool operator==(const Rect &R_) const {
        return WH.DX == R_.WH.DX && WH.DY == R_.WH.DY;
    }

    Rect operator&(const Rect &R_) const {
        return Intersect(R_);
    }


    // ------- disabled, for now....
    //    Rect &operator &= (const Rect &r) {
    //        *this = intersect(r);
    //        return *this;
    //    }

    Rect operator|(const Rect &R_) {
        return Un(R_);
    }

    //    Rect &operator|=(const Rect &r) {
    //        *this = un(r);
    //        return *this;
    //    }

    Rect &operator+=(const Rect &R_) {
        Move(R_.A);
        return *this;
    }

    Rect &operator-=(const Rect &R_) {
        Move(-R_.A.X, -R_.A.Y);
        return *this;
    }

    Rect &operator-=(const Point &P_) {
        Move(-P_.X, -P_.Y);
        return *this;
    }

    Rect &operator+=(const Point &P_) {
        Move(P_);
        return *this;
    }



    [[nodiscard]] bool Within(float X_, float Y_) const {
        return Within(Point(X_, Y_));
    }

    [[nodiscard]] bool Within(const Point &A_) const {
        return ((A_.X >= A.X) && (A_.X <= B.X) && (A_.Y >= A.Y) && (A_.Y <= B.Y));
    }

    Rect Intersect(const Rect &) const;


    void Set(float X_, float Y_, float W_, float H_) {
        A.X = X_;
        A.Y = Y_;
        WH.DX = W_;
        WH.DY = H_;
        B.X = A.X + W_ - 1;
        B.Y = A.Y + H_ - 1;
    }

    void Set(const Point &A_, const Point &B_) {
        A = A_;
        B = B_;
        WH.DX = B.X - A.X + 1;
        WH.DY = B.Y - A.Y + 1;
    }

    [[nodiscard]] Rect Un(const Rect &R_) const;

    //void ResizeTo(const Point &P_);

    void Resize(const Size &S_);

    //    void br_resize(const Point &dxy);

    void MoveTo(const Point &P_) {
        A.X = P_.X;
        A.Y = P_.Y;
        B.X = A.X + Width() - (A.X > 0.f ? 1 : 0.f);
        B.Y = A.Y + Height() -(A.Y > 0.f ? 1 : 0.f);
        //logdebugpfn << _b.x << '=' << _a.x << '+' << width() << '-' << (_a.x == 0 ? 1 : 0) << ends;
    }

    void Move(const Point &dxy) {
        A.X += WH.DX;
        A.Y += WH.DY;
        B.X += WH.DX;
        B.Y += WH.DY;
        // no validation check needed here...
    }

    void Move(float DX, float DY) {
        A.X += DX;
        A.Y += DY;
        B.X += DX;
        B.Y += DY;
    }

    void MoveTo(float X_, float Y_) {
        MoveTo({X_,Y_});
    }

    [[nodiscard]] float Sz() const {
        return Width() * Height();
    }

    [[nodiscard]] Lsc::String ToString() const;

    void RWC(const Point &dxy) {
        Set(A.X + (-1 * WH.DX), A.Y + (-1 * WH.DY), Width() + WH.DX * 2, Height() + WH.DY * 2);
    }

    /*!
     *        \fn stdui::Rect::bottomleft()
     */
    [[nodiscard]] Point B_L() const {
        return {A.X, B.Y};
    }

    /*!
     *        \fn stdui::Rect::topright()
     */
    [[nodiscard]] Point T_R() const {
        return {B.X, A.Y};
    }

    [[nodiscard]] bool operator&&(const Point &P_) const;


    static Rect Null;
};

}
    

//#endif //ui_RECT_H