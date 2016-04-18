// RUN: %clang_cc1 %s -triple spir-unknown-unknown -emit-llvm -O0 -cl-std=c++ -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_math_constants>
using namespace cl;

bool all(bool2 b) { return b.x && b.y; }
bool all(bool3 b) { return b.x && b.y && b.z; }
bool all(bool4 b) { return b.x && b.y && b.z && b.w; }
bool all(bool8 b) { return b.s0 && b.s1 && b.s2 && b.s3 && b.s4 && b.s5 && b.s6 && b.s7; }
bool all(bool16 b) { return b.s0 && b.s1 && b.s2 && b.s3 && b.s4 && b.s5 && b.s6 && b.s7 && b.s8 && b.s9 && b.sa && b.sb && b.sc && b.sd && b.se && b.sf; }

kernel void worker() {
    if (math_constants<float>::e() != float{ M_E_F }) return;
    if (math_constants<float>::log2e() != float{ M_LOG2E_F }) return;
    if (math_constants<float>::log10e() != float{ M_LOG10E_F }) return;
    if (math_constants<float>::ln2() != float{ M_LN2_F }) return;
    if (math_constants<float>::ln10() != float{ M_LN10_F }) return;
    if (math_constants<float>::pi() != float{ M_PI_F }) return;
    if (math_constants<float>::pi_2() != float{ M_PI_2_F }) return;
    if (math_constants<float>::pi_4() != float{ M_PI_4_F }) return;
    if (math_constants<float>::one_pi() != float{ M_1_PI_F }) return;
    if (math_constants<float>::two_pi() != float{ M_2_PI_F }) return;
    if (math_constants<float>::two_sqrtpi() != float{ M_2_SQRTPI_F }) return;
    if (math_constants<float>::sqrt2() != float{ M_SQRT2_F }) return;
    if (math_constants<float>::sqrt1_2() != float{ M_SQRT1_2_F }) return;

    if (all(math_constants<float2>::e() != float2{ M_E_F })) return;
    if (all(math_constants<float2>::log2e() != float2{ M_LOG2E_F })) return;
    if (all(math_constants<float2>::log10e() != float2{ M_LOG10E_F })) return;
    if (all(math_constants<float2>::ln2() != float2{ M_LN2_F })) return;
    if (all(math_constants<float2>::ln10() != float2{ M_LN10_F })) return;
    if (all(math_constants<float2>::pi() != float2{ M_PI_F })) return;
    if (all(math_constants<float2>::pi_2() != float2{ M_PI_2_F })) return;
    if (all(math_constants<float2>::pi_4() != float2{ M_PI_4_F })) return;
    if (all(math_constants<float2>::one_pi() != float2{ M_1_PI_F })) return;
    if (all(math_constants<float2>::two_pi() != float2{ M_2_PI_F })) return;
    if (all(math_constants<float2>::two_sqrtpi() != float2{ M_2_SQRTPI_F })) return;
    if (all(math_constants<float2>::sqrt2() != float2{ M_SQRT2_F })) return;
    if (all(math_constants<float2>::sqrt1_2() != float2{ M_SQRT1_2_F })) return;

    if (all(math_constants<float3>::e() != float3{ M_E_F })) return;
    if (all(math_constants<float3>::log2e() != float3{ M_LOG2E_F })) return;
    if (all(math_constants<float3>::log10e() != float3{ M_LOG10E_F })) return;
    if (all(math_constants<float3>::ln2() != float3{ M_LN2_F })) return;
    if (all(math_constants<float3>::ln10() != float3{ M_LN10_F })) return;
    if (all(math_constants<float3>::pi() != float3{ M_PI_F })) return;
    if (all(math_constants<float3>::pi_2() != float3{ M_PI_2_F })) return;
    if (all(math_constants<float3>::pi_4() != float3{ M_PI_4_F })) return;
    if (all(math_constants<float3>::one_pi() != float3{ M_1_PI_F })) return;
    if (all(math_constants<float3>::two_pi() != float3{ M_2_PI_F })) return;
    if (all(math_constants<float3>::two_sqrtpi() != float3{ M_2_SQRTPI_F })) return;
    if (all(math_constants<float3>::sqrt2() != float3{ M_SQRT2_F })) return;
    if (all(math_constants<float3>::sqrt1_2() != float3{ M_SQRT1_2_F })) return;

    if (all(math_constants<float4>::e() != float4{ M_E_F })) return;
    if (all(math_constants<float4>::log2e() != float4{ M_LOG2E_F })) return;
    if (all(math_constants<float4>::log10e() != float4{ M_LOG10E_F })) return;
    if (all(math_constants<float4>::ln2() != float4{ M_LN2_F })) return;
    if (all(math_constants<float4>::ln10() != float4{ M_LN10_F })) return;
    if (all(math_constants<float4>::pi() != float4{ M_PI_F })) return;
    if (all(math_constants<float4>::pi_2() != float4{ M_PI_2_F })) return;
    if (all(math_constants<float4>::pi_4() != float4{ M_PI_4_F })) return;
    if (all(math_constants<float4>::one_pi() != float4{ M_1_PI_F })) return;
    if (all(math_constants<float4>::two_pi() != float4{ M_2_PI_F })) return;
    if (all(math_constants<float4>::two_sqrtpi() != float4{ M_2_SQRTPI_F })) return;
    if (all(math_constants<float4>::sqrt2() != float4{ M_SQRT2_F })) return;
    if (all(math_constants<float4>::sqrt1_2() != float4{ M_SQRT1_2_F })) return;

    if (all(math_constants<float8>::e() != float8{ M_E_F })) return;
    if (all(math_constants<float8>::log2e() != float8{ M_LOG2E_F })) return;
    if (all(math_constants<float8>::log10e() != float8{ M_LOG10E_F })) return;
    if (all(math_constants<float8>::ln2() != float8{ M_LN2_F })) return;
    if (all(math_constants<float8>::ln10() != float8{ M_LN10_F })) return;
    if (all(math_constants<float8>::pi() != float8{ M_PI_F })) return;
    if (all(math_constants<float8>::pi_2() != float8{ M_PI_2_F })) return;
    if (all(math_constants<float8>::pi_4() != float8{ M_PI_4_F })) return;
    if (all(math_constants<float8>::one_pi() != float8{ M_1_PI_F })) return;
    if (all(math_constants<float8>::two_pi() != float8{ M_2_PI_F })) return;
    if (all(math_constants<float8>::two_sqrtpi() != float8{ M_2_SQRTPI_F })) return;
    if (all(math_constants<float8>::sqrt2() != float8{ M_SQRT2_F })) return;
    if (all(math_constants<float8>::sqrt1_2() != float8{ M_SQRT1_2_F })) return;

    if (all(math_constants<float16>::e() != float16{ M_E_F })) return;
    if (all(math_constants<float16>::log2e() != float16{ M_LOG2E_F })) return;
    if (all(math_constants<float16>::log10e() != float16{ M_LOG10E_F })) return;
    if (all(math_constants<float16>::ln2() != float16{ M_LN2_F })) return;
    if (all(math_constants<float16>::ln10() != float16{ M_LN10_F })) return;
    if (all(math_constants<float16>::pi() != float16{ M_PI_F })) return;
    if (all(math_constants<float16>::pi_2() != float16{ M_PI_2_F })) return;
    if (all(math_constants<float16>::pi_4() != float16{ M_PI_4_F })) return;
    if (all(math_constants<float16>::one_pi() != float16{ M_1_PI_F })) return;
    if (all(math_constants<float16>::two_pi() != float16{ M_2_PI_F })) return;
    if (all(math_constants<float16>::two_sqrtpi() != float16{ M_2_SQRTPI_F })) return;
    if (all(math_constants<float16>::sqrt2() != float16{ M_SQRT2_F })) return;
    if (all(math_constants<float16>::sqrt1_2() != float16{ M_SQRT1_2_F })) return;
}
