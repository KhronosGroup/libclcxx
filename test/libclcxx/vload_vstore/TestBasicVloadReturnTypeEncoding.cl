// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -O0 -o -
// CHECK: call spir_func <2 x float> @_Z27__spirv_ocl_vloadn__Rfloat2mPU3AS1Kfm

#include <opencl_vector_load_store>

__kernel void test_vload(cl::global_ptr<float[]> x)
{
    float2 f = cl::vload<2>(0,x.get());
}