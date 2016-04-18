// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_type_traits>
using namespace cl; 

kernel void worker( )
{     
    // tests of type features
    struct c1 { };
    struct c2 { void m( ) { } };
    struct c3 { int m; ~c3( ) { } };
    struct c4 : c2 { };
    struct c5 : c3 { };
    struct c6 { int m; };
    struct c7 : c6 { int n; };
    struct c8 { c8( const c8& ) { } };
    struct c9 { c9& operator=( const c9& ) = delete; };
    struct c10 { c10& operator=( const c9& ) noexcept { return *this; } };
    struct c11 { c11( int, float ) { } };
    struct c12 { c12( const c12& ) { } };
    struct c13 { c13( const c13& ) = delete; };
    struct c14 { ~c14( ) = delete; };
    struct c15 { private: ~c15( ) { } };
    struct c16 { c16& operator=( c16&& ) = delete; };
    struct c17 { c17( c17&& ) = delete; };
    struct c18 { c18( ) = delete; };
    struct c19 { c19( ) { } };
    struct c20 { c20& operator=( c20&& ) { return *this; } };
    struct c21 { c21( c21&& ) { } };
    struct c22 { c22& operator=( const c22& ) { return *this; } };
    struct c23 { c23( ) { } };
    
    static_assert( has_virtual_destructor<c3>::value == false, "" );

    static_assert( is_assignable<c9, c10>::value == false, "" );
    //static_assert( is_assignable<c10, c9>::value == true, "" );

    static_assert( is_constructible<c11>::value == false, "" );
    static_assert( is_constructible<c11, bool>::value == false, "" );
    static_assert( is_constructible<c11, c10, float>::value == false, "" );
    static_assert( is_constructible<c11, int, int, int>::value == false, "" );
    static_assert( is_constructible<c11, int, float>::value == true, "" );

    static_assert( is_copy_assignable<c9>::value == false, "" );
    //static_assert( is_copy_assignable<c1>::value == true, "" );

    static_assert( is_copy_constructible<c1>::value == true, "" );
    static_assert( is_copy_constructible<c12>::value == true, "" );
    static_assert( is_copy_constructible<c13>::value == false, "" );

    static_assert( is_destructible<c12>::value == true, "" );
    static_assert( is_destructible<c14>::value == false, "" );
    static_assert( is_destructible<c15>::value == false, "" );

    //static_assert( is_move_assignable<c1>::value == true, "" );
    static_assert( is_move_assignable<c16>::value == false, "" );

    static_assert( is_move_constructible<c1>::value == true, "" );
    static_assert( is_move_constructible<c17>::value == false, "" );

    //static_assert( is_trivially_assignable<c2, c2>::value == true, "" );
    static_assert( is_trivially_assignable<int&, int>::value == true, "" );
    static_assert( is_trivially_assignable<int, int>::value == false, "" );

    static_assert( is_default_constructible<c1>::value == true, "" );
    static_assert( is_default_constructible<c18>::value == false, "" );

    //static_assert( is_trivially_copy_assignable<c4>::value == true, "" );
    static_assert( is_trivially_copy_assignable<c16>::value == false, "" );
    static_assert( is_trivially_copy_assignable<int>::value == true, "" );
    static_assert( is_trivially_copy_assignable<int&>::value == true, "" );

    static_assert( is_trivially_copy_constructible<c1>::value == true, "" );
    static_assert( is_trivially_copy_constructible<c12>::value == false, "" );

    static_assert( is_trivially_destructible<c1>::value == true, "" );
    static_assert( is_trivially_destructible<c3>::value == false, "" );

    static_assert( is_trivially_default_constructible<c1>::value == true, "" );
    static_assert( is_trivially_default_constructible<c19>::value == false, "" );

    //static_assert( is_trivially_move_assignable<c1>::value == true, "" );
    static_assert( is_trivially_move_assignable<c20>::value == false, "" );

    static_assert( is_trivially_move_constructible<c1>::value == true, "" );
    static_assert( is_trivially_move_constructible<c21>::value == false, "" );

    static_assert( is_nothrow_assignable<c9, c10>::value == false, "" );
    //static_assert( is_nothrow_assignable<c10, c9>::value == true, "" );

    static_assert( is_nothrow_constructible<c21, c21&&>::value == false, "" );
    static_assert( is_nothrow_constructible<c1>::value == true, "" );

    //static_assert( is_nothrow_copy_assignable<c1>::value == true, "" );
    static_assert( is_nothrow_copy_assignable<c22>::value == false, "" );

    static_assert( is_nothrow_copy_constructible<c1>::value == true, "" );
    static_assert( is_nothrow_copy_constructible<c12>::value == false, "" );

    static_assert( is_nothrow_default_constructible<c1>::value == true, "" );
    static_assert( is_nothrow_default_constructible<c23>::value == false, "" );

    //static_assert( is_nothrow_move_assignable<c1>::value == true, "" );
    static_assert( is_nothrow_move_assignable<c20>::value == false, "" );

    static_assert( is_nothrow_move_constructible<c1>::value == true, "" );
    static_assert( is_nothrow_move_constructible<c21>::value == false, "" );
}
