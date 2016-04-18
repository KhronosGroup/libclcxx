// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_limits>

kernel void worker()
{
    static_assert(cl::numeric_limits<bool>::is_specialized ==  true, "<bool>::is_specialized invalid value");
    static_assert(cl::numeric_limits<bool>::min() == false, "<bool>::min invalid value");
    static_assert(cl::numeric_limits<bool>::max() == true, "<bool>::max invalid value");
    static_assert(cl::numeric_limits<bool>::lowest() == false, "<bool>::lowest invalid value");
    static_assert(cl::numeric_limits<bool>::digits ==  1, "<bool>::digits invalid value");
    static_assert(cl::numeric_limits<bool>::digits10 ==  0, "<bool>::digits10 invalid value");
    static_assert(cl::numeric_limits<bool>::max_digits10 ==  0, "<bool>::max_digits10 invalid value");
    static_assert(cl::numeric_limits<bool>::is_signed ==  false, "<bool>::is_signed invalid value");
    static_assert(cl::numeric_limits<bool>::is_integer ==  true, "<bool>::is_integer invalid value");
    static_assert(cl::numeric_limits<bool>::is_exact ==  true, "<bool>::is_exact invalid value");
    static_assert(cl::numeric_limits<bool>::radix ==  2, "<bool>::radix invalid value");
    static_assert(cl::numeric_limits<bool>::epsilon() == 0, "<bool>::epsilon invalid value");
    static_assert(cl::numeric_limits<bool>::round_error() == 0, "<bool>::round_error invalid value");
    static_assert(cl::numeric_limits<bool>::min_exponent ==  0, "<bool>::min_exponent invalid value");
    static_assert(cl::numeric_limits<bool>::min_exponent10 ==  0, "<bool>::min_exponent10 invalid value");
    static_assert(cl::numeric_limits<bool>::max_exponent ==  0, "<bool>::max_exponent invalid value");
    static_assert(cl::numeric_limits<bool>::max_exponent10 ==  0, "<bool>::max_exponent10 invalid value");
    static_assert(cl::numeric_limits<bool>::has_infinity ==  false, "<bool>::has_infinity invalid value");
    static_assert(cl::numeric_limits<bool>::has_quiet_NaN ==  false, "<bool>::has_quiet_NaN invalid value");
    static_assert(cl::numeric_limits<bool>::has_signaling_NaN ==  false, "<bool>::has_signaling_NaN invalid value");
    static_assert(cl::numeric_limits<bool>::has_denorm ==  cl::denorm_absent, "<bool>::has_denorm invalid value");
    static_assert(cl::numeric_limits<bool>::has_denorm_loss ==  false, "<bool>::has_denorm_loss invalid value");
    static_assert(cl::numeric_limits<bool>::infinity() == 0, "<bool>::infinity invalid value");
    static_assert(cl::numeric_limits<bool>::quiet_NaN() == 0, "<bool>::quiet_NaN invalid value");
    static_assert(cl::numeric_limits<bool>::signaling_NaN() == 0, "<bool>::signaling_NaN invalid value");
    static_assert(cl::numeric_limits<bool>::denorm_min() == 0, "<bool>::denorm_min invalid value");
    static_assert(cl::numeric_limits<bool>::is_iec559 ==  false, "<bool>::is_iec559 invalid value");
    static_assert(cl::numeric_limits<bool>::is_bounded ==  true, "<bool>::is_bounded invalid value");
    static_assert(cl::numeric_limits<bool>::is_modulo ==  false, "<bool>::is_modulo invalid value");
    static_assert(cl::numeric_limits<bool>::traps ==  false, "<bool>::traps invalid value");
    static_assert(cl::numeric_limits<bool>::tinyness_before ==  false, "<bool>::tinyness_before invalid value");
    static_assert(cl::numeric_limits<bool>::round_style == cl::round_toward_zero, "<bool>::round_style invalid value");
    static_assert(cl::numeric_limits<bool>::is_scalar ==  false, "<bool>::is_scalar invalid value");
    static_assert(cl::numeric_limits<bool>::is_vector ==  false, "<bool>::is_vector invalid value");
}