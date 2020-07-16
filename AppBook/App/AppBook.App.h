//
// Created by lsc on 20-07-07.
//

//#ifndef LSC_APP_H
//#define LSC_APP_H

#pragma once

#include <Lsc/Rem/Rem.h>
#include <Lsc/AppBook/AppBook.h>



namespace Lsc
{


class AppBookApp
{
    String mDbName;
    
public:
    
    AppBookApp() = default;
    Return operator()(const String::Collection& Args_);
    
    Return InitAndCreateDatabase();
    
    
    
};
}


//#endif //LSC_APP_H
