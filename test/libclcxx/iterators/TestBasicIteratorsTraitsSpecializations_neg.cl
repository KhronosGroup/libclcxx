// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -cl-fp64-enable -fsyntax-only -pedantic -verify
// XFAIL: *

#include <opencl_memory>
using namespace cl;

struct invalid_iterator { };

kernel void worker()
{
    iterator_traits<invalid_iterator> it;
}