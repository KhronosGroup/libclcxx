// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// XFAIL: *

#define cl_khr_mipmap_image 1
#include <opencl_image>
using namespace cl; 

kernel void worker(sampler s, image1d_array<uint4, image_access::read> _d1au4r, image1d_array<uint4, image_access::write> _d1au4w, image1d_array<uint4, image_access::read_write> _d1au4rw, image1d_array<uint4, image_access::sample> _d1au4s)
{     float4 _d1au4r_sf4f1 = _d1au4r.sample(s, float{0});         //BAD QUALIFIER
    float4 _d1au4r_sf4f1_l = _d1au4r.sample(s, float{0}, 0.7);  //BAD QUALIFIER
    float4 _d1au4w_sf4f1 = _d1au4w.sample(s, float{0});         //BAD QUALIFIER
    float4 _d1au4w_sf4f1_l = _d1au4w.sample(s, float{0}, 0.7);  //BAD QUALIFIER
    float4 _d1au4rw_sf4f1 = _d1au4rw.sample(s, float{0});         //BAD QUALIFIER
    float4 _d1au4rw_sf4f1_l = _d1au4rw.sample(s, float{0}, 0.7);  //BAD QUALIFIER
    float4 _d1au4s_sf4f1 = _d1au4s.sample(s, float{0});         //BAD INOUT TYPE
    float4 _d1au4s_sf4f1_l = _d1au4s.sample(s, float{0}, 0.7);  //BAD INOUT TYPE
    uint4 _d1au4s_su4f3 = _d1au4s.sample(s, float3{0, 0, 0});         //BAD COORDS TYPE
    uint4 _d1au4s_su4f3_l = _d1au4s.sample(s, float3{0, 0, 0}, 0.7);  //BAD COORDS TYPE
}
