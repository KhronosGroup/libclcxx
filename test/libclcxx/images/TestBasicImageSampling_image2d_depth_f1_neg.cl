// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// XFAIL: *

#define cl_khr_mipmap_image 1
#include <opencl_image>
using namespace cl; 

kernel void worker(sampler s, image2d_depth<float, image_access::read> _d2df1r, image2d_depth<float, image_access::write> _d2df1w, image2d_depth<float, image_access::read_write> _d2df1rw, image2d_depth<float, image_access::sample> _d2df1s)
{     float4 _d2df1r_sf4f1 = _d2df1r.sample(s, float{0});         //BAD QUALIFIER
    float4 _d2df1r_sf4f1_l = _d2df1r.sample(s, float{0}, 0.7);  //BAD QUALIFIER
    float4 _d2df1w_sf4f1 = _d2df1w.sample(s, float{0});         //BAD QUALIFIER
    float4 _d2df1w_sf4f1_l = _d2df1w.sample(s, float{0}, 0.7);  //BAD QUALIFIER
    float4 _d2df1rw_sf4f1 = _d2df1rw.sample(s, float{0});         //BAD QUALIFIER
    float4 _d2df1rw_sf4f1_l = _d2df1rw.sample(s, float{0}, 0.7);  //BAD QUALIFIER
    float4 _d2df1s_sf4f3 = _d2df1s.sample(s, float3{0, 0, 0});         //BAD COORDS TYPE
    float4 _d2df1s_sf4f3_l = _d2df1s.sample(s, float3{0, 0, 0}, 0.7);  //BAD COORDS TYPE
}
