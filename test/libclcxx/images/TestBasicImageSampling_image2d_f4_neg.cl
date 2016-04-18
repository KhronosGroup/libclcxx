// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// XFAIL: *

#define cl_khr_mipmap_image 1
#include <opencl_image>
using namespace cl; 

kernel void worker(sampler s, image2d<float4, image_access::read> _d2f4r, image2d<float4, image_access::write> _d2f4w, image2d<float4, image_access::read_write> _d2f4rw, image2d<float4, image_access::sample> _d2f4s)
{     float4 _d2f4r_sf4f1 = _d2f4r.sample(s, float{0});         //BAD QUALIFIER
    float4 _d2f4r_sf4f1_l = _d2f4r.sample(s, float{0}, 0.7);  //BAD QUALIFIER
    float4 _d2f4w_sf4f1 = _d2f4w.sample(s, float{0});         //BAD QUALIFIER
    float4 _d2f4w_sf4f1_l = _d2f4w.sample(s, float{0}, 0.7);  //BAD QUALIFIER
    float4 _d2f4rw_sf4f1 = _d2f4rw.sample(s, float{0});         //BAD QUALIFIER
    float4 _d2f4rw_sf4f1_l = _d2f4rw.sample(s, float{0}, 0.7);  //BAD QUALIFIER
    float4 _d2f4s_sf4f3 = _d2f4s.sample(s, float3{0, 0, 0});         //BAD COORDS TYPE
    float4 _d2f4s_sf4f3_l = _d2f4s.sample(s, float3{0, 0, 0}, 0.7);  //BAD COORDS TYPE
    int4 _d2f4s_si4f1 = _d2f4s.sample(s, float{0});         //BAD INOUT TYPE
    int4 _d2f4s_si4f1_l = _d2f4s.sample(s, float{0}, 0.7);  //BAD INOUT TYPE
}
