// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable -Dcl_khr_gl_msaa_sharing -Dcl_khr_gl_depth_images -Dcl_khr_mipmap_image -Dcl_khr_mipmap_image_writes -O0 -emit-llvm -o -
// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable -Dcl_khr_gl_msaa_sharing -Dcl_khr_gl_depth_images -Dcl_khr_mipmap_image -Dcl_khr_mipmap_image_writes -O3 -emit-llvm -o -
// RUN: %clang_cc1 %s -triple spir64-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable -Dcl_khr_gl_msaa_sharing -Dcl_khr_gl_depth_images -Dcl_khr_mipmap_image -Dcl_khr_mipmap_image_writes -O0 -emit-llvm -o -
// RUN: %clang_cc1 %s -triple spir64-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable -Dcl_khr_gl_msaa_sharing -Dcl_khr_gl_depth_images -Dcl_khr_mipmap_image -Dcl_khr_mipmap_image_writes -O3 -emit-llvm -o -
// expected-no-diagnostics

#define cl_khr_mipmap_image 1
#include <opencl_image>
using namespace cl;

kernel void worker(image1d<float4, image_access::write> _d1f4w,
                   image1d_array<float4, image_access::write> _d1af4w,
                   image2d<float4, image_access::write> _d2f4w,
                   image2d_array<float4, image_access::write> _d2af4w,
                   image2d_depth<float, image_access::write> _d2df1w,
                   image2d_array_depth<float, image_access::write> _d2adf1w,
                   image3d<float4, image_access::write> _d3f4w)
{
    _d1f4w.write(float{0}, float4{0, 0, 0, 0});
    _d1af4w.write(float{0}, float4{0, 0, 0, 0});
    _d2f4w.write(float{0}, float4{0, 0, 0, 0});
    _d2af4w.write(float{0}, float4{0, 0, 0, 0});
    _d2df1w.write(float{0}, 0);
    _d2adf1w.write(float{0}, 0);
    _d3f4w.write(float{0}, float4{0, 0, 0, 0});

    // CHECK: spir_func void {{.*}}__spirv_ImageWrite
}