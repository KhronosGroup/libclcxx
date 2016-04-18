// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_vector_utility>
#include <opencl_range>

using namespace cl;

kernel void worker()
{
    int16 a;
    auto x = cl::get<5>(a);
    cl::set<6>(a, x);
}
