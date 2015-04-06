#include <memory>
#include <new>
#include <cstdio>

#define REALLY_FREE
#define CLEAR_FREED_MEMORY
#define OUTFILE stdout
#ifndef MW_PREFIX
#  define MW_PREFIX
#endif

#if defined(CXXTEST_TRACE_STACK) && !defined(MW_STACK_WINDOW_SIZE)
#  define MW_STACK_WINDOW_SIZE 8
#endif
#ifndef MW_STACK_TRACE_INITIAL_PREFIX
#   define MW_STACK_TRACE_INITIAL_PREFIX MW_PREFIX "  allocated using: "
#endif
#ifndef MW_STACK_TRACE_OTHER_PREFIX
#   define MW_STACK_TRACE_OTHER_PREFIX MW_PREFIX "  allocated using: "
#endif


namespace Memwatch
{
//*******************************************************//
//                       MemWatch                        //
//*******************************************************//
// Copyright © 1995 Terry Richards Software. All rights  //
// reserved. You may use this code free of charge except //
// that you may not sell it. If you distribute this file //
// please do so without modification.                    //
//*******************************************************//
// If you feel this code is of some value please locate  //
// somebody that needs it and give that amount to them.  //
// I would appreciate it if you would let me know what   //
// you did.                                              //
//*******************************************************//
// MemWatch is a simple but suprisingly powerful memory  //
// monitor. It can detect the following memory errors:   //
//  1) new without delete.                               //
//  2) multiple deletes of the same block.               //
//  3) corrupted pointers.                               //
//  4) memory overwrites.                                //
//  5) memory underwrites.                               //
// A comprehensive report of any errors detected is      //
// written to MEMWATCH.LOG                               //
//*******************************************************//
// To use MemWatch simply add this file to your project  //
// and recompile. After testing you should remove it as  //
// it disables the XAlloc exception and it has an impact //
// on performance.                                       //
// This code is most useful in a 32 bit program but also //
// works and provides useful data in a 16 bit EXE.       //
//*******************************************************//
// Version 1 released 7/13/95 - Initial release          //
// Version 2 (10/10/04) - heavily revised for use in     //
//                        in CS 2704/2604                //
//*******************************************************//
// Terry Richards                                        //
// Terry Richards Software                               //
// 58A Phelps Ave.                                       //
// New Brunswick NJ 08901                                //
// USA                                                   //
// (908) 545-6533                                        //
// CIS: 72330,1026                                       //
//*******************************************************//

// By default, this code reports all NULL deletes. If you have
// a lot of these this can become annoying. You can turn off
// these reports by commenting out the next line.
// #define REPORT_NULLS

// Number of memory blocks that can be open.
// A message will be generated if
// this is too small. As a rough guide, 400 is
// enough for a trivial AppExpert program but
// a program with a lot of memory activity can
// use as many as 10,000 entries.
const int numEntries = 10000;

// The safety character. The safety areas are filled with this
// character so we can check them for memory over/underwrites
const char safetyChar = '!';

// The size of the safety areas.
// The bigger you make these, the better your chances
// of catching a memory over/under-run. However,
// hiSafetySize + loSafetySize bytes are added
// to each memory allocation.

//    ***** IMPORTANT *****
// If you link with the dynamic libraries of if you have
// any classes that have their own operator delete (or
// delete[]) without a corresponding operator new (or
// new[]) and that operator doesn't call ::delete
// (or ::delete[]) then you should set loSafetySize to
// zero. If you start getting strange crashes on deletes
// this is probably the problem.
const int hiSafetySize = 30;
const int loSafetySize = 30;

// The max depth of the call stack to save (and print)
// Currently this is only used for 32 bit code.
// It does no harm to reduce this but you may not see the
// full call stack on some calls.
#define CALL_STACK_DEPTH 30

struct MemControl
{
    void*  Address;
    size_t Size;
    bool   isArray;
};

MemControl DB[numEntries];
bool DB_Blown = false;

// Global variables are used because we can't change
// the parms or return types for new & delete.

int     MaxUsed;
int     NumNewArray;
int     NumNewNonArray;
int     NumArrayDeletes;
int     NumNonArrayDeletes;
int     NumNullDeletes;
bool    NewCalled = false;

// This flag is used to prevent recursion. We set it whenever we are creating
// or destroying an ofstream object.

bool InternalCall    = false;
bool reportGenerated = false;

// EggSit. This is the exit reporter. It is installed by
// an object declaration immediately following the class definition.
// This method makes it execute even later than a function
// installed with atexit(). It scans the database to see
// if there are any memory blocks left that have been
// allocated but not deleted.
class FinalReportGenerator
{
public:
    ~FinalReportGenerator() _CXXTEST_NO_INSTR;
};
FinalReportGenerator::~FinalReportGenerator()
{
    // Have to use C-style output, since the
    // standard C++ objects have already been finalized!
    bool First = true;
    reportGenerated = true;
    InternalCall = true; // Turn off reporting

#ifdef MW_XML_OUTPUT_FILE
	FILE* xmlFile = fopen(MW_XML_OUTPUT_FILE, "w");
	fprintf( xmlFile, "<?xml version='1.0'?>\n");
	fprintf( xmlFile, "<memwatch>\n");
#endif

    // Search the database
    for ( int i = 0; i < MaxUsed; i++ )
    {
        if ( DB[i].Address )
        {
        // We found an orphan block.
        if ( First )
            {
        // At least, we think we did. The text explains all.
#ifndef MW_XML_OUTPUT_FILE
                fprintf( OUTFILE,
                         "\n" MW_PREFIX
             "******************* LEAKS *******************\n"
             MW_PREFIX
                         "Possible memory leaks detected.\n"
             // MW_PREFIX
             //" A small number of these leaks"
                         // "may be due to standard library code.\n"
             MW_PREFIX
                         "The identified leaks:\n" MW_PREFIX "\n" );
#endif
                         
                First = false;
            }

            // Write out everything we know about the bad block.
            // If you put a breakpoint here and a watch on
            // DB[i].From you can use the CPU window to find
            // the exact statement. (Right click, Go To)
#ifdef MW_XML_OUTPUT_FILE
			fprintf( xmlFile, "    <leak "
				"address=\"%p\" size=\"%lu\" %s>\n",
				DB[i].Address, (unsigned long)DB[i].Size,
				(DB[i].isArray ? "array=\"yes\"" : ""));
				
#else
            fprintf( OUTFILE,
                     // "\n******************* ERROR *******************\n"
             MW_PREFIX
                     "Memory block at %p not deleted (", DB[i].Address );
            if ( DB[i].isArray ) fprintf( OUTFILE, "array " );
            fprintf( OUTFILE, "%lu byte(s) long", (unsigned long)DB[i].Size );
      //if ( DB[i].Size > 500 ) fprintf( OUTFILE, "--possible STL leak?" );
            fprintf( OUTFILE, ").\n" );
#endif

#ifdef CXXTEST_TRACE_STACK
            fprintf( 
#ifdef MW_XML_OUTPUT_FILE
			xmlFile,
#else            
            OUTFILE,
#endif
                     getStackTrace( MW_STACK_WINDOW_SIZE,
                                    (CxxTest::StackElem*)(
                                        ((char*)DB[i].Address)
                                        + DB[i].Size + hiSafetySize ),
									MW_STACK_TRACE_INITIAL_PREFIX
                                  ).c_str() );
#endif
#ifdef MW_XML_OUTPUT_FILE
			fprintf( xmlFile, "    </leak>\n" );
#endif
        }
    }

#ifdef MW_XML_OUTPUT_FILE
	fprintf( xmlFile, "    <summary "
		"max-blocks=\"%d\" "
		"calls-to-new=\"%d\" "
		"calls-to-delete=\"%d\" "
		"calls-to-new-array=\"%d\" "
		"calls-to-delete-array=\"%d\" "
#ifdef REPORT_NULLS
		"calls-to-delete-null=\"%d\" "
#endif
		"/>\n",
        (MaxUsed + 1),
         NumNewNonArray,
         NumNonArrayDeletes,
         NumNewArray,
         NumArrayDeletes
#ifdef REPORT_NULLS
		,NumNullDeletes
#endif         
		);
#else
    fprintf( OUTFILE, "\n**************** SUMMARY ****************\n"
                      "Max blocks in use:            %d\n"
                      "Calls to new:                 %d\n"
                      "Calls to delete (non-NULL):   %d\n"
                      "Calls to new[]:               %d\n"
                      "Calls to delete[] (non-NULL): %d\n",
             (MaxUsed + 1),
             NumNewNonArray,
             NumNonArrayDeletes,
             NumNewArray,
             NumArrayDeletes );

#ifdef REPORT_NULLS
    fprintf( OUTFILE, "Calls to delete (NULL):     %d\n", NumNullDeletes );
#endif

#endif

#ifdef MW_XML_OUTPUT_FILE
	fprintf( xmlFile, "</memwatch>\n");
	fclose( xmlFile );
#endif

    InternalCall = false;
}


// This object declaration installs the exit function. Strictly speaking,
// priorities < 101 are reserved for the RTL but we want to execute as
// late as possible so we "borrow" it.
FinalReportGenerator reportGenerator __attribute__((init_priority(101)));


} // end of namespace


