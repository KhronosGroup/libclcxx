// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable -Dcl_khr_gl_msaa_sharing -Dcl_khr_gl_depth_images -Dcl_khr_mipmap_image -Dcl_khr_mipmap_image_writes -O0 -emit-llvm -o -
// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable -Dcl_khr_gl_msaa_sharing -Dcl_khr_gl_depth_images -Dcl_khr_mipmap_image -Dcl_khr_mipmap_image_writes -O3 -emit-llvm -o -
// RUN: %clang_cc1 %s -triple spir64-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable -Dcl_khr_gl_msaa_sharing -Dcl_khr_gl_depth_images -Dcl_khr_mipmap_image -Dcl_khr_mipmap_image_writes -O0 -emit-llvm -o -
// RUN: %clang_cc1 %s -triple spir64-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable -Dcl_khr_gl_msaa_sharing -Dcl_khr_gl_depth_images -Dcl_khr_mipmap_image -Dcl_khr_mipmap_image_writes -O3 -emit-llvm -o -
// expected-no-diagnostics
#include <opencl_image>

using namespace cl;

kernel void worker(sampler s, image1d<int4, image_access::sample> _1d_s_int4, image1d_buffer<int4, image_access::sample> _1db_s_int4,
    image1d_array<int4, image_access::sample> _1d_a_s_int4, image2d<int4, image_access::sample> _2d_s_int4,
    image2d_array<int4, image_access::sample> _2d_a_s_int4, image3d<int4, image_access::sample> _3d_s_int4,
    image1d<uint4, image_access::sample> _1d_s_uint4, image1d_buffer<uint4, image_access::sample> _1db_s_uint4,
    image1d_array<uint4, image_access::sample> _1d_a_s_uint4, image2d<uint4, image_access::sample> _2d_s_uint4,
    image2d_array<uint4, image_access::sample> _2d_a_s_uint4, image3d<uint4, image_access::sample> _3d_s_uint4,
    image1d<float4, image_access::sample> _1d_s_float4, image1d_buffer<float4, image_access::sample> _1db_s_float4,
    image1d_array<float4, image_access::sample> _1d_a_s_float4, image2d<float4, image_access::sample> _2d_s_float4,
    image2d_array<float4, image_access::sample> _2d_a_s_float4, image3d<float4, image_access::sample> _3d_s_float4,
    image1d<half4, image_access::sample> _1d_s_half4, image1d_buffer<half4, image_access::sample> _1db_s_half4,
    image1d_array<half4, image_access::sample> _1d_a_s_half4, image2d<half4, image_access::sample> _2d_s_half4,
    image2d_array<half4, image_access::sample> _2d_a_s_half4, image3d<half4, image_access::sample> _3d_s_half4,
    image2d_depth<float, image_access::sample> _2d_d_s_float, image2d_array_depth<float, image_access::sample> _2d_a_d_s_float,
    image2d_depth<half, image_access::sample> _2d_d_s_half, image2d_array_depth<half, image_access::sample> _2d_a_d_s_half)
{
    int4 _ret1_1d_s_int4 = _1d_s_int4.sample(s, int{ 0 });
    int4 _ret2_1d_s_int4 = _1d_s_int4.sample(s, float{ 0 });

#ifdef cl_khr_mipmap_image
    int4 _ret3_1d_s_int4 = _1d_s_int4.sample(s, float{ 0 }, float{ 0 });
#endif
    int4 _ret1_1db_s_int4 = _1db_s_int4.sample(s, int{ 0 });
    int4 _ret2_1db_s_int4 = _1db_s_int4.sample(s, float{ 0 });

#ifdef cl_khr_mipmap_image
    int4 _ret3_1db_s_int4 = _1db_s_int4.sample(s, float{ 0 }, float{ 0 });
#endif
    int4 _ret1_1d_a_s_int4 = _1d_a_s_int4.sample(s, int2{ 0, 0 });
    int4 _ret2_1d_a_s_int4 = _1d_a_s_int4.sample(s, float2{ 0, 0 });

#ifdef cl_khr_mipmap_image
    int4 _ret3_1d_a_s_int4 = _1d_a_s_int4.sample(s, float2{ 0, 0 }, float{ 0 });
#endif
    int4 _ret1_2d_s_int4 = _2d_s_int4.sample(s, int2{ 0, 0 });
    int4 _ret2_2d_s_int4 = _2d_s_int4.sample(s, float2{ 0, 0 });

#ifdef cl_khr_mipmap_image
    int4 _ret3_2d_s_int4 = _2d_s_int4.sample(s, float2{ 0, 0 }, float{ 0 });
#endif

#ifdef cl_khr_mipmap_image
    int4 _ret4_2d_s_int4 = _2d_s_int4.sample(s, float2{ 0, 0 }, float2{ 0, 0 }, float2{ 0, 0 });
#endif
    int4 _ret1_2d_a_s_int4 = _2d_a_s_int4.sample(s, int3{ 0, 0, 0 });
    int4 _ret2_2d_a_s_int4 = _2d_a_s_int4.sample(s, float3{ 0, 0, 0 });

#ifdef cl_khr_mipmap_image
    int4 _ret3_2d_a_s_int4 = _2d_a_s_int4.sample(s, float3{ 0, 0, 0 }, float{ 0 });
#endif

#ifdef cl_khr_mipmap_image
    int4 _ret4_2d_a_s_int4 = _2d_a_s_int4.sample(s, float3{ 0, 0, 0 }, float2{ 0, 0 }, float2{ 0, 0 });
#endif
    int4 _ret1_3d_s_int4 = _3d_s_int4.sample(s, int3{ 0, 0, 0 });
    int4 _ret2_3d_s_int4 = _3d_s_int4.sample(s, float3{ 0, 0, 0 });

#ifdef cl_khr_mipmap_image
    int4 _ret3_3d_s_int4 = _3d_s_int4.sample(s, float3{ 0, 0, 0 }, float{ 0 });
#endif

#ifdef cl_khr_mipmap_image
    int4 _ret4_3d_s_int4 = _3d_s_int4.sample(s, float3{ 0, 0, 0 }, float3{ 0, 0, 0 }, float3{ 0, 0, 0 });
#endif
    uint4 _ret1_1d_s_uint4 = _1d_s_uint4.sample(s, int{ 0 });
    uint4 _ret2_1d_s_uint4 = _1d_s_uint4.sample(s, float{ 0 });

#ifdef cl_khr_mipmap_image
    uint4 _ret3_1d_s_uint4 = _1d_s_uint4.sample(s, float{ 0 }, float{ 0 });
#endif
    uint4 _ret1_1db_s_uint4 = _1db_s_uint4.sample(s, int{ 0 });
    uint4 _ret2_1db_s_uint4 = _1db_s_uint4.sample(s, float{ 0 });

#ifdef cl_khr_mipmap_image
    uint4 _ret3_1db_s_uint4 = _1db_s_uint4.sample(s, float{ 0 }, float{ 0 });
#endif
    uint4 _ret1_1d_a_s_uint4 = _1d_a_s_uint4.sample(s, int2{ 0, 0 });
    uint4 _ret2_1d_a_s_uint4 = _1d_a_s_uint4.sample(s, float2{ 0, 0 });

#ifdef cl_khr_mipmap_image
    uint4 _ret3_1d_a_s_uint4 = _1d_a_s_uint4.sample(s, float2{ 0, 0 }, float{ 0 });
#endif
    uint4 _ret1_2d_s_uint4 = _2d_s_uint4.sample(s, int2{ 0, 0 });
    uint4 _ret2_2d_s_uint4 = _2d_s_uint4.sample(s, float2{ 0, 0 });

#ifdef cl_khr_mipmap_image
    uint4 _ret3_2d_s_uint4 = _2d_s_uint4.sample(s, float2{ 0, 0 }, float{ 0 });
#endif

#ifdef cl_khr_mipmap_image
    uint4 _ret4_2d_s_uint4 = _2d_s_uint4.sample(s, float2{ 0, 0 }, float2{ 0, 0 }, float2{ 0, 0 });
#endif
    uint4 _ret1_2d_a_s_uint4 = _2d_a_s_uint4.sample(s, int3{ 0, 0, 0 });
    uint4 _ret2_2d_a_s_uint4 = _2d_a_s_uint4.sample(s, float3{ 0, 0, 0 });

#ifdef cl_khr_mipmap_image
    uint4 _ret3_2d_a_s_uint4 = _2d_a_s_uint4.sample(s, float3{ 0, 0, 0 }, float{ 0 });
#endif

#ifdef cl_khr_mipmap_image
    uint4 _ret4_2d_a_s_uint4 = _2d_a_s_uint4.sample(s, float3{ 0, 0, 0 }, float2{ 0, 0 }, float2{ 0, 0 });
#endif
    uint4 _ret1_3d_s_uint4 = _3d_s_uint4.sample(s, int3{ 0, 0, 0 });
    uint4 _ret2_3d_s_uint4 = _3d_s_uint4.sample(s, float3{ 0, 0, 0 });

#ifdef cl_khr_mipmap_image
    uint4 _ret3_3d_s_uint4 = _3d_s_uint4.sample(s, float3{ 0, 0, 0 }, float{ 0 });
#endif

#ifdef cl_khr_mipmap_image
    uint4 _ret4_3d_s_uint4 = _3d_s_uint4.sample(s, float3{ 0, 0, 0 }, float3{ 0, 0, 0 }, float3{ 0, 0, 0 });
#endif
    float4 _ret1_1d_s_float4 = _1d_s_float4.sample(s, int{ 0 });
    float4 _ret2_1d_s_float4 = _1d_s_float4.sample(s, float{ 0 });

#ifdef cl_khr_mipmap_image
    float4 _ret3_1d_s_float4 = _1d_s_float4.sample(s, float{ 0 }, float{ 0 });
#endif
    float4 _ret1_1db_s_float4 = _1db_s_float4.sample(s, int{ 0 });
    float4 _ret2_1db_s_float4 = _1db_s_float4.sample(s, float{ 0 });

#ifdef cl_khr_mipmap_image
    float4 _ret3_1db_s_float4 = _1db_s_float4.sample(s, float{ 0 }, float{ 0 });
#endif
    float4 _ret1_1d_a_s_float4 = _1d_a_s_float4.sample(s, int2{ 0, 0 });
    float4 _ret2_1d_a_s_float4 = _1d_a_s_float4.sample(s, float2{ 0, 0 });

#ifdef cl_khr_mipmap_image
    float4 _ret3_1d_a_s_float4 = _1d_a_s_float4.sample(s, float2{ 0, 0 }, float{ 0 });
#endif
    float4 _ret1_2d_s_float4 = _2d_s_float4.sample(s, int2{ 0, 0 });
    float4 _ret2_2d_s_float4 = _2d_s_float4.sample(s, float2{ 0, 0 });

#ifdef cl_khr_mipmap_image
    float4 _ret3_2d_s_float4 = _2d_s_float4.sample(s, float2{ 0, 0 }, float{ 0 });
#endif

#ifdef cl_khr_mipmap_image
    float4 _ret4_2d_s_float4 = _2d_s_float4.sample(s, float2{ 0, 0 }, float2{ 0, 0 }, float2{ 0, 0 });
#endif
    float4 _ret1_2d_a_s_float4 = _2d_a_s_float4.sample(s, int3{ 0, 0, 0 });
    float4 _ret2_2d_a_s_float4 = _2d_a_s_float4.sample(s, float3{ 0, 0, 0 });

#ifdef cl_khr_mipmap_image
    float4 _ret3_2d_a_s_float4 = _2d_a_s_float4.sample(s, float3{ 0, 0, 0 }, float{ 0 });
#endif

#ifdef cl_khr_mipmap_image
    float4 _ret4_2d_a_s_float4 = _2d_a_s_float4.sample(s, float3{ 0, 0, 0 }, float2{ 0, 0 }, float2{ 0, 0 });
#endif
    float4 _ret1_3d_s_float4 = _3d_s_float4.sample(s, int3{ 0, 0, 0 });
    float4 _ret2_3d_s_float4 = _3d_s_float4.sample(s, float3{ 0, 0, 0 });

#ifdef cl_khr_mipmap_image
    float4 _ret3_3d_s_float4 = _3d_s_float4.sample(s, float3{ 0, 0, 0 }, float{ 0 });
#endif

#ifdef cl_khr_mipmap_image
    float4 _ret4_3d_s_float4 = _3d_s_float4.sample(s, float3{ 0, 0, 0 }, float3{ 0, 0, 0 }, float3{ 0, 0, 0 });
#endif
    half4 _ret1_1d_s_half4 = _1d_s_half4.sample(s, int{ 0 });
    half4 _ret2_1d_s_half4 = _1d_s_half4.sample(s, float{ 0 });

#ifdef cl_khr_mipmap_image
    half4 _ret3_1d_s_half4 = _1d_s_half4.sample(s, float{ 0 }, float{ 0 });
#endif
    half4 _ret1_1db_s_half4 = _1db_s_half4.sample(s, int{ 0 });
    half4 _ret2_1db_s_half4 = _1db_s_half4.sample(s, float{ 0 });

#ifdef cl_khr_mipmap_image
    half4 _ret3_1db_s_half4 = _1db_s_half4.sample(s, float{ 0 }, float{ 0 });
#endif
    half4 _ret1_1d_a_s_half4 = _1d_a_s_half4.sample(s, int2{ 0, 0 });
    half4 _ret2_1d_a_s_half4 = _1d_a_s_half4.sample(s, float2{ 0, 0 });

#ifdef cl_khr_mipmap_image
    half4 _ret3_1d_a_s_half4 = _1d_a_s_half4.sample(s, float2{ 0, 0 }, float{ 0 });
#endif
    half4 _ret1_2d_s_half4 = _2d_s_half4.sample(s, int2{ 0, 0 });
    half4 _ret2_2d_s_half4 = _2d_s_half4.sample(s, float2{ 0, 0 });

#ifdef cl_khr_mipmap_image
    half4 _ret3_2d_s_half4 = _2d_s_half4.sample(s, float2{ 0, 0 }, float{ 0 });
#endif

#ifdef cl_khr_mipmap_image
    half4 _ret4_2d_s_half4 = _2d_s_half4.sample(s, float2{ 0, 0 }, float2{ 0, 0 }, float2{ 0, 0 });
#endif
    half4 _ret1_2d_a_s_half4 = _2d_a_s_half4.sample(s, int3{ 0, 0, 0 });
    half4 _ret2_2d_a_s_half4 = _2d_a_s_half4.sample(s, float3{ 0, 0, 0 });

#ifdef cl_khr_mipmap_image
    half4 _ret3_2d_a_s_half4 = _2d_a_s_half4.sample(s, float3{ 0, 0, 0 }, float{ 0 });
#endif

#ifdef cl_khr_mipmap_image
    half4 _ret4_2d_a_s_half4 = _2d_a_s_half4.sample(s, float3{ 0, 0, 0 }, float2{ 0, 0 }, float2{ 0, 0 });
#endif
    half4 _ret1_3d_s_half4 = _3d_s_half4.sample(s, int3{ 0, 0, 0 });
    half4 _ret2_3d_s_half4 = _3d_s_half4.sample(s, float3{ 0, 0, 0 });

#ifdef cl_khr_mipmap_image
    half4 _ret3_3d_s_half4 = _3d_s_half4.sample(s, float3{ 0, 0, 0 }, float{ 0 });
#endif

#ifdef cl_khr_mipmap_image
    half4 _ret4_3d_s_half4 = _3d_s_half4.sample(s, float3{ 0, 0, 0 }, float3{ 0, 0, 0 }, float3{ 0, 0, 0 });
#endif
    float _ret1_2d_d_s_float = _2d_d_s_float.sample(s, int2{ 0, 0 });
    float _ret2_2d_d_s_float = _2d_d_s_float.sample(s, float2{ 0, 0 });

#ifdef cl_khr_mipmap_image
    float _ret3_2d_d_s_float = _2d_d_s_float.sample(s, float2{ 0, 0 }, float{ 0 });
#endif

#ifdef cl_khr_mipmap_image
    float _ret4_2d_d_s_float = _2d_d_s_float.sample(s, float2{ 0, 0 }, float2{ 0, 0 }, float2{ 0, 0 });
#endif
    float _ret1_2d_a_d_s_float = _2d_a_d_s_float.sample(s, int3{ 0, 0, 0 });
    float _ret2_2d_a_d_s_float = _2d_a_d_s_float.sample(s, float3{ 0, 0, 0 });

#ifdef cl_khr_mipmap_image
    float _ret3_2d_a_d_s_float = _2d_a_d_s_float.sample(s, float3{ 0, 0, 0 }, float{ 0 });
#endif

#ifdef cl_khr_mipmap_image
    float _ret4_2d_a_d_s_float = _2d_a_d_s_float.sample(s, float3{ 0, 0, 0 }, float2{ 0, 0 }, float2{ 0, 0 });
#endif
    half _ret1_2d_d_s_half = _2d_d_s_half.sample(s, int2{ 0, 0 });
    half _ret2_2d_d_s_half = _2d_d_s_half.sample(s, float2{ 0, 0 });

#ifdef cl_khr_mipmap_image
    half _ret3_2d_d_s_half = _2d_d_s_half.sample(s, float2{ 0, 0 }, float{ 0 });
#endif

#ifdef cl_khr_mipmap_image
    half _ret4_2d_d_s_half = _2d_d_s_half.sample(s, float2{ 0, 0 }, float2{ 0, 0 }, float2{ 0, 0 });
#endif
    half _ret1_2d_a_d_s_half = _2d_a_d_s_half.sample(s, int3{ 0, 0, 0 });
    half _ret2_2d_a_d_s_half = _2d_a_d_s_half.sample(s, float3{ 0, 0, 0 });

#ifdef cl_khr_mipmap_image
    half _ret3_2d_a_d_s_half = _2d_a_d_s_half.sample(s, float3{ 0, 0, 0 }, float{ 0 });
#endif

#ifdef cl_khr_mipmap_image
    half _ret4_2d_a_d_s_half = _2d_a_d_s_half.sample(s, float3{ 0, 0, 0 }, float2{ 0, 0 }, float2{ 0, 0 });
#endif
}