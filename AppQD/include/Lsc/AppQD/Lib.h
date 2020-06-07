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

#   ifdef APPQD_DLL_EXPORT
#       define APPQD_LIB __declspec(dllexport)
#       if __GNUC__ >= 4
#           define APPQD_LIB __attribute__ ((visibility ("default")))
#           define PRIVATE_LIB  __attribute__ ((visibility ("hidden")))
//#       else
//#           define APPQD_LIB
//#           define PRIVATE_LIB
#       endif
#   else
#       define APPQD_LIB __declspec(dllimport)
#   endif
#   else
#       define APPQD_LIB    // Not ms-Windows/MSVC
#endif

// Mandatory. Globally used where it needs to.

//---------------------------------------------

#ifndef DECLOBJ_ID
#define DECLOBJ_ID \
    public:\
        virtual const char*  RefClassName() const noexcept; \
    private:

#define  CLASSNAME_IMPL(CLASS) \
         const char*   CLASS::RefClassName() const noexcept{ return #CLASS; }
#endif

#ifndef _WIN32
#   define _strdup  strdup

#   include <thread>
#   include <cstdint>

#else
#   define __PRETTY_FUNCTION__ __FUNCSIG__
#endif
//#endif //APPQD_LIB_H
