// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// XFAIL: *

#define cl_khr_mipmap_image 1
#include <opencl_image>
using namespace cl; 

kernel void worker(sampler s, image1d<float4, image_access::read> _d1f4r, image1d<float4, image_access::write> _d1f4w, image1d<float4, image_access::read_write> _d1f4rw, image1d<float4, image_access::sample> _d1f4s)
{     float4 _d1f4r_sf4f1 = _d1f4r.sample(s, float{0});         //BAD QUALIFIER
    float4 _d1f4r_sf4f1_l = _d1f4r.sample(s, float{0}, 0.7);  //BAD QUALIFIER
    float4 _d1f4w_sf4f1 = _d1f4w.sample(s, float{0});         //BAD QUALIFIER
    float4 _d1f4w_sf4f1_l = _d1f4w.sample(s, float{0}, 0.7);  //BAD QUALIFIER
    float4 _d1f4rw_sf4f1 = _d1f4rw.sample(s, float{0});         //BAD QUALIFIER
    float4 _d1f4rw_sf4f1_l = _d1f4rw.sample(s, float{0}, 0.7);  //BAD QUALIFIER
    float4 _d1f4s_sf4f2 = _d1f4s.sample(s, float2{0, 0});         //BAD COORDS TYPE
    float4 _d1f4s_sf4f2_l = _d1f4s.sample(s, float2{0, 0}, 0.7);  //BAD COORDS TYPE
    int4 _d1f4s_si4f1 = _d1f4s.sample(s, float{0});         //BAD INOUT TYPE
    int4 _d1f4s_si4f1_l = _d1f4s.sample(s, float{0}, 0.7);  //BAD INOUT TYPE
}
