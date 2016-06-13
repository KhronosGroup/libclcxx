// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -O0 -emit-llvm  -o - | FileCheck %s
// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -O3 -emit-llvm  -o - | FileCheck %s
// expected-no-diagnostics
// CHECK-NOT: @llvm.global_ctors*
// CHECK-NOT: define spir_kernel void @_SPIRV_GLOBAL__I_{{(.*)}}

#include <opencl_image>
using namespace cl;

sampler s2 = make_sampler<addressing_mode::mirrored_repeat, normalized_coordinates::normalized, filtering_mode::nearest>();

kernel void worker()
{
    static sampler s = make_sampler<addressing_mode::mirrored_repeat, normalized_coordinates::normalized, filtering_mode::nearest>();
    addressing_mode am_mr  = addressing_mode::mirrored_repeat;
    addressing_mode am_r   = addressing_mode::repeat;
    addressing_mode am_cte = addressing_mode::clamp_to_edge;
    addressing_mode am_c   = addressing_mode::clamp;
    addressing_mode am_n   = addressing_mode::none;

    normalized_coordinates nc_n  = normalized_coordinates::normalized;
    normalized_coordinates nc_dn = normalized_coordinates::unnormalized;

    filtering_mode fm_n = filtering_mode::nearest;
    filtering_mode fm_l = filtering_mode::linear;
}
