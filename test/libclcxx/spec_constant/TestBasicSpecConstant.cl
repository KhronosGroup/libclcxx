// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_spec_constant>
using namespace cl;

spec_constant<int, 1> test{ 10 };

void foo(int);

[[cl::required_work_group_size(test, 1, 1)]]
kernel void worker()
{
    foo(test.get());
}
