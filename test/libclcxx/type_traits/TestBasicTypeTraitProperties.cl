// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_type_traits>
using namespace cl; 

kernel void worker( )
{     
    // tests of type properties
    struct c1 { };
    struct c2 { void m( ) { } };
    struct c3 { int m; ~c3( ) { } };
    struct c4 : c2 { };
    struct c5 : c3 { };
    struct c6 { int m; };
    struct c7 : c6 { int n; };
    struct c8 { c8( const c8& ) { } };
    
    static_assert( is_abstract<c1>::value == false, "" );

    static_assert( is_const<int>::value == false, "" );
    static_assert( is_const<const int>::value == true, "" );
    static_assert( is_const<const int *>::value == false, "" );
    static_assert( is_const<const int &>::value == false, "" );
    static_assert( is_const<int * const>::value == true, "" );

    
    static_assert( is_empty<c1>::value == true, "" );
    static_assert( is_empty<c2>::value == true, "" );
    static_assert( is_empty<c3>::value == false, "" );
    static_assert( is_empty<long>::value == false, "" );

    static_assert( is_literal_type<c1>::value == true, "" );
    static_assert( is_literal_type<c3>::value == false, "" );
    static_assert( is_literal_type<int>::value == true, "" );
    static_assert( is_literal_type<int *>::value == true, "" );
    static_assert( is_literal_type<int &>::value == true, "" );

    static_assert( is_pod<c1>::value == true, "" );
    static_assert( is_pod<c2>::value == true, "" );
    static_assert( is_pod<c3>::value == false, "" );
    static_assert( is_pod<c4>::value == true, "" );
    static_assert( is_pod<c5>::value == false, "" );
    static_assert( is_pod<int[4]>::value == true, "" );
    static_assert( is_pod<float>::value == true, "" );
    static_assert( is_pod<char*>::value == true, "" );
    static_assert( is_pod<unsigned long &>::value == false, "" );

    static_assert( is_polymorphic<c1>::value == false, "" );

    static_assert( is_signed<c1>::value == false, "" );
    static_assert( is_signed<float>::value == true, "" );
    static_assert( is_signed<int>::value == true, "" );
    static_assert( is_signed<unsigned char>::value == false, "" );
    static_assert( is_signed<unsigned long>::value == false, "" );

    static_assert( is_standard_layout<float>::value == true, "" );
    static_assert( is_standard_layout<c6>::value == true, "" );
    static_assert( is_standard_layout<c7>::value == false, "" );

    static_assert( is_trivial<int>::value == true, "" );
    static_assert( is_trivial<c1>::value == true, "" );
    static_assert( is_trivial<c2>::value == true, "" );
    static_assert( is_trivial<c3>::value == false, "" );
    static_assert( is_trivial<c4>::value == true, "" );
    static_assert( is_trivial<c5>::value == false, "" );
    static_assert( is_trivial<c6>::value == true, "" );

    static_assert( is_trivially_copyable<float>::value == true, "" );
    static_assert( is_trivially_copyable<c1>::value == true, "" );
    static_assert( is_trivially_copyable<c8>::value == false, "" );

    static_assert( is_unsigned<c1>::value == false, "" );
    static_assert( is_unsigned<float>::value == false, "" );
    static_assert( is_unsigned<int>::value == false, "" );
    static_assert( is_unsigned<unsigned char>::value == true, "" );
    static_assert( is_unsigned<unsigned long>::value == true, "" );

    static_assert( is_volatile<int>::value == false, "" );
    static_assert( is_volatile<volatile int>::value == true, "" );
    static_assert( is_volatile<volatile int *>::value == false, "" );
    static_assert( is_volatile<volatile int &>::value == false, "" );
    static_assert( is_volatile<int * volatile>::value == true, "" );    
}
