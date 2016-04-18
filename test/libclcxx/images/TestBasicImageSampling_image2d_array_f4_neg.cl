// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// XFAIL: *

#define cl_khr_mipmap_image 1
#include <opencl_image>
using namespace cl; 

kernel void worker(sampler s, image2d_array<float4, image_access::read> _d2af4r, image2d_array<float4, image_access::write> _d2af4w, image2d_array<float4, image_access::read_write> _d2af4rw, image2d_array<float4, image_access::sample> _d2af4s)
{     float4 _d2af4r_sf4f1 = _d2af4r.sample(s, float{0});         //BAD QUALIFIER
    float4 _d2af4r_sf4f1_l = _d2af4r.sample(s, float{0}, 0.7);  //BAD QUALIFIER
    float4 _d2af4w_sf4f1 = _d2af4w.sample(s, float{0});         //BAD QUALIFIER
    float4 _d2af4w_sf4f1_l = _d2af4w.sample(s, float{0}, 0.7);  //BAD QUALIFIER
    float4 _d2af4rw_sf4f1 = _d2af4rw.sample(s, float{0});         //BAD QUALIFIER
    float4 _d2af4rw_sf4f1_l = _d2af4rw.sample(s, float{0}, 0.7);  //BAD QUALIFIER
    float4 _d2af4s_sf4f2 = _d2af4s.sample(s, float2{0, 0});         //BAD COORDS TYPE
    float4 _d2af4s_sf4f2_l = _d2af4s.sample(s, float2{0, 0}, 0.7);  //BAD COORDS TYPE
    int4 _d2af4s_si4f1 = _d2af4s.sample(s, float{0});         //BAD INOUT TYPE
    int4 _d2af4s_si4f1_l = _d2af4s.sample(s, float{0}, 0.7);  //BAD INOUT TYPE
}
