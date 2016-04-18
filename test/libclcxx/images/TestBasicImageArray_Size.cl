// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable -Dcl_khr_gl_msaa_sharing -Dcl_khr_gl_depth_images -Dcl_khr_mipmap_image -Dcl_khr_mipmap_image_writes -O0 -emit-llvm -o -
// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable -Dcl_khr_gl_msaa_sharing -Dcl_khr_gl_depth_images -Dcl_khr_mipmap_image -Dcl_khr_mipmap_image_writes -O3 -emit-llvm -o -
// RUN: %clang_cc1 %s -triple spir64-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable -Dcl_khr_gl_msaa_sharing -Dcl_khr_gl_depth_images -Dcl_khr_mipmap_image -Dcl_khr_mipmap_image_writes -O0 -emit-llvm -o -
// RUN: %clang_cc1 %s -triple spir64-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable -Dcl_khr_gl_msaa_sharing -Dcl_khr_gl_depth_images -Dcl_khr_mipmap_image -Dcl_khr_mipmap_image_writes -O3 -emit-llvm -o -
// expected-no-diagnostics
#include <opencl_image>

using namespace cl;

kernel void worker(image1d_array<int4, image_access::read> _1d_a_r_int4, image2d_array<int4, image_access::read> _2d_a_r_int4,
    image2d_array_ms<int4, image_access::read> _2d_ms_a_r_int4, image1d_array<int4, image_access::write> _1d_a_w_int4,
    image2d_array<int4, image_access::write> _2d_a_w_int4, image2d_array_ms<int4, image_access::write> _2d_ms_a_w_int4,
    image1d_array<int4, image_access::read_write> _1d_a_rw_int4, image2d_array<int4, image_access::read_write> _2d_a_rw_int4,
    image2d_array_ms<int4, image_access::read_write> _2d_ms_a_rw_int4, image1d_array<int4, image_access::sample> _1d_a_s_int4,
    image2d_array<int4, image_access::sample> _2d_a_s_int4, image1d_array<uint4, image_access::read> _1d_a_r_uint4,
    image2d_array<uint4, image_access::read> _2d_a_r_uint4, image2d_array_ms<uint4, image_access::read> _2d_ms_a_r_uint4,
    image1d_array<uint4, image_access::write> _1d_a_w_uint4, image2d_array<uint4, image_access::write> _2d_a_w_uint4,
    image2d_array_ms<uint4, image_access::write> _2d_ms_a_w_uint4, image1d_array<uint4, image_access::read_write> _1d_a_rw_uint4,
    image2d_array<uint4, image_access::read_write> _2d_a_rw_uint4, image2d_array_ms<uint4, image_access::read_write> _2d_ms_a_rw_uint4,
    image1d_array<uint4, image_access::sample> _1d_a_s_uint4, image2d_array<uint4, image_access::sample> _2d_a_s_uint4,
    image1d_array<float4, image_access::read> _1d_a_r_float4, image2d_array<float4, image_access::read> _2d_a_r_float4,
    image2d_array_ms<float4, image_access::read> _2d_ms_a_r_float4, image1d_array<float4, image_access::write> _1d_a_w_float4,
    image2d_array<float4, image_access::write> _2d_a_w_float4, image2d_array_ms<float4, image_access::write> _2d_ms_a_w_float4,
    image1d_array<float4, image_access::read_write> _1d_a_rw_float4, image2d_array<float4, image_access::read_write> _2d_a_rw_float4,
    image2d_array_ms<float4, image_access::read_write> _2d_ms_a_rw_float4, image1d_array<float4, image_access::sample> _1d_a_s_float4,
    image2d_array<float4, image_access::sample> _2d_a_s_float4, image1d_array<half4, image_access::read> _1d_a_r_half4,
    image2d_array<half4, image_access::read> _2d_a_r_half4, image1d_array<half4, image_access::write> _1d_a_w_half4,
    image2d_array<half4, image_access::write> _2d_a_w_half4, image1d_array<half4, image_access::read_write> _1d_a_rw_half4,
    image2d_array<half4, image_access::read_write> _2d_a_rw_half4, image1d_array<half4, image_access::sample> _1d_a_s_half4,
    image2d_array<half4, image_access::sample> _2d_a_s_half4, image2d_array_depth<float, image_access::read> _2d_a_d_r_float,
    image2d_array_depth_ms<float, image_access::read> _2d_ms_a_d_r_float, image2d_array_depth<float, image_access::write> _2d_a_d_w_float,
    image2d_array_depth_ms<float, image_access::write> _2d_ms_a_d_w_float, image2d_array_depth<float, image_access::read_write> _2d_a_d_rw_float,
    image2d_array_depth_ms<float, image_access::read_write> _2d_ms_a_d_rw_float, image2d_array_depth<float, image_access::sample> _2d_a_d_s_float,
    image2d_array_depth<half, image_access::read> _2d_a_d_r_half, image2d_array_depth<half, image_access::write> _2d_a_d_w_half,
    image2d_array_depth<half, image_access::read_write> _2d_a_d_rw_half, image2d_array_depth<half, image_access::sample> _2d_a_d_s_half)
{
    int _ret1_1d_a_r_int4 = _1d_a_r_int4.array_size();

#ifdef cl_khr_mipmap_image
    int _ret2_1d_a_r_int4 = _1d_a_r_int4.array_size(int{ 0 });
#endif
    int _ret1_2d_a_r_int4 = _2d_a_r_int4.array_size();

#ifdef cl_khr_mipmap_image
    int _ret2_2d_a_r_int4 = _2d_a_r_int4.array_size(int{ 0 });
#endif
    int _ret1_2d_ms_a_r_int4 = _2d_ms_a_r_int4.array_size();
    int _ret1_1d_a_w_int4 = _1d_a_w_int4.array_size();

#ifdef cl_khr_mipmap_image
    int _ret2_1d_a_w_int4 = _1d_a_w_int4.array_size(int{ 0 });
#endif
    int _ret1_2d_a_w_int4 = _2d_a_w_int4.array_size();

#ifdef cl_khr_mipmap_image
    int _ret2_2d_a_w_int4 = _2d_a_w_int4.array_size(int{ 0 });
#endif
    int _ret1_2d_ms_a_w_int4 = _2d_ms_a_w_int4.array_size();
    int _ret1_1d_a_rw_int4 = _1d_a_rw_int4.array_size();

#ifdef cl_khr_mipmap_image
    int _ret2_1d_a_rw_int4 = _1d_a_rw_int4.array_size(int{ 0 });
#endif
    int _ret1_2d_a_rw_int4 = _2d_a_rw_int4.array_size();

#ifdef cl_khr_mipmap_image
    int _ret2_2d_a_rw_int4 = _2d_a_rw_int4.array_size(int{ 0 });
#endif
    int _ret1_2d_ms_a_rw_int4 = _2d_ms_a_rw_int4.array_size();
    int _ret1_1d_a_s_int4 = _1d_a_s_int4.array_size();

#ifdef cl_khr_mipmap_image
    int _ret2_1d_a_s_int4 = _1d_a_s_int4.array_size(int{ 0 });
#endif
    int _ret1_2d_a_s_int4 = _2d_a_s_int4.array_size();

#ifdef cl_khr_mipmap_image
    int _ret2_2d_a_s_int4 = _2d_a_s_int4.array_size(int{ 0 });
#endif
    int _ret1_1d_a_r_uint4 = _1d_a_r_uint4.array_size();

#ifdef cl_khr_mipmap_image
    int _ret2_1d_a_r_uint4 = _1d_a_r_uint4.array_size(int{ 0 });
#endif
    int _ret1_2d_a_r_uint4 = _2d_a_r_uint4.array_size();

#ifdef cl_khr_mipmap_image
    int _ret2_2d_a_r_uint4 = _2d_a_r_uint4.array_size(int{ 0 });
#endif
    int _ret1_2d_ms_a_r_uint4 = _2d_ms_a_r_uint4.array_size();
    int _ret1_1d_a_w_uint4 = _1d_a_w_uint4.array_size();

#ifdef cl_khr_mipmap_image
    int _ret2_1d_a_w_uint4 = _1d_a_w_uint4.array_size(int{ 0 });
#endif
    int _ret1_2d_a_w_uint4 = _2d_a_w_uint4.array_size();

#ifdef cl_khr_mipmap_image
    int _ret2_2d_a_w_uint4 = _2d_a_w_uint4.array_size(int{ 0 });
#endif
    int _ret1_2d_ms_a_w_uint4 = _2d_ms_a_w_uint4.array_size();
    int _ret1_1d_a_rw_uint4 = _1d_a_rw_uint4.array_size();

#ifdef cl_khr_mipmap_image
    int _ret2_1d_a_rw_uint4 = _1d_a_rw_uint4.array_size(int{ 0 });
#endif
    int _ret1_2d_a_rw_uint4 = _2d_a_rw_uint4.array_size();

#ifdef cl_khr_mipmap_image
    int _ret2_2d_a_rw_uint4 = _2d_a_rw_uint4.array_size(int{ 0 });
#endif
    int _ret1_2d_ms_a_rw_uint4 = _2d_ms_a_rw_uint4.array_size();
    int _ret1_1d_a_s_uint4 = _1d_a_s_uint4.array_size();

#ifdef cl_khr_mipmap_image
    int _ret2_1d_a_s_uint4 = _1d_a_s_uint4.array_size(int{ 0 });
#endif
    int _ret1_2d_a_s_uint4 = _2d_a_s_uint4.array_size();

#ifdef cl_khr_mipmap_image
    int _ret2_2d_a_s_uint4 = _2d_a_s_uint4.array_size(int{ 0 });
#endif
    int _ret1_1d_a_r_float4 = _1d_a_r_float4.array_size();

#ifdef cl_khr_mipmap_image
    int _ret2_1d_a_r_float4 = _1d_a_r_float4.array_size(int{ 0 });
#endif
    int _ret1_2d_a_r_float4 = _2d_a_r_float4.array_size();

#ifdef cl_khr_mipmap_image
    int _ret2_2d_a_r_float4 = _2d_a_r_float4.array_size(int{ 0 });
#endif
    int _ret1_2d_ms_a_r_float4 = _2d_ms_a_r_float4.array_size();
    int _ret1_1d_a_w_float4 = _1d_a_w_float4.array_size();

#ifdef cl_khr_mipmap_image
    int _ret2_1d_a_w_float4 = _1d_a_w_float4.array_size(int{ 0 });
#endif
    int _ret1_2d_a_w_float4 = _2d_a_w_float4.array_size();

#ifdef cl_khr_mipmap_image
    int _ret2_2d_a_w_float4 = _2d_a_w_float4.array_size(int{ 0 });
#endif
    int _ret1_2d_ms_a_w_float4 = _2d_ms_a_w_float4.array_size();
    int _ret1_1d_a_rw_float4 = _1d_a_rw_float4.array_size();

#ifdef cl_khr_mipmap_image
    int _ret2_1d_a_rw_float4 = _1d_a_rw_float4.array_size(int{ 0 });
#endif
    int _ret1_2d_a_rw_float4 = _2d_a_rw_float4.array_size();

#ifdef cl_khr_mipmap_image
    int _ret2_2d_a_rw_float4 = _2d_a_rw_float4.array_size(int{ 0 });
#endif
    int _ret1_2d_ms_a_rw_float4 = _2d_ms_a_rw_float4.array_size();
    int _ret1_1d_a_s_float4 = _1d_a_s_float4.array_size();

#ifdef cl_khr_mipmap_image
    int _ret2_1d_a_s_float4 = _1d_a_s_float4.array_size(int{ 0 });
#endif
    int _ret1_2d_a_s_float4 = _2d_a_s_float4.array_size();

#ifdef cl_khr_mipmap_image
    int _ret2_2d_a_s_float4 = _2d_a_s_float4.array_size(int{ 0 });
#endif
    int _ret1_1d_a_r_half4 = _1d_a_r_half4.array_size();

#ifdef cl_khr_mipmap_image
    int _ret2_1d_a_r_half4 = _1d_a_r_half4.array_size(int{ 0 });
#endif
    int _ret1_2d_a_r_half4 = _2d_a_r_half4.array_size();

#ifdef cl_khr_mipmap_image
    int _ret2_2d_a_r_half4 = _2d_a_r_half4.array_size(int{ 0 });
#endif
    int _ret1_1d_a_w_half4 = _1d_a_w_half4.array_size();

#ifdef cl_khr_mipmap_image
    int _ret2_1d_a_w_half4 = _1d_a_w_half4.array_size(int{ 0 });
#endif
    int _ret1_2d_a_w_half4 = _2d_a_w_half4.array_size();

#ifdef cl_khr_mipmap_image
    int _ret2_2d_a_w_half4 = _2d_a_w_half4.array_size(int{ 0 });
#endif
    int _ret1_1d_a_rw_half4 = _1d_a_rw_half4.array_size();

#ifdef cl_khr_mipmap_image
    int _ret2_1d_a_rw_half4 = _1d_a_rw_half4.array_size(int{ 0 });
#endif
    int _ret1_2d_a_rw_half4 = _2d_a_rw_half4.array_size();

#ifdef cl_khr_mipmap_image
    int _ret2_2d_a_rw_half4 = _2d_a_rw_half4.array_size(int{ 0 });
#endif
    int _ret1_1d_a_s_half4 = _1d_a_s_half4.array_size();

#ifdef cl_khr_mipmap_image
    int _ret2_1d_a_s_half4 = _1d_a_s_half4.array_size(int{ 0 });
#endif
    int _ret1_2d_a_s_half4 = _2d_a_s_half4.array_size();

#ifdef cl_khr_mipmap_image
    int _ret2_2d_a_s_half4 = _2d_a_s_half4.array_size(int{ 0 });
#endif
    int _ret1_2d_a_d_r_float = _2d_a_d_r_float.array_size();

#ifdef cl_khr_mipmap_image
    int _ret2_2d_a_d_r_float = _2d_a_d_r_float.array_size(int{ 0 });
#endif
    int _ret1_2d_ms_a_d_r_float = _2d_ms_a_d_r_float.array_size();
    int _ret1_2d_a_d_w_float = _2d_a_d_w_float.array_size();

#ifdef cl_khr_mipmap_image
    int _ret2_2d_a_d_w_float = _2d_a_d_w_float.array_size(int{ 0 });
#endif
    int _ret1_2d_ms_a_d_w_float = _2d_ms_a_d_w_float.array_size();
    int _ret1_2d_a_d_rw_float = _2d_a_d_rw_float.array_size();

#ifdef cl_khr_mipmap_image
    int _ret2_2d_a_d_rw_float = _2d_a_d_rw_float.array_size(int{ 0 });
#endif
    int _ret1_2d_ms_a_d_rw_float = _2d_ms_a_d_rw_float.array_size();
    int _ret1_2d_a_d_s_float = _2d_a_d_s_float.array_size();

#ifdef cl_khr_mipmap_image
    int _ret2_2d_a_d_s_float = _2d_a_d_s_float.array_size(int{ 0 });
#endif
    int _ret1_2d_a_d_r_half = _2d_a_d_r_half.array_size();

#ifdef cl_khr_mipmap_image
    int _ret2_2d_a_d_r_half = _2d_a_d_r_half.array_size(int{ 0 });
#endif
    int _ret1_2d_a_d_w_half = _2d_a_d_w_half.array_size();

#ifdef cl_khr_mipmap_image
    int _ret2_2d_a_d_w_half = _2d_a_d_w_half.array_size(int{ 0 });
#endif
    int _ret1_2d_a_d_rw_half = _2d_a_d_rw_half.array_size();

#ifdef cl_khr_mipmap_image
    int _ret2_2d_a_d_rw_half = _2d_a_d_rw_half.array_size(int{ 0 });
#endif
    int _ret1_2d_a_d_s_half = _2d_a_d_s_half.array_size();

#ifdef cl_khr_mipmap_image
    int _ret2_2d_a_d_s_half = _2d_a_d_s_half.array_size(int{ 0 });
#endif
}