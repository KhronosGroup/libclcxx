// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable -Dcl_khr_gl_msaa_sharing -Dcl_khr_gl_depth_images -Dcl_khr_mipmap_image -Dcl_khr_mipmap_image_writes -O0 -emit-llvm -o -
// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable -Dcl_khr_gl_msaa_sharing -Dcl_khr_gl_depth_images -Dcl_khr_mipmap_image -Dcl_khr_mipmap_image_writes -O3 -emit-llvm -o -
// RUN: %clang_cc1 %s -triple spir64-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable -Dcl_khr_gl_msaa_sharing -Dcl_khr_gl_depth_images -Dcl_khr_mipmap_image -Dcl_khr_mipmap_image_writes -O0 -emit-llvm -o -
// RUN: %clang_cc1 %s -triple spir64-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable -Dcl_khr_gl_msaa_sharing -Dcl_khr_gl_depth_images -Dcl_khr_mipmap_image -Dcl_khr_mipmap_image_writes -O3 -emit-llvm -o -
// expected-no-diagnostics
#include <opencl_image>

using namespace cl;

kernel void worker(image1d<int4, image_access::write> _1d_w_int4, image1d_buffer<int4, image_access::write> _1db_w_int4,
    image1d_array<int4, image_access::write> _1d_a_w_int4, image2d<int4, image_access::write> _2d_w_int4,
    image2d_array<int4, image_access::write> _2d_a_w_int4, image3d<int4, image_access::write> _3d_w_int4,
    image1d<int4, image_access::read_write> _1d_rw_int4, image1d_buffer<int4, image_access::read_write> _1db_rw_int4,
    image1d_array<int4, image_access::read_write> _1d_a_rw_int4, image2d<int4, image_access::read_write> _2d_rw_int4,
    image2d_array<int4, image_access::read_write> _2d_a_rw_int4, image3d<int4, image_access::read_write> _3d_rw_int4,
    image1d<uint4, image_access::write> _1d_w_uint4, image1d_buffer<uint4, image_access::write> _1db_w_uint4,
    image1d_array<uint4, image_access::write> _1d_a_w_uint4, image2d<uint4, image_access::write> _2d_w_uint4,
    image2d_array<uint4, image_access::write> _2d_a_w_uint4, image3d<uint4, image_access::write> _3d_w_uint4,
    image1d<uint4, image_access::read_write> _1d_rw_uint4, image1d_buffer<uint4, image_access::read_write> _1db_rw_uint4,
    image1d_array<uint4, image_access::read_write> _1d_a_rw_uint4, image2d<uint4, image_access::read_write> _2d_rw_uint4,
    image2d_array<uint4, image_access::read_write> _2d_a_rw_uint4, image3d<uint4, image_access::read_write> _3d_rw_uint4,
    image1d<float4, image_access::write> _1d_w_float4, image1d_buffer<float4, image_access::write> _1db_w_float4,
    image1d_array<float4, image_access::write> _1d_a_w_float4, image2d<float4, image_access::write> _2d_w_float4,
    image2d_array<float4, image_access::write> _2d_a_w_float4, image3d<float4, image_access::write> _3d_w_float4,
    image1d<float4, image_access::read_write> _1d_rw_float4, image1d_buffer<float4, image_access::read_write> _1db_rw_float4,
    image1d_array<float4, image_access::read_write> _1d_a_rw_float4, image2d<float4, image_access::read_write> _2d_rw_float4,
    image2d_array<float4, image_access::read_write> _2d_a_rw_float4, image3d<float4, image_access::read_write> _3d_rw_float4,
    image1d<half4, image_access::write> _1d_w_half4, image1d_buffer<half4, image_access::write> _1db_w_half4,
    image1d_array<half4, image_access::write> _1d_a_w_half4, image2d<half4, image_access::write> _2d_w_half4,
    image2d_array<half4, image_access::write> _2d_a_w_half4, image3d<half4, image_access::write> _3d_w_half4,
    image1d<half4, image_access::read_write> _1d_rw_half4, image1d_buffer<half4, image_access::read_write> _1db_rw_half4,
    image1d_array<half4, image_access::read_write> _1d_a_rw_half4, image2d<half4, image_access::read_write> _2d_rw_half4,
    image2d_array<half4, image_access::read_write> _2d_a_rw_half4, image3d<half4, image_access::read_write> _3d_rw_half4,
    image2d_depth<float, image_access::write> _2d_d_w_float, image2d_array_depth<float, image_access::write> _2d_a_d_w_float,
    image2d_depth<float, image_access::read_write> _2d_d_rw_float, image2d_array_depth<float, image_access::read_write> _2d_a_d_rw_float,
    image2d_depth<half, image_access::write> _2d_d_w_half, image2d_array_depth<half, image_access::write> _2d_a_d_w_half,
    image2d_depth<half, image_access::read_write> _2d_d_rw_half, image2d_array_depth<half, image_access::read_write> _2d_a_d_rw_half)
{
    _1d_w_int4.write(int{ 0 }, int4{ 0, 0, 0, 0 });
    _1db_w_int4.write(int{ 0 }, int4{ 0, 0, 0, 0 });
    _1d_a_w_int4.write(int2{ 0, 0 }, int4{ 0, 0, 0, 0 });
    _2d_w_int4.write(int2{ 0, 0 }, int4{ 0, 0, 0, 0 });
    _2d_a_w_int4.write(int3{ 0, 0, 0 }, int4{ 0, 0, 0, 0 });
    _3d_w_int4.write(int3{ 0, 0, 0 }, int4{ 0, 0, 0, 0 });
    _1d_rw_int4.write(int{ 0 }, int4{ 0, 0, 0, 0 });
    _1db_rw_int4.write(int{ 0 }, int4{ 0, 0, 0, 0 });
    _1d_a_rw_int4.write(int2{ 0, 0 }, int4{ 0, 0, 0, 0 });
    _2d_rw_int4.write(int2{ 0, 0 }, int4{ 0, 0, 0, 0 });
    _2d_a_rw_int4.write(int3{ 0, 0, 0 }, int4{ 0, 0, 0, 0 });
    _3d_rw_int4.write(int3{ 0, 0, 0 }, int4{ 0, 0, 0, 0 });
    _1d_w_uint4.write(int{ 0 }, uint4{ 0, 0, 0, 0 });
    _1db_w_uint4.write(int{ 0 }, uint4{ 0, 0, 0, 0 });
    _1d_a_w_uint4.write(int2{ 0, 0 }, uint4{ 0, 0, 0, 0 });
    _2d_w_uint4.write(int2{ 0, 0 }, uint4{ 0, 0, 0, 0 });
    _2d_a_w_uint4.write(int3{ 0, 0, 0 }, uint4{ 0, 0, 0, 0 });
    _3d_w_uint4.write(int3{ 0, 0, 0 }, uint4{ 0, 0, 0, 0 });
    _1d_rw_uint4.write(int{ 0 }, uint4{ 0, 0, 0, 0 });
    _1db_rw_uint4.write(int{ 0 }, uint4{ 0, 0, 0, 0 });
    _1d_a_rw_uint4.write(int2{ 0, 0 }, uint4{ 0, 0, 0, 0 });
    _2d_rw_uint4.write(int2{ 0, 0 }, uint4{ 0, 0, 0, 0 });
    _2d_a_rw_uint4.write(int3{ 0, 0, 0 }, uint4{ 0, 0, 0, 0 });
    _3d_rw_uint4.write(int3{ 0, 0, 0 }, uint4{ 0, 0, 0, 0 });
    _1d_w_float4.write(int{ 0 }, float4{ 0, 0, 0, 0 });
    _1db_w_float4.write(int{ 0 }, float4{ 0, 0, 0, 0 });
    _1d_a_w_float4.write(int2{ 0, 0 }, float4{ 0, 0, 0, 0 });
    _2d_w_float4.write(int2{ 0, 0 }, float4{ 0, 0, 0, 0 });
    _2d_a_w_float4.write(int3{ 0, 0, 0 }, float4{ 0, 0, 0, 0 });
    _3d_w_float4.write(int3{ 0, 0, 0 }, float4{ 0, 0, 0, 0 });
    _1d_rw_float4.write(int{ 0 }, float4{ 0, 0, 0, 0 });
    _1db_rw_float4.write(int{ 0 }, float4{ 0, 0, 0, 0 });
    _1d_a_rw_float4.write(int2{ 0, 0 }, float4{ 0, 0, 0, 0 });
    _2d_rw_float4.write(int2{ 0, 0 }, float4{ 0, 0, 0, 0 });
    _2d_a_rw_float4.write(int3{ 0, 0, 0 }, float4{ 0, 0, 0, 0 });
    _3d_rw_float4.write(int3{ 0, 0, 0 }, float4{ 0, 0, 0, 0 });
    _1d_w_half4.write(int{ 0 }, half4{ 0, 0, 0, 0 });
    _1db_w_half4.write(int{ 0 }, half4{ 0, 0, 0, 0 });
    _1d_a_w_half4.write(int2{ 0, 0 }, half4{ 0, 0, 0, 0 });
    _2d_w_half4.write(int2{ 0, 0 }, half4{ 0, 0, 0, 0 });
    _2d_a_w_half4.write(int3{ 0, 0, 0 }, half4{ 0, 0, 0, 0 });
    _3d_w_half4.write(int3{ 0, 0, 0 }, half4{ 0, 0, 0, 0 });
    _1d_rw_half4.write(int{ 0 }, half4{ 0, 0, 0, 0 });
    _1db_rw_half4.write(int{ 0 }, half4{ 0, 0, 0, 0 });
    _1d_a_rw_half4.write(int2{ 0, 0 }, half4{ 0, 0, 0, 0 });
    _2d_rw_half4.write(int2{ 0, 0 }, half4{ 0, 0, 0, 0 });
    _2d_a_rw_half4.write(int3{ 0, 0, 0 }, half4{ 0, 0, 0, 0 });
    _3d_rw_half4.write(int3{ 0, 0, 0 }, half4{ 0, 0, 0, 0 });
    _2d_d_w_float.write(int2{ 0, 0 }, float{ 0 });
    _2d_a_d_w_float.write(int3{ 0, 0, 0 }, float{ 0 });
    _2d_d_rw_float.write(int2{ 0, 0 }, float{ 0 });
    _2d_a_d_rw_float.write(int3{ 0, 0, 0 }, float{ 0 });
    _2d_d_w_half.write(int2{ 0, 0 }, half{ 0 });
    _2d_a_d_w_half.write(int3{ 0, 0, 0 }, half{ 0 });
    _2d_d_rw_half.write(int2{ 0, 0 }, half{ 0 });
    _2d_a_d_rw_half.write(int3{ 0, 0, 0 }, half{ 0 });
}