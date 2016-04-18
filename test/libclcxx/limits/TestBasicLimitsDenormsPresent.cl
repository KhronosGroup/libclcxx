// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -cl-fp64-enable -cl-fp16-enable -DHAS_HALF_FP_DENORM -DHAS_SINGLE_FP_DENORM -DHAS_DOUBLE_FP_DENORM -fsyntax-only -pedantic -verify 
// expected-no-diagnostics

#include <opencl_limits>
using namespace cl;

kernel void worker()
{
    static_assert(numeric_limits<half>::has_denorm == float_denorm_style::denorm_present, "Denormalized half values should be enabled when HAS_HALF_FP_DENORM macro is defined");
    static_assert(numeric_limits<float>::has_denorm == float_denorm_style::denorm_present, "Denormalized float values should be enabled when HAS_FLOAT_FP_DENORM macro is defined");
    static_assert(numeric_limits<double>::has_denorm == float_denorm_style::denorm_present, "Denormalized double values should be enabled when HAS_DOUBLE_FP_DENORM macro is defined");
}
