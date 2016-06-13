// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#define SIMPLE_SWIZZLES
#include <opencl_vec>
using namespace cl;

kernel void worker()
{
    vec<bool, 16> v;
    
    v.xyz() = false;
    bool3 t1 = v.xxx();
    auto t2 = v.xyz().zyx();
    
    v.x() = true;
    v.y() = v.z();
    v.zyx() = v.x();
}
