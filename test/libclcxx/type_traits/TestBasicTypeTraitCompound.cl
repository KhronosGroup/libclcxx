// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_type_traits>
using namespace cl; 

kernel void worker( )
{     
    // tests of compound types alterations
    static_assert( is_same<typename add_pointer<int>::type, int*>::value == true, "" );
    static_assert( is_same<typename add_pointer<int&>::type, int*>::value == true, "" );
    static_assert( is_same<typename add_pointer<int*>::type, int**>::value == true, "" );
    static_assert( is_same<typename add_pointer<const int>::type, const int*>::value == true, "" );
    
    static_assert( is_same<typename add_lvalue_reference<int>::type, int&>::value == true, "" );
    static_assert( is_same<typename add_lvalue_reference<int&>::type, int&>::value == true, "" );
    static_assert( is_same<typename add_lvalue_reference<int&&>::type, int&>::value == true, "" );
    static_assert( is_same<typename add_lvalue_reference<int*>::type, int*&>::value == true, "" );
    
    static_assert( is_same<typename add_rvalue_reference<int>::type, int&&>::value == true, "" );
    static_assert( is_same<typename add_rvalue_reference<int&>::type, int&>::value == true, "" );
    static_assert( is_same<typename add_rvalue_reference<int&&>::type, int&&>::value == true, "" );
    static_assert( is_same<typename add_rvalue_reference<int*>::type, int*&&>::value == true, "" );

    static_assert( is_same<typename decay<int>::type, int>::value == true, "" );
    static_assert( is_same<typename decay<int&>::type, int>::value == true, "" );
    static_assert( is_same<typename decay<int&&>::type, int>::value == true, "" );
    static_assert( is_same<typename decay<int*>::type, int*>::value == true, "" );
    static_assert( is_same<typename decay<const int>::type, int>::value == true, "" );
    static_assert( is_same<typename decay<int[10]>::type, int*>::value == true, "" );
    
    enum en1 { e1a, e2b };
    enum class en2 : unsigned short { e2a, e2b };
    static_assert( is_same<typename make_signed<int>::type, int>::value == true, "" );
    static_assert( is_same<typename make_signed<unsigned int>::type, int>::value == true, "" );
    static_assert( is_same<typename make_signed<unsigned char>::type, signed char>::value == true, "" );
    static_assert( is_same<typename make_signed<en1>::type, int>::value == true, "" );
    static_assert( is_same<typename make_signed<en2>::type, short>::value == true, "" );

    static_assert( is_same<typename make_unsigned<int>::type, unsigned int>::value == true, "" );
    static_assert( is_same<typename make_unsigned<unsigned int>::type, unsigned int>::value == true, "" );
    static_assert( is_same<typename make_unsigned<signed char>::type, unsigned char>::value == true, "" );
    static_assert( is_same<typename make_unsigned<en1>::type, unsigned int>::value == true, "" );
    static_assert( is_same<typename make_unsigned<en2>::type, unsigned short>::value == true, "" );

    static_assert( is_same<typename remove_all_extents<int>::type, int>::value == true, "" );
    static_assert( is_same<typename remove_all_extents<int[]>::type, int>::value == true, "" );
    static_assert( is_same<typename remove_all_extents<int[10]>::type, int>::value == true, "" );
    static_assert( is_same<typename remove_all_extents<int[][10]>::type, int>::value == true, "" );
    static_assert( is_same<typename remove_all_extents<int[10][10]>::type, int>::value == true, "" );
    static_assert( is_same<typename remove_all_extents<int[][10][10]>::type, int>::value == true, "" );

    static_assert( is_same<typename remove_extent<int>::type, int>::value == true, "" );
    static_assert( is_same<typename remove_extent<int[]>::type, int>::value == true, "" );
    static_assert( is_same<typename remove_extent<int[10]>::type, int>::value == true, "" );
    static_assert( is_same<typename remove_extent<int[][10]>::type, int[10]>::value == true, "" );
    static_assert( is_same<typename remove_extent<int[10][10]>::type, int[10]>::value == true, "" );
    static_assert( is_same<typename remove_extent<int[][10][10]>::type, int[10][10]>::value == true, "" );

    static_assert( is_same<typename remove_pointer<int>::type, int>::value == true, "" );
    static_assert( is_same<typename remove_as<remove_pointer<int*>::type>::type, int>::value == true, "" );
    static_assert( is_same<typename remove_as<remove_pointer<int**>::type>::type, int*>::value == true, "" );
    static_assert( is_same<typename remove_as<remove_pointer<const int*>::type>::type, const int>::value == true, "" );
    static_assert( is_same<typename remove_as<remove_pointer<int* const>::type>::type, int>::value == true, "" );

    static_assert( is_same<typename remove_reference<int>::type, int>::value == true, "" );
    static_assert( is_same<typename remove_as<remove_reference<int&>::type>::type, int>::value == true, "" );
    static_assert( is_same<typename remove_as<remove_reference<int&&>::type>::type, int>::value == true, "" );

    static_assert( is_same<typename underlying_type<en2>::type, unsigned short>::value == true, "" );
    static_assert( is_same<typename underlying_type<en2>::type, unsigned char>::value == false, "" );
}
