#ifndef __cxxtest__XmlFilePrinter_h__
#define __cxxtest__XmlFilePrinter_h__

//
// The XmlFilePrinter is a simple TestListener that
// uses the XmlFormatter for formatting the test suites' output.
// This class uses <stdio.h>, i.e. FILE * and fprintf().
//

#include <cxxtest/XmlFormatter.h>
#include <stdio.h>
#include <string>

namespace CxxTest 
{
    class XmlFilePrinter : public XmlFormatter
    {
    public:
        XmlFilePrinter(std::string s) :
            XmlFormatter( new Adapter( fopen( (s.length() > 0 ? s.c_str() : "TestSuiteReport.xml"), "w" ) ) ) {}
        virtual ~XmlFilePrinter() { delete outputStream(); }

    private:
        class Adapter : public OutputStream
        {
            Adapter( const Adapter & );
            Adapter &operator=( const Adapter & );
            
            FILE *_o;
            
        public:
            Adapter( FILE *o ) : _o(o) {}
            void flush() { fflush( _o ); }
            OutputStream &operator<<( unsigned i ) { fprintf( _o, "%u", i ); return *this; }
            OutputStream &operator<<( const char *s ) { fputs( s, _o ); return *this; }
            OutputStream &operator<<( Manipulator m ) { return OutputStream::operator<<( m ); }
        };
    };
}

#endif // __cxxtest__XmlFilePrinter_h__
