// RUN: not %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -nobuiltininc -verify -O0 -o - 2>%t
// RUN: FileCheck -input-file=%t %s

#include <opencl_convert>
using namespace cl;

kernel void worker()
{
    bool4 b;
    float4 f;
    int4 i;
    
    f = convert_cast<float4, roundingmode::rtp>(b);
    i = convert_cast<int4, saturate::on>(b);
    b = convert_cast<bool4, saturate::on>(f);
    b = convert_cast<bool4, saturate::on>(i);

    // CHECK: static_assert failed "rounding mode cannot be used while converting to/from bool."
    // CHECK: static_assert failed "convert_cast with saturate option cannot be used in conversions to/from bool."
    // CHECK: static_assert failed "convert_cast with saturate option cannot be used in conversions to/from bool."
    // CHECK: static_assert failed "convert_cast with saturate option cannot be used in conversions to/from bool."
    
    // CHECK: TestBasicConvertCast_booleans_neg.cl Line 13: in instantiation of function template specialization 'cl::convert_cast
    // CHECK: TestBasicConvertCast_booleans_neg.cl Line 14: in instantiation of function template specialization 'cl::convert_cast
    // CHECK: TestBasicConvertCast_booleans_neg.cl Line 15: in instantiation of function template specialization 'cl::convert_cast
    // CHECK: TestBasicConvertCast_booleans_neg.cl Line 16: in instantiation of function template specialization 'cl::convert_cast
}
