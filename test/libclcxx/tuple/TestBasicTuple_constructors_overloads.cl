// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_tuple>
using namespace cl;

struct Foo2
{
  Foo2() = default;
  Foo2(Foo2 const&) = default;
};

struct Foo
{
  Foo() = default;
  Foo(Foo2 const&) { }
  
  Foo(Foo2&&) = delete;
};

kernel void worker()
{
    tuple<Foo> test = make_tuple(Foo2());
}
