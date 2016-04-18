// RUN: %clang_cc1 %s -triple spir-unknown-unknown -emit-llvm -O0 -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable
// expected-no-diagnostics

#include <opencl_math_constants>
using namespace cl;

#define CHECK_VAR(varname, type) static_assert(math_constants<type>::varname() == varname##_v<type>, "fail")

CHECK_VAR(e, float);
CHECK_VAR(log2e, float);
CHECK_VAR(log10e, float);
CHECK_VAR(ln2, float);
CHECK_VAR(ln10, float);
CHECK_VAR(pi, float);
CHECK_VAR(pi_2, float);
CHECK_VAR(pi_4, float);
CHECK_VAR(one_pi, float);
CHECK_VAR(two_pi, float);
CHECK_VAR(two_sqrtpi, float);
CHECK_VAR(sqrt2, float);
CHECK_VAR(sqrt1_2, float);

CHECK_VAR(e, half);
CHECK_VAR(log2e, half);
CHECK_VAR(log10e, half);
CHECK_VAR(ln2, half);
CHECK_VAR(ln10, half);
CHECK_VAR(pi, half);
CHECK_VAR(pi_2, half);
CHECK_VAR(pi_4, half);
CHECK_VAR(one_pi, half);
CHECK_VAR(two_pi, half);
CHECK_VAR(two_sqrtpi, half);
CHECK_VAR(sqrt2, half);
CHECK_VAR(sqrt1_2, half);

CHECK_VAR(e, double);
CHECK_VAR(log2e, double);
CHECK_VAR(log10e, double);
CHECK_VAR(ln2, double);
CHECK_VAR(ln10, double);
CHECK_VAR(pi, double);
CHECK_VAR(pi_2, double);
CHECK_VAR(pi_4, double);
CHECK_VAR(one_pi, double);
CHECK_VAR(two_pi, double);
CHECK_VAR(two_sqrtpi, double);
CHECK_VAR(sqrt2, double);
CHECK_VAR(sqrt1_2, double);
