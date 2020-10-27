//
// Created by lsc on 20-10-27.
//

//#ifndef LSC_TERMINAL_H
//#define LSC_TERMINAL_H
#pragma once
#include <ncurses.h>
#include <Lsc/TerminalAppApi/Rect.h>


namespace Lsc::TAA
{

class Terminal
{
    WINDOW*  _W = nullptr;
    Size     _SZ;
    
    
};
}
//#endif //LSC_TERMINAL_H
