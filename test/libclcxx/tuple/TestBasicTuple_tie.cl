// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_tuple>
using namespace cl;



kernel void worker()
{
    int a;
    char c;
    tie(a, ignore, c) = make_tuple(123, nullptr, 'c');
}
