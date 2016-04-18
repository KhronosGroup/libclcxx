// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -cl-fp64-enable -cl-fp16-enable -fsyntax-only -pedantic -verify 
// expected-no-diagnostics

#include <opencl_limits>
using namespace cl;

kernel void worker()
{
    static_assert(numeric_limits<float>::is_signed, "float should be signed");
    static_assert(numeric_limits<float2>::is_signed, "float2 should be signed");
    static_assert(numeric_limits<float2>::is_scalar == false,   "<float2>::is_scalar should return false");
    static_assert(numeric_limits<float2>::is_vector == true,   "<float2>::is_vector should return true");
    static_assert(numeric_limits<float>::is_scalar == true, "<float>::is_scalar should return true");
    static_assert(numeric_limits<float>::is_vector == false, "<float>::is_vector should return false");
    static_assert(numeric_limits<float>::has_infinity ==  true, "<float>::has_infinity invalid value");
    static_assert(numeric_limits<float>::has_quiet_NaN ==  true, "<float>::has_quiet_NaN invalid value");
    static_assert(numeric_limits<float>::is_bounded ==  true, "<float>::is_bounded invalid value");
    static_assert(numeric_limits<float>::is_exact ==  false, "<float>::is_exact invalid value");
    static_assert(numeric_limits<float>::is_iec559 ==  true, "<float>::is_iec559 invalid value");
    static_assert(numeric_limits<float>::is_integer ==  false, "<float>::is_integer invalid value");
    static_assert(numeric_limits<float>::is_modulo ==  false, "<float>::is_modulo invalid value");
    static_assert(numeric_limits<float>::is_signed ==  true, "<float>::is_signed invalid value");
    static_assert(numeric_limits<float>::is_specialized ==  true, "<float>::is_specialized invalid value");
    static_assert(numeric_limits<float>::tinyness_before ==  true, "<float>::tinyness_before invalid value");
    static_assert(numeric_limits<float>::traps ==  false, "<float>::traps invalid value");
    static_assert(numeric_limits<float>::round_style ==  round_to_nearest, "<float>::round_style invalid value");
    static_assert(numeric_limits<float>::radix ==  2, "<float>::radix invalid value");

    static_assert(numeric_limits<double>::is_signed, "double should be signed");
    static_assert(numeric_limits<double2>::is_signed, "double2 should be signed");
    static_assert(numeric_limits<double>::is_scalar == true, "<double>::is_scalar should return true");
    static_assert(numeric_limits<double>::is_vector == false, "<double>::is_vector should return false");
    static_assert(numeric_limits<double2>::is_scalar == false,   "<double2>::is_scalar should return false");
    static_assert(numeric_limits<double2>::is_vector == true,   "<double2>::is_vector should return true");
    static_assert(numeric_limits<double>::has_infinity ==  true, "<double>::has_infinity invalid value");
    static_assert(numeric_limits<double>::has_quiet_NaN ==  true, "<double>::has_quiet_NaN invalid value");
    static_assert(numeric_limits<double>::is_bounded ==  true, "<double>::is_bounded invalid value");
    static_assert(numeric_limits<double>::is_exact ==  false, "<double>::is_exact invalid value");
    static_assert(numeric_limits<double>::is_iec559 ==  true, "<double>::is_iec559 invalid value");
    static_assert(numeric_limits<double>::is_integer ==  false, "<double>::is_integer invalid value");
    static_assert(numeric_limits<double>::is_modulo ==  false, "<double>::is_modulo invalid value");
    static_assert(numeric_limits<double>::is_signed ==  true, "<double>::is_signed invalid value");
    static_assert(numeric_limits<double>::is_specialized ==  true, "<double>::is_specialized invalid value");
    static_assert(numeric_limits<double>::tinyness_before ==  true, "<double>::tinyness_before invalid value");
    static_assert(numeric_limits<double>::traps ==  false, "<double>::traps invalid value");
    static_assert(numeric_limits<double>::round_style ==  round_to_nearest, "<double>::round_style invalid value");
    static_assert(numeric_limits<double>::radix ==  2, "<double>::radix invalid value");

    static_assert(numeric_limits<half>::min() != 0, "<half>::min should not equal 0");
    static_assert(numeric_limits<half>::max() != 0, "<half>::max should not equal 0");
    static_assert(numeric_limits<half>::lowest() != 0, "<half>::lowest should not equal 0");
    static_assert(numeric_limits<half>::epsilon() != 0, "<half>::epsilon should not equal 0");
    static_assert(numeric_limits<half>::infinity() != 0, "<half>::infinity should not equal 0");
    static_assert(numeric_limits<half>::quiet_NaN() != 0, "<half>::quiet_nan should not equal 0");
    static_assert(numeric_limits<half>::signaling_NaN() != 0, "<half>::signaling_nan should not equal 0");

    static_assert(numeric_limits<float>::min() != 0, "<float>::min should not equal 0");
    static_assert(numeric_limits<float>::max() != 0, "<float>::max should not equal 0");
    static_assert(numeric_limits<float>::lowest() != 0, "<float>::lowest should not equal 0");
    static_assert(numeric_limits<float>::epsilon() != 0, "<float>::epsilon should not equal 0");
    static_assert(numeric_limits<float>::infinity() != 0, "<float>::infinity should not equal 0");
    static_assert(numeric_limits<float>::quiet_NaN() != 0, "<float>::quiet_NaN should not equal 0");
    static_assert(numeric_limits<float>::signaling_NaN() != 0, "<float>::signaling_NaN should not equal 0");
    static_assert(numeric_limits<double>::min() != 0, "<double>::min should not equal 0");
    static_assert(numeric_limits<double>::max() != 0, "<double>::max should not equal 0");
    static_assert(numeric_limits<double>::lowest() != 0, "<double>::lowest should not equal 0");
    static_assert(numeric_limits<double>::epsilon() != 0, "<double>::epsilon should not equal 0");
    static_assert(numeric_limits<double>::infinity() != 0, "<double>::infinity should not equal 0");
    static_assert(numeric_limits<double>::quiet_NaN() != 0, "<double>::quiet_NaN should not equal 0");
    static_assert(numeric_limits<double>::signaling_NaN() != 0, "<double>::signaling_NaN should not equal 0");
}
