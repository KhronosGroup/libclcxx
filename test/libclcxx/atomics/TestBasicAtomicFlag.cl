// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -nobuiltininc -verify -O0 -o -
// expected-no-diagnostics

#include <opencl_work_item>
#include <opencl_atomic>

volatile cl::atomic_flag vf = ATOMIC_FLAG_INIT;
cl::atomic_flag f;

__kernel void worker()
{
    f.clear();
    while(f.test_and_set());
    while(vf.test_and_set());
    vf.clear();
}
