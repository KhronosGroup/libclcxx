// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -nobuiltininc -verify -O0 -o - | FileCheck %s
// expected-no-diagnostics

#include <opencl_vector_load_store>
using namespace cl;

kernel void worker()
{
    auto test = vloada_half<3>(0, (const half*)nullptr);
    //CHECK: call spir_func <3 x float> @_Z{{[1-9][0-9]*}}__spirv_ocl_vloada_halfn{{[a-zA-Z0-9_]+}}({{.*}})
    
    constant_ptr<half> ptr;
    auto test2 = vloada_half<3>(0, ptr);
    //CHECK: call spir_func <3 x float> @_Z{{[1-9][0-9]*}}__spirv_ocl_vloada_halfn{{[a-zA-Z0-9_]+}}({{.*}})
}
