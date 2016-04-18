// RUN: %clang_cc1 %s -triple spir-unknown-unknown -emit-llvm -O0 -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp64-enable
// expected-no-diagnostics

#include <opencl_math_constants>
using namespace cl;

bool all(bool2 b) { return b.x && b.y; }
bool all(bool3 b) { return b.x && b.y && b.z; }
bool all(bool4 b) { return b.x && b.y && b.z && b.w; }
bool all(bool8 b) { return b.s0 && b.s1 && b.s2 && b.s3 && b.s4 && b.s5 && b.s6 && b.s7; }
bool all(bool16 b) { return b.s0 && b.s1 && b.s2 && b.s3 && b.s4 && b.s5 && b.s6 && b.s7 && b.s8 && b.s9 && b.sa && b.sb && b.sc && b.sd && b.se && b.sf; }

kernel void worker() {
    if (math_constants<double>::e() != double{ M_E }) return;
    if (math_constants<double>::log2e() != double{ M_LOG2E }) return;
    if (math_constants<double>::log10e() != double{ M_LOG10E }) return;
    if (math_constants<double>::ln2() != double{ M_LN2 }) return;
    if (math_constants<double>::ln10() != double{ M_LN10 }) return;
    if (math_constants<double>::pi() != double{ M_PI }) return;
    if (math_constants<double>::pi_2() != double{ M_PI_2 }) return;
    if (math_constants<double>::pi_4() != double{ M_PI_4 }) return;
    if (math_constants<double>::one_pi() != double{ M_1_PI }) return;
    if (math_constants<double>::two_pi() != double{ M_2_PI }) return;
    if (math_constants<double>::two_sqrtpi() != double{ M_2_SQRTPI }) return;
    if (math_constants<double>::sqrt2() != double{ M_SQRT2 }) return;
    if (math_constants<double>::sqrt1_2() != double{ M_SQRT1_2 }) return;

    if (all(math_constants<double2>::e() != double2{ M_E })) return;
    if (all(math_constants<double2>::log2e() != double2{ M_LOG2E })) return;
    if (all(math_constants<double2>::log10e() != double2{ M_LOG10E })) return;
    if (all(math_constants<double2>::ln2() != double2{ M_LN2 })) return;
    if (all(math_constants<double2>::ln10() != double2{ M_LN10 })) return;
    if (all(math_constants<double2>::pi() != double2{ M_PI })) return;
    if (all(math_constants<double2>::pi_2() != double2{ M_PI_2 })) return;
    if (all(math_constants<double2>::pi_4() != double2{ M_PI_4 })) return;
    if (all(math_constants<double2>::one_pi() != double2{ M_1_PI })) return;
    if (all(math_constants<double2>::two_pi() != double2{ M_2_PI })) return;
    if (all(math_constants<double2>::two_sqrtpi() != double2{ M_2_SQRTPI })) return;
    if (all(math_constants<double2>::sqrt2() != double2{ M_SQRT2 })) return;
    if (all(math_constants<double2>::sqrt1_2() != double2{ M_SQRT1_2 })) return;

    if (all(math_constants<double3>::e() != double3{ M_E })) return;
    if (all(math_constants<double3>::log2e() != double3{ M_LOG2E })) return;
    if (all(math_constants<double3>::log10e() != double3{ M_LOG10E })) return;
    if (all(math_constants<double3>::ln2() != double3{ M_LN2 })) return;
    if (all(math_constants<double3>::ln10() != double3{ M_LN10 })) return;
    if (all(math_constants<double3>::pi() != double3{ M_PI })) return;
    if (all(math_constants<double3>::pi_2() != double3{ M_PI_2 })) return;
    if (all(math_constants<double3>::pi_4() != double3{ M_PI_4 })) return;
    if (all(math_constants<double3>::one_pi() != double3{ M_1_PI })) return;
    if (all(math_constants<double3>::two_pi() != double3{ M_2_PI })) return;
    if (all(math_constants<double3>::two_sqrtpi() != double3{ M_2_SQRTPI })) return;
    if (all(math_constants<double3>::sqrt2() != double3{ M_SQRT2 })) return;
    if (all(math_constants<double3>::sqrt1_2() != double3{ M_SQRT1_2 })) return;

    if (all(math_constants<double4>::e() != double4{ M_E })) return;
    if (all(math_constants<double4>::log2e() != double4{ M_LOG2E })) return;
    if (all(math_constants<double4>::log10e() != double4{ M_LOG10E })) return;
    if (all(math_constants<double4>::ln2() != double4{ M_LN2 })) return;
    if (all(math_constants<double4>::ln10() != double4{ M_LN10 })) return;
    if (all(math_constants<double4>::pi() != double4{ M_PI })) return;
    if (all(math_constants<double4>::pi_2() != double4{ M_PI_2 })) return;
    if (all(math_constants<double4>::pi_4() != double4{ M_PI_4 })) return;
    if (all(math_constants<double4>::one_pi() != double4{ M_1_PI })) return;
    if (all(math_constants<double4>::two_pi() != double4{ M_2_PI })) return;
    if (all(math_constants<double4>::two_sqrtpi() != double4{ M_2_SQRTPI })) return;
    if (all(math_constants<double4>::sqrt2() != double4{ M_SQRT2 })) return;
    if (all(math_constants<double4>::sqrt1_2() != double4{ M_SQRT1_2 })) return;

    if (all(math_constants<double8>::e() != double8{ M_E })) return;
    if (all(math_constants<double8>::log2e() != double8{ M_LOG2E })) return;
    if (all(math_constants<double8>::log10e() != double8{ M_LOG10E })) return;
    if (all(math_constants<double8>::ln2() != double8{ M_LN2 })) return;
    if (all(math_constants<double8>::ln10() != double8{ M_LN10 })) return;
    if (all(math_constants<double8>::pi() != double8{ M_PI })) return;
    if (all(math_constants<double8>::pi_2() != double8{ M_PI_2 })) return;
    if (all(math_constants<double8>::pi_4() != double8{ M_PI_4 })) return;
    if (all(math_constants<double8>::one_pi() != double8{ M_1_PI })) return;
    if (all(math_constants<double8>::two_pi() != double8{ M_2_PI })) return;
    if (all(math_constants<double8>::two_sqrtpi() != double8{ M_2_SQRTPI })) return;
    if (all(math_constants<double8>::sqrt2() != double8{ M_SQRT2 })) return;
    if (all(math_constants<double8>::sqrt1_2() != double8{ M_SQRT1_2 })) return;

    if (all(math_constants<double16>::e() != double16{ M_E })) return;
    if (all(math_constants<double16>::log2e() != double16{ M_LOG2E })) return;
    if (all(math_constants<double16>::log10e() != double16{ M_LOG10E })) return;
    if (all(math_constants<double16>::ln2() != double16{ M_LN2 })) return;
    if (all(math_constants<double16>::ln10() != double16{ M_LN10 })) return;
    if (all(math_constants<double16>::pi() != double16{ M_PI })) return;
    if (all(math_constants<double16>::pi_2() != double16{ M_PI_2 })) return;
    if (all(math_constants<double16>::pi_4() != double16{ M_PI_4 })) return;
    if (all(math_constants<double16>::one_pi() != double16{ M_1_PI })) return;
    if (all(math_constants<double16>::two_pi() != double16{ M_2_PI })) return;
    if (all(math_constants<double16>::two_sqrtpi() != double16{ M_2_SQRTPI })) return;
    if (all(math_constants<double16>::sqrt2() != double16{ M_SQRT2 })) return;
    if (all(math_constants<double16>::sqrt1_2() != double16{ M_SQRT1_2 })) return;
}
