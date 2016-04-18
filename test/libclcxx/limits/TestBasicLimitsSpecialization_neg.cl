// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -nobuiltininc -O0
// XFAIL:*

#include <opencl_limits>
using namespace cl;

struct A
{
};

kernel void worker() {
    numeric_limits<A>::min(); //invalid specialization
}