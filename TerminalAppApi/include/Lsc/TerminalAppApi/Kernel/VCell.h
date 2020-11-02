//
// Created by lsc on 20-10-29.
//

//#ifndef LSC_VCELL_H
//#define LSC_VCELL_H
#pragma once
#include <ncurses.h>

#include <Lsc/Rem/Rem.h>



namespace Lsc::TAA
{

struct VCell
{
    using Str = VCell *;
    chtype A = 0x20;
    
    VCell() = default;
    VCell(VCell &&) noexcept = default;
    VCell(const VCell &) = default;
    ~VCell() = default;
    
    void SetFG(Lsc::Ansi::Color FG_);
    void SetBG(Lsc::Ansi::Color BG_);
    
    void SetColor(Lsc::Ansi::Color BG_, Lsc::Ansi::Color FG_);
    void SetColor(short C_);
    
    void SetAttr(chtype A_, bool Set = true);
    
    VCell &operator=(uint8_t);
    
    VCell &operator=(VCell &&) noexcept = default;
    VCell &operator=(const VCell &) = default;
    VCell &operator=(chtype A_)
    {
        A = A_;
        return *this;
    }
    VCell &operator=(int A_)
    {
        A = static_cast<chtype>(A_);
        return *this;
    }
    chtype operator*()
    { return A; }
    
    static VCell::Str Render(const Lsc::String& S_, const VCell& V_);
    static void Free(VCell::Str B_);
    
    static Return Initialize();
};

}

//#endif //LSC_VCELL_H
