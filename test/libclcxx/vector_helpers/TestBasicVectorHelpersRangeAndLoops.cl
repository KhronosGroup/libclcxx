// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_vector_utility>
#include <opencl_range>

kernel void worker( )
{
    int16 a;

    for (auto it = cl::begin(a); it != cl::end(a); it++)
    {
        int b = *it;
        *it = 2;
    }

    for (auto c : cl::range(a,3,6))
    {
        int b = c;
        c = 2;
    }
}
