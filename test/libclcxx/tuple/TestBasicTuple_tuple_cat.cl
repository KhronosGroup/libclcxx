// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_tuple>
using namespace cl;

kernel void worker()
{
    auto test = tuple_cat(make_tuple(1, 2.0f, 'c'), make_tuple(12), make_tuple(1, 2, 3, 4, 5, 6), make_tuple(1.2f, 3.3f));
    static_assert(is_same<remove_as_t<decltype(test)>, tuple<int, float, char, int, int, int, int, int, int, int, float, float>>::value, "type mismatch");
}
