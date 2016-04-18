// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_functional>
#include <opencl_type_traits>
using namespace cl;

kernel void worker()
{
    static_assert(is_same<reference_wrapper<int>::type, int>::value, "Fail");
    static_assert(is_same<reference_wrapper<void(int)>::type, void(int)>::value, "Fail");
    static_assert(is_same<reference_wrapper<void(int)>::result_type, void>::value, "Fail");
    static_assert(is_same<reference_wrapper<void(int)>::argument_type, int>::value, "Fail");
    static_assert(is_same<reference_wrapper<void(int&, const float)>::first_argument_type, int&>::value, "Fail");
    static_assert(is_same<reference_wrapper<void(int&, const float)>::second_argument_type, float>::value, "Fail");
}
