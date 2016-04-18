// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_type_traits>
using namespace cl; 

kernel void worker( )
{     
    // tests of composite types categories
    struct a { int m; a( int i, char j ) { } };
    union u { int a; char b; };
    
    static_assert( is_arithmetic<int>::value == true, "" );
    static_assert( is_arithmetic<float>::value == true, "" );
    static_assert( is_arithmetic<char>::value == true, "" );
    static_assert( is_arithmetic<a>::value == false, "" );
    static_assert( is_arithmetic<u>::value == false, "" );

    static_assert( is_compound<int>::value == false, "" );
    static_assert( is_compound<float>::value == false, "" );
    static_assert( is_compound<char>::value == false, "" );
    static_assert( is_compound<a>::value == true, "" );
    static_assert( is_compound<u>::value == true, "" );

    static_assert( is_fundamental<int>::value == true, "" );
    static_assert( is_fundamental<void>::value == true, "" );
    static_assert( is_fundamental<decltype(nullptr)>::value == true, "" );
    static_assert( is_fundamental<float>::value == true, "" );
    static_assert( is_fundamental<a>::value == false, "" );
    static_assert( is_fundamental<u>::value == false, "" );

    static_assert( is_member_pointer<a*>::value == false, "" );
    static_assert( is_member_pointer<int a::*>::value == true, "" );
    static_assert( is_member_pointer<void(a::*)( )>::value == true, "" );

    static_assert( is_object<float>::value == true, "" );
    static_assert( is_object<a>::value == true, "" );
    static_assert( is_object<int(float)>::value == false, "" );
    static_assert( is_object<a&>::value == false, "" );
    static_assert( is_object<a*>::value == true, "" );

    static_assert( is_reference<a>::value == false, "" );
    static_assert( is_reference<int&>::value == true, "" );
    static_assert( is_reference<u&&>::value == true, "" );

    static_assert( is_scalar<float>::value == true, "" );
    static_assert( is_scalar<a>::value == false, "" );
    static_assert( is_scalar<int(float)>::value == false, "" );
    static_assert( is_scalar<a&>::value == false, "" );
    static_assert( is_scalar<a*>::value == true, "" );
}
