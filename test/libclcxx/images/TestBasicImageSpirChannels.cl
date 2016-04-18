// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable -Dcl_khr_gl_msaa_sharing -Dcl_khr_gl_depth_images -Dcl_khr_mipmap_image -Dcl_khr_mipmap_image_writes -O0 -emit-llvm -o -
// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable -Dcl_khr_gl_msaa_sharing -Dcl_khr_gl_depth_images -Dcl_khr_mipmap_image -Dcl_khr_mipmap_image_writes -O3 -emit-llvm -o -
// RUN: %clang_cc1 %s -triple spir64-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable -Dcl_khr_gl_msaa_sharing -Dcl_khr_gl_depth_images -Dcl_khr_mipmap_image -Dcl_khr_mipmap_image_writes -O0 -emit-llvm -o -
// RUN: %clang_cc1 %s -triple spir64-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable -Dcl_khr_gl_msaa_sharing -Dcl_khr_gl_depth_images -Dcl_khr_mipmap_image -Dcl_khr_mipmap_image_writes -O3 -emit-llvm -o -
// expected-no-diagnostics

#include <opencl_image>
using namespace cl;

kernel void worker(image1d<float4, image_access::read> _d1f4r)
{
    image_channel_order _d1f4r_co = _d1f4r.order();
    image_channel_type _d1f4r_ct = _d1f4r.data_type();

    // CHECK-DAG: call spir_func i32 {{.*}}__spirv_ImageQueryOrder
    // CHECK-DAG: call spir_func i32 {{.*}}__spirv_ImageQueryFormat
}