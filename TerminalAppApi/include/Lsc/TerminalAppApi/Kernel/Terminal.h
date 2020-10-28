//
// Created by lsc on 20-10-27.
//

//#ifndef LSC_TERMINAL_H
//#define LSC_TERMINAL_H
#pragma once
#include <ncurses.h>
#include <Lsc/TerminalAppApi/Rect.h>
#include <Lsc/Rem/Rem.h>


namespace Lsc::TAA
{

class Terminal
{
    WINDOW*  _W = nullptr;
    Size     _SZ;
    Point    _XY;
public:
    Terminal();
    virtual ~Terminal();
    
    void Close();
    void Init();
    
};
}
//#endif //LSC_TERMINAL_H
