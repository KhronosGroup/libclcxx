// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -nobuiltininc -verify -O0 -o - | FileCheck %s
// expected-no-diagnostics

#include <opencl_vector_load_store>
using namespace cl;

kernel void worker()
{
    auto test = vload_half<3>(0, (const half*)nullptr);
    //CHECK: call spir_func <3 x float> @_Z{{[1-9][0-9]*}}__spirv_ocl_vload_halfn{{[a-zA-Z0-9_]+}}({{.*}})
    
    constant_ptr<half> ptr;
    auto test2 = vload_half<3>(0, ptr);
    //CHECK: call spir_func <3 x float> @_Z{{[1-9][0-9]*}}__spirv_ocl_vload_halfn{{[a-zA-Z0-9_]+}}({{.*}})
    
    auto test3 = vload_half<1>(0, (const half*)nullptr);
    //CHECK: call spir_func float @_Z{{[1-9][0-9]*}}__spirv_ocl_vload_half{{[a-zA-Z0-9_]+}}({{.*}})
    
    auto test4 = vload_half<1>(0, ptr);
    //CHECK: call spir_func float @_Z{{[1-9][0-9]*}}__spirv_ocl_vload_half{{[a-zA-Z0-9_]+}}({{.*}})
	
    auto test5 = vload_half<1>(0, ptr + 5);
    //CHECK: call spir_func float @_Z{{[1-9][0-9]*}}__spirv_ocl_vload_half{{[a-zA-Z0-9_]+}}({{.*}})
}
