//
// Created by lsc on 20-07-23.
//

#include <Lsc/Rem/RemColor.h>


namespace Lsc::Ansi
{
    
String ToString(Color C_)
{
    String Str ;
    if(C_ == Color::Reset )
    {   Str << "\033[0m;";
        return Str;
    }
    
    Str << "\033[38;5;" << static_cast<int>(C_) << 'm';
    return Str;    
}

}
