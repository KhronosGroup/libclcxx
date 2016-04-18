// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -emit-llvm -O0 -o  -| FileCheck %s
// expected-no-diagnostics

#include <opencl_printf>
#include <opencl_memory>
typedef unsigned int uint;
using namespace cl;

kernel void worker(global_ptr<int> dr, global_ptr<unsigned int> ur, global_ptr<float> fr, global_ptr<char> cr)
{
    int d = -1;
    uint u = 1;
    float f = 1.0;
    char c = '1';

    printf("test : %d %u %f %c", d, u, f, c);
    // CHECK: call {{.*}} @_Z{{[1-9][0-9]*}}__spirv_ocl_printf{{[a-zA-Z0-9_]+}}({{.*}})

    printf("test : %d %u %f %c", *dr, *ur, *fr, *cr);
    printf("test : %d %u %f %c", -1, 1, 1.0, '1');
    printf("test : %s", "test string");
    printf("test : %c", 'c');
}