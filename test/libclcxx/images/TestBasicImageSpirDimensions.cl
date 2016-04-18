// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable -Dcl_khr_gl_msaa_sharing -Dcl_khr_gl_depth_images -Dcl_khr_mipmap_image -Dcl_khr_mipmap_image_writes -O0 -emit-llvm -o -
// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable -Dcl_khr_gl_msaa_sharing -Dcl_khr_gl_depth_images -Dcl_khr_mipmap_image -Dcl_khr_mipmap_image_writes -O3 -emit-llvm -o -
// RUN: %clang_cc1 %s -triple spir64-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable -Dcl_khr_gl_msaa_sharing -Dcl_khr_gl_depth_images -Dcl_khr_mipmap_image -Dcl_khr_mipmap_image_writes -O0 -emit-llvm -o -
// RUN: %clang_cc1 %s -triple spir64-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable -Dcl_khr_gl_msaa_sharing -Dcl_khr_gl_depth_images -Dcl_khr_mipmap_image -Dcl_khr_mipmap_image_writes -O3 -emit-llvm -o -
// expected-no-diagnostics

#include <opencl_image>
using namespace cl;

kernel void worker(image1d<float4, image_access::read> _d1f4r,
                   image2d<float4, image_access::read> _d2f4r,
                   image2d_array<float4, image_access::read> _d2af4r,
                   image3d<float4, image_access::read> _d3f4r)
{
    int _d1f4r_w = _d1f4r.width();
    // CHECK: i32 {{.*}}__spirv_ImageQuerySize

    int _d2f4r_h = _d2f4r.height();
    // CHECK: <2 x i32> {{.*}}__spirv_ImageQuerySize

    int _d3f4r_d = _d3f4r.depth();
    // CHECK: <3 x i32> {{.*}}__spirv_ImageQuerySize

}