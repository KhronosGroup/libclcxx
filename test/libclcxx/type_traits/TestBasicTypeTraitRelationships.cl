// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_type_traits>
using namespace cl; 

kernel void worker( )
{     
    // tests of type relationships
    struct c1 { void m( ) { } };
    struct c2 : c1 { };
    
    static_assert( is_base_of<c1, c2>::value == true, "" );
    static_assert( is_base_of<c2, c1>::value == false, "");

    static_assert( is_convertible<c1, c2>::value == false, "" );
    static_assert( is_convertible<c2, c1>::value == true, "");

    static_assert( is_same<c1, c2>::value == false, "" );
    static_assert( is_same<c1, c1>::value == true, "");

    typedef int t[][1][2][3];
    static_assert( extent<t, 0>::value == 0, "" );
    static_assert( extent<t, 1>::value == 1, "" );
    static_assert( extent<t, 2>::value == 2, "" );
    static_assert( extent<t, 3>::value == 3, "" );
    static_assert( extent<t, 4>::value == 0, "" );

    static_assert( rank<int>::value == 0, "" );
    static_assert( rank<int[]>::value == 1, "" );
    static_assert( rank<int[5]>::value == 1, "" );
    static_assert( rank<int[][5]>::value == 2, "" );
}
