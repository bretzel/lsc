//
// Created by lsc on 20-05-18.
//
//
//#ifndef LSC_APP_H
//#define LSC_APP_H
#pragma once
#include <Lsc/Rem/Rem.h>
#include <Lsc/Scripture/Types.h>


namespace Lsc
{

    class App
    {
        String mString;

    public:
        App() = default;
        ~App();

        Return operator()();

    private:

        Return Type(std::string Txt_);
        Return Tokens(std::string Txt_);
        Return LexerScan(std::string Txt_);
        Return ArithmeticLogicalUnit();

    };
}
//#endif //LSC_APP_H
