//
// Created by lsc on 20-10-29.
//

#include "Lsc/TerminalAppApi/Kernel/VCell.h"


namespace Lsc::TAA
{
void VCell::SetFG(Lsc::Ansi::Color FG_)
{
    A = (A & ~0xF00) | ((chtype)(static_cast<uint8_t>(FG_) << 8));
}

void VCell::SetBG(Lsc::Ansi::Color BG_)
{
    A = (A & ~0xF000) | ((chtype)(static_cast<uint8_t>(BG_) <<4) << 8);
}

void VCell::SetColor(Lsc::Ansi::Color BG_, Lsc::Ansi::Color FG_)
{
    A = (A & ~A_COLOR) | (((uint8_t)BG_ << 4 | (uint8_t)FG_) << 8);
}

void VCell::SetColor(short C_)
{
    A = (A & ~A_COLOR) | COLOR_PAIR(C_);
}


void VCell::SetAttr(chtype A_, bool Set)
{
    if(!Set)
        A |= ~A_;
    else
        A |= A_;
}


VCell &VCell::operator=(uint8_t Asc_)
{
    A = (A & ~0xFF) | Asc_;
    return *this;
}


Return VCell::Initialize()
{
    start_color();
    // Build 256 color pairs from the first 16 std colors.
    int C = 0;
    for(int fg=0; fg<16;fg++)
        for(int bg=0;bg<16; bg++)
            init_pair(C++, fg,bg);
        
    return Rem::Int::Implement;
}
VCell::Str VCell::Render(const String &S_, const VCell& V_)
{
    auto Bloc = new VCell[S_.Length() + 1];
    Rem::Debug() << "Bloc of " << S_.Length() << " bytes created...";
    
    int i=0;
    for(auto c : S_())
        Bloc[i] = V_.A|c;
    return Bloc;
}

void VCell::Free(VCell::Str B_)
{
    delete [] B_;
}

}