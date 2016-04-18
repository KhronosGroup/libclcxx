// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// XFAIL: *

#define cl_khr_mipmap_image 1
#include <opencl_image>
using namespace cl; 

kernel void worker(sampler s, image3d<uint4, image_access::read> _d3u4r, image3d<uint4, image_access::write> _d3u4w, image3d<uint4, image_access::read_write> _d3u4rw, image3d<uint4, image_access::sample> _d3u4s)
{     float4 _d3u4r_sf4f1 = _d3u4r.sample(s, float{0});         //BAD QUALIFIER
    float4 _d3u4r_sf4f1_l = _d3u4r.sample(s, float{0}, 0.7);  //BAD QUALIFIER
    float4 _d3u4w_sf4f1 = _d3u4w.sample(s, float{0});         //BAD QUALIFIER
    float4 _d3u4w_sf4f1_l = _d3u4w.sample(s, float{0}, 0.7);  //BAD QUALIFIER
    float4 _d3u4rw_sf4f1 = _d3u4rw.sample(s, float{0});         //BAD QUALIFIER
    float4 _d3u4rw_sf4f1_l = _d3u4rw.sample(s, float{0}, 0.7);  //BAD QUALIFIER
    float4 _d3u4s_sf4f1 = _d3u4s.sample(s, float{0});         //BAD INOUT TYPE
    float4 _d3u4s_sf4f1_l = _d3u4s.sample(s, float{0}, 0.7);  //BAD INOUT TYPE
    uint4 _d3u4s_su4f2 = _d3u4s.sample(s, float2{0, 0});         //BAD COORDS TYPE
    uint4 _d3u4s_su4f2_l = _d3u4s.sample(s, float2{0, 0}, 0.7);  //BAD COORDS TYPE
}
