// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -nobuiltininc -verify -O0 -o - | FileCheck %s
// expected-no-diagnostics

#include <opencl_vector_load_store>
using namespace cl;

kernel void worker()
{
    auto test = vload<2>(0, (float*)nullptr);
    // CHECK: call spir_func <2 x float> @_Z{{[1-9][0-9]*}}__spirv_ocl_vloadn{{[a-zA-Z0-9_]+}}({{.*}})
    
    constant_ptr<float> ptr;
    auto test2 = vload<4>(0, ptr);
    // CHECK: call spir_func <4 x float> @_Z{{[1-9][0-9]*}}__spirv_ocl_vloadn{{[a-zA-Z0-9_]+}}({{.*}})
	
    auto test3 = vload<4>(0, ptr + 10);
    // CHECK: call spir_func <4 x float> @_Z{{[1-9][0-9]*}}__spirv_ocl_vloadn{{[a-zA-Z0-9_]+}}({{.*}})
}
