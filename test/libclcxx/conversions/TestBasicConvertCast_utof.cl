// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -verify -nobuiltininc -O0 -o - | FileCheck %s
// expected-no-diagnostics

#include <opencl_convert>
using namespace cl;

kernel void worker()
{
    ushort4 f;
    
    float4 i1 = convert_cast<float4>(f);
    // CHECK: call spir_func <4 x float> @_Z{{[1-9][0-9]+}}__spirv_ConvertUToF_Rfloat4_rte{{[a-zA-Z0-9_]+}}(<4 x i16> {{.*}})
        
    float4 i3 = convert_cast<float4, saturate::off>(f);
    // CHECK: call spir_func <4 x float> @_Z{{[1-9][0-9]+}}__spirv_ConvertUToF_Rfloat4_rte{{[a-zA-Z0-9_]+}}(<4 x i16> {{.*}})
    
    float4 i4 = convert_cast<float4, rounding_mode::rte>(f);
    // CHECK: call spir_func <4 x float> @_Z{{[1-9][0-9]+}}__spirv_ConvertUToF_Rfloat4_rte{{[a-zA-Z0-9_]+}}(<4 x i16> {{.*}})
    
    float4 i5 = convert_cast<float4, rounding_mode::rtz>(f);
    // CHECK: call spir_func <4 x float> @_Z{{[1-9][0-9]+}}__spirv_ConvertUToF_Rfloat4_rtz{{[a-zA-Z0-9_]+}}(<4 x i16> {{.*}})
    
    float4 i6 = convert_cast<float4, rounding_mode::rtp>(f);
    // CHECK: call spir_func <4 x float> @_Z{{[1-9][0-9]+}}__spirv_ConvertUToF_Rfloat4_rtp{{[a-zA-Z0-9_]+}}(<4 x i16> {{.*}})
    
    float4 i7 = convert_cast<float4, rounding_mode::rtn>(f);
    // CHECK: call spir_func <4 x float> @_Z{{[1-9][0-9]+}}__spirv_ConvertUToF_Rfloat4_rtn{{[a-zA-Z0-9_]+}}(<4 x i16> {{.*}})
        
    float4 i12 = convert_cast<float4, rounding_mode::rte, saturate::off>(f);
    // CHECK: call spir_func <4 x float> @_Z{{[1-9][0-9]+}}__spirv_ConvertUToF_Rfloat4_rte{{[a-zA-Z0-9_]+}}(<4 x i16> {{.*}})
    
    float4 i13 = convert_cast<float4, rounding_mode::rtz, saturate::off>(f);
    // CHECK: call spir_func <4 x float> @_Z{{[1-9][0-9]+}}__spirv_ConvertUToF_Rfloat4_rtz{{[a-zA-Z0-9_]+}}(<4 x i16> {{.*}})
    
    float4 i14 = convert_cast<float4, rounding_mode::rtp, saturate::off>(f);
    // CHECK: call spir_func <4 x float> @_Z{{[1-9][0-9]+}}__spirv_ConvertUToF_Rfloat4_rtp{{[a-zA-Z0-9_]+}}(<4 x i16> {{.*}})
    
    float4 i15 = convert_cast<float4, rounding_mode::rtn, saturate::off>(f);
    // CHECK: call spir_func <4 x float> @_Z{{[1-9][0-9]+}}__spirv_ConvertUToF_Rfloat4_rtn{{[a-zA-Z0-9_]+}}(<4 x i16> {{.*}})
}
