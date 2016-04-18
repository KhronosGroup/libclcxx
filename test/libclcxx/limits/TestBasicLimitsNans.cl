// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -cl-fp64-enable -cl-fp16-enable -emit-llvm -pedantic -verify -nobuiltininc  -O0 -o - | FileCheck %s
// expected-no-diagnostics

#include <opencl_limits>
using namespace cl;

kernel void worker()
{
    numeric_limits<double>::quiet_NaN();
    // CHECK: spir_func double @{{.*}}quiet_NaN
    // CHECK: ret double 0x{{[7,F]FF[8,9,A,B,C,D,E,F][0-9a-fA-F]*$}}
    static_assert(numeric_limits<double>::quiet_NaN() != 0, "<double>::quiet_NaN should not return 0 (default value)");

    numeric_limits<float>::quiet_NaN();
    // CHECK: spir_func float @{{.*}}quiet_NaN
    // CHECK: ret float 0x{{[7,f,F]}}F{{[c,C,d,D,e,E,f,F][0-9a-fA-F]*$}}
    static_assert(numeric_limits<float>::quiet_NaN() != 0, "<float>::quiet_NaN should not return 0 (base class default value)");

    numeric_limits<half>::quiet_NaN();
    // CHECK: spir_func half @{{.*}}quiet_NaN
    // CHECK: ret half 0xH{{[7,f,F][e,E,f,F]0*$}}
    static_assert(numeric_limits<half>::quiet_NaN() != 0, "<half>::quiet_NaN should not return 0 (base class default value)");
}

