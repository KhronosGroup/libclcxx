// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -verify -nobuiltininc -O0 -o - | FileCheck %s
// expected-no-diagnostics

#include <opencl_convert>
using namespace cl;

kernel void worker()
{
    float4 f;
    
    int4 i1 = convert_cast<int4>(f);
    // CHECK: call spir_func <4 x i32> @_Z{{[1-9][0-9]*}}__spirv_ConvertFToS_Rint4_rtz{{[a-zA-Z0-9_]+}}(<4 x float> {{.*}})
    
    int4 i2 = convert_cast<int4, saturate::on>(f);
    // CHECK: call spir_func <4 x i32> @_Z{{[1-9][0-9]*}}__spirv_ConvertFToS_Rint4_sat_rtz{{[a-zA-Z0-9_]+}}(<4 x float> {{.*}})
    
    int4 i3 = convert_cast<int4, saturate::off>(f);
    // CHECK: call spir_func <4 x i32> @_Z{{[1-9][0-9]*}}__spirv_ConvertFToS_Rint4_rtz{{[a-zA-Z0-9_]+}}(<4 x float> {{.*}})
    
    int4 i4 = convert_cast<int4, rounding_mode::rte>(f);
    // CHECK: call spir_func <4 x i32> @_Z{{[1-9][0-9]*}}__spirv_ConvertFToS_Rint4_rte{{[a-zA-Z0-9_]+}}(<4 x float> {{.*}})
    
    int4 i5 = convert_cast<int4, rounding_mode::rtz>(f);
    // CHECK: call spir_func <4 x i32> @_Z{{[1-9][0-9]*}}__spirv_ConvertFToS_Rint4_rtz{{[a-zA-Z0-9_]+}}(<4 x float> {{.*}})
    
    int4 i6 = convert_cast<int4, rounding_mode::rtp>(f);
    // CHECK: call spir_func <4 x i32> @_Z{{[1-9][0-9]*}}__spirv_ConvertFToS_Rint4_rtp{{[a-zA-Z0-9_]+}}(<4 x float> {{.*}})
    
    int4 i7 = convert_cast<int4, rounding_mode::rtn>(f);
    // CHECK: call spir_func <4 x i32> @_Z{{[1-9][0-9]*}}__spirv_ConvertFToS_Rint4_rtn{{[a-zA-Z0-9_]+}}(<4 x float> {{.*}})
    
    int4 i8 = convert_cast<int4, rounding_mode::rte, saturate::on>(f);
    // CHECK: call spir_func <4 x i32> @_Z{{[1-9][0-9]*}}__spirv_ConvertFToS_Rint4_sat_rte{{[a-zA-Z0-9_]+}}(<4 x float> {{.*}})
    
    int4 i9 = convert_cast<int4, rounding_mode::rtz, saturate::on>(f);
    // CHECK: call spir_func <4 x i32> @_Z{{[1-9][0-9]*}}__spirv_ConvertFToS_Rint4_sat_rtz{{[a-zA-Z0-9_]+}}(<4 x float> {{.*}})
    
    int4 i10 = convert_cast<int4, rounding_mode::rtp, saturate::on>(f);
    // CHECK: call spir_func <4 x i32> @_Z{{[1-9][0-9]*}}__spirv_ConvertFToS_Rint4_sat_rtp{{[a-zA-Z0-9_]+}}(<4 x float> {{.*}})
    
    int4 i11 = convert_cast<int4, rounding_mode::rtn, saturate::on>(f);
    // CHECK: call spir_func <4 x i32> @_Z{{[1-9][0-9]*}}__spirv_ConvertFToS_Rint4_sat_rtn{{[a-zA-Z0-9_]+}}(<4 x float> {{.*}})
    
    int4 i12 = convert_cast<int4, rounding_mode::rte, saturate::off>(f);
    // CHECK: call spir_func <4 x i32> @_Z{{[1-9][0-9]*}}__spirv_ConvertFToS_Rint4_rte{{[a-zA-Z0-9_]+}}(<4 x float> {{.*}})
    
    int4 i13 = convert_cast<int4, rounding_mode::rtz, saturate::off>(f);
    // CHECK: call spir_func <4 x i32> @_Z{{[1-9][0-9]*}}__spirv_ConvertFToS_Rint4_rtz{{[a-zA-Z0-9_]+}}(<4 x float> {{.*}})
    
    int4 i14 = convert_cast<int4, rounding_mode::rtp, saturate::off>(f);
    // CHECK: call spir_func <4 x i32> @_Z{{[1-9][0-9]*}}__spirv_ConvertFToS_Rint4_rtp{{[a-zA-Z0-9_]+}}(<4 x float> {{.*}})
    
    int4 i15 = convert_cast<int4, rounding_mode::rtn, saturate::off>(f);
    // CHECK: call spir_func <4 x i32> @_Z{{[1-9][0-9]*}}__spirv_ConvertFToS_Rint4_rtn{{[a-zA-Z0-9_]+}}(<4 x float> {{.*}})
}
