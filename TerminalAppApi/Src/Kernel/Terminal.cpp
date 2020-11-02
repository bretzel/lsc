//
// Created by lsc on 20-10-27.
//

#include <Lsc/TerminalAppApi/Kernel/Terminal.h>
#include <Lsc/TerminalAppApi/Kernel/VCell.h>



namespace Lsc::TAA
{

Terminal::Terminal()
{

}
Terminal::~Terminal()
{
    if(_W)
        Close();
}
void Terminal::Close()
{
    endwin();
    _W = nullptr;
}


void Terminal::Init()
{
    setlocale(LC_ALL, "");
    _W = initscr();
    raw();
    noecho();
    keypad ( _W, true );
    cbreak();
    curs_set ( false );
    mousemask ( ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION | BUTTON1_RELEASED | BUTTON2_RELEASED | BUTTON3_RELEASED, nullptr );
    //nodelay(stdscr, true); // esc key ... ?
    
    getmaxyx ( _W, _SZ.DY, _SZ.DX );
    //Geometry = Rect{ {0, 0}, Geometry.WH};
    Rem::Debug();
    Rem::Debug() << " initial screen geometry: " << Ansi::Color::Yellow << _SZ.DX << Ansi::Color::White << "x" << Ansi::Color::Yellow << _SZ.DY;
    meta ( _W, true );
    int b = baudrate();
    Rem::Info();
    Rem::Info() << " the terminal baudrate is : " << Ansi::Color::Yellow << b;
    Rem::Info() << " mouse version is " << Ansi::Color::Yellow << NCURSES_MOUSE_VERSION;
    
    VCell::Initialize();
    
    Rem::Info() << " Can redefine RGB: " <<  (can_change_color() ? "YES" : "No");
    Rem::Info() << " color_pairs: " << Ansi::Color::DeepSkyBlue1 << COLOR_PAIRS;
    Rem::Info() << " Colors : " << Ansi::Color::DeepPink8 << COLORS;
    Rem::Info() << " Size of cchar_t:" << Ansi::Color::Lime << sizeof(cchar_t);
    Rem::Info() << " Size of VCell:" << Ansi::Color::Lime << sizeof(VCell);
    
    Lsc::String Str = " Color BITS: %s [%08b]";
    Str << Lsc::Ansi::ToString(Ansi::Color::White) << A_COLOR;
    Rem::Info() << Str();
    
    Rem::Info() << " Screen Area: " << Ansi::Color::OrangeRed1 << _SZ.R() << Ansi::Color::Reset << " bytes";
    //Rem::Info() << " Size of one VCAttr: " << Ansi::Color::OrangeRed1 << sizeof(VCA) << Color::Reset << " bytes";
    //Rem::Info() << " SizeOf VCA: " << Color::OrangeRed1 << (int)Geometry.R() * sizeof(VCA) << Color::Reset << " bytes";
    int Char = 0, Y=1, X=1;
    mvaddch(Y,X-1,' ');
    const char *H="0123456789ABCDEF";
    for(int p=0; p<256; p++)
    {
        if(Char > 15 )
        {
            Char=0;
            ++Y;
            mvaddch(Y, X,p<<8 | H[Char++]);
        }
        else
            addch(p<<8 | H[Char++]);
    }
    
    VCell::Str Bloc = nullptr;
    VCell C;
    C.SetFG(Lsc::Ansi::Color::White);
    C.SetBG(Lsc::Ansi::Color::Blue);
    VCell::Render(Str, C);
    mvaddchnstr(1,1,(chtype*)Bloc,Str.Length());
    VCell::Free(Bloc);

    
}
}