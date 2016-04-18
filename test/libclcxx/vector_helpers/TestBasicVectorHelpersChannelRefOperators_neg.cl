// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable 
#include <opencl_vector_utility>

kernel void worker() 
{

#ifdef cl_khr_fp16
    half8 _half8;
    auto it_half8 = cl::begin(_half8);
    *it_half8 %= 1; //expected-error {{no viable overloaded '%='}}
    *it_half8 ^= 1; //expected-error {{no viable overloaded '^='}}
    *it_half8 &= 1; //expected-error {{no viable overloaded '&='}}
    *it_half8 |= 1; //expected-error {{no viable overloaded '|='}}
#endif

    float8 _float8;
    auto it_float8 = cl::begin(_float8);
    *it_float8 %= 1; //expected-error {{no viable overloaded '%='}}
    *it_float8 ^= 1; //expected-error {{no viable overloaded '^='}}
    *it_float8 &= 1; //expected-error {{no viable overloaded '&='}}
    *it_float8 |= 1; //expected-error {{no viable overloaded '|='}}

#ifdef cl_khr_fp64
    double8 _double8;
    auto it_double8 = cl::begin(_double8);
    *it_double8 %= 1; //expected-error {{no viable overloaded '%='}}
    *it_double8 ^= 1; //expected-error {{no viable overloaded '^='}}
    *it_double8 &= 1; //expected-error {{no viable overloaded '&='}}
    *it_double8 |= 1; //expected-error {{no viable overloaded '|='}}
#endif
}