// Note, the static allocation of this will force its destructor
// to run *after* main(), but it won't properly account for
// deletions performed in the destructors of other globally
// allocated objects, since order of finalization isn't guaranteed here.

// This is the overloaded global new function. It stores info.
// about each allocation in the database and it puts a safety
// area before and after the memory block filled with a known character.
// For increased reliability you could run this twice with two
// different characters - just change the #define for safetyChar.
void* operator new(size_t Size)
{
    using namespace Memwatch;
    // If this is the first time, do some initialization...
    if ( !NewCalled )
    {
        NewCalled = true;
        // Initialize the stats
        MaxUsed            = 0;
        NumNewNonArray     = 0;
        NumNewArray        = 0;
        NumNonArrayDeletes = 0;
        NumArrayDeletes    = 0;
        NumNullDeletes     = 0;
    }

    // We don't report on ourselves
    if ( InternalCall )
        return malloc( Size );

    // Allocate the memory + the two safety pools
    void * RealMem = malloc( Size + loSafetySize + hiSafetySize
#ifdef CXXTEST_TRACE_STACK
                             + CxxTest::stackTraceSize( MW_STACK_WINDOW_SIZE )
#endif
                             );

    // Did we get it
    if ( !RealMem )
    {
        // No. All bets are off at this point but lets try
        // to report it.
#ifdef CXXTEST_TRAP_SIGNALS
    memwatch_assert( "out of memory" );
#else
        InternalCall = true;
        // Set a breakpoint on the next statement
        // to detect out of memory errors
        fprintf( OUTFILE, "\n" MW_PREFIX
             "******************* ERROR *******************\n"
             MW_PREFIX "Out of memory.\n" );
        InternalCall = false;
#endif

        return RealMem;
    }

    // This is the address we will tell the calling program
    // it can use.
    void * TheMem = (char *)RealMem + loSafetySize;

    if ( DB_Blown )
        return TheMem;

    // Fill the safety areas
    memset( (char *)RealMem, safetyChar, loSafetySize );
    memset( ((char *)TheMem) + Size, safetyChar, hiSafetySize );
#ifdef CXXTEST_TRACE_STACK
    CxxTest::saveStackTraceWindow( (CxxTest::StackElem*)(
                                     ((char *)TheMem) + Size + hiSafetySize ),
                                   MW_STACK_WINDOW_SIZE );
#endif

    // Find a free database entry
    int i;
    for ( i = 0; i < numEntries && DB[i].Address; i++ );

    if ( i == numEntries )
    {
        DB_Blown = true;
        InternalCall = true;
        // You can set a breakpoint on the next statement
        // If it is reached increase numEntries
        fprintf( OUTFILE, "\n" MW_PREFIX
             "*************** SERIOUS ERROR ***************\n"
         MW_PREFIX
         "Memory database too small - increase numEntries\n"
         MW_PREFIX
             "All following messages may be incorrect.\n" );
        InternalCall = false;

        return TheMem;
    }

    // Stats
    if ( i > MaxUsed )
        MaxUsed = i;
    NumNewNonArray++;

    // Store what we know about the memory block
    DB[i].Address = TheMem;
    DB[i].Size    = Size;
    DB[i].isArray = false;

    // and hand it back.
    return TheMem;
}


