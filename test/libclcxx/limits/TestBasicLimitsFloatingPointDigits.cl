// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -cl-fp64-enable -cl-fp16-enable -fsyntax-only -pedantic -verify 
// expected-no-diagnostics

#include <opencl_limits>
using namespace cl;

kernel void worker()
{
    static_assert(numeric_limits<half>::digits == 11, "numeric_limits<half>::digits should equal 24");
    static_assert(numeric_limits<half>::digits10 == 3, "numeric_limits<half>::digits10 should equal 24");
    static_assert(numeric_limits<half>::max_digits10 == 5, "numeric_limits<half>::max_digits10 should equal 24");

    static_assert(numeric_limits<float>::digits == 24, "numeric_limits<float>::digits should equal 24");
    static_assert(numeric_limits<float>::digits10 == 6, "numeric_limits<float>::digits10 should equal 6");
    static_assert(numeric_limits<float>::max_digits10 == 9, "numeric_limits<float>::max_digits10 should equal 9");
    
    static_assert(numeric_limits<double>::digits == 53, "numeric_limits<double>::digits should equal 24");
    static_assert(numeric_limits<double>::digits10 == 15, "numeric_limits<double>::digits10 should equal 6");
    static_assert(numeric_limits<double>::max_digits10 == 17, "numeric_limits<double>::max_digits10 should equal 9");
}
