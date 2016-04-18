// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// XFAIL:*

#include <opencl_image>
using namespace cl;

kernel void worker()
{
    static sampler s = make_sampler<addressing_mode::mirrored_repeat, normalized_coordinates::normalized, filtering_mode::nearest>();
    static sampler s2 = make_sampler<addressing_mode::mirrored_repeat, normalized_coordinates::normalized, filtering_mode::nearest>();
    s = s2;
}