// We just pass it through to the regular new operator.
void* operator new( size_t size, const std::nothrow_t& )
{
    return ::operator new( size );
}


void* operator new[] ( size_t Size )
{
    using namespace Memwatch;
    // If this is the first time, do some initialization...
    if ( !NewCalled )
    {
        NewCalled = true;

        // Initialize the stats
        MaxUsed            = 0;
        NumNewNonArray     = 0;
        NumNewArray        = 0;
        NumNonArrayDeletes = 0;
        NumArrayDeletes    = 0;
        NumNullDeletes     = 0;
    }

    // We don't report on ourselves
    if ( InternalCall )
        return malloc( Size );

    // Allocate the memory + the two safety pools
    void * RealMem = malloc( Size + loSafetySize + hiSafetySize
#ifdef CXXTEST_TRACE_STACK
                             + CxxTest::stackTraceSize( MW_STACK_WINDOW_SIZE )
#endif
                             );

    // Did we get it
    if ( !RealMem )
    {
        // No. All bets are off at this point but lets try
        // to report it.
#ifdef CXXTEST_TRAP_SIGNALS
    memwatch_assert( "out of memory" );
#else
        InternalCall = true;
        // Set a breakpoint on the next statement
        // to detect out of memory errors
        fprintf( OUTFILE, "\n" MW_PREFIX
         "******************* ERROR *******************\n"
         MW_PREFIX "Out of memory.\n" );
        InternalCall = false;
#endif

        return RealMem;
    }

    // This is the address we will tell the calling program
    // it can use.
    void * TheMem = (char *)RealMem + loSafetySize;

    if ( DB_Blown )
        return TheMem;

    // Fill the safety areas
    memset( (char *)RealMem ,safetyChar, loSafetySize );
    memset( ((char *)TheMem) + Size, safetyChar, hiSafetySize );
#ifdef CXXTEST_TRACE_STACK
    CxxTest::saveStackTraceWindow( (CxxTest::StackElem*)(
                                     ((char *)TheMem) + Size + hiSafetySize ),
                                   MW_STACK_WINDOW_SIZE );
#endif

    // Find a free database entry
    int i;
    for ( i = 0; i < numEntries && DB[i].Address; i++ );

    if ( i == numEntries )
    {
        DB_Blown = true;
        InternalCall = true;
        // You can set a breakpoint on the next statement
        // If it is reached increase numEntries
        fprintf( OUTFILE, "\n" MW_PREFIX
         "*************** SERIOUS ERROR ***************\n"
         MW_PREFIX
                 "Memory database too small - increase numEntries\n"
         MW_PREFIX
                 "All following messages may be incorrect.\n" );
        InternalCall = false;

       return TheMem;
    }

    // Stats
    if ( i > MaxUsed )
        MaxUsed = i;
    NumNewArray++;

    // Store what we know about the memory block
    DB[i].Address = TheMem;
    DB[i].Size    = Size;
    DB[i].isArray = true;

    // and hand it back.
    return TheMem;
}


