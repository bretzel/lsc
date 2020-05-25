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
//class __declspec(dllimport) std::thread;
#   define _CRT_SECURE_NO_WARNINGS
#   define _SCL_SECURE_NO_WARNINGS

#   ifdef SCRIPTURE_DLL_EXPORT
#       define SCRIPTURE_LIB __declspec(dllexport)
#       if __GNUC__ >= 4
#           define SCRIPTURE_LIB __attribute__ ((visibility ("default")))
#           define PRIVATE_LIB  __attribute__ ((visibility ("hidden")))
//#       else
//#           define SCRIPTURE_LIB
//#           define PRIVATE_LIB
#       endif
#   else
#       define SCRIPTURE_LIB __declspec(dllimport)
#   endif
#   else
#       define SCRIPTURE_LIB    // Not ms-Windows/MSVC
#endif

// Mandatory. Globally used where it needs to.

//---------------------------------------------

#ifndef DECLOBJ_ID
#define DECLOBJ_ID \
    public:\
        virtual const char* RefClassName() const noexcept; \
    private:

#define  CLASSNAME_IMPL(CLASS) \
         const char*  CLASS::RefClassName() const noexcept{ return #CLASS; }
#endif

#ifndef _WIN32
#   define _strdup  strdup

#   include <thread>
#   include <cstdint>

#else
#   define __PRETTY_FUNCTION__ __FUNCSIG__
#endif
//#endif //SCRIPTURE_LIB_H
