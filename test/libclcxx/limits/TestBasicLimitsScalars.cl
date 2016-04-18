// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -cl-fp64-enable  -cl-fp16-enable  -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_limits>
using namespace cl;

kernel void worker()
{
    static_assert(is_vector_type<decltype(numeric_limits<int>::min())>::value == false, "<int>::min() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<int>::max())>::value == false, "<int>::max() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<int>::lowest())>::value == false, "<int>::lowest() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<char>::min())>::value == false, "<char>::min() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<char>::max())>::value == false, "<char>::max() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<char>::lowest())>::value == false, "<char>::lowest() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<short>::min())>::value == false, "<short>::min() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<short>::max())>::value == false, "<short>::max() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<short>::lowest())>::value == false, "<short>::lowest() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<long>::min())>::value == false, "<long>::min() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<long>::max())>::value == false, "<long>::max() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<long>::lowest())>::value == false, "<long>::lowest() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<uint>::min())>::value == false, "<uint>::min() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<uint>::max())>::value == false, "<uint>::max() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<uint>::lowest())>::value == false, "<uint>::lowest() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<uchar>::min())>::value == false, "<uchar>::min() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<uchar>::max())>::value == false, "<uchar>::max() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<uchar>::lowest())>::value == false, "<uchar>::lowest() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<ushort>::min())>::value == false, "<ushort>::min() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<ushort>::max())>::value == false, "<ushort>::max() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<ushort>::lowest())>::value == false, "<ushort>::lowest() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<ulong>::min())>::value == false, "<ulong>::min() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<ulong>::max())>::value == false, "<ulong>::max() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<ulong>::lowest())>::value == false, "<ulong>::lowest() should return scalar");

    static_assert(is_vector_type<decltype(numeric_limits<half>::min())>::value == false, "<half>::min() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<half>::max())>::value == false, "<half>::max() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<half>::lowest())>::value == false, "<half>::lowest() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<half>::epsilon())>::value == false, "<half>::epsilon() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<half>::infinity())>::value == false, "<half>::infinity() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<half>::quiet_NaN())>::value == false, "<half>::quiet_NaN() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<half>::signaling_NaN())>::value == false, "<half>::signaling_NaN() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<half>::denorm_min())>::value == false, "<half>::denorm_min() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<float>::min())>::value == false, "<float>::min() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<float>::max())>::value == false, "<float>::max() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<float>::lowest())>::value == false, "<float>::lowest() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<float>::epsilon())>::value == false, "<float>::epsilon() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<float>::infinity())>::value == false, "<float>::infinity() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<float>::quiet_NaN())>::value == false, "<float>::quiet_NaN() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<float>::signaling_NaN())>::value == false, "<float>::signaling_NaN() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<float>::denorm_min())>::value == false, "<float>::denorm_min() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<double>::min())>::value == false, "<double>::min() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<double>::max())>::value == false, "<double>::max() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<double>::lowest())>::value == false, "<double>::lowest() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<double>::epsilon())>::value == false, "<double>::epsilon() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<double>::infinity())>::value == false, "<double>::infinity() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<double>::quiet_NaN())>::value == false, "<double>::quiet_NaN() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<double>::signaling_NaN())>::value == false, "<double>::signaling_NaN() should return scalar");
    static_assert(is_vector_type<decltype(numeric_limits<double>::denorm_min())>::value == false, "<double>::denorm_min() should return scalar");
}