void* operator new[]( size_t size, const std::nothrow_t& )
{
    return ::operator new[]( size );
}


// Operator delete. We can check that the pointer was
// previously created by new and that it has not already been
// deleted. We can also check if the safety pools have been
// stepped on.
void operator delete( void* TheMem )
{
    using namespace Memwatch;
    char  HiTestString[hiSafetySize];
    char  LoTestString[ ( loSafetySize > 0 ) ? loSafetySize : 0 ];
    void* RealMem = (char *)TheMem - loSafetySize;
    bool  UnderWrite = false;
    bool  OverWrite = false;

    // Memory we allocated ourselves is not watched
    if ( InternalCall )
    {
        if ( TheMem )
            free( TheMem );
        return;
    }

    if ( TheMem )
    {
        NumNonArrayDeletes++;
        if ( reportGenerated )
        {
            InternalCall = true;
            fprintf( OUTFILE, "\n" MW_PREFIX
             "****************** Wait ******************\n"
             MW_PREFIX
                     "Caught one more deleted block (%d/%d"
             MW_PREFIX
                     " non-array blocks freed).\n",
                     NumNonArrayDeletes, NumNewNonArray );
            InternalCall = false;
        }
    }
    else
        NumNullDeletes++;

    if ( !TheMem )
    {
#ifdef REPORT_NULLS
        InternalCall = true;
        // It is always valid to delete a null pointer
        // but you can set a breakpoint here to detect it.
        fprintf( OUTFILE, "\n" MW_PREFIX
             "****************** WARNING ******************\n"
             MW_PREFIX "NULL pointer deleted.\n"
             MW_PREFIX "This is valid but suspicious\n" );
        InternalCall = false;
#endif //REPORT_NULLS
        return;
    }

    if ( DB_Blown )
        return;

    // Is this pointer in our database?
    int i;
    for ( i = 0; i < numEntries && DB[i].Address != TheMem; i++ );

    if ( i == numEntries )
    {
        // No. This is not good.
#ifdef CXXTEST_TRAP_SIGNALS
        memwatch_assert( "attempt to delete unknown pointer" );
#else
        InternalCall = true;
        // Set a breakpoint on the next statement
        // If it is reached you are freeing something
        // that was not allocated or you are freeing
        // something twice.
        fprintf( OUTFILE, "\n" MW_PREFIX
             "******************* ERROR *******************\n"
             MW_PREFIX
             "Attempt to delete unknown pointer %p.\n"
             MW_PREFIX
             "Either the pointer is corrupt or was deleted \n"
             MW_PREFIX
             "multiple times. \n",
             TheMem );
        InternalCall = false;
#endif
#ifdef REALLY_FREE
#  ifdef ALLOW_CORRUPTION
        free(RealMem);  // Don't actually corrupt the stack!
#  endif
#endif
        return;
    }

    // Check the safety areas to see if they are the same as when
    // we handed the memory out.
    memset( HiTestString, safetyChar, hiSafetySize );
    memset( LoTestString, safetyChar, loSafetySize );

    if ( memcmp( (char *)RealMem, LoTestString, loSafetySize ) )
        UnderWrite = true;

    if ( memcmp( ((char *)TheMem) + DB[i].Size,
             HiTestString,
             hiSafetySize ) )
        OverWrite = true;

    if ( OverWrite || UnderWrite )
    {
        // It's different--report the fact.
        InternalCall = true;
        // Set a breakpoint on the next statement
        // If it is reached the memory block has been
        // corrupted.
        fprintf( OUTFILE, "\n" MW_PREFIX
             "****************** WARNING ******************\n"
             MW_PREFIX "The memory block at %p is corrupt.\n",
             TheMem );
        if ( UnderWrite )
            fprintf( OUTFILE, MW_PREFIX
                 "The low safety area has been changed.\n" );
        if ( OverWrite )
            fprintf( OUTFILE, MW_PREFIX
                 "The high safety area has been changed.\n" );
        InternalCall = false;
    }

#ifdef CLEAR_FREED_MEMORY
    // Zero out the memory to detect memory errors
    memset( TheMem, 0, DB[i].Size );
#endif

    // We found the pointer so remove it from the database.
    DB[i].Address = 0;
#ifdef CXXTEST_TRAP_SIGNALS
    if ( OverWrite || UnderWrite )
        memwatch_assert( "corrupt heap-allocated memory block detected" );
#endif
    if ( DB[i].isArray )
    {
#ifdef CXXTEST_TRAP_SIGNALS
    memwatch_assert( "pointer to array deleted incorrectly using "
             "operator delete" );
#else
        InternalCall = true;
        fprintf( OUTFILE, "\n" MW_PREFIX
         "******************* ERROR *******************\n"
         MW_PREFIX
                 "Pointer to array %p deleted using\n"
         MW_PREFIX
                 "operator delete instead of operator delete[]. \n",
                 TheMem );
        InternalCall = false;
#endif
    }
#ifdef REALLY_FREE
    free( RealMem );
#endif
}


