// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -verify -nobuiltininc -O0 -o - | FileCheck %s
// expected-no-diagnostics

#include <opencl_convert>
using namespace cl;

kernel void worker()
{
    short16 s;
    
    char16 c = convert_cast<char16>(s);
    // CHECK: call spir_func <16 x i8> @_Z{{[1-9][0-9]+}}__spirv_SConvert_Rchar16{{[a-zA-Z0-9_]+}}(<16 x i16> {{.*}})
    
    long16 l = convert_cast<long16, saturate::off>(c);
    // CHECK: call spir_func <16 x i64> @_Z{{[1-9][0-9]+}}__spirv_SConvert_Rlong16{{[a-zA-Z0-9_]+}}(<16 x i8> {{.*}})
    
    int16 i = convert_cast<int16, saturate::on>(l);
    // CHECK: call spir_func <16 x i32> @_Z{{[1-9][0-9]+}}__spirv_SConvert_Rint16_sat{{[a-zA-Z0-9_]+}}(<16 x i64> {{.*}})
}
