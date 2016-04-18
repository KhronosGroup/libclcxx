// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_tuple>
using namespace cl;

struct Foo
{
    Foo() = default;
    Foo(Foo const&) = delete;

    void operator =(float) {}

    Foo& operator =(int) { return *this; }
    void operator ,(int) {}
};

kernel void worker()
{
    tuple<int> t1(1);
    tuple<float> t2(1.2f);

    tuple<Foo> test;

    test = t1;
    test = t2;
}
