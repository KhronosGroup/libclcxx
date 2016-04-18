// RUN: %clang_cc1 %s -triple spir-unknown-unknown -emit-llvm -O0 -cl-std=c++ -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_device_queue>
using namespace cl;

struct PseudoLambda
{
    template <typename T>
    void operator ()(T t) const
    {
    }
};

kernel void worker(device_queue q)
{
    auto lambda = PseudoLambda{};
    q.enqueue_kernel(enqueue_policy::no_wait, ndrange{1}, lambda, local_ptr<ushort16>::size_type{1});
}