// See the comment for operator new( nothrow )
void operator delete( void* TheMem, const std::nothrow_t& )
{
    // pass through to delete.
    ::delete (int*)TheMem;
}
void operator delete[]( void* TheMem )
{
    using namespace Memwatch;
    char      HiTestString[hiSafetySize];
    char      LoTestString[( loSafetySize > 0 ) ? loSafetySize : 0 ];
    void*     RealMem = (char *)TheMem - loSafetySize;
    bool      UnderWrite = false;
    bool      OverWrite = false;

    // Memory we allocated ourselves is not watched
    if ( InternalCall )
    {
        if ( TheMem )
            free( TheMem );
        return;
    }

    if ( TheMem )
    {
        NumArrayDeletes++;
        if ( reportGenerated )
        {
            InternalCall = true;
            fprintf( OUTFILE, "\n" MW_PREFIX
             "****************** Wait ******************\n"
             MW_PREFIX
                     "Caught one more deleted block (%d/%d"
             MW_PREFIX
                     " array blocks freed).\n",
                     NumArrayDeletes, NumNewArray );
            InternalCall = false;
        }
    }
    else
        NumNullDeletes++;

    if ( !TheMem )
    {
#ifdef REPORT_NULLS
        InternalCall = true;
        // It is always valid to delete a null pointer
        // but you can set a breakpoint here to detect it.
        fprintf( OUTFILE, "\n" MW_PREFIX
         "****************** WARNING ******************\n"
         MW_PREFIX
                 "NULL pointer deleted.\n"
         MW_PREFIX
                 "This is valid but suspicious\n" );
        InternalCall = false;
#endif //REPORT_NULLS
        return;
    }

    if ( DB_Blown )
        return;

    // Is this pointer in our database?
    int i;
    for ( i = 0; i < numEntries && DB[i].Address != TheMem; i++ );

    if ( i == numEntries )
    {
        // No. This is not good.
#ifdef CXXTEST_TRAP_SIGNALS
        memwatch_assert( "attempt to delete unknown pointer" );
#else
        InternalCall = true;
        // Set a breakpoint on the next statement
        // If it is reached you are freeing something
        // that was not allocated or you are freeing
        // something twice.
        fprintf( OUTFILE, "\n" MW_PREFIX
         "******************* ERROR *******************\n"
         MW_PREFIX
                 "Attempt to delete unknown pointer %p.\n"
         MW_PREFIX
                 "Either the pointer is corrupt or was deleted \n"
         MW_PREFIX
      "multiple times. \n",
      TheMem );
        InternalCall = false;
#endif
#ifdef REALLY_FREE
#  ifdef ALLOW_CORRUPTION
        free( RealMem );  // Don't actually corrupt the stack!
#  endif
#endif
        return;
    }

    // Check the safety areas to see if they are the same as when
    // we handed the memory out.
    memset( HiTestString, safetyChar, hiSafetySize );
    memset( LoTestString, safetyChar, loSafetySize );

    if ( memcmp( (char *)RealMem, LoTestString, loSafetySize ) )
        UnderWrite = true;
    if ( memcmp( ((char *)TheMem) + DB[i].Size, HiTestString, hiSafetySize ) )
        OverWrite = true;

    if ( OverWrite || UnderWrite )
    {
        // It's different - report the fact.
        InternalCall = true;
        // Set a breakpoint on the next statement
        // If it is reached the memory block has been
        // corrupted.
        fprintf( OUTFILE, "\n" MW_PREFIX
         "****************** WARNING ******************\n"
         MW_PREFIX
                 "The memory block at %p is corrupt.\n",
                 TheMem );
        if ( UnderWrite )
            fprintf( OUTFILE, MW_PREFIX
             "The low safety area has been changed.\n" );
        if ( OverWrite )
            fprintf( OUTFILE, MW_PREFIX
             "The high safety area has been changed.\n" );
        InternalCall = false;
    }

#ifdef CLEAR_FREED_MEMORY
    // Zero out the memory to detect memory errors
    memset( TheMem, 0, DB[i].Size );
#endif

    // We found the pointer so remove it from the database.
    DB[i].Address = 0;
#ifdef CXXTEST_TRAP_SIGNALS
    if ( OverWrite || UnderWrite )
        memwatch_assert( "corrupt heap-allocated memory block detected" );
#endif
    if ( !DB[i].isArray )
    {
#ifdef CXXTEST_TRAP_SIGNALS
    memwatch_assert( "pointer to non-array deleted "
             "incorrectly using operator delete[]" );
#else
        InternalCall = true;
        fprintf( OUTFILE, "\n" MW_PREFIX
         "******************* ERROR *******************\n"
         MW_PREFIX
                 "Pointer to non-array %p deleted using\n"
         MW_PREFIX
                 "operator delete[] instead of operator delete. \n",
                 TheMem );
        InternalCall = false;
#endif
    }
#ifdef REALLY_FREE
    free( RealMem );
#endif
}


void operator delete[]( void* TheMem, const std::nothrow_t& )
{
    // pass through to delete.
    ::delete[] (int*)TheMem;
}
