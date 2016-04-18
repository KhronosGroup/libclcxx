// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable -Dcl_khr_gl_msaa_sharing -Dcl_khr_gl_depth_images -Dcl_khr_mipmap_image -Dcl_khr_mipmap_image_writes -O0 -emit-llvm -o -
// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable -Dcl_khr_gl_msaa_sharing -Dcl_khr_gl_depth_images -Dcl_khr_mipmap_image -Dcl_khr_mipmap_image_writes -O3 -emit-llvm -o -
// RUN: %clang_cc1 %s -triple spir64-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable -Dcl_khr_gl_msaa_sharing -Dcl_khr_gl_depth_images -Dcl_khr_mipmap_image -Dcl_khr_mipmap_image_writes -O0 -emit-llvm -o -
// RUN: %clang_cc1 %s -triple spir64-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable -Dcl_khr_gl_msaa_sharing -Dcl_khr_gl_depth_images -Dcl_khr_mipmap_image -Dcl_khr_mipmap_image_writes -O3 -emit-llvm -o -
// expected-no-diagnostics
#include <opencl_image>

using namespace cl;

kernel void worker(image1d<int4, image_access::read> _1d_r_int4, image1d_buffer<int4, image_access::read> _1db_r_int4,
    image1d_array<int4, image_access::read> _1d_a_r_int4, image2d<int4, image_access::read> _2d_r_int4,
    image2d_array<int4, image_access::read> _2d_a_r_int4, image3d<int4, image_access::read> _3d_r_int4,
    image2d_ms<int4, image_access::read> _2d_ms_r_int4, image2d_array_ms<int4, image_access::read> _2d_ms_a_r_int4,
    image1d<int4, image_access::write> _1d_w_int4, image1d_buffer<int4, image_access::write> _1db_w_int4,
    image1d_array<int4, image_access::write> _1d_a_w_int4, image2d<int4, image_access::write> _2d_w_int4,
    image2d_array<int4, image_access::write> _2d_a_w_int4, image3d<int4, image_access::write> _3d_w_int4,
    image2d_ms<int4, image_access::write> _2d_ms_w_int4, image2d_array_ms<int4, image_access::write> _2d_ms_a_w_int4,
    image1d<int4, image_access::read_write> _1d_rw_int4, image1d_buffer<int4, image_access::read_write> _1db_rw_int4,
    image1d_array<int4, image_access::read_write> _1d_a_rw_int4, image2d<int4, image_access::read_write> _2d_rw_int4,
    image2d_array<int4, image_access::read_write> _2d_a_rw_int4, image3d<int4, image_access::read_write> _3d_rw_int4,
    image2d_ms<int4, image_access::read_write> _2d_ms_rw_int4, image2d_array_ms<int4, image_access::read_write> _2d_ms_a_rw_int4,
    image1d<int4, image_access::sample> _1d_s_int4, image1d_buffer<int4, image_access::sample> _1db_s_int4,
    image1d_array<int4, image_access::sample> _1d_a_s_int4, image2d<int4, image_access::sample> _2d_s_int4,
    image2d_array<int4, image_access::sample> _2d_a_s_int4, image3d<int4, image_access::sample> _3d_s_int4,
    image1d<uint4, image_access::read> _1d_r_uint4, image1d_buffer<uint4, image_access::read> _1db_r_uint4,
    image1d_array<uint4, image_access::read> _1d_a_r_uint4, image2d<uint4, image_access::read> _2d_r_uint4,
    image2d_array<uint4, image_access::read> _2d_a_r_uint4, image3d<uint4, image_access::read> _3d_r_uint4,
    image2d_ms<uint4, image_access::read> _2d_ms_r_uint4, image2d_array_ms<uint4, image_access::read> _2d_ms_a_r_uint4,
    image1d<uint4, image_access::write> _1d_w_uint4, image1d_buffer<uint4, image_access::write> _1db_w_uint4,
    image1d_array<uint4, image_access::write> _1d_a_w_uint4, image2d<uint4, image_access::write> _2d_w_uint4,
    image2d_array<uint4, image_access::write> _2d_a_w_uint4, image3d<uint4, image_access::write> _3d_w_uint4,
    image2d_ms<uint4, image_access::write> _2d_ms_w_uint4, image2d_array_ms<uint4, image_access::write> _2d_ms_a_w_uint4,
    image1d<uint4, image_access::read_write> _1d_rw_uint4, image1d_buffer<uint4, image_access::read_write> _1db_rw_uint4,
    image1d_array<uint4, image_access::read_write> _1d_a_rw_uint4, image2d<uint4, image_access::read_write> _2d_rw_uint4,
    image2d_array<uint4, image_access::read_write> _2d_a_rw_uint4, image3d<uint4, image_access::read_write> _3d_rw_uint4,
    image2d_ms<uint4, image_access::read_write> _2d_ms_rw_uint4, image2d_array_ms<uint4, image_access::read_write> _2d_ms_a_rw_uint4,
    image1d<uint4, image_access::sample> _1d_s_uint4, image1d_buffer<uint4, image_access::sample> _1db_s_uint4,
    image1d_array<uint4, image_access::sample> _1d_a_s_uint4, image2d<uint4, image_access::sample> _2d_s_uint4,
    image2d_array<uint4, image_access::sample> _2d_a_s_uint4, image3d<uint4, image_access::sample> _3d_s_uint4,
    image1d<float4, image_access::read> _1d_r_float4, image1d_buffer<float4, image_access::read> _1db_r_float4,
    image1d_array<float4, image_access::read> _1d_a_r_float4, image2d<float4, image_access::read> _2d_r_float4,
    image2d_array<float4, image_access::read> _2d_a_r_float4, image3d<float4, image_access::read> _3d_r_float4,
    image2d_ms<float4, image_access::read> _2d_ms_r_float4, image2d_array_ms<float4, image_access::read> _2d_ms_a_r_float4,
    image1d<float4, image_access::write> _1d_w_float4, image1d_buffer<float4, image_access::write> _1db_w_float4,
    image1d_array<float4, image_access::write> _1d_a_w_float4, image2d<float4, image_access::write> _2d_w_float4,
    image2d_array<float4, image_access::write> _2d_a_w_float4, image3d<float4, image_access::write> _3d_w_float4,
    image2d_ms<float4, image_access::write> _2d_ms_w_float4, image2d_array_ms<float4, image_access::write> _2d_ms_a_w_float4,
    image1d<float4, image_access::read_write> _1d_rw_float4, image1d_buffer<float4, image_access::read_write> _1db_rw_float4,
    image1d_array<float4, image_access::read_write> _1d_a_rw_float4, image2d<float4, image_access::read_write> _2d_rw_float4,
    image2d_array<float4, image_access::read_write> _2d_a_rw_float4, image3d<float4, image_access::read_write> _3d_rw_float4,
    image2d_ms<float4, image_access::read_write> _2d_ms_rw_float4, image2d_array_ms<float4, image_access::read_write> _2d_ms_a_rw_float4,
    image1d<float4, image_access::sample> _1d_s_float4, image1d_buffer<float4, image_access::sample> _1db_s_float4,
    image1d_array<float4, image_access::sample> _1d_a_s_float4, image2d<float4, image_access::sample> _2d_s_float4,
    image2d_array<float4, image_access::sample> _2d_a_s_float4, image3d<float4, image_access::sample> _3d_s_float4,
    image1d<half4, image_access::read> _1d_r_half4, image1d_buffer<half4, image_access::read> _1db_r_half4,
    image1d_array<half4, image_access::read> _1d_a_r_half4, image2d<half4, image_access::read> _2d_r_half4,
    image2d_array<half4, image_access::read> _2d_a_r_half4, image3d<half4, image_access::read> _3d_r_half4,
    image1d<half4, image_access::write> _1d_w_half4, image1d_buffer<half4, image_access::write> _1db_w_half4,
    image1d_array<half4, image_access::write> _1d_a_w_half4, image2d<half4, image_access::write> _2d_w_half4,
    image2d_array<half4, image_access::write> _2d_a_w_half4, image3d<half4, image_access::write> _3d_w_half4,
    image1d<half4, image_access::read_write> _1d_rw_half4, image1d_buffer<half4, image_access::read_write> _1db_rw_half4,
    image1d_array<half4, image_access::read_write> _1d_a_rw_half4, image2d<half4, image_access::read_write> _2d_rw_half4,
    image2d_array<half4, image_access::read_write> _2d_a_rw_half4, image3d<half4, image_access::read_write> _3d_rw_half4,
    image1d<half4, image_access::sample> _1d_s_half4, image1d_buffer<half4, image_access::sample> _1db_s_half4,
    image1d_array<half4, image_access::sample> _1d_a_s_half4, image2d<half4, image_access::sample> _2d_s_half4,
    image2d_array<half4, image_access::sample> _2d_a_s_half4, image3d<half4, image_access::sample> _3d_s_half4,
    image2d_depth<float, image_access::read> _2d_d_r_float, image2d_array_depth<float, image_access::read> _2d_a_d_r_float,
    image2d_depth_ms<float, image_access::read> _2d_ms_d_r_float, image2d_array_depth_ms<float, image_access::read> _2d_ms_a_d_r_float,
    image2d_depth<float, image_access::write> _2d_d_w_float, image2d_array_depth<float, image_access::write> _2d_a_d_w_float,
    image2d_depth_ms<float, image_access::write> _2d_ms_d_w_float, image2d_array_depth_ms<float, image_access::write> _2d_ms_a_d_w_float,
    image2d_depth<float, image_access::read_write> _2d_d_rw_float, image2d_array_depth<float, image_access::read_write> _2d_a_d_rw_float,
    image2d_depth_ms<float, image_access::read_write> _2d_ms_d_rw_float, image2d_array_depth_ms<float, image_access::read_write> _2d_ms_a_d_rw_float,
    image2d_depth<float, image_access::sample> _2d_d_s_float, image2d_array_depth<float, image_access::sample> _2d_a_d_s_float,
    image2d_depth<half, image_access::read> _2d_d_r_half, image2d_array_depth<half, image_access::read> _2d_a_d_r_half,
    image2d_depth<half, image_access::write> _2d_d_w_half, image2d_array_depth<half, image_access::write> _2d_a_d_w_half,
    image2d_depth<half, image_access::read_write> _2d_d_rw_half, image2d_array_depth<half, image_access::read_write> _2d_a_d_rw_half,
    image2d_depth<half, image_access::sample> _2d_d_s_half, image2d_array_depth<half, image_access::sample> _2d_a_d_s_half)
{
    image1d<int4, image_access::read>::pixel _ret_p1_1d_r_int4 = _1d_r_int4[int{ 0 }];
    image1d_buffer<int4, image_access::read>::pixel _ret_p1_1db_r_int4 = _1db_r_int4[int{ 0 }];
    image1d_array<int4, image_access::read>::pixel _ret_p1_1d_a_r_int4 = _1d_a_r_int4[int2{ 0, 0 }];
    image2d<int4, image_access::read>::pixel _ret_p1_2d_r_int4 = _2d_r_int4[int2{ 0, 0 }];
    image2d_array<int4, image_access::read>::pixel _ret_p1_2d_a_r_int4 = _2d_a_r_int4[int3{ 0, 0, 0 }];
    image3d<int4, image_access::read>::pixel _ret_p1_3d_r_int4 = _3d_r_int4[int3{ 0, 0, 0 }];
    image2d_ms<int4, image_access::read>::pixel _ret_p1_2d_ms_r_int4 = _2d_ms_r_int4[int2{ 0, 0 }];
    image2d_array_ms<int4, image_access::read>::pixel _ret_p1_2d_ms_a_r_int4 = _2d_ms_a_r_int4[int3{ 0, 0, 0 }];
    image1d<int4, image_access::write>::pixel _ret_p1_1d_w_int4 = _1d_w_int4[int{ 0 }];
    image1d<int4, image_access::write>::pixel  _pixel_2_1d_w_int4 = _1d_w_int4[int{ 0 }];
    _pixel_2_1d_w_int4 = int4{ 0, 0, 0, 0 };

    image1d_buffer<int4, image_access::write>::pixel _ret_p1_1db_w_int4 = _1db_w_int4[int{ 0 }];
    image1d_buffer<int4, image_access::write>::pixel  _pixel_2_1db_w_int4 = _1db_w_int4[int{ 0 }];
    _pixel_2_1db_w_int4 = int4{ 0, 0, 0, 0 };

    image1d_array<int4, image_access::write>::pixel _ret_p1_1d_a_w_int4 = _1d_a_w_int4[int2{ 0, 0 }];
    image1d_array<int4, image_access::write>::pixel  _pixel_2_1d_a_w_int4 = _1d_a_w_int4[int2{ 0, 0 }];
    _pixel_2_1d_a_w_int4 = int4{ 0, 0, 0, 0 };

    image2d<int4, image_access::write>::pixel _ret_p1_2d_w_int4 = _2d_w_int4[int2{ 0, 0 }];
    image2d<int4, image_access::write>::pixel  _pixel_2_2d_w_int4 = _2d_w_int4[int2{ 0, 0 }];
    _pixel_2_2d_w_int4 = int4{ 0, 0, 0, 0 };

    image2d_array<int4, image_access::write>::pixel _ret_p1_2d_a_w_int4 = _2d_a_w_int4[int3{ 0, 0, 0 }];
    image2d_array<int4, image_access::write>::pixel  _pixel_2_2d_a_w_int4 = _2d_a_w_int4[int3{ 0, 0, 0 }];
    _pixel_2_2d_a_w_int4 = int4{ 0, 0, 0, 0 };

    image3d<int4, image_access::write>::pixel _ret_p1_3d_w_int4 = _3d_w_int4[int3{ 0, 0, 0 }];
    image3d<int4, image_access::write>::pixel  _pixel_2_3d_w_int4 = _3d_w_int4[int3{ 0, 0, 0 }];
    _pixel_2_3d_w_int4 = int4{ 0, 0, 0, 0 };

    image2d_ms<int4, image_access::write>::pixel _ret_p1_2d_ms_w_int4 = _2d_ms_w_int4[int2{ 0, 0 }];
    image2d_ms<int4, image_access::write>::pixel  _pixel_2_2d_ms_w_int4 = _2d_ms_w_int4[int2{ 0, 0 }];

    image2d_array_ms<int4, image_access::write>::pixel _ret_p1_2d_ms_a_w_int4 = _2d_ms_a_w_int4[int3{ 0, 0, 0 }];
    image2d_array_ms<int4, image_access::write>::pixel  _pixel_2_2d_ms_a_w_int4 = _2d_ms_a_w_int4[int3{ 0, 0, 0 }];

    image1d<int4, image_access::read_write>::pixel _ret_p1_1d_rw_int4 = _1d_rw_int4[int{ 0 }];
    image1d<int4, image_access::read_write>::pixel  _pixel_2_1d_rw_int4 = _1d_rw_int4[int{ 0 }];
    _pixel_2_1d_rw_int4 = int4{ 0, 0, 0, 0 };
    int4 _ret_3_1d_rw_int4 =  _pixel_2_1d_rw_int4;

    image1d_buffer<int4, image_access::read_write>::pixel _ret_p1_1db_rw_int4 = _1db_rw_int4[int{ 0 }];
    image1d_buffer<int4, image_access::read_write>::pixel  _pixel_2_1db_rw_int4 = _1db_rw_int4[int{ 0 }];
    _pixel_2_1db_rw_int4 = int4{ 0, 0, 0, 0 };
    int4 _ret_3_1db_rw_int4 =  _pixel_2_1db_rw_int4;

    image1d_array<int4, image_access::read_write>::pixel _ret_p1_1d_a_rw_int4 = _1d_a_rw_int4[int2{ 0, 0 }];
    image1d_array<int4, image_access::read_write>::pixel  _pixel_2_1d_a_rw_int4 = _1d_a_rw_int4[int2{ 0, 0 }];
    _pixel_2_1d_a_rw_int4 = int4{ 0, 0, 0, 0 };
    int4 _ret_3_1d_a_rw_int4 =  _pixel_2_1d_a_rw_int4;

    image2d<int4, image_access::read_write>::pixel _ret_p1_2d_rw_int4 = _2d_rw_int4[int2{ 0, 0 }];
    image2d<int4, image_access::read_write>::pixel  _pixel_2_2d_rw_int4 = _2d_rw_int4[int2{ 0, 0 }];
    _pixel_2_2d_rw_int4 = int4{ 0, 0, 0, 0 };
    int4 _ret_3_2d_rw_int4 =  _pixel_2_2d_rw_int4;

    image2d_array<int4, image_access::read_write>::pixel _ret_p1_2d_a_rw_int4 = _2d_a_rw_int4[int3{ 0, 0, 0 }];
    image2d_array<int4, image_access::read_write>::pixel  _pixel_2_2d_a_rw_int4 = _2d_a_rw_int4[int3{ 0, 0, 0 }];
    _pixel_2_2d_a_rw_int4 = int4{ 0, 0, 0, 0 };
    int4 _ret_3_2d_a_rw_int4 =  _pixel_2_2d_a_rw_int4;

    image3d<int4, image_access::read_write>::pixel _ret_p1_3d_rw_int4 = _3d_rw_int4[int3{ 0, 0, 0 }];
    image3d<int4, image_access::read_write>::pixel  _pixel_2_3d_rw_int4 = _3d_rw_int4[int3{ 0, 0, 0 }];
    _pixel_2_3d_rw_int4 = int4{ 0, 0, 0, 0 };
    int4 _ret_3_3d_rw_int4 =  _pixel_2_3d_rw_int4;

    image2d_ms<int4, image_access::read_write>::pixel _ret_p1_2d_ms_rw_int4 = _2d_ms_rw_int4[int2{ 0, 0 }];
    image2d_ms<int4, image_access::read_write>::pixel  _pixel_2_2d_ms_rw_int4 = _2d_ms_rw_int4[int2{ 0, 0 }];

    image2d_array_ms<int4, image_access::read_write>::pixel _ret_p1_2d_ms_a_rw_int4 = _2d_ms_a_rw_int4[int3{ 0, 0, 0 }];
    image2d_array_ms<int4, image_access::read_write>::pixel  _pixel_2_2d_ms_a_rw_int4 = _2d_ms_a_rw_int4[int3{ 0, 0, 0 }];

    image1d<int4, image_access::sample>::pixel _ret_p1_1d_s_int4 = _1d_s_int4[int{ 0 }];
    image1d<int4, image_access::sample>::pixel  _pixel_2_1d_s_int4 = _1d_s_int4[int{ 0 }];

    int4 _ret_3_1d_s_int4 =  _pixel_2_1d_s_int4;


    image1d_buffer<int4, image_access::sample>::pixel _ret_p1_1db_s_int4 = _1db_s_int4[int{ 0 }];
    image1d_buffer<int4, image_access::sample>::pixel  _pixel_2_1db_s_int4 = _1db_s_int4[int{ 0 }];

    int4 _ret_3_1db_s_int4 =  _pixel_2_1db_s_int4;


    image1d_array<int4, image_access::sample>::pixel _ret_p1_1d_a_s_int4 = _1d_a_s_int4[int2{ 0, 0 }];
    image1d_array<int4, image_access::sample>::pixel  _pixel_2_1d_a_s_int4 = _1d_a_s_int4[int2{ 0, 0 }];

    int4 _ret_3_1d_a_s_int4 =  _pixel_2_1d_a_s_int4;


    image2d<int4, image_access::sample>::pixel _ret_p1_2d_s_int4 = _2d_s_int4[int2{ 0, 0 }];
    image2d<int4, image_access::sample>::pixel  _pixel_2_2d_s_int4 = _2d_s_int4[int2{ 0, 0 }];

    int4 _ret_3_2d_s_int4 =  _pixel_2_2d_s_int4;


    image2d_array<int4, image_access::sample>::pixel _ret_p1_2d_a_s_int4 = _2d_a_s_int4[int3{ 0, 0, 0 }];
    image2d_array<int4, image_access::sample>::pixel  _pixel_2_2d_a_s_int4 = _2d_a_s_int4[int3{ 0, 0, 0 }];

    int4 _ret_3_2d_a_s_int4 =  _pixel_2_2d_a_s_int4;


    image3d<int4, image_access::sample>::pixel _ret_p1_3d_s_int4 = _3d_s_int4[int3{ 0, 0, 0 }];
    image3d<int4, image_access::sample>::pixel  _pixel_2_3d_s_int4 = _3d_s_int4[int3{ 0, 0, 0 }];

    int4 _ret_3_3d_s_int4 =  _pixel_2_3d_s_int4;


    image1d<uint4, image_access::read>::pixel _ret_p1_1d_r_uint4 = _1d_r_uint4[int{ 0 }];
    image1d_buffer<uint4, image_access::read>::pixel _ret_p1_1db_r_uint4 = _1db_r_uint4[int{ 0 }];
    image1d_array<uint4, image_access::read>::pixel _ret_p1_1d_a_r_uint4 = _1d_a_r_uint4[int2{ 0, 0 }];
    image2d<uint4, image_access::read>::pixel _ret_p1_2d_r_uint4 = _2d_r_uint4[int2{ 0, 0 }];
    image2d_array<uint4, image_access::read>::pixel _ret_p1_2d_a_r_uint4 = _2d_a_r_uint4[int3{ 0, 0, 0 }];
    image3d<uint4, image_access::read>::pixel _ret_p1_3d_r_uint4 = _3d_r_uint4[int3{ 0, 0, 0 }];
    image2d_ms<uint4, image_access::read>::pixel _ret_p1_2d_ms_r_uint4 = _2d_ms_r_uint4[int2{ 0, 0 }];
    image2d_array_ms<uint4, image_access::read>::pixel _ret_p1_2d_ms_a_r_uint4 = _2d_ms_a_r_uint4[int3{ 0, 0, 0 }];
    image1d<uint4, image_access::write>::pixel _ret_p1_1d_w_uint4 = _1d_w_uint4[int{ 0 }];
    image1d<uint4, image_access::write>::pixel  _pixel_2_1d_w_uint4 = _1d_w_uint4[int{ 0 }];
    _pixel_2_1d_w_uint4 = uint4{ 0, 0, 0, 0 };

    image1d_buffer<uint4, image_access::write>::pixel _ret_p1_1db_w_uint4 = _1db_w_uint4[int{ 0 }];
    image1d_buffer<uint4, image_access::write>::pixel  _pixel_2_1db_w_uint4 = _1db_w_uint4[int{ 0 }];
    _pixel_2_1db_w_uint4 = uint4{ 0, 0, 0, 0 };

    image1d_array<uint4, image_access::write>::pixel _ret_p1_1d_a_w_uint4 = _1d_a_w_uint4[int2{ 0, 0 }];
    image1d_array<uint4, image_access::write>::pixel  _pixel_2_1d_a_w_uint4 = _1d_a_w_uint4[int2{ 0, 0 }];
    _pixel_2_1d_a_w_uint4 = uint4{ 0, 0, 0, 0 };

    image2d<uint4, image_access::write>::pixel _ret_p1_2d_w_uint4 = _2d_w_uint4[int2{ 0, 0 }];
    image2d<uint4, image_access::write>::pixel  _pixel_2_2d_w_uint4 = _2d_w_uint4[int2{ 0, 0 }];
    _pixel_2_2d_w_uint4 = uint4{ 0, 0, 0, 0 };

    image2d_array<uint4, image_access::write>::pixel _ret_p1_2d_a_w_uint4 = _2d_a_w_uint4[int3{ 0, 0, 0 }];
    image2d_array<uint4, image_access::write>::pixel  _pixel_2_2d_a_w_uint4 = _2d_a_w_uint4[int3{ 0, 0, 0 }];
    _pixel_2_2d_a_w_uint4 = uint4{ 0, 0, 0, 0 };

    image3d<uint4, image_access::write>::pixel _ret_p1_3d_w_uint4 = _3d_w_uint4[int3{ 0, 0, 0 }];
    image3d<uint4, image_access::write>::pixel  _pixel_2_3d_w_uint4 = _3d_w_uint4[int3{ 0, 0, 0 }];
    _pixel_2_3d_w_uint4 = uint4{ 0, 0, 0, 0 };

    image2d_ms<uint4, image_access::write>::pixel _ret_p1_2d_ms_w_uint4 = _2d_ms_w_uint4[int2{ 0, 0 }];
    image2d_ms<uint4, image_access::write>::pixel  _pixel_2_2d_ms_w_uint4 = _2d_ms_w_uint4[int2{ 0, 0 }];

    image2d_array_ms<uint4, image_access::write>::pixel _ret_p1_2d_ms_a_w_uint4 = _2d_ms_a_w_uint4[int3{ 0, 0, 0 }];
    image2d_array_ms<uint4, image_access::write>::pixel  _pixel_2_2d_ms_a_w_uint4 = _2d_ms_a_w_uint4[int3{ 0, 0, 0 }];

    image1d<uint4, image_access::read_write>::pixel _ret_p1_1d_rw_uint4 = _1d_rw_uint4[int{ 0 }];
    image1d<uint4, image_access::read_write>::pixel  _pixel_2_1d_rw_uint4 = _1d_rw_uint4[int{ 0 }];
    _pixel_2_1d_rw_uint4 = uint4{ 0, 0, 0, 0 };
    uint4 _ret_3_1d_rw_uint4 =  _pixel_2_1d_rw_uint4;

    image1d_buffer<uint4, image_access::read_write>::pixel _ret_p1_1db_rw_uint4 = _1db_rw_uint4[int{ 0 }];
    image1d_buffer<uint4, image_access::read_write>::pixel  _pixel_2_1db_rw_uint4 = _1db_rw_uint4[int{ 0 }];
    _pixel_2_1db_rw_uint4 = uint4{ 0, 0, 0, 0 };
    uint4 _ret_3_1db_rw_uint4 =  _pixel_2_1db_rw_uint4;

    image1d_array<uint4, image_access::read_write>::pixel _ret_p1_1d_a_rw_uint4 = _1d_a_rw_uint4[int2{ 0, 0 }];
    image1d_array<uint4, image_access::read_write>::pixel  _pixel_2_1d_a_rw_uint4 = _1d_a_rw_uint4[int2{ 0, 0 }];
    _pixel_2_1d_a_rw_uint4 = uint4{ 0, 0, 0, 0 };
    uint4 _ret_3_1d_a_rw_uint4 =  _pixel_2_1d_a_rw_uint4;

    image2d<uint4, image_access::read_write>::pixel _ret_p1_2d_rw_uint4 = _2d_rw_uint4[int2{ 0, 0 }];
    image2d<uint4, image_access::read_write>::pixel  _pixel_2_2d_rw_uint4 = _2d_rw_uint4[int2{ 0, 0 }];
    _pixel_2_2d_rw_uint4 = uint4{ 0, 0, 0, 0 };
    uint4 _ret_3_2d_rw_uint4 =  _pixel_2_2d_rw_uint4;

    image2d_array<uint4, image_access::read_write>::pixel _ret_p1_2d_a_rw_uint4 = _2d_a_rw_uint4[int3{ 0, 0, 0 }];
    image2d_array<uint4, image_access::read_write>::pixel  _pixel_2_2d_a_rw_uint4 = _2d_a_rw_uint4[int3{ 0, 0, 0 }];
    _pixel_2_2d_a_rw_uint4 = uint4{ 0, 0, 0, 0 };
    uint4 _ret_3_2d_a_rw_uint4 =  _pixel_2_2d_a_rw_uint4;

    image3d<uint4, image_access::read_write>::pixel _ret_p1_3d_rw_uint4 = _3d_rw_uint4[int3{ 0, 0, 0 }];
    image3d<uint4, image_access::read_write>::pixel  _pixel_2_3d_rw_uint4 = _3d_rw_uint4[int3{ 0, 0, 0 }];
    _pixel_2_3d_rw_uint4 = uint4{ 0, 0, 0, 0 };
    uint4 _ret_3_3d_rw_uint4 =  _pixel_2_3d_rw_uint4;

    image2d_ms<uint4, image_access::read_write>::pixel _ret_p1_2d_ms_rw_uint4 = _2d_ms_rw_uint4[int2{ 0, 0 }];
    image2d_ms<uint4, image_access::read_write>::pixel  _pixel_2_2d_ms_rw_uint4 = _2d_ms_rw_uint4[int2{ 0, 0 }];

    image2d_array_ms<uint4, image_access::read_write>::pixel _ret_p1_2d_ms_a_rw_uint4 = _2d_ms_a_rw_uint4[int3{ 0, 0, 0 }];
    image2d_array_ms<uint4, image_access::read_write>::pixel  _pixel_2_2d_ms_a_rw_uint4 = _2d_ms_a_rw_uint4[int3{ 0, 0, 0 }];

    image1d<uint4, image_access::sample>::pixel _ret_p1_1d_s_uint4 = _1d_s_uint4[int{ 0 }];
    image1d<uint4, image_access::sample>::pixel  _pixel_2_1d_s_uint4 = _1d_s_uint4[int{ 0 }];

    uint4 _ret_3_1d_s_uint4 =  _pixel_2_1d_s_uint4;


    image1d_buffer<uint4, image_access::sample>::pixel _ret_p1_1db_s_uint4 = _1db_s_uint4[int{ 0 }];
    image1d_buffer<uint4, image_access::sample>::pixel  _pixel_2_1db_s_uint4 = _1db_s_uint4[int{ 0 }];

    uint4 _ret_3_1db_s_uint4 =  _pixel_2_1db_s_uint4;


    image1d_array<uint4, image_access::sample>::pixel _ret_p1_1d_a_s_uint4 = _1d_a_s_uint4[int2{ 0, 0 }];
    image1d_array<uint4, image_access::sample>::pixel  _pixel_2_1d_a_s_uint4 = _1d_a_s_uint4[int2{ 0, 0 }];

    uint4 _ret_3_1d_a_s_uint4 =  _pixel_2_1d_a_s_uint4;


    image2d<uint4, image_access::sample>::pixel _ret_p1_2d_s_uint4 = _2d_s_uint4[int2{ 0, 0 }];
    image2d<uint4, image_access::sample>::pixel  _pixel_2_2d_s_uint4 = _2d_s_uint4[int2{ 0, 0 }];

    uint4 _ret_3_2d_s_uint4 =  _pixel_2_2d_s_uint4;


    image2d_array<uint4, image_access::sample>::pixel _ret_p1_2d_a_s_uint4 = _2d_a_s_uint4[int3{ 0, 0, 0 }];
    image2d_array<uint4, image_access::sample>::pixel  _pixel_2_2d_a_s_uint4 = _2d_a_s_uint4[int3{ 0, 0, 0 }];

    uint4 _ret_3_2d_a_s_uint4 =  _pixel_2_2d_a_s_uint4;


    image3d<uint4, image_access::sample>::pixel _ret_p1_3d_s_uint4 = _3d_s_uint4[int3{ 0, 0, 0 }];
    image3d<uint4, image_access::sample>::pixel  _pixel_2_3d_s_uint4 = _3d_s_uint4[int3{ 0, 0, 0 }];

    uint4 _ret_3_3d_s_uint4 =  _pixel_2_3d_s_uint4;


    image1d<float4, image_access::read>::pixel _ret_p1_1d_r_float4 = _1d_r_float4[int{ 0 }];
    image1d_buffer<float4, image_access::read>::pixel _ret_p1_1db_r_float4 = _1db_r_float4[int{ 0 }];
    image1d_array<float4, image_access::read>::pixel _ret_p1_1d_a_r_float4 = _1d_a_r_float4[int2{ 0, 0 }];
    image2d<float4, image_access::read>::pixel _ret_p1_2d_r_float4 = _2d_r_float4[int2{ 0, 0 }];
    image2d_array<float4, image_access::read>::pixel _ret_p1_2d_a_r_float4 = _2d_a_r_float4[int3{ 0, 0, 0 }];
    image3d<float4, image_access::read>::pixel _ret_p1_3d_r_float4 = _3d_r_float4[int3{ 0, 0, 0 }];
    image2d_ms<float4, image_access::read>::pixel _ret_p1_2d_ms_r_float4 = _2d_ms_r_float4[int2{ 0, 0 }];
    image2d_array_ms<float4, image_access::read>::pixel _ret_p1_2d_ms_a_r_float4 = _2d_ms_a_r_float4[int3{ 0, 0, 0 }];
    image1d<float4, image_access::write>::pixel _ret_p1_1d_w_float4 = _1d_w_float4[int{ 0 }];
    image1d<float4, image_access::write>::pixel  _pixel_2_1d_w_float4 = _1d_w_float4[int{ 0 }];
    _pixel_2_1d_w_float4 = float4{ 0, 0, 0, 0 };

    image1d_buffer<float4, image_access::write>::pixel _ret_p1_1db_w_float4 = _1db_w_float4[int{ 0 }];
    image1d_buffer<float4, image_access::write>::pixel  _pixel_2_1db_w_float4 = _1db_w_float4[int{ 0 }];
    _pixel_2_1db_w_float4 = float4{ 0, 0, 0, 0 };

    image1d_array<float4, image_access::write>::pixel _ret_p1_1d_a_w_float4 = _1d_a_w_float4[int2{ 0, 0 }];
    image1d_array<float4, image_access::write>::pixel  _pixel_2_1d_a_w_float4 = _1d_a_w_float4[int2{ 0, 0 }];
    _pixel_2_1d_a_w_float4 = float4{ 0, 0, 0, 0 };

    image2d<float4, image_access::write>::pixel _ret_p1_2d_w_float4 = _2d_w_float4[int2{ 0, 0 }];
    image2d<float4, image_access::write>::pixel  _pixel_2_2d_w_float4 = _2d_w_float4[int2{ 0, 0 }];
    _pixel_2_2d_w_float4 = float4{ 0, 0, 0, 0 };

    image2d_array<float4, image_access::write>::pixel _ret_p1_2d_a_w_float4 = _2d_a_w_float4[int3{ 0, 0, 0 }];
    image2d_array<float4, image_access::write>::pixel  _pixel_2_2d_a_w_float4 = _2d_a_w_float4[int3{ 0, 0, 0 }];
    _pixel_2_2d_a_w_float4 = float4{ 0, 0, 0, 0 };

    image3d<float4, image_access::write>::pixel _ret_p1_3d_w_float4 = _3d_w_float4[int3{ 0, 0, 0 }];
    image3d<float4, image_access::write>::pixel  _pixel_2_3d_w_float4 = _3d_w_float4[int3{ 0, 0, 0 }];
    _pixel_2_3d_w_float4 = float4{ 0, 0, 0, 0 };

    image2d_ms<float4, image_access::write>::pixel _ret_p1_2d_ms_w_float4 = _2d_ms_w_float4[int2{ 0, 0 }];
    image2d_ms<float4, image_access::write>::pixel  _pixel_2_2d_ms_w_float4 = _2d_ms_w_float4[int2{ 0, 0 }];

    image2d_array_ms<float4, image_access::write>::pixel _ret_p1_2d_ms_a_w_float4 = _2d_ms_a_w_float4[int3{ 0, 0, 0 }];
    image2d_array_ms<float4, image_access::write>::pixel  _pixel_2_2d_ms_a_w_float4 = _2d_ms_a_w_float4[int3{ 0, 0, 0 }];

    image1d<float4, image_access::read_write>::pixel _ret_p1_1d_rw_float4 = _1d_rw_float4[int{ 0 }];
    image1d<float4, image_access::read_write>::pixel  _pixel_2_1d_rw_float4 = _1d_rw_float4[int{ 0 }];
    _pixel_2_1d_rw_float4 = float4{ 0, 0, 0, 0 };
    float4 _ret_3_1d_rw_float4 =  _pixel_2_1d_rw_float4;

    image1d_buffer<float4, image_access::read_write>::pixel _ret_p1_1db_rw_float4 = _1db_rw_float4[int{ 0 }];
    image1d_buffer<float4, image_access::read_write>::pixel  _pixel_2_1db_rw_float4 = _1db_rw_float4[int{ 0 }];
    _pixel_2_1db_rw_float4 = float4{ 0, 0, 0, 0 };
    float4 _ret_3_1db_rw_float4 =  _pixel_2_1db_rw_float4;

    image1d_array<float4, image_access::read_write>::pixel _ret_p1_1d_a_rw_float4 = _1d_a_rw_float4[int2{ 0, 0 }];
    image1d_array<float4, image_access::read_write>::pixel  _pixel_2_1d_a_rw_float4 = _1d_a_rw_float4[int2{ 0, 0 }];
    _pixel_2_1d_a_rw_float4 = float4{ 0, 0, 0, 0 };
    float4 _ret_3_1d_a_rw_float4 =  _pixel_2_1d_a_rw_float4;

    image2d<float4, image_access::read_write>::pixel _ret_p1_2d_rw_float4 = _2d_rw_float4[int2{ 0, 0 }];
    image2d<float4, image_access::read_write>::pixel  _pixel_2_2d_rw_float4 = _2d_rw_float4[int2{ 0, 0 }];
    _pixel_2_2d_rw_float4 = float4{ 0, 0, 0, 0 };
    float4 _ret_3_2d_rw_float4 =  _pixel_2_2d_rw_float4;

    image2d_array<float4, image_access::read_write>::pixel _ret_p1_2d_a_rw_float4 = _2d_a_rw_float4[int3{ 0, 0, 0 }];
    image2d_array<float4, image_access::read_write>::pixel  _pixel_2_2d_a_rw_float4 = _2d_a_rw_float4[int3{ 0, 0, 0 }];
    _pixel_2_2d_a_rw_float4 = float4{ 0, 0, 0, 0 };
    float4 _ret_3_2d_a_rw_float4 =  _pixel_2_2d_a_rw_float4;

    image3d<float4, image_access::read_write>::pixel _ret_p1_3d_rw_float4 = _3d_rw_float4[int3{ 0, 0, 0 }];
    image3d<float4, image_access::read_write>::pixel  _pixel_2_3d_rw_float4 = _3d_rw_float4[int3{ 0, 0, 0 }];
    _pixel_2_3d_rw_float4 = float4{ 0, 0, 0, 0 };
    float4 _ret_3_3d_rw_float4 =  _pixel_2_3d_rw_float4;

    image2d_ms<float4, image_access::read_write>::pixel _ret_p1_2d_ms_rw_float4 = _2d_ms_rw_float4[int2{ 0, 0 }];
    image2d_ms<float4, image_access::read_write>::pixel  _pixel_2_2d_ms_rw_float4 = _2d_ms_rw_float4[int2{ 0, 0 }];

    image2d_array_ms<float4, image_access::read_write>::pixel _ret_p1_2d_ms_a_rw_float4 = _2d_ms_a_rw_float4[int3{ 0, 0, 0 }];
    image2d_array_ms<float4, image_access::read_write>::pixel  _pixel_2_2d_ms_a_rw_float4 = _2d_ms_a_rw_float4[int3{ 0, 0, 0 }];

    image1d<float4, image_access::sample>::pixel _ret_p1_1d_s_float4 = _1d_s_float4[int{ 0 }];
    image1d<float4, image_access::sample>::pixel  _pixel_2_1d_s_float4 = _1d_s_float4[int{ 0 }];

    float4 _ret_3_1d_s_float4 =  _pixel_2_1d_s_float4;


    image1d_buffer<float4, image_access::sample>::pixel _ret_p1_1db_s_float4 = _1db_s_float4[int{ 0 }];
    image1d_buffer<float4, image_access::sample>::pixel  _pixel_2_1db_s_float4 = _1db_s_float4[int{ 0 }];

    float4 _ret_3_1db_s_float4 =  _pixel_2_1db_s_float4;


    image1d_array<float4, image_access::sample>::pixel _ret_p1_1d_a_s_float4 = _1d_a_s_float4[int2{ 0, 0 }];
    image1d_array<float4, image_access::sample>::pixel  _pixel_2_1d_a_s_float4 = _1d_a_s_float4[int2{ 0, 0 }];

    float4 _ret_3_1d_a_s_float4 =  _pixel_2_1d_a_s_float4;


    image2d<float4, image_access::sample>::pixel _ret_p1_2d_s_float4 = _2d_s_float4[int2{ 0, 0 }];
    image2d<float4, image_access::sample>::pixel  _pixel_2_2d_s_float4 = _2d_s_float4[int2{ 0, 0 }];

    float4 _ret_3_2d_s_float4 =  _pixel_2_2d_s_float4;


    image2d_array<float4, image_access::sample>::pixel _ret_p1_2d_a_s_float4 = _2d_a_s_float4[int3{ 0, 0, 0 }];
    image2d_array<float4, image_access::sample>::pixel  _pixel_2_2d_a_s_float4 = _2d_a_s_float4[int3{ 0, 0, 0 }];

    float4 _ret_3_2d_a_s_float4 =  _pixel_2_2d_a_s_float4;


    image3d<float4, image_access::sample>::pixel _ret_p1_3d_s_float4 = _3d_s_float4[int3{ 0, 0, 0 }];
    image3d<float4, image_access::sample>::pixel  _pixel_2_3d_s_float4 = _3d_s_float4[int3{ 0, 0, 0 }];

    float4 _ret_3_3d_s_float4 =  _pixel_2_3d_s_float4;


    image1d<half4, image_access::read>::pixel _ret_p1_1d_r_half4 = _1d_r_half4[int{ 0 }];
    image1d_buffer<half4, image_access::read>::pixel _ret_p1_1db_r_half4 = _1db_r_half4[int{ 0 }];
    image1d_array<half4, image_access::read>::pixel _ret_p1_1d_a_r_half4 = _1d_a_r_half4[int2{ 0, 0 }];
    image2d<half4, image_access::read>::pixel _ret_p1_2d_r_half4 = _2d_r_half4[int2{ 0, 0 }];
    image2d_array<half4, image_access::read>::pixel _ret_p1_2d_a_r_half4 = _2d_a_r_half4[int3{ 0, 0, 0 }];
    image3d<half4, image_access::read>::pixel _ret_p1_3d_r_half4 = _3d_r_half4[int3{ 0, 0, 0 }];
    image1d<half4, image_access::write>::pixel _ret_p1_1d_w_half4 = _1d_w_half4[int{ 0 }];
    image1d<half4, image_access::write>::pixel  _pixel_2_1d_w_half4 = _1d_w_half4[int{ 0 }];
    _pixel_2_1d_w_half4 = half4{ 0, 0, 0, 0 };

    image1d_buffer<half4, image_access::write>::pixel _ret_p1_1db_w_half4 = _1db_w_half4[int{ 0 }];
    image1d_buffer<half4, image_access::write>::pixel  _pixel_2_1db_w_half4 = _1db_w_half4[int{ 0 }];
    _pixel_2_1db_w_half4 = half4{ 0, 0, 0, 0 };

    image1d_array<half4, image_access::write>::pixel _ret_p1_1d_a_w_half4 = _1d_a_w_half4[int2{ 0, 0 }];
    image1d_array<half4, image_access::write>::pixel  _pixel_2_1d_a_w_half4 = _1d_a_w_half4[int2{ 0, 0 }];
    _pixel_2_1d_a_w_half4 = half4{ 0, 0, 0, 0 };

    image2d<half4, image_access::write>::pixel _ret_p1_2d_w_half4 = _2d_w_half4[int2{ 0, 0 }];
    image2d<half4, image_access::write>::pixel  _pixel_2_2d_w_half4 = _2d_w_half4[int2{ 0, 0 }];
    _pixel_2_2d_w_half4 = half4{ 0, 0, 0, 0 };

    image2d_array<half4, image_access::write>::pixel _ret_p1_2d_a_w_half4 = _2d_a_w_half4[int3{ 0, 0, 0 }];
    image2d_array<half4, image_access::write>::pixel  _pixel_2_2d_a_w_half4 = _2d_a_w_half4[int3{ 0, 0, 0 }];
    _pixel_2_2d_a_w_half4 = half4{ 0, 0, 0, 0 };

    image3d<half4, image_access::write>::pixel _ret_p1_3d_w_half4 = _3d_w_half4[int3{ 0, 0, 0 }];
    image3d<half4, image_access::write>::pixel  _pixel_2_3d_w_half4 = _3d_w_half4[int3{ 0, 0, 0 }];
    _pixel_2_3d_w_half4 = half4{ 0, 0, 0, 0 };

    image1d<half4, image_access::read_write>::pixel _ret_p1_1d_rw_half4 = _1d_rw_half4[int{ 0 }];
    image1d<half4, image_access::read_write>::pixel  _pixel_2_1d_rw_half4 = _1d_rw_half4[int{ 0 }];
    _pixel_2_1d_rw_half4 = half4{ 0, 0, 0, 0 };
    half4 _ret_3_1d_rw_half4 =  _pixel_2_1d_rw_half4;

    image1d_buffer<half4, image_access::read_write>::pixel _ret_p1_1db_rw_half4 = _1db_rw_half4[int{ 0 }];
    image1d_buffer<half4, image_access::read_write>::pixel  _pixel_2_1db_rw_half4 = _1db_rw_half4[int{ 0 }];
    _pixel_2_1db_rw_half4 = half4{ 0, 0, 0, 0 };
    half4 _ret_3_1db_rw_half4 =  _pixel_2_1db_rw_half4;

    image1d_array<half4, image_access::read_write>::pixel _ret_p1_1d_a_rw_half4 = _1d_a_rw_half4[int2{ 0, 0 }];
    image1d_array<half4, image_access::read_write>::pixel  _pixel_2_1d_a_rw_half4 = _1d_a_rw_half4[int2{ 0, 0 }];
    _pixel_2_1d_a_rw_half4 = half4{ 0, 0, 0, 0 };
    half4 _ret_3_1d_a_rw_half4 =  _pixel_2_1d_a_rw_half4;

    image2d<half4, image_access::read_write>::pixel _ret_p1_2d_rw_half4 = _2d_rw_half4[int2{ 0, 0 }];
    image2d<half4, image_access::read_write>::pixel  _pixel_2_2d_rw_half4 = _2d_rw_half4[int2{ 0, 0 }];
    _pixel_2_2d_rw_half4 = half4{ 0, 0, 0, 0 };
    half4 _ret_3_2d_rw_half4 =  _pixel_2_2d_rw_half4;

    image2d_array<half4, image_access::read_write>::pixel _ret_p1_2d_a_rw_half4 = _2d_a_rw_half4[int3{ 0, 0, 0 }];
    image2d_array<half4, image_access::read_write>::pixel  _pixel_2_2d_a_rw_half4 = _2d_a_rw_half4[int3{ 0, 0, 0 }];
    _pixel_2_2d_a_rw_half4 = half4{ 0, 0, 0, 0 };
    half4 _ret_3_2d_a_rw_half4 =  _pixel_2_2d_a_rw_half4;

    image3d<half4, image_access::read_write>::pixel _ret_p1_3d_rw_half4 = _3d_rw_half4[int3{ 0, 0, 0 }];
    image3d<half4, image_access::read_write>::pixel  _pixel_2_3d_rw_half4 = _3d_rw_half4[int3{ 0, 0, 0 }];
    _pixel_2_3d_rw_half4 = half4{ 0, 0, 0, 0 };
    half4 _ret_3_3d_rw_half4 =  _pixel_2_3d_rw_half4;

    image1d<half4, image_access::sample>::pixel _ret_p1_1d_s_half4 = _1d_s_half4[int{ 0 }];
    image1d<half4, image_access::sample>::pixel  _pixel_2_1d_s_half4 = _1d_s_half4[int{ 0 }];

    half4 _ret_3_1d_s_half4 =  _pixel_2_1d_s_half4;


    image1d_buffer<half4, image_access::sample>::pixel _ret_p1_1db_s_half4 = _1db_s_half4[int{ 0 }];
    image1d_buffer<half4, image_access::sample>::pixel  _pixel_2_1db_s_half4 = _1db_s_half4[int{ 0 }];

    half4 _ret_3_1db_s_half4 =  _pixel_2_1db_s_half4;


    image1d_array<half4, image_access::sample>::pixel _ret_p1_1d_a_s_half4 = _1d_a_s_half4[int2{ 0, 0 }];
    image1d_array<half4, image_access::sample>::pixel  _pixel_2_1d_a_s_half4 = _1d_a_s_half4[int2{ 0, 0 }];

    half4 _ret_3_1d_a_s_half4 =  _pixel_2_1d_a_s_half4;


    image2d<half4, image_access::sample>::pixel _ret_p1_2d_s_half4 = _2d_s_half4[int2{ 0, 0 }];
    image2d<half4, image_access::sample>::pixel  _pixel_2_2d_s_half4 = _2d_s_half4[int2{ 0, 0 }];

    half4 _ret_3_2d_s_half4 =  _pixel_2_2d_s_half4;


    image2d_array<half4, image_access::sample>::pixel _ret_p1_2d_a_s_half4 = _2d_a_s_half4[int3{ 0, 0, 0 }];
    image2d_array<half4, image_access::sample>::pixel  _pixel_2_2d_a_s_half4 = _2d_a_s_half4[int3{ 0, 0, 0 }];

    half4 _ret_3_2d_a_s_half4 =  _pixel_2_2d_a_s_half4;


    image3d<half4, image_access::sample>::pixel _ret_p1_3d_s_half4 = _3d_s_half4[int3{ 0, 0, 0 }];
    image3d<half4, image_access::sample>::pixel  _pixel_2_3d_s_half4 = _3d_s_half4[int3{ 0, 0, 0 }];

    half4 _ret_3_3d_s_half4 =  _pixel_2_3d_s_half4;


    image2d_depth<float, image_access::read>::pixel _ret_p1_2d_d_r_float = _2d_d_r_float[int2{ 0, 0 }];
    image2d_array_depth<float, image_access::read>::pixel _ret_p1_2d_a_d_r_float = _2d_a_d_r_float[int3{ 0, 0, 0 }];
    image2d_depth_ms<float, image_access::read>::pixel _ret_p1_2d_ms_d_r_float = _2d_ms_d_r_float[int2{ 0, 0 }];
    image2d_array_depth_ms<float, image_access::read>::pixel _ret_p1_2d_ms_a_d_r_float = _2d_ms_a_d_r_float[int3{ 0, 0, 0 }];
    image2d_depth<float, image_access::write>::pixel _ret_p1_2d_d_w_float = _2d_d_w_float[int2{ 0, 0 }];
    image2d_depth<float, image_access::write>::pixel  _pixel_2_2d_d_w_float = _2d_d_w_float[int2{ 0, 0 }];
    _pixel_2_2d_d_w_float = float{ 0 };

    image2d_array_depth<float, image_access::write>::pixel _ret_p1_2d_a_d_w_float = _2d_a_d_w_float[int3{ 0, 0, 0 }];
    image2d_array_depth<float, image_access::write>::pixel  _pixel_2_2d_a_d_w_float = _2d_a_d_w_float[int3{ 0, 0, 0 }];
    _pixel_2_2d_a_d_w_float = float{ 0 };

    image2d_depth_ms<float, image_access::write>::pixel _ret_p1_2d_ms_d_w_float = _2d_ms_d_w_float[int2{ 0, 0 }];
    image2d_depth_ms<float, image_access::write>::pixel  _pixel_2_2d_ms_d_w_float = _2d_ms_d_w_float[int2{ 0, 0 }];

    image2d_array_depth_ms<float, image_access::write>::pixel _ret_p1_2d_ms_a_d_w_float = _2d_ms_a_d_w_float[int3{ 0, 0, 0 }];
    image2d_array_depth_ms<float, image_access::write>::pixel  _pixel_2_2d_ms_a_d_w_float = _2d_ms_a_d_w_float[int3{ 0, 0, 0 }];

    image2d_depth<float, image_access::read_write>::pixel _ret_p1_2d_d_rw_float = _2d_d_rw_float[int2{ 0, 0 }];
    image2d_depth<float, image_access::read_write>::pixel  _pixel_2_2d_d_rw_float = _2d_d_rw_float[int2{ 0, 0 }];
    _pixel_2_2d_d_rw_float = float{ 0 };
    float _ret_3_2d_d_rw_float =  _pixel_2_2d_d_rw_float;

    image2d_array_depth<float, image_access::read_write>::pixel _ret_p1_2d_a_d_rw_float = _2d_a_d_rw_float[int3{ 0, 0, 0 }];
    image2d_array_depth<float, image_access::read_write>::pixel  _pixel_2_2d_a_d_rw_float = _2d_a_d_rw_float[int3{ 0, 0, 0 }];
    _pixel_2_2d_a_d_rw_float = float{ 0 };
    float _ret_3_2d_a_d_rw_float =  _pixel_2_2d_a_d_rw_float;

    image2d_depth_ms<float, image_access::read_write>::pixel _ret_p1_2d_ms_d_rw_float = _2d_ms_d_rw_float[int2{ 0, 0 }];
    image2d_depth_ms<float, image_access::read_write>::pixel  _pixel_2_2d_ms_d_rw_float = _2d_ms_d_rw_float[int2{ 0, 0 }];

    image2d_array_depth_ms<float, image_access::read_write>::pixel _ret_p1_2d_ms_a_d_rw_float = _2d_ms_a_d_rw_float[int3{ 0, 0, 0 }];
    image2d_array_depth_ms<float, image_access::read_write>::pixel  _pixel_2_2d_ms_a_d_rw_float = _2d_ms_a_d_rw_float[int3{ 0, 0, 0 }];

    image2d_depth<float, image_access::sample>::pixel _ret_p1_2d_d_s_float = _2d_d_s_float[int2{ 0, 0 }];
    image2d_depth<float, image_access::sample>::pixel  _pixel_2_2d_d_s_float = _2d_d_s_float[int2{ 0, 0 }];

    float _ret_3_2d_d_s_float =  _pixel_2_2d_d_s_float;


    image2d_array_depth<float, image_access::sample>::pixel _ret_p1_2d_a_d_s_float = _2d_a_d_s_float[int3{ 0, 0, 0 }];
    image2d_array_depth<float, image_access::sample>::pixel  _pixel_2_2d_a_d_s_float = _2d_a_d_s_float[int3{ 0, 0, 0 }];

    float _ret_3_2d_a_d_s_float =  _pixel_2_2d_a_d_s_float;


    image2d_depth<half, image_access::read>::pixel _ret_p1_2d_d_r_half = _2d_d_r_half[int2{ 0, 0 }];
    image2d_array_depth<half, image_access::read>::pixel _ret_p1_2d_a_d_r_half = _2d_a_d_r_half[int3{ 0, 0, 0 }];
    image2d_depth<half, image_access::write>::pixel _ret_p1_2d_d_w_half = _2d_d_w_half[int2{ 0, 0 }];
    image2d_depth<half, image_access::write>::pixel  _pixel_2_2d_d_w_half = _2d_d_w_half[int2{ 0, 0 }];
    _pixel_2_2d_d_w_half = half{ 0 };

    image2d_array_depth<half, image_access::write>::pixel _ret_p1_2d_a_d_w_half = _2d_a_d_w_half[int3{ 0, 0, 0 }];
    image2d_array_depth<half, image_access::write>::pixel  _pixel_2_2d_a_d_w_half = _2d_a_d_w_half[int3{ 0, 0, 0 }];
    _pixel_2_2d_a_d_w_half = half{ 0 };

    image2d_depth<half, image_access::read_write>::pixel _ret_p1_2d_d_rw_half = _2d_d_rw_half[int2{ 0, 0 }];
    image2d_depth<half, image_access::read_write>::pixel  _pixel_2_2d_d_rw_half = _2d_d_rw_half[int2{ 0, 0 }];
    _pixel_2_2d_d_rw_half = half{ 0 };
    half _ret_3_2d_d_rw_half =  _pixel_2_2d_d_rw_half;

    image2d_array_depth<half, image_access::read_write>::pixel _ret_p1_2d_a_d_rw_half = _2d_a_d_rw_half[int3{ 0, 0, 0 }];
    image2d_array_depth<half, image_access::read_write>::pixel  _pixel_2_2d_a_d_rw_half = _2d_a_d_rw_half[int3{ 0, 0, 0 }];
    _pixel_2_2d_a_d_rw_half = half{ 0 };
    half _ret_3_2d_a_d_rw_half =  _pixel_2_2d_a_d_rw_half;

    image2d_depth<half, image_access::sample>::pixel _ret_p1_2d_d_s_half = _2d_d_s_half[int2{ 0, 0 }];
    image2d_depth<half, image_access::sample>::pixel  _pixel_2_2d_d_s_half = _2d_d_s_half[int2{ 0, 0 }];

    half _ret_3_2d_d_s_half =  _pixel_2_2d_d_s_half;


    image2d_array_depth<half, image_access::sample>::pixel _ret_p1_2d_a_d_s_half = _2d_a_d_s_half[int3{ 0, 0, 0 }];
    image2d_array_depth<half, image_access::sample>::pixel  _pixel_2_2d_a_d_s_half = _2d_a_d_s_half[int3{ 0, 0, 0 }];

    half _ret_3_2d_a_d_s_half =  _pixel_2_2d_a_d_s_half;


}