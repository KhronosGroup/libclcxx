// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -verify -O0 -o /dev/null
// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -verify -O3 -o /dev/null
// expected-no-diagnostics

#include <opencl_memory>
using namespace cl;

struct Base {};
struct Derived : Base {};

kernel void worker()
{
    global_ptr<int> a;
    global_ptr<const int> b = a;

    private_ptr<Derived> der;
    private_ptr<Base> base = der;

    if (der == base) return;

    local_ptr<float[]> f;
    local_ptr<const float[]> f2 = f;
    f[10] = 5.0f;

    constant_ptr<const int*[]> pptr;
    constant_ptr<const int* const[]> pptr2 = pptr;

    global_ptr<const typename local_ptr<const short8>::pointer> raw = global_ptr<typename local_ptr<const short8>::pointer>{};

    global_ptr<local_ptr<volatile int16>[]> wrapped = (add_global_t<local_ptr<volatile int16>>*)nullptr;
    wrapped[1] = nullptr;
}
