// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify

#include <opencl_tuple>
using namespace cl;

struct Foo
{
    Foo() = default;
    Foo(Foo const& f) = delete;
};

struct Foo2
{
    Foo2() = delete;
    Foo2(Foo const& f) {}
};

tuple<Foo> f{Foo()}; //expected-error@opencl_tuple:* {{static_assert failed "At least one type in T... is not copy constructible!"}}
                     //expected-error@opencl_tuple:* {{call to deleted constructor of 'Foo'}}
                     //expected-note@opencl_tuple:* 2 {{in instantiation of}}
                     //expected-note@-3 2 {{in instantiation of}}
                     //expected-note@9 {{'Foo' has been explicitly marked deleted here}}
                     
tuple<Foo2> f2(f);
tuple<Foo2> f2_2; //expected-error@opencl_tuple:* {{static_assert failed "At least one type in T... is not default constructible!"}}
                  //expected-error@opencl_tuple:* {{call to deleted constructor of 'Foo2'}}
                  //expected-note@opencl_tuple:* 2 {{in instantiation of}}
                  //expected-note@-3 2 {{in instantiation of}}
                  //expected-note@14 {{'Foo2' has been explicitly marked deleted here}}
