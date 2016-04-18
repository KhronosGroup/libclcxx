// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_type_traits>
using namespace cl; 

void f1( ){ }

kernel void worker( )
{     
    // tests of general type traits
    static_assert( is_array<int>::value == false, "" );
    static_assert( is_array<int[]>::value == true, "" );
    static_assert( is_array<int[5]>::value == true, "" );

    struct a { int m; a( int i, char j ) { } };
    static_assert( is_class<a>::value == true, "" );
    static_assert( is_class<char>::value == false, "" );
    
    enum e1 { x };
    enum class e2 { y };
    static_assert( is_enum<e1>::value == true, "" );
    static_assert( is_enum<e2>::value == true, "" );
    static_assert( is_enum<bool>::value == false, "" );

    static_assert( is_floating_point<int>::value == false, "" );
    static_assert( is_floating_point<float>::value == true, "" );

    void f1( );
    struct f3 { void operator( )( ){ } };
    static_assert( is_function<decltype(f1)>::value == true, "" );
    static_assert( is_function<f3>::value == false, "" );

    static_assert( is_integral<bool>::value == true, "" );
    static_assert( is_integral<char>::value == true, "" );
    static_assert( is_integral<short>::value == true, "" );
    static_assert( is_integral<int>::value == true, "" );
    static_assert( is_integral<cl::size_t>::value == true, "" );
    static_assert( is_integral<float>::value == false, "" );
    
    static_assert( is_lvalue_reference<int>::value == false, "" );
    static_assert( is_lvalue_reference<int&>::value == true, "" );
    static_assert( is_lvalue_reference<int&&>::value == false, "" );

    static_assert( is_member_function_pointer<void(a::*)(int, char)>::value == true, "" );
    static_assert( is_member_function_pointer<decltype(f1)>::value == false, "" );
    
    static_assert( is_member_object_pointer<decltype(&a::m)>::value == true, "" );
    static_assert( is_member_object_pointer<char *>::value == false, "" );

    static_assert( is_pointer<char>::value == false, "" );
    static_assert( is_pointer<char*>::value == true, "" );
    static_assert( is_pointer<const char*>::value == true, "" );

    static_assert( is_rvalue_reference<int>::value == false, "" );
    static_assert( is_rvalue_reference<int&>::value == false, "" );
    static_assert( is_rvalue_reference<int&&>::value == true, "" );

    union u { int a; char b; };
    static_assert( is_union<u>::value == true, "" );
    static_assert( is_union<a>::value == false, "" );

    static_assert( is_void<void>::value == true, "" );
    static_assert( is_void<int>::value == false, "" );
}
