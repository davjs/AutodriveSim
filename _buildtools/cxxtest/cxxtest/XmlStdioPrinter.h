#ifndef __CXXTEST__XMLSTDIOPRINTER_H
#define __CXXTEST__XMLSTDIOPRINTER_H

//
// The XmlStdioPrinter is an XmlFormatter which defaults to stdout.
//

#include <cxxtest/XmlFormatter.h>

#include <cxxtest/Flags.h>
#ifndef _CXXTEST_HAVE_STD
#   define _CXXTEST_HAVE_STD
#endif // _CXXTEST_HAVE_STD

#ifdef _CXXTEST_OLD_STD
#   include <iostream.h>
#else // !_CXXTEST_OLD_STD
#   include <iostream>
#endif // _CXXTEST_OLD_STD

namespace CxxTest 
{
    class XmlStdioPrinter : public XmlFormatter
    {
    public:
        XmlStdioPrinter( std::ostream &o = std::cout) : XmlFormatter( new Adapter(o) ) {}
        virtual ~XmlStdioPrinter() { delete outputStream(); }

    private:
        class Adapter : public OutputStream
        {
            std::ostream &_o;
        public:
            Adapter( std::ostream &o ) : _o(o) {}
            void flush() { _o.flush(); }
            OutputStream &operator<<( const char *s ) { _o << s; return *this; }
            OutputStream &operator<<( Manipulator m ) { return OutputStream::operator<<( m ); }
            OutputStream &operator<<( unsigned i )
            {
                char s[1 + 3 * sizeof(unsigned)];
                numberToString( i, s );
                _o << s;
                return *this;
            }
        };
    };
}

#endif // __CXXTEST__XMLSTDIOPRINTER_H
