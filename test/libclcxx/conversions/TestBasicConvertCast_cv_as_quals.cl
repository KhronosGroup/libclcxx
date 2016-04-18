// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -nobuiltininc -verify -O0 -o - | FileCheck %s
// expected-no-diagnostics

#include <opencl_convert>
using namespace cl;

kernel void worker()
{
    auto test = convert_cast<const uint4>(uint4{ 0 });
    //CHECK-NOT: call spir_func
    
    auto test2 = convert_cast<volatile char2>(char2{ 0 });
    //CHECK-NOT: call spir_func
    
    __local float3 tmp;
    auto test3 = convert_cast<const decltype(tmp)>(tmp);
    //CHECK-NOT: call spir_func
}
