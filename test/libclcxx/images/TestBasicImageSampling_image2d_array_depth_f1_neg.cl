// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// XFAIL: *

#define cl_khr_mipmap_image 1
#include <opencl_image>
using namespace cl; 

kernel void worker(sampler s, image2d_array_depth<float, image_access::read> _d2adf1r, image2d_array_depth<float, image_access::write> _d2adf1w, image2d_array_depth<float, image_access::read_write> _d2adf1rw, image2d_array_depth<float, image_access::sample> _d2adf1s)
{     float4 _d2adf1r_sf4f1 = _d2adf1r.sample(s, float{0});         //BAD QUALIFIER
    float4 _d2adf1r_sf4f1_l = _d2adf1r.sample(s, float{0}, 0.7);  //BAD QUALIFIER
    float4 _d2adf1w_sf4f1 = _d2adf1w.sample(s, float{0});         //BAD QUALIFIER
    float4 _d2adf1w_sf4f1_l = _d2adf1w.sample(s, float{0}, 0.7);  //BAD QUALIFIER
    float4 _d2adf1rw_sf4f1 = _d2adf1rw.sample(s, float{0});         //BAD QUALIFIER
    float4 _d2adf1rw_sf4f1_l = _d2adf1rw.sample(s, float{0}, 0.7);  //BAD QUALIFIER
    float4 _d2adf1s_sf4f2 = _d2adf1s.sample(s, float2{0, 0});         //BAD COORDS TYPE
    float4 _d2adf1s_sf4f2_l = _d2adf1s.sample(s, float2{0, 0}, 0.7);  //BAD COORDS TYPE
}
