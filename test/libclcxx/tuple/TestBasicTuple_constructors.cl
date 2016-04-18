// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_tuple>
using namespace cl;

struct Foo
{
    Foo(int) {}
};

struct Foo2
{
    Foo2() = delete;
    Foo2(Foo const& f) {}

    operator int() const { return 1; }
};

struct Foo3
{
    Foo3() { }
    Foo3(int) { }
};

kernel void worker()
{
    tuple<Foo> t(12);
    tuple<Foo2> t2(t);
    tuple<Foo3> t3;
}
