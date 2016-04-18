// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -cl-fp64-enable -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_memory>
#include <opencl_array>
using namespace cl;

kernel void worker()
{
    static_assert(is_same<tuple_element<1, array<int, 3>>::type, int>::value, "tuple_element<array<int, N>>::type should be int");
    static_assert(tuple_size<array<int, 3>>::value == 3, "tuple_size<array<int,N>>::value should equal N");
}