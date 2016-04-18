// RUN: %clang_cc1 %s -triple spir-unknown-unknown -emit-llvm -O0 -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable
// expected-no-diagnostics

#include <opencl_math_constants>
using namespace cl;

bool all(bool2 b) { return b.x && b.y; }
bool all(bool3 b) { return b.x && b.y && b.z; }
bool all(bool4 b) { return b.x && b.y && b.z && b.w; }
bool all(bool8 b) { return b.s0 && b.s1 && b.s2 && b.s3 && b.s4 && b.s5 && b.s6 && b.s7; }
bool all(bool16 b) { return b.s0 && b.s1 && b.s2 && b.s3 && b.s4 && b.s5 && b.s6 && b.s7 && b.s8 && b.s9 && b.sa && b.sb && b.sc && b.sd && b.se && b.sf; }

kernel void worker() {
    if (math_constants<half>::e() != half{ M_E_H }) return;
    if (math_constants<half>::log2e() != half{ M_LOG2E_H }) return;
    if (math_constants<half>::log10e() != half{ M_LOG10E_H }) return;
    if (math_constants<half>::ln2() != half{ M_LN2_H }) return;
    if (math_constants<half>::ln10() != half{ M_LN10_H }) return;
    if (math_constants<half>::pi() != half{ M_PI_H }) return;
    if (math_constants<half>::pi_2() != half{ M_PI_2_H }) return;
    if (math_constants<half>::pi_4() != half{ M_PI_4_H }) return;
    if (math_constants<half>::one_pi() != half{ M_1_PI_H }) return;
    if (math_constants<half>::two_pi() != half{ M_2_PI_H }) return;
    if (math_constants<half>::two_sqrtpi() != half{ M_2_SQRTPI_H }) return;
    if (math_constants<half>::sqrt2() != half{ M_SQRT2_H }) return;
    if (math_constants<half>::sqrt1_2() != half{ M_SQRT1_2_H }) return;

    if (all(math_constants<half2>::e() != half2{ M_E_H })) return;
    if (all(math_constants<half2>::log2e() != half2{ M_LOG2E_H })) return;
    if (all(math_constants<half2>::log10e() != half2{ M_LOG10E_H })) return;
    if (all(math_constants<half2>::ln2() != half2{ M_LN2_H })) return;
    if (all(math_constants<half2>::ln10() != half2{ M_LN10_H })) return;
    if (all(math_constants<half2>::pi() != half2{ M_PI_H })) return;
    if (all(math_constants<half2>::pi_2() != half2{ M_PI_2_H })) return;
    if (all(math_constants<half2>::pi_4() != half2{ M_PI_4_H })) return;
    if (all(math_constants<half2>::one_pi() != half2{ M_1_PI_H })) return;
    if (all(math_constants<half2>::two_pi() != half2{ M_2_PI_H })) return;
    if (all(math_constants<half2>::two_sqrtpi() != half2{ M_2_SQRTPI_H })) return;
    if (all(math_constants<half2>::sqrt2() != half2{ M_SQRT2_H })) return;
    if (all(math_constants<half2>::sqrt1_2() != half2{ M_SQRT1_2_H })) return;

    if (all(math_constants<half3>::e() != half3{ M_E_H })) return;
    if (all(math_constants<half3>::log2e() != half3{ M_LOG2E_H })) return;
    if (all(math_constants<half3>::log10e() != half3{ M_LOG10E_H })) return;
    if (all(math_constants<half3>::ln2() != half3{ M_LN2_H })) return;
    if (all(math_constants<half3>::ln10() != half3{ M_LN10_H })) return;
    if (all(math_constants<half3>::pi() != half3{ M_PI_H })) return;
    if (all(math_constants<half3>::pi_2() != half3{ M_PI_2_H })) return;
    if (all(math_constants<half3>::pi_4() != half3{ M_PI_4_H })) return;
    if (all(math_constants<half3>::one_pi() != half3{ M_1_PI_H })) return;
    if (all(math_constants<half3>::two_pi() != half3{ M_2_PI_H })) return;
    if (all(math_constants<half3>::two_sqrtpi() != half3{ M_2_SQRTPI_H })) return;
    if (all(math_constants<half3>::sqrt2() != half3{ M_SQRT2_H })) return;
    if (all(math_constants<half3>::sqrt1_2() != half3{ M_SQRT1_2_H })) return;

    if (all(math_constants<half4>::e() != half4{ M_E_H })) return;
    if (all(math_constants<half4>::log2e() != half4{ M_LOG2E_H })) return;
    if (all(math_constants<half4>::log10e() != half4{ M_LOG10E_H })) return;
    if (all(math_constants<half4>::ln2() != half4{ M_LN2_H })) return;
    if (all(math_constants<half4>::ln10() != half4{ M_LN10_H })) return;
    if (all(math_constants<half4>::pi() != half4{ M_PI_H })) return;
    if (all(math_constants<half4>::pi_2() != half4{ M_PI_2_H })) return;
    if (all(math_constants<half4>::pi_4() != half4{ M_PI_4_H })) return;
    if (all(math_constants<half4>::one_pi() != half4{ M_1_PI_H })) return;
    if (all(math_constants<half4>::two_pi() != half4{ M_2_PI_H })) return;
    if (all(math_constants<half4>::two_sqrtpi() != half4{ M_2_SQRTPI_H })) return;
    if (all(math_constants<half4>::sqrt2() != half4{ M_SQRT2_H })) return;
    if (all(math_constants<half4>::sqrt1_2() != half4{ M_SQRT1_2_H })) return;

    if (all(math_constants<half8>::e() != half8{ M_E_H })) return;
    if (all(math_constants<half8>::log2e() != half8{ M_LOG2E_H })) return;
    if (all(math_constants<half8>::log10e() != half8{ M_LOG10E_H })) return;
    if (all(math_constants<half8>::ln2() != half8{ M_LN2_H })) return;
    if (all(math_constants<half8>::ln10() != half8{ M_LN10_H })) return;
    if (all(math_constants<half8>::pi() != half8{ M_PI_H })) return;
    if (all(math_constants<half8>::pi_2() != half8{ M_PI_2_H })) return;
    if (all(math_constants<half8>::pi_4() != half8{ M_PI_4_H })) return;
    if (all(math_constants<half8>::one_pi() != half8{ M_1_PI_H })) return;
    if (all(math_constants<half8>::two_pi() != half8{ M_2_PI_H })) return;
    if (all(math_constants<half8>::two_sqrtpi() != half8{ M_2_SQRTPI_H })) return;
    if (all(math_constants<half8>::sqrt2() != half8{ M_SQRT2_H })) return;
    if (all(math_constants<half8>::sqrt1_2() != half8{ M_SQRT1_2_H })) return;

    if (all(math_constants<half16>::e() != half16{ M_E_H })) return;
    if (all(math_constants<half16>::log2e() != half16{ M_LOG2E_H })) return;
    if (all(math_constants<half16>::log10e() != half16{ M_LOG10E_H })) return;
    if (all(math_constants<half16>::ln2() != half16{ M_LN2_H })) return;
    if (all(math_constants<half16>::ln10() != half16{ M_LN10_H })) return;
    if (all(math_constants<half16>::pi() != half16{ M_PI_H })) return;
    if (all(math_constants<half16>::pi_2() != half16{ M_PI_2_H })) return;
    if (all(math_constants<half16>::pi_4() != half16{ M_PI_4_H })) return;
    if (all(math_constants<half16>::one_pi() != half16{ M_1_PI_H })) return;
    if (all(math_constants<half16>::two_pi() != half16{ M_2_PI_H })) return;
    if (all(math_constants<half16>::two_sqrtpi() != half16{ M_2_SQRTPI_H })) return;
    if (all(math_constants<half16>::sqrt2() != half16{ M_SQRT2_H })) return;
    if (all(math_constants<half16>::sqrt1_2() != half16{ M_SQRT1_2_H })) return;
}
