// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -cl-fp64-enable -cl-fp16-enable -fsyntax-only -pedantic -verify 
// expected-no-diagnostics

#include <opencl_limits>
using namespace cl;

kernel void worker()
{
    static_assert(numeric_limits<half>::has_denorm == float_denorm_style::denorm_absent, "Denormalized half values should be disabled by default");
    static_assert(numeric_limits<float>::has_denorm == float_denorm_style::denorm_absent, "Denormalized float values should be disabled by default");
    static_assert(numeric_limits<double>::has_denorm == float_denorm_style::denorm_absent, "Denormalized double values should be disabled by default");
}
