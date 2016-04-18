// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable -Dcl_khr_gl_msaa_sharing -Dcl_khr_gl_depth_images -Dcl_khr_mipmap_image -Dcl_khr_mipmap_image_writes -O0 -emit-llvm -o -
// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable -Dcl_khr_gl_msaa_sharing -Dcl_khr_gl_depth_images -Dcl_khr_mipmap_image -Dcl_khr_mipmap_image_writes -O3 -emit-llvm -o -
// RUN: %clang_cc1 %s -triple spir64-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable -Dcl_khr_gl_msaa_sharing -Dcl_khr_gl_depth_images -Dcl_khr_mipmap_image -Dcl_khr_mipmap_image_writes -O0 -emit-llvm -o -
// RUN: %clang_cc1 %s -triple spir64-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -cl-fp16-enable -cl-fp64-enable -Dcl_khr_gl_msaa_sharing -Dcl_khr_gl_depth_images -Dcl_khr_mipmap_image -Dcl_khr_mipmap_image_writes -O3 -emit-llvm -o -
// expected-no-diagnostics

#include <opencl_image>
using namespace cl;

kernel void worker(image1d<float4, image_access::read> d1,
                    image1d_array<float4, image_access::read> d1a,
                    image1d_buffer<float4, image_access::read> d1_b,
                    image2d<float4, image_access::read> d2,
                    image2d_array<float4, image_access::read> d2a,
                    image2d_depth<float, image_access::read> d2d,
                    image2d_array_depth<float, image_access::read> d2ad,
                    image3d<float4, image_access::read> d3,
                    image2d_ms<float4, image_access::read> d1_ms,
                    image2d_array_ms<float4, image_access::read> d2a_ms,
                    image2d_depth_ms<float, image_access::read> d2d_ms,
                    image2d_array_depth_ms<float, image_access::read> d2ad_ms)
{
    // CHECK: cl::__details::__image_helper<float __attribute__((ext_vector_type(4))), cl::image_access::read, cl::image_dim::image_1d, false, false, false>
    // CHECK: cl::__details::__image_helper<float __attribute__((ext_vector_type(4))), cl::image_access::read, cl::image_dim::image_1d, false, true, false>
    // CHECK: cl::__details::__image_helper<float __attribute__((ext_vector_type(4))), cl::image_access::read, cl::image_dim::image_buffer, false, false, false>
    // CHECK: cl::__details::__image_helper<float __attribute__((ext_vector_type(4))), cl::image_access::read, cl::image_dim::image_2d, false, false, false>
    // CHECK: cl::__details::__image_helper<float __attribute__((ext_vector_type(4))), cl::image_access::read, cl::image_dim::image_2d, false, true, false>
    // CHECK: cl::__details::__image_helper<float, cl::image_access::read, cl::image_dim::image_2d, true, false, false>
    // CHECK: cl::__details::__image_helper<float, cl::image_access::read, cl::image_dim::image_2d, true, true, false>
    // CHECK: cl::__details::__image_helper<float __attribute__((ext_vector_type(4))), cl::image_access::read, cl::image_dim::image_3d, true, false, false>

    // CHECK: cl::__details::__image_helper<float __attribute__((ext_vector_type(4))), cl::image_access::read, cl::image_dim::image_2d, false, false, true>
    // CHECK: cl::__details::__image_helper<float __attribute__((ext_vector_type(4))), cl::image_access::read, cl::image_dim::image_2d, false, true, true>
    // CHECK: cl::__details::__image_helper<float, cl::image_access::read, cl::image_dim::image_2d, true, false, true>
    // CHECK: cl::__details::__image_helper<float, cl::image_access::read, cl::image_dim::image_2d, true, true, true>
}