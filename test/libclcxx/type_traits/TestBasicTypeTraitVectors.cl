// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_type_traits>
using namespace cl;

#define validate(exp) static_assert(exp, "Fail")
#define check_type(typea, typeb) static_assert(is_same<typea, typeb>::value, "Fail")

struct foo { int a, b; };

check_type(vector_element_t<float4>, float);
check_type(vector_element_t<uint2>, uint);
check_type(vector_element_t<char>, char);

check_type(vector_element_t<foo>, foo);

check_type(vector_element_t<const float4>, const float);
check_type(vector_element_t<volatile float4>, volatile float);
check_type(vector_element_t<const volatile float4>, const volatile float);

check_type(vector_element_t<const float4&>, const float);
check_type(vector_element_t<volatile float4&>, volatile float);
check_type(vector_element_t<const volatile float4&>, const volatile float);

validate(vector_size<float>::value == 1);
validate(vector_size<float2>::value == 2);
validate(vector_size<float3>::value == 3);
validate(vector_size<float4>::value == 4);
validate(vector_size<float8>::value == 8);
validate(vector_size<float16>::value == 16);

validate(vector_size<foo>::value == 1);
validate(vector_size<const uint4>::value == 4);
validate(vector_size<volatile uint4>::value == 4);
validate(vector_size<const volatile uint4>::value == 4);
validate(vector_size<uint2&>::value == 2);
validate(vector_size<const uint2&>::value == 2);

static_assert(is_same<make_vector_t<float,4>, float4>::value, "");
static_assert(is_same<make_vector_t<uint,2>, uint2>::value, "");
static_assert(is_same<make_vector_t<int,7>, int>::value, "");
static_assert(is_same<make_vector_t<foo,2>, foo>::value, "");
static_assert(is_same<make_vector_t<const float, 3>, const float3>::value, "");
static_assert(is_same<make_vector_t<volatile float, 3>, volatile float3>::value, "");
static_assert(is_same<make_vector_t<const volatile float, 3>, const volatile float3>::value, "");

static_assert(is_same<make_vector_t<float&, 3>, float3>::value, "");
static_assert(is_same<make_vector_t<float const&, 3>, const float3>::value, "");
static_assert(is_same<make_vector_t<volatile float&, 3>, volatile float3>::value, "");
static_assert(is_same<make_vector_t<const volatile float, 3>, const volatile float3>::value, "");
static_assert(is_same<make_vector_t<const uchar, 2>, const uchar2>::value, "");

static_assert(is_same<make_vector_t<char, 2>, char2>::value, "");
//static_assert(is_same<make_vector_t<signed char, 2>, char2>::value, "");
static_assert(is_same<make_vector_t<signed int, 3>, int3>::value, "");

static_assert(is_same<make_vector_t<foo, 2>, foo>::value, "");
static_assert(is_same<make_vector_t<const volatile foo&, 12>, const volatile foo>::value, "");

validate(is_signed<int3>::value);
validate(!is_signed<uint2>::value);
validate(is_unsigned<uchar16>::value);
validate(!is_unsigned<float2>::value);
validate(is_signed<float2>::value);
validate(is_integral<short3>::value);
validate(is_integral<ulong8>::value);
validate(!is_integral<half4>::value);
validate(is_floating_point<half16>::value);
validate(is_floating_point<float3>::value);
validate(!is_floating_point<bool3>::value);

check_type(make_signed_t<int2>, int2);
check_type(make_signed_t<uint2>, int2);
check_type(make_signed_t<const uchar2>, const char2);

check_type(make_unsigned_t<int2>, uint2);
check_type(make_unsigned_t<uint2>, uint2);
check_type(make_unsigned_t<const volatile uchar2>, const volatile uchar2);

kernel void worker()
{
}

