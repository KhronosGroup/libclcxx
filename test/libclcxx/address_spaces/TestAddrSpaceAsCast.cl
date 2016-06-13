// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -verify -O0 -o /dev/null
// expected-no-diagnostics

#include <opencl_memory>
using namespace cl;

global_ptr<char> mychar;
global_ptr<long> mylong = reinterpret_asptr_cast<long>(mychar);

constant_ptr<uint> myuint;
constant_ptr<ushort> myushort = reinterpret_asptr_cast<ushort>(myuint);

struct Base {};
struct Derive : Base {};

kernel void worker()
{
    local_ptr<const int> myint;
    local_ptr<const ulong> myulong = reinterpret_asptr_cast<const ulong>(myint);
    
    private_ptr<float> myfloat;
    private_ptr<const short> myshort = reinterpret_asptr_cast<const short>(myfloat);
    
    local_ptr<int> test;
    local_ptr<void> voidptr = static_asptr_cast<void>(test);
    local_ptr<double> test2 = static_asptr_cast<double>(voidptr);
    
    local_ptr<const int> test3;
    local_ptr<const void> cvoidptr = static_asptr_cast<const void>(test3);
    local_ptr<const double> test4 = static_asptr_cast<const double>(cvoidptr);
    
    global_ptr<Derive> d;
    global_ptr<const Base> b = static_asptr_cast<const Base>(d);
}
