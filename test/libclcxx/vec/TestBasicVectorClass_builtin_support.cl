// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_vec>
using namespace cl;

void test(float4);

kernel void worker()
{
    vec<float, 4> v{ float4{0} };
    
    v = float4{0};
    float4 tmp;
    v = tmp;
    test(v);
    
    tmp = v;
    tmp = move(v);
}
