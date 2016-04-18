// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -cl-fp64-enable -cl-fp16-enable -emit-llvm   -pedantic -verify -nobuiltininc -O0 -o - | FileCheck %s
// expected-no-diagnostics

#include <opencl_limits>
using namespace cl;

kernel void worker()
{
    numeric_limits<double>::signaling_NaN();
    // CHECK: spir_func double @{{.*}}signaling_NaN
    // CHECK: ret double 0x{{[f,F,7]FF4[0]*$}}

    numeric_limits<float>::signaling_NaN();
    // CHECK: spir_func float @{{.*}}signaling_NaN
    // CHECK: ret float 0x{{[f,F,7]FF4[0]*$}}

    numeric_limits<half>::signaling_NaN();
    // CHECK: spir_func half @{{.*}}signaling_NaN
    // CHECK: ret half 0xH{{[7,f,F][d,D[0-9a-fA-F]*$}}
}

