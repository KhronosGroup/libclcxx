// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -nobuiltininc -verify -O0 -o - | FileCheck %s
// expected-no-diagnostics

#include <opencl_vector_load_store>
using namespace cl;

kernel void worker()
{
    vstore(float3{ 0, 0, 0}, 0, (float*)nullptr);
    // CHECK: call spir_func void @_Z{{[1-9][0-9]*}}__spirv_ocl_vstoren{{[a-zA-Z0-9_]+}}(<3 x float> {{.*}})
}
