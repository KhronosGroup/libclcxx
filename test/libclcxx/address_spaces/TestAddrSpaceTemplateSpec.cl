// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -verify -O0 -o /dev/null
// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -verify -O3 -o /dev/null
// expected-no-diagnostics

#include <opencl_memory>

template <typename T>
struct SpecTester;

template <typename T>
struct SpecTester<cl::local_ptr<T>> { };

template <typename T>
struct SpecTester<cl::constant_ptr<T>> { };

template <typename T>
struct SpecTester<cl::global_ptr<T>> { };

template <typename T>
struct SpecTester<cl::private_ptr<T>> { };

kernel void worker()
{
	SpecTester<cl::local_ptr<int>> a;
	SpecTester<cl::constant_ptr<int>> b;
	SpecTester<cl::global_ptr<int>> c;
	SpecTester<cl::private_ptr<int>> d;
}
