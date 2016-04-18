// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable -Dcl_khr_gl_msaa_sharing -Dcl_khr_gl_depth_images -Dcl_khr_mipmap_image -Dcl_khr_mipmap_image_writes -O0 -emit-llvm -o -
// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable -Dcl_khr_gl_msaa_sharing -Dcl_khr_gl_depth_images -Dcl_khr_mipmap_image -Dcl_khr_mipmap_image_writes -O3 -emit-llvm -o -
// RUN: %clang_cc1 %s -triple spir64-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable -Dcl_khr_gl_msaa_sharing -Dcl_khr_gl_depth_images -Dcl_khr_mipmap_image -Dcl_khr_mipmap_image_writes -O0 -emit-llvm -o -
// RUN: %clang_cc1 %s -triple spir64-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable -Dcl_khr_gl_msaa_sharing -Dcl_khr_gl_depth_images -Dcl_khr_mipmap_image -Dcl_khr_mipmap_image_writes -O3 -emit-llvm -o -
// expected-no-diagnostics
#include <opencl_image>

using namespace cl;

kernel void worker(image1d<int4, image_access::read> d1,
                   image1d_buffer<int4, image_access::read> d1_b,
                   image1d_array<int4, image_access::read> d1_a,
                   image2d<int4, image_access::read> d2,
                   image2d_array<int4, image_access::read> d2_a,
                   image2d_depth<float, image_access::read> d2_d,
                   image2d_array_depth<float, image_access::read> d2_ad,
                   image3d<int4, image_access::read> d3,
                   image2d_ms<int4, image_access::read> d2_ms,
                   image2d_array_ms<int4, image_access::read> d2_a_ms,
                   image2d_depth_ms<float, image_access::read> d2_d_ms,
                   image2d_array_depth_ms<float, image_access::read> d2_ad_ms)
{
    static_assert(!d1.is_ms, "image1d should have is_ms value set to false");
    static_assert(!d1_b.is_ms, "image1d_buffer should have is_ms value set to false");
    static_assert(!d1_a.is_ms, "image1d_array should have is_ms value set to false");
    static_assert(!d2.is_ms, "image2d should have is_ms value set to false");
    static_assert(!d2_a.is_ms, "image2d_array should have is_ms value set to false");
    static_assert(!d2_d.is_ms, "image1d_depth should have is_ms value set to false");
    static_assert(!d2_ad.is_ms, "image2d_array_depth should have is_ms value set to false");

    static_assert(!d3.is_ms, "image3d should have is_ms value set to false");

    static_assert(d2_ms.is_ms, "image2d_ms should have is_ms value set to true");
    static_assert(d2_a_ms.is_ms, "image2d_array_ms should have is_ms value set to true");
    static_assert(d2_d_ms.is_ms, "image2d_depth_ms should have is_ms value set to true");
    static_assert(d2_ad_ms.is_ms, "image2d_array_depth_ms should have is_ms value set to true");
}