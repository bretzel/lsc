#pragma once


#include <ncurses.h>
#include <Lsc/TerminalAppApi/Kernel/VCell.h>
#include <Lsc/TerminalAppApi/Rect.h>



namespace Lsc::TAA 
{

struct VCD
{
    VCell::Str _D = nullptr;
    Size       _SZ;
    
    VCD() = default;
    VDC(const Size& Sz_);
    
    ~VDC();
    
    Return Copy(const VDC& Src_, const Point Off_);
    Return Scroll(const Point& DT_);
    
        
};


}