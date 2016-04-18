// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -verify -O0 -o /dev/null
// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -verify -O3 -o /dev/null
// expected-no-diagnostics

#include <opencl_type_traits>
using namespace cl; 

kernel void worker( )
{
    // tests of AS transformations
    static_assert(is_same<typename remove_constant<__constant int>::type, int>::value == true, "");
    static_assert(is_same<typename remove_constant<int>::type, int>::value == true,  "");
    static_assert(is_same<typename remove_constant<__global int>::type, __global int>::value == true, "");
    static_assert(is_same<typename remove_constant<__local int>::type, __local int>::value == true, "");
    static_assert(is_same<typename remove_constant<__generic int>::type, __generic int>::value == true, "");
    static_assert(is_same<typename remove_constant<__private int>::type, __private int>::value == true, "");

    static_assert(is_same<typename remove_global<__global int>::type, int>::value == true, "");
    static_assert(is_same<typename remove_global<int>::type, int>::value == true, "");
    static_assert(is_same<typename remove_global<__constant int>::type, __constant int>::value == true, "");
    static_assert(is_same<typename remove_global<__local int>::type, __local int>::value == true, "");
    static_assert(is_same<typename remove_global<__generic int>::type, __generic int>::value == true, "");
    static_assert(is_same<typename remove_global<__private int>::type, __private int>::value == true, "");

    static_assert(is_same<typename remove_local<__local int>::type, int>::value == true, "");
    static_assert(is_same<typename remove_local<int>::type, int>::value == true, "");
    static_assert(is_same<typename remove_local<__constant int>::type, __constant int>::value == true, "");
    static_assert(is_same<typename remove_local<__global int>::type, __global int>::value == true, "");
    static_assert(is_same<typename remove_local<__generic int>::type, __generic int>::value == true, "");
    static_assert(is_same<typename remove_local<__private int>::type, __private int>::value == true, "");

    static_assert(is_same<typename remove_private<__private int>::type, int>::value == true, "");
    static_assert(is_same<typename remove_private<int>::type, int>::value == true, "");
    static_assert(is_same<typename remove_private<__constant int>::type, __constant int>::value == true, "");
    static_assert(is_same<typename remove_private<__global int>::type, __global int>::value == true, "");
    static_assert(is_same<typename remove_private<__generic int>::type, __generic int>::value == true, "");
    static_assert(is_same<typename remove_private<__local int>::type, __local int>::value == true, "");

    static_assert(is_same<typename remove_generic<__generic int>::type, int>::value == true, "");
    static_assert(is_same<typename remove_generic<int>::type, int>::value == true, "");
    static_assert(is_same<typename remove_generic<__constant int>::type, __constant int>::value == true, "");
    static_assert(is_same<typename remove_generic<__global int>::type, __global int>::value == true, "");
    static_assert(is_same<typename remove_generic<__local int>::type, __local int>::value == true, "");
    static_assert(is_same<typename remove_generic<__private int>::type, __private int>::value == true, "");

    static_assert(is_same<typename remove_as<__constant int>::type, int>::value == true, "");
    static_assert(is_same<typename remove_as<__global int>::type, int>::value == true, "");
    static_assert(is_same<typename remove_as<__local int>::type, int>::value == true, "");
    static_assert(is_same<typename remove_as<__private int>::type, int>::value == true, "");
    static_assert(is_same<typename remove_as<__generic int>::type, int>::value == true, "");
    static_assert(is_same<typename remove_as<int>::type, int>::value == true, "");

    static_assert(is_same<typename add_constant<int>::type, __constant int>::value == true, "");
    static_assert(is_same<typename add_constant<__constant int>::type, __constant int>::value == true, "");

    static_assert(is_same<typename add_global<int>::type, __global int>::value == true, "");
    static_assert(is_same<typename add_global<__global int>::type, __global int>::value == true, "");

    static_assert(is_same<typename add_local<int>::type, __local int>::value == true, "");
    static_assert(is_same<typename add_local<__local int>::type, __local int>::value == true, "");

    static_assert(is_same<typename add_private<int>::type, __private int>::value == true, "");
    static_assert(is_same<typename add_private<__private int>::type, __private int>::value == true, "");

    static_assert(is_same<typename add_generic<int>::type, __generic int>::value == true, "");
    static_assert(is_same<typename add_generic<__generic int>::type, __generic int>::value == true, "");

    static_assert(is_constant<__global int>::value == false, "" );
    static_assert(is_constant<__constant int>::value == true, "" );
    static_assert(is_constant<int>::value == false, "" );

    static_assert(is_local<__global int>::value == false, "" );
    static_assert(is_local<__local int>::value == true, "" );
    static_assert(is_local<int>::value == false, "" );
    
    static_assert(is_global<__local int>::value == false, "" );
    static_assert(is_global<__global int>::value == true, "" );
    static_assert(is_global<int>::value == false, "" );

    static_assert(is_private<__global int>::value == false, "" );
    static_assert(is_private<__constant int>::value == false, "" );
    static_assert(is_private<__local int>::value == false, "" );
    static_assert(is_private<__generic int>::value == false, "" );
    static_assert(is_private<__private int>::value == true, "" );
    static_assert(is_private<int>::value == false, "" );

    static_assert(is_generic<__global int>::value == false, "" );
    static_assert(is_generic<__generic int>::value == true, "" );
    static_assert(is_generic<int>::value == false, "" );
}