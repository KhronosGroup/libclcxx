// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_type_traits>
using namespace cl; 

kernel void worker( )
{     
    // tests of cv transformations
    static_assert( is_same<typename add_const<int>::type, const int>::value == true, "" );
    static_assert( is_same<typename add_const<const int>::type, const int>::value == true, "" );
    static_assert( is_same<typename add_const<int*>::type, int* const>::value == true, "" );
    static_assert( is_same<typename add_const<const int*>::type, const int* const>::value == true, "" );
    static_assert( is_same<typename add_const<const int&>::type, const int&>::value == true, "" );

    static_assert( is_same<typename add_cv<int>::type, const volatile int>::value == true, "" );
    static_assert( is_same<typename add_cv<volatile int>::type, const volatile int>::value == true, "" );
    static_assert( is_same<typename add_cv<int*>::type, int* const volatile>::value == true, "" );
    static_assert( is_same<typename add_cv<const int*>::type, const int* const volatile>::value == true, "" );
    static_assert( is_same<typename add_cv<const volatile int&>::type, const volatile int&>::value == true, "" );

    static_assert( is_same<typename add_volatile<int>::type, volatile int>::value == true, "" );
    static_assert( is_same<typename add_volatile<volatile int>::type, volatile int>::value == true, "" );
    static_assert( is_same<typename add_volatile<int*>::type, int* volatile>::value == true, "" );
    static_assert( is_same<typename add_volatile<volatile int*>::type, volatile int* volatile>::value == true, "" );
    static_assert( is_same<typename add_volatile<volatile int&>::type, volatile int&>::value == true, "" );

    static_assert( is_same<typename remove_const<int>::type, int>::value == true, "" );
    static_assert( is_same<typename remove_const<const int>::type, int>::value == true, "" );
    static_assert( is_same<typename remove_const<int* const>::type, int*>::value == true, "" );
    static_assert( is_same<typename remove_const<const int* const>::type, const int*>::value == true, "" );
    static_assert( is_same<typename remove_const<const int&>::type, const int&>::value == true, "" );

    static_assert( is_same<typename remove_cv<int>::type, int>::value == true, "" );
    static_assert( is_same<typename remove_cv<const volatile int>::type, int>::value == true, "" );
    static_assert( is_same<typename remove_cv<int* const volatile>::type, int*>::value == true, "" );
    static_assert( is_same<typename remove_cv<const int* const volatile>::type, const int*>::value == true, "" );
    static_assert( is_same<typename remove_cv<const volatile int&>::type, const volatile int&>::value == true, "" );

    static_assert( is_same<typename remove_volatile<volatile int>::type, int>::value == true, "" );
    static_assert( is_same<typename remove_volatile<int>::type, int>::value == true, "" );
    static_assert( is_same<typename remove_volatile<int* volatile>::type, int*>::value == true, "" );
    static_assert( is_same<typename remove_volatile<volatile int* volatile>::type, volatile int*>::value == true, "" );
    static_assert( is_same<typename remove_volatile<volatile int&>::type, volatile int&>::value == true, "" );
}
