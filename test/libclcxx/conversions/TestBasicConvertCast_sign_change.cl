// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -verify -nobuiltininc -O0 -o - | FileCheck %s
// expected-no-diagnostics

#include <opencl_convert>
using namespace cl;

kernel void worker()
{
    int4 i;
    uint4 u;
    
    i = convert_cast<int4>(u);
    // CHECK: call spir_func <4 x i32> @_Z{{[1-9][0-9]+}}__spirv_Bitcast_Rint4{{[a-zA-Z0-9_]+}}(<4 x i32> {{.*}})
    i = convert_cast<int4, saturate::on>(u);
    // CHECK-NOT: call spir_func <4 x i32> @_Z{{[1-9][0-9]+}}__spirv_SatConvertUToS_Rint4_sat{{[a-zA-Z0-9_]+}}(<4 x i32> {{.*}})
    // CHECK: call spir_func <4 x i32> @_Z{{[1-9][0-9]+}}__spirv_SatConvertUToS_Rint4{{[a-zA-Z0-9_]+}}(<4 x i32> {{.*}})
    
    u = convert_cast<uint4>(i);
    // CHECK: call spir_func <4 x i32> @_Z{{[1-9][0-9]+}}__spirv_Bitcast_Ruint4{{[a-zA-Z0-9_]+}}(<4 x i32> {{.*}})
    u = convert_cast<uint4, saturate::on>(i);
    // CHECK-NOT: call spir_func <4 x i32> @_Z{{[1-9][0-9]+}}__spirv_SatConvertSToU_Ruint4_sat{{[a-zA-Z0-9_]+}}(<4 x i32> {{.*}})
    // CHECK: call spir_func <4 x i32> @_Z{{[1-9][0-9]+}}__spirv_SatConvertSToU_Ruint4{{[a-zA-Z0-9_]+}}(<4 x i32> {{.*}}) 
    
    short4 s;
    uchar4 c;
    
    c = convert_cast<uchar4>(i);
    // CHECK: call spir_func <4 x i8> @_Z{{[1-9][0-9]+}}__spirv_SConvert_Ruchar4{{[a-zA-Z0-9_]+}}(<4 x i32> {{.*}})
    c = convert_cast<uchar4, saturate::on>(i);
    // CHECK-NOT: call spir_func <4 x i8> @_Z{{[1-9][0-9]+}}__spirv_SatConvertSToU_Ruchar4_sat{{[a-zA-Z0-9_]+}}(<4 x i32> {{.*}})
    // CHECK: call spir_func <4 x i8> @_Z{{[1-9][0-9]+}}__spirv_SatConvertSToU_Ruchar4{{[a-zA-Z0-9_]+}}(<4 x i32> {{.*}})
    
    s = convert_cast<short4>(u);
    // CHECK: call spir_func <4 x i16> @_Z{{[1-9][0-9]+}}__spirv_UConvert_Rshort4{{[a-zA-Z0-9_]+}}(<4 x i32> {{.*}})
    s = convert_cast<short4, saturate::on>(u);
    // CHECK-NOT: call spir_func <4 x i16> @_Z{{[1-9][0-9]+}}__spirv_SatConvertUToS_Rshort4_sat{{[a-zA-Z0-9_]+}}(<4 x i32> {{.*}})
    // CHECK: call spir_func <4 x i16> @_Z{{[1-9][0-9]+}}__spirv_SatConvertUToS_Rshort4{{[a-zA-Z0-9_]+}}(<4 x i32> {{.*}})
}
