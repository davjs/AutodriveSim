#ifndef __CXXTEST_PRESYSTEM_H
#define __CXXTEST_PRESYSTEM_H

//
// This file basically does #include <string>
// It exists to support warning level 4 in Visual C++
//

#ifdef _MSC_VER
#   pragma warning( push, 1 )
#endif // _MSC_VER

#include <string>

#ifdef _MSC_VER
#   pragma warning( pop )
#endif // _MSC_VER

#endif // __CXXTEST_PRESYSTEM_H
