//
// Created by lsc on 20-05-18.
//
//
//#ifndef LSC_APP_H
//#define LSC_APP_H
#pragma once
#include <Lsc/Rem/Rem.h>
#include <Lsc/Rem/Object.h>



namespace Lsc
{

class AppBook
{
    String mString;
    
public:
    AppBook() = default;
    ~AppBook();
    
    Return operator()();
    
private:
    
    //Return  Log();
    Return  LscObject();
};
}
//#endif //LSC_APP_H
