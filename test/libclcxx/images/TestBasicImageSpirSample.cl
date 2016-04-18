// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable -Dcl_khr_gl_msaa_sharing -Dcl_khr_gl_depth_images -Dcl_khr_mipmap_image -Dcl_khr_mipmap_image_writes -O0 -emit-llvm -o -
// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable -Dcl_khr_gl_msaa_sharing -Dcl_khr_gl_depth_images -Dcl_khr_mipmap_image -Dcl_khr_mipmap_image_writes -O3 -emit-llvm -o -
// RUN: %clang_cc1 %s -triple spir64-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable -Dcl_khr_gl_msaa_sharing -Dcl_khr_gl_depth_images -Dcl_khr_mipmap_image -Dcl_khr_mipmap_image_writes -O0 -emit-llvm -o -
// RUN: %clang_cc1 %s -triple spir64-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable -Dcl_khr_gl_msaa_sharing -Dcl_khr_gl_depth_images -Dcl_khr_mipmap_image -Dcl_khr_mipmap_image_writes -O3 -emit-llvm -o -
// expected-no-diagnostics

#include <opencl_image>
using namespace cl;

kernel void worker(image1d<float4, image_access::sample> _d1f4r,
                   image1d_array<float4, image_access::sample> _d1af4r,
                   image2d<float4, image_access::sample> _d2f4r,
                   image2d_array<float4, image_access::sample> _d2af4r,
                   image2d_depth<float, image_access::sample> _d2df1r,
                   image2d_array_depth<float, image_access::sample> _d2adf1r,
                   image3d<float4, image_access::sample> _d3f4r,
                   sampler s)
{
    float4 _d1af4r_rf4f1 = _d1af4r.sample(s, float{0});
    float4 _d2f4r_rf4f1 = _d2f4r.sample(s, float{0});
    float4 _d2af4r_rf4f1 = _d2af4r.sample(s, float{0});
    float4 _d2df1r_rf4f1 = _d2df1r.sample(s, float{0});
    float4 _d2adf1r_rf4f1 = _d2adf1r.sample(s, float{0});
    float4 _d3f4r_rf4f1 = _d3f4r.sample(s, int{0});

    // CHECK: __spirv_ImageSampleExplicitLod
}