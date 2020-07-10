//
// Created by bretzel on 20-04-17.
//

//#ifndef LIB_H
//#define LIB_H

#pragma once

//#pragma warning(once: 4251)


#ifdef LSC
# undef LSC
#endif

#ifdef _WIN32
#   pragma warning(disable : 4996)
#   pragma warning(disable : 4005)
//class __declspec(dllimport) std::thread;
#   define _CRT_SECURE_NO_WARNINGS
#   define _SCL_SECURE_NO_WARNINGS

#   ifdef VAULT_DLL_EXPORT
#       define VAULT_LIB __declspec(dllexport)
#   else
#       define VAULT_LIB __declspec(dllimport)
#   endif
#else
#   ifdef VAULT_DLL_EXPORT
#       if __GNUC__ >= 4
#           define VAULT_LIB __attribute__ ((visibility ("default")))
#           define PRIVATE_LIB  __attribute__ ((visibility ("hidden")))
#       endif
#   else 
#       define VAULT_LIB    // Not ms-Windows/MSVC
#   endif
#endif

// Mandatory. Globally used where it needs to.
#include <sqlite3.h>


//#ifndef _WIN32
//#   define _strdup  strdup
//
//#   include <thread>
//#   include <cstdint>
//
//#else
//#   define __PRETTY_FUNCTION__ __FUNCSIG__
//#endif
//#endif //VAULT_LIB_H
