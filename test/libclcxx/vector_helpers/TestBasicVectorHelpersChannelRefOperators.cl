// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable 
// expected-no-diagnostics

#include <opencl_vector_utility>
#include <opencl_range>

kernel void worker() 
{

    int8 _int8;
    auto it_int8 = cl::begin(_int8);
    *it_int8 += 1;
    *it_int8 -= 1;
    *it_int8 *= 1;
    *it_int8 /= 1;
    *it_int8 %= 1;
    *it_int8 ^= 1;
    *it_int8 &= 1;
    *it_int8 |= 1;
    (*it_int8)++;
    ++(*it_int8);
    (*it_int8)--;
    --(*it_int8);
    *it_int8 = 1;
    int _int_conv = *it_int8;

    uint8 _uint8;
    auto it_uint8 = cl::begin(_uint8);
    *it_uint8 += 1;
    *it_uint8 -= 1;
    *it_uint8 *= 1;
    *it_uint8 /= 1;
    *it_uint8 %= 1;
    *it_uint8 ^= 1;
    *it_uint8 &= 1;
    *it_uint8 |= 1;
    (*it_uint8)++;
    ++(*it_uint8);
    (*it_uint8)--;
    --(*it_uint8);
    *it_uint8 = 1;
    uint _uint_conv = *it_uint8;

#ifdef cl_khr_fp16
    half8 _half8;
    auto it_half8 = cl::begin(_half8);
    *it_half8 += 1;
    *it_half8 -= 1;
    *it_half8 *= 1;
    *it_half8 /= 1;
    (*it_half8)++;
    ++(*it_half8);
    (*it_half8)--;
    --(*it_half8);
    *it_half8 = 1;
    half _half_conv = *it_half8;
#endif

    float8 _float8;
    auto it_float8 = cl::begin(_float8);
    *it_float8 += 1;
    *it_float8 -= 1;
    *it_float8 *= 1;
    *it_float8 /= 1;
    (*it_float8)++;
    ++(*it_float8);
    (*it_float8)--;
    --(*it_float8);
    *it_float8 = 1;
    float _float_conv = *it_float8;

#ifdef cl_khr_fp64
    double8 _double8;
    auto it_double8 = cl::begin(_double8);
    *it_double8 += 1;
    *it_double8 -= 1;
    *it_double8 *= 1;
    *it_double8 /= 1;
    (*it_double8)++;
    ++(*it_double8);
    (*it_double8)--;
    --(*it_double8);
    *it_double8 = 1;
    double _double_conv = *it_double8;
#endif

    bool8 _bool8;
    auto it_bool8 = cl::begin(_bool8);
    *it_bool8 += 1;
    *it_bool8 -= 1;
    *it_bool8 *= 1;
    *it_bool8 /= 1;
    *it_bool8 %= 1;
    *it_bool8 ^= 1;
    *it_bool8 &= 1;
    *it_bool8 |= 1;
    (*it_bool8)++;
    ++(*it_bool8);
    *it_bool8 = 1;
    bool _bool_conv = *it_bool8;
}