// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -cl-fp64-enable -cl-fp16-enable -emit-llvm -pedantic -verify -nobuiltininc  -O0 -o - | FileCheck %s
// expected-no-diagnostics

#include <opencl_limits>
using namespace cl;

kernel void worker()
{
    numeric_limits<float>::infinity();
    // CHECK: spir_func float @{{.*}}infinity
    // CHECK: ret float 0x7{{[f,F]{2}0*$}}
    static_assert(numeric_limits<float>::infinity() != 0, "<float>::infinity should not return 0 (default value)");

    numeric_limits<double>::infinity();
    // CHECK: spir_func double @{{.*}}infinity
    // CHECK: ret double 0x7{{[f,F]{2}0*$}}
    static_assert(numeric_limits<double>::infinity() != 0, "<double>::infinity should not return 0 (default value)");

    numeric_limits<half>::infinity();
    // CHECK: spir_func half @{{.*}}infinity
    // CHECK: ret half 0xH{{[7,f,F]C[0]*$}}
    static_assert(numeric_limits<half>::infinity() != 0, "<half>::infinity should not return 0 (default value)");
}