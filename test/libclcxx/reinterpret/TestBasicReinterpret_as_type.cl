// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -emit-llvm -O0 -o - | FileCheck %s
// expected-no-diagnostics

#include <__ocl_reinterpret.h>
using namespace cl;

kernel void worker()
{
    int4 i;
    
    short8 s = as_type<short8>(i);
    // CHECK: call spir_func <8 x i16> @_Z{{[1-9][0-9]*}}__spirv_Bitcast_Rshort8{{[a-zA-Z0-9_]+}}(<4 x i32> {{.*}})

    //ambiguity  test: as_type only differ by return type from previous
    float4 f = as_type<float4>(i);
    // CHECK: call spir_func <4 x float> @_Z{{[1-9][0-9]*}}__spirv_Bitcast_Rfloat4{{[a-zA-Z0-9_]+}}(<4 x i32> {{.*}})
}
