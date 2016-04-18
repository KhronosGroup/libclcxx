// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -verify -nobuiltininc -O0 -o -

#include <opencl_convert>
using namespace cl;

kernel void worker()
{
    short16 s;
    
    //expected-error@__ocl_convert.h:* {{static_assert failed "convert_cast with rounding mode option can be used only in conversions to/from floating point types."}}
    //expected-note@+1 {{in instantiation}}
    char16 c = convert_cast<char16, rounding_mode::rtp>(s);
}
