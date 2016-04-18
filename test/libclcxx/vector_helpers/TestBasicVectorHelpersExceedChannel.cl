// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable 
#include <opencl_vector_utility>
#include <opencl_range>

kernel void worker() 
{
    int2 _int2;
    auto _int2_get2 = cl::get<3>(_int2);//expected-error@__ocl_vector_utility.h:* {{vector component access exceeds type}}
                //expected-note@-1 {{in instantiation of}}
                //expected-note@__ocl_vector_utility.h:* {{in instantiation of}}
    int3 _int3;
    auto _int3_get3 = cl::get<4>(_int3);//expected-error@__ocl_vector_utility.h:* {{vector component access exceeds type}}
                //expected-note@-1 {{in instantiation of}}
                //expected-note@__ocl_vector_utility.h:* {{in instantiation of}}
    int4 _int4;
    auto _int4_get4 = cl::get<5>(_int4);//expected-error@__ocl_vector_utility.h:* {{vector component access exceeds type}}
                //expected-note@-1 {{in instantiation of}}
                //expected-note@__ocl_vector_utility.h:* {{in instantiation of}}
    int8 _int8;
    auto _int8_get8 = cl::get<9>(_int8);//expected-error@__ocl_vector_utility.h:* {{vector component access exceeds type}}
                //expected-note@-1 {{in instantiation of}}
                //expected-note@__ocl_vector_utility.h:* {{in instantiation of}}
    int16 _int16;
    auto _int16_get16 = cl::get<17>(_int16);//expected-error@__ocl_vector_utility.h:* {{implicit instantiation of undefined template}}
                //expected-note@-1 {{in instantiation of}}
                //expected-note@__ocl_vector_utility.h:* {{template is declared here}}
    uint2 _uint2;
    auto _uint2_get2 = cl::get<3>(_uint2);//expected-error@__ocl_vector_utility.h:* {{vector component access exceeds type}}
                //expected-note@-1 {{in instantiation of}}
                //expected-note@__ocl_vector_utility.h:* {{in instantiation of}}
    uint3 _uint3;
    auto _uint3_get3 = cl::get<4>(_uint3);//expected-error@__ocl_vector_utility.h:* {{vector component access exceeds type}}
                //expected-note@-1 {{in instantiation of}}
                //expected-note@__ocl_vector_utility.h:* {{in instantiation of}}
    uint4 _uint4;
    auto _uint4_get4 = cl::get<5>(_uint4);//expected-error@__ocl_vector_utility.h:* {{vector component access exceeds type}}
                //expected-note@-1 {{in instantiation of}}
                //expected-note@__ocl_vector_utility.h:* {{in instantiation of}}
    uint8 _uint8;
    auto _uint8_get8 = cl::get<9>(_uint8);//expected-error@__ocl_vector_utility.h:* {{vector component access exceeds type}}
                //expected-note@-1 {{in instantiation of}}
                //expected-note@__ocl_vector_utility.h:* {{in instantiation of}}
    uint16 _uint16;
    auto _uint16_get16 = cl::get<17>(_uint16);//expected-error@__ocl_vector_utility.h:* {{implicit instantiation of undefined template}}
                //expected-note@-1 {{in instantiation of}}
                //expected-note@__ocl_vector_utility.h:* {{template is declared here}}
#ifdef cl_khr_fp16
    half2 _half2;
    auto _half2_get2 = cl::get<3>(_half2);//expected-error@__ocl_vector_utility.h:* {{vector component access exceeds type}}
                //expected-note@-1 {{in instantiation of}}
                //expected-note@__ocl_vector_utility.h:* {{in instantiation of}}
#endif
#ifdef cl_khr_fp16
    half3 _half3;
    auto _half3_get3 = cl::get<4>(_half3);//expected-error@__ocl_vector_utility.h:* {{vector component access exceeds type}}
                //expected-note@-1 {{in instantiation of}}
                //expected-note@__ocl_vector_utility.h:* {{in instantiation of}}
#endif
#ifdef cl_khr_fp16
    half4 _half4;
    auto _half4_get4 = cl::get<5>(_half4);//expected-error@__ocl_vector_utility.h:* {{vector component access exceeds type}}
                //expected-note@-1 {{in instantiation of}}
                //expected-note@__ocl_vector_utility.h:* {{in instantiation of}}
#endif
#ifdef cl_khr_fp16
    half8 _half8;
    auto _half8_get8 = cl::get<9>(_half8);//expected-error@__ocl_vector_utility.h:* {{vector component access exceeds type}}
                //expected-note@-1 {{in instantiation of}}
                //expected-note@__ocl_vector_utility.h:* {{in instantiation of}}
#endif
#ifdef cl_khr_fp16
    half16 _half16;
    auto _half16_get16 = cl::get<17>(_half16);//expected-error@__ocl_vector_utility.h:* {{implicit instantiation of undefined template}}
                //expected-note@-1 {{in instantiation of}}
                //expected-note@__ocl_vector_utility.h:* {{template is declared here}}
#endif
    float2 _float2;
    auto _float2_get2 = cl::get<3>(_float2);//expected-error@__ocl_vector_utility.h:* {{vector component access exceeds type}}
                //expected-note@-1 {{in instantiation of}}
                //expected-note@__ocl_vector_utility.h:* {{in instantiation of}}
    float3 _float3;
    auto _float3_get3 = cl::get<4>(_float3);//expected-error@__ocl_vector_utility.h:* {{vector component access exceeds type}}
                //expected-note@-1 {{in instantiation of}}
                //expected-note@__ocl_vector_utility.h:* {{in instantiation of}}
    float4 _float4;
    auto _float4_get4 = cl::get<5>(_float4);//expected-error@__ocl_vector_utility.h:* {{vector component access exceeds type}}
                //expected-note@-1 {{in instantiation of}}
                //expected-note@__ocl_vector_utility.h:* {{in instantiation of}}
    float8 _float8;
    auto _float8_get8 = cl::get<9>(_float8);//expected-error@__ocl_vector_utility.h:* {{vector component access exceeds type}}
                //expected-note@-1 {{in instantiation of}}
                //expected-note@__ocl_vector_utility.h:* {{in instantiation of}}
    float16 _float16;
    auto _float16_get16 = cl::get<17>(_float16);//expected-error@__ocl_vector_utility.h:* {{implicit instantiation of undefined template}}
                //expected-note@-1 {{in instantiation of}}
                //expected-note@__ocl_vector_utility.h:* {{template is declared here}}
#ifdef cl_khr_fp64
    double2 _double2;
    auto _double2_get2 = cl::get<3>(_double2);//expected-error@__ocl_vector_utility.h:* {{vector component access exceeds type}}
                //expected-note@-1 {{in instantiation of}}
                //expected-note@__ocl_vector_utility.h:* {{in instantiation of}}
#endif
#ifdef cl_khr_fp64
    double3 _double3;
    auto _double3_get3 = cl::get<4>(_double3);//expected-error@__ocl_vector_utility.h:* {{vector component access exceeds type}}
                //expected-note@-1 {{in instantiation of}}
                //expected-note@__ocl_vector_utility.h:* {{in instantiation of}}
#endif
#ifdef cl_khr_fp64
    double4 _double4;
    auto _double4_get4 = cl::get<5>(_double4);//expected-error@__ocl_vector_utility.h:* {{vector component access exceeds type}}
                //expected-note@-1 {{in instantiation of}}
                //expected-note@__ocl_vector_utility.h:* {{in instantiation of}}
#endif
#ifdef cl_khr_fp64
    double8 _double8;
    auto _double8_get8 = cl::get<9>(_double8);//expected-error@__ocl_vector_utility.h:* {{vector component access exceeds type}}
                //expected-note@-1 {{in instantiation of}}
                //expected-note@__ocl_vector_utility.h:* {{in instantiation of}}
#endif
#ifdef cl_khr_fp64
    double16 _double16;
    auto _double16_get16 = cl::get<17>(_double16);//expected-error@__ocl_vector_utility.h:* {{implicit instantiation of undefined template}}
                //expected-note@-1 {{in instantiation of}}
                //expected-note@__ocl_vector_utility.h:* {{template is declared here}}
#endif
    bool2 _bool2;
    auto _bool2_get2 = cl::get<3>(_bool2);//expected-error@__ocl_vector_utility.h:* {{vector component access exceeds type}}
                //expected-note@-1 {{in instantiation of}}
                //expected-note@__ocl_vector_utility.h:* {{in instantiation of}}
    bool3 _bool3;
    auto _bool3_get3 = cl::get<4>(_bool3);//expected-error@__ocl_vector_utility.h:* {{vector component access exceeds type}}
                //expected-note@-1 {{in instantiation of}}
                //expected-note@__ocl_vector_utility.h:* {{in instantiation of}}
    bool4 _bool4;
    auto _bool4_get4 = cl::get<5>(_bool4);//expected-error@__ocl_vector_utility.h:* {{vector component access exceeds type}}
                //expected-note@-1 {{in instantiation of}}
                //expected-note@__ocl_vector_utility.h:* {{in instantiation of}}
    bool8 _bool8;
    auto _bool8_get8 = cl::get<9>(_bool8);//expected-error@__ocl_vector_utility.h:* {{vector component access exceeds type}}
                //expected-note@-1 {{in instantiation of}}
                //expected-note@__ocl_vector_utility.h:* {{in instantiation of}}
    bool16 _bool16;
    auto _bool16_get16 = cl::get<17>(_bool16);//expected-error@__ocl_vector_utility.h:* {{implicit instantiation of undefined template}}
                //expected-note@-1 {{in instantiation of}}
                //expected-note@__ocl_vector_utility.h:* {{template is declared here}}
}