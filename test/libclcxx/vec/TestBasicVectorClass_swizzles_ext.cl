// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#define SIMPLE_SWIZZLES
#include <opencl_vec>
using namespace cl;

void f(float4 f4);
void f2(float3 f3);
void f3(float3& f);
void f4(float2);
void f5(float);

kernel void worker()
{
    vec<float, 4> tmp(float4{0});
    vec<float, 3> tmp2;
    tmp.xyz().zyx() = tmp2.xxx().z().xxx().zzz().yyy();
    
    f(tmp);
    f2(tmp.xxz());
    f3(tmp2);
    
    float3 tmp3;
    
    float2 x = swizzle<undef_channel, 0>(tmp3);
    float4 y = swizzle<channel::r, channel::undef, channel::g, channel::undef>(tmp3);

    vec<float, 3> tmp4;
    auto a2 = tmp4.hi();
    f4(tmp4.odd());
    f5(a2.even());
}
