// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -verify -nobuiltininc -O0 -o -

#include <opencl_convert>
using namespace cl;

kernel void worker()
{
    ushort4 f;
    
    //expected-error@__ocl_convert.h:* {{static_assert failed "convert_cast with saturate option can be used only in conversions to integer types."}}
    //expected-note@+1 {{in instantiation}}
    float4 i2 = convert_cast<float4, saturate::on>(f);
    
    //expected-error@__ocl_convert.h:* {{static_assert failed "convert_cast with saturate option can be used only in conversions to integer types."}}
    //expected-note@+1 {{in instantiation}}
    float4 i8 = convert_cast<float4, rounding_mode::rte, saturate::on>(f);
    
    //expected-error@__ocl_convert.h:* {{static_assert failed "convert_cast with saturate option can be used only in conversions to integer types."}}
    //expected-note@+1 {{in instantiation}}
    float4 i9 = convert_cast<float4, rounding_mode::rtz, saturate::on>(f);
    
    //expected-error@__ocl_convert.h:* {{static_assert failed "convert_cast with saturate option can be used only in conversions to integer types."}}
    //expected-note@+1 {{in instantiation}}
    float4 i10 = convert_cast<float4, rounding_mode::rtp, saturate::on>(f);
    
    //expected-error@__ocl_convert.h:* {{static_assert failed "convert_cast with saturate option can be used only in conversions to integer types."}}
    //expected-note@+1 {{in instantiation}}
    float4 i11 = convert_cast<float4, rounding_mode::rtn, saturate::on>(f);
}
