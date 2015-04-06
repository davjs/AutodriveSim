#ifndef __CXXTEST__SIGNALS_H
#define __CXXTEST__SIGNALS_H

#ifdef CXXTEST_TRAP_SIGNALS

#include <iostream>
#include <string>
#include <setjmp.h>

// This file holds the declarations for the support
// features used for trapping and returning from signal-
// based failures.

namespace CxxTest
{
    const int __cxxtest_jmpmax = 10;
    extern sigjmp_buf            __cxxtest_jmpbuf[__cxxtest_jmpmax];
#ifdef CXXTEST_TRACE_STACK
    extern unsigned int          __cxxtest_stackTopBuf[__cxxtest_jmpmax];
    extern unsigned int          __cxxtest_stackTop;
    extern bool                  __cxxtest_handlingOverflow;
#   define _TS_SAVE_TRACE_STACK \
    CxxTest::__cxxtest_stackTopBuf[CxxTest::__cxxtest_jmppos] = \
    CxxTest::__cxxtest_stackTop
#   define _TS_RESTORE_TRACE_STACK \
    CxxTest::__cxxtest_stackTop = \
    CxxTest::__cxxtest_stackTopBuf[CxxTest::__cxxtest_jmppos]; \
    CxxTest::__cxxtest_handlingOverflow = false
#else
#   define _TS_SAVE_TRACE_STACK
#   define _TS_RESTORE_TRACE_STACK
#endif
    extern volatile sig_atomic_t __cxxtest_jmppos;
    extern std::string           __cxxtest_sigmsg;
    extern std::string           __cxxtest_assertmsg;

#define _TS_TRY_WITH_SIGNAL_PROTECTION					\
    if ( ++CxxTest::__cxxtest_jmppos >= CxxTest::__cxxtest_jmpmax ) {	\
	std::cout << "Too many nested signal handler levels.\n";	\
	exit( 1 ); }							\
    _TS_SAVE_TRACE_STACK;						\
    if ( !sigsetjmp(CxxTest::__cxxtest_jmpbuf[CxxTest::__cxxtest_jmppos], 1) )
#define _TS_SIGNAL_CLEANUP \
    { CxxTest::__cxxtest_jmppos--; __cxxtest_sigmsg = ""; }
#define _TS_CATCH_SIGNAL( action )					\
    else { action; _TS_RESTORE_TRACE_STACK; } _TS_SIGNAL_CLEANUP
    
#define _TS_THROWS_NO_SIGNAL( msg, action )          	   		\
    _TS_TRY_WITH_SIGNAL_PROTECTION action				\
    _TS_CATCH_SIGNAL( { CxxTest::doFailTest( __FILE__, __LINE__, msg ); } )
#define TS_MESSAGE_FOR_SIGNAL( msg ) ( CxxTest::__cxxtest_sigmsg = msg )
}

#else
#define _TS_TRY_WITH_SIGNAL_PROTECTION
#define _TS_CATCH_SIGNAL( action )
#define _TS_SIGNAL_CLEANUP
#define _TS_THROWS_NO_SIGNAL( msg, action ) action
#define TS_MESSAGE_FOR_SIGNAL( msg )
#endif

#endif
