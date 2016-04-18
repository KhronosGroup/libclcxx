// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -emit-llvm -O0 -o - | FileCheck %s
// expected-no-diagnostics

#include <opencl_reinterpret>
using namespace cl;

kernel void worker()
{
    auto test = as_type<const uint4>(uint4{ 0 });
    //CHECK-NOT: call spir_func
    
    auto test2 = as_type<volatile char2>(char2{ 0 });
    //CHECK-NOT: call spir_func
    
    __local float3 tmp;
    auto test3 = as_type<const decltype(tmp)>(tmp);
    //CHECK-NOT: call spir_func
}
