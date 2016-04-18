// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -nobuiltininc -verify -O0 -o - | FileCheck %s
// expected-no-diagnostics

#include <opencl_convert>
using namespace cl;

kernel void worker()
{
    bool4 b;
    float4 f;
    int4 i;
    
    f = convert_cast<float4>(b);
    // CHECK: call spir_func <4 x float> @_Z{{[1-9][0-9]+}}__spirv_Select{{[a-zA-Z0-9_]+}}(<4 x i1> {{.*}}, <4 x float> {{.*}}, <4 x float> {{.*}})

    i = convert_cast<int4>(b);
    // CHECK: call spir_func <4 x i32> @_Z{{[1-9][0-9]+}}__spirv_Select{{[a-zA-Z0-9_]+}}(<4 x i1> {{.*}}, <4 x i32> {{.*}}, <4 x i32> {{.*}})

    b = convert_cast<bool4>(f);
    // CHECK: call spir_func <4 x i1> @_Z{{[1-9][0-9]+}}__spirv_FOrdNotEqual{{[a-zA-Z0-9_]+}}(<4 x float> {{.*}}, <4 x float> {{.*}})
    
    b = convert_cast<bool4>(i);
    // CHECK: call spir_func <4 x i1> @_Z{{[1-9][0-9]+}}__spirv_INotEqual{{[a-zA-Z0-9_]+}}(<4 x i32> {{.*}}, <4 x i32> {{.*}})
}
