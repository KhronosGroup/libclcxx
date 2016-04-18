// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// XFAIL: *

#define cl_khr_mipmap_image 1
#include <opencl_image>
using namespace cl; 

kernel void worker(sampler s, image3d<float4, image_access::read> _d3f4r, image3d<float4, image_access::write> _d3f4w, image3d<float4, image_access::read_write> _d3f4rw, image3d<float4, image_access::sample> _d3f4s)
{     float4 _d3f4r_sf4f1 = _d3f4r.sample(s, float{0});         //BAD QUALIFIER
    float4 _d3f4r_sf4f1_l = _d3f4r.sample(s, float{0}, 0.7);  //BAD QUALIFIER
    float4 _d3f4w_sf4f1 = _d3f4w.sample(s, float{0});         //BAD QUALIFIER
    float4 _d3f4w_sf4f1_l = _d3f4w.sample(s, float{0}, 0.7);  //BAD QUALIFIER
    float4 _d3f4rw_sf4f1 = _d3f4rw.sample(s, float{0});         //BAD QUALIFIER
    float4 _d3f4rw_sf4f1_l = _d3f4rw.sample(s, float{0}, 0.7);  //BAD QUALIFIER
    float4 _d3f4s_sf4f2 = _d3f4s.sample(s, float2{0, 0});         //BAD COORDS TYPE
    float4 _d3f4s_sf4f2_l = _d3f4s.sample(s, float2{0, 0}, 0.7);  //BAD COORDS TYPE
    int4 _d3f4s_si4f1 = _d3f4s.sample(s, float{0});         //BAD INOUT TYPE
    int4 _d3f4s_si4f1_l = _d3f4s.sample(s, float{0}, 0.7);  //BAD INOUT TYPE
}
