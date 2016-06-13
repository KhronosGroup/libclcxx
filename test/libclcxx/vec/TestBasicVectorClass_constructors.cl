// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_vec>
using namespace cl;

kernel void worker()
{
    vec<float, 4> t1{};
    vec<float, 4> t2{ t1 };
    vec<float, 4> t3{ move(t2) };
    vec<float, 4> t4{ float4{0} };
    vec<float, 4> t5{ float2{0}, float2{0} };
    vec<float, 4> t6{ float4{0}.xyz, float2{0}.y };
    vec<float, 4> t7{ float4{0}.xy, float2{0}.xy };
    vec<float, 4> t8{ 0, 0, 0, 0 };
    vec<float, 4> t9{ 0 };
    
    int a = 12;
    vec<float, 4> t10{ a };
    
    vec<float, 4> t11{ t9.swizzle<0,1,2,3>() };
    
    // conversion operators to built-in vector types are currently not considered during built-in vectors' constructor lookup
    //vec<float, 4> t12{ t9.swizzle<0,1>(), t8.swizzle<0,1>() };
    vec<float, 4> t12{ t9.swizzle<0,1>().operator float2(), t8.swizzle<0,1>().operator float2() };
    
    //conversion to float is however ok
    vec<float, 4> t13{ t9.swizzle<0>(), t8.swizzle<0>(), t7.swizzle<0>(), t6.swizzle<0>() };
}
