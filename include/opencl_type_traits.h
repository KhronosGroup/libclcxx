#pragma OPENCL EXTENSION __cl_clang_function_pointers : enable
#pragma OPENCL EXTENSION __cl_clang_variadic_functions : enable
#include <type_traits>
#pragma OPENCL EXTENSION __cl_clang_function_pointers : disable
#pragma OPENCL EXTENSION __cl_clang_variadic_functions : disable

template<typename T>
struct is_signed : public std::false_type {};

template<>
struct is_signed<int2> : public std::true_type {};
template<>
struct is_signed<int3> : public std::true_type {};
template<>
struct is_signed<int4> : public std::true_type {};
template<>
struct is_signed<int8> : public std::true_type {};
template<>
struct is_signed<int16> : public std::true_type {};

template<>
struct is_signed<char2> : public std::true_type {};
template<>
struct is_signed<char3> : public std::true_type {};
template<>
struct is_signed<char4> : public std::true_type {};
template<>
struct is_signed<char8> : public std::true_type {};
template<>
struct is_signed<char16> : public std::true_type {};

template<>
struct is_signed<short2> : public std::true_type {};
template<>
struct is_signed<short3> : public std::true_type {};
template<>
struct is_signed<short4> : public std::true_type {};
template<>
struct is_signed<short8> : public std::true_type {};
template<>
struct is_signed<short16> : public std::true_type {};

template<>
struct is_signed<long2> : public std::true_type {};
template<>
struct is_signed<long3> : public std::true_type {};
template<>
struct is_signed<long4> : public std::true_type {};
template<>
struct is_signed<long8> : public std::true_type {};
template<>
struct is_signed<long16> : public std::true_type {};

template<>
struct is_signed<float2> : public std::true_type {};
template<>
struct is_signed<float3> : public std::true_type {};
template<>
struct is_signed<float4> : public std::true_type {};
template<>
struct is_signed<float8> : public std::true_type {};
template<>
struct is_signed<float16> : public std::true_type {};

template<>
struct is_signed<double2> : public std::true_type {};
template<>
struct is_signed<double3> : public std::true_type {};
template<>
struct is_signed<double4> : public std::true_type {};
template<>
struct is_signed<double8> : public std::true_type {};
template<>
struct is_signed<double16> : public std::true_type {};


template<typename T>
struct is_unsigned : public std::false_type {};

template<>
struct is_unsigned<uint2> : public std::true_type {};
template<>
struct is_unsigned<uint3> : public std::true_type {};
template<>
struct is_unsigned<uint4> : public std::true_type {};
template<>
struct is_unsigned<uint8> : public std::true_type {};
template<>
struct is_unsigned<uint16> : public std::true_type {};

template<>
struct is_unsigned<uchar2> : public std::true_type {};
template<>
struct is_unsigned<uchar3> : public std::true_type {};
template<>
struct is_unsigned<uchar4> : public std::true_type {};
template<>
struct is_unsigned<uchar8> : public std::true_type {};
template<>
struct is_unsigned<uchar16> : public std::true_type {};

template<>
struct is_unsigned<ushort2> : public std::true_type {};
template<>
struct is_unsigned<ushort3> : public std::true_type {};
template<>
struct is_unsigned<ushort4> : public std::true_type {};
template<>
struct is_unsigned<ushort8> : public std::true_type {};
template<>
struct is_unsigned<ushort16> : public std::true_type {};

template<>
struct is_unsigned<ulong2> : public std::true_type {};
template<>
struct is_unsigned<ulong3> : public std::true_type {};
template<>
struct is_unsigned<ulong4> : public std::true_type {};
template<>
struct is_unsigned<ulong8> : public std::true_type {};
template<>
struct is_unsigned<ulong16> : public std::true_type {};


template<typename T>
struct make_signed {typedef T type;};

template<>
struct make_signed<uint2> {typedef int2 type;};
template<>
struct make_signed<uint3> {typedef int3 type;};
template<>
struct make_signed<uint4> {typedef int4 type;};
template<>
struct make_signed<uint8> {typedef int8 type;};
template<>
struct make_signed<uint16> {typedef int16 type;};

template<>
struct make_signed<uchar2> {typedef char2 type;};
template<>
struct make_signed<uchar3> {typedef char3 type;};
template<>
struct make_signed<uchar4> {typedef char4 type;};
template<>
struct make_signed<uchar8> {typedef char8 type;};
template<>
struct make_signed<uchar16> {typedef char16 type;};

template<>
struct make_signed<ushort2> {typedef short2 type;};
template<>
struct make_signed<ushort3> {typedef short3 type;};
template<>
struct make_signed<ushort4> {typedef short4 type;};
template<>
struct make_signed<ushort8> {typedef short8 type;};
template<>
struct make_signed<ushort16> {typedef short16 type;};

template<>
struct make_signed<ulong2> {typedef long2 type;};
template<>
struct make_signed<ulong3> {typedef long3 type;};
template<>
struct make_signed<ulong4> {typedef long4 type;};
template<>
struct make_signed<ulong8> {typedef long8 type;};
template<>
struct make_signed<ulong16> {typedef long16 type;};


template<typename T>
struct make_unsigned {typedef T type;};

template<>
struct make_unsigned<int2> {typedef uint2 type;};
template<>
struct make_unsigned<int3> {typedef uint3 type;};
template<>
struct make_unsigned<int4> {typedef uint4 type;};
template<>
struct make_unsigned<int8> {typedef uint8 type;};
template<>
struct make_unsigned<int16> {typedef uint16 type;};

template<>
struct make_unsigned<char2> {typedef uchar2 type;};
template<>
struct make_unsigned<char3> {typedef uchar3 type;};
template<>
struct make_unsigned<char4> {typedef uchar4 type;};
template<>
struct make_unsigned<char8> {typedef uchar8 type;};
template<>
struct make_unsigned<char16> {typedef uchar16 type;};

template<>
struct make_unsigned<short2> {typedef ushort2 type;};
template<>
struct make_unsigned<short3> {typedef ushort3 type;};
template<>
struct make_unsigned<short4> {typedef ushort4 type;};
template<>
struct make_unsigned<short8> {typedef ushort8 type;};
template<>
struct make_unsigned<short16> {typedef ushort16 type;};

template<>
struct make_unsigned<long2> {typedef ulong2 type;};
template<>
struct make_unsigned<long3> {typedef ulong3 type;};
template<>
struct make_unsigned<long4> {typedef ulong4 type;};
template<>
struct make_unsigned<long8> {typedef ulong8 type;};
template<>
struct make_unsigned<long16> {typedef ulong16 type;};


template<typename T>
struct is_vector_type : public std::false_type {};

template<>
struct is_vector_type<int2> : public std::true_type {};
template<>
struct is_vector_type<int3> : public std::true_type {};
template<>
struct is_vector_type<int4> : public std::true_type {};
template<>
struct is_vector_type<int8> : public std::true_type {};
template<>
struct is_vector_type<int16> : public std::true_type {};

template<>
struct is_vector_type<uint2> : public std::true_type {};
template<>
struct is_vector_type<uint3> : public std::true_type {};
template<>
struct is_vector_type<uint4> : public std::true_type {};
template<>
struct is_vector_type<uint8> : public std::true_type {};
template<>
struct is_vector_type<uint16> : public std::true_type {};

template<>
struct is_vector_type<char2> : public std::true_type {};
template<>
struct is_vector_type<char3> : public std::true_type {};
template<>
struct is_vector_type<char4> : public std::true_type {};
template<>
struct is_vector_type<char8> : public std::true_type {};
template<>
struct is_vector_type<char16> : public std::true_type {};

template<>
struct is_vector_type<uchar2> : public std::true_type {};
template<>
struct is_vector_type<uchar3> : public std::true_type {};
template<>
struct is_vector_type<uchar4> : public std::true_type {};
template<>
struct is_vector_type<uchar8> : public std::true_type {};
template<>
struct is_vector_type<uchar16> : public std::true_type {};

template<>
struct is_vector_type<short2> : public std::true_type {};
template<>
struct is_vector_type<short3> : public std::true_type {};
template<>
struct is_vector_type<short4> : public std::true_type {};
template<>
struct is_vector_type<short8> : public std::true_type {};
template<>
struct is_vector_type<short16> : public std::true_type {};

template<>
struct is_vector_type<ushort2> : public std::true_type {};
template<>
struct is_vector_type<ushort3> : public std::true_type {};
template<>
struct is_vector_type<ushort4> : public std::true_type {};
template<>
struct is_vector_type<ushort8> : public std::true_type {};
template<>
struct is_vector_type<ushort16> : public std::true_type {};

template<>
struct is_vector_type<long2> : public std::true_type {};
template<>
struct is_vector_type<long3> : public std::true_type {};
template<>
struct is_vector_type<long4> : public std::true_type {};
template<>
struct is_vector_type<long8> : public std::true_type {};
template<>
struct is_vector_type<long16> : public std::true_type {};

template<>
struct is_vector_type<ulong2> : public std::true_type {};
template<>
struct is_vector_type<ulong3> : public std::true_type {};
template<>
struct is_vector_type<ulong4> : public std::true_type {};
template<>
struct is_vector_type<ulong8> : public std::true_type {};
template<>
struct is_vector_type<ulong16> : public std::true_type {};

template<>
struct is_vector_type<float2> : public std::true_type {};
template<>
struct is_vector_type<float3> : public std::true_type {};
template<>
struct is_vector_type<float4> : public std::true_type {};
template<>
struct is_vector_type<float8> : public std::true_type {};
template<>
struct is_vector_type<float16> : public std::true_type {};

template<>
struct is_vector_type<double2> : public std::true_type {};
template<>
struct is_vector_type<double3> : public std::true_type {};
template<>
struct is_vector_type<double4> : public std::true_type {};
template<>
struct is_vector_type<double8> : public std::true_type {};
template<>
struct is_vector_type<double16> : public std::true_type {};


template<typename T>
struct vector_size : public std::integral_constant<size_t, 0> {}; //Set to 0 for non vector inputs

template<>
struct vector_size<int2> : public std::integral_constant<size_t, 2> {};
template<>
struct vector_size<int3> : public std::integral_constant<size_t, 3> {};
template<>
struct vector_size<int4> : public std::integral_constant<size_t, 4> {};
template<>
struct vector_size<int8> : public std::integral_constant<size_t, 8> {};
template<>
struct vector_size<int16> : public std::integral_constant<size_t, 16> {};

template<>
struct vector_size<uint2> : public std::integral_constant<size_t, 2> {};
template<>
struct vector_size<uint3> : public std::integral_constant<size_t, 3> {};
template<>
struct vector_size<uint4> : public std::integral_constant<size_t, 4> {};
template<>
struct vector_size<uint8> : public std::integral_constant<size_t, 8> {};
template<>
struct vector_size<uint16> : public std::integral_constant<size_t, 16> {};

template<>
struct vector_size<char2> : public std::integral_constant<size_t, 2> {};
template<>
struct vector_size<char3> : public std::integral_constant<size_t, 3> {};
template<>
struct vector_size<char4> : public std::integral_constant<size_t, 4> {};
template<>
struct vector_size<char8> : public std::integral_constant<size_t, 8> {};
template<>
struct vector_size<char16> : public std::integral_constant<size_t, 16> {};

template<>
struct vector_size<uchar2> : public std::integral_constant<size_t, 2> {};
template<>
struct vector_size<uchar3> : public std::integral_constant<size_t, 3> {};
template<>
struct vector_size<uchar4> : public std::integral_constant<size_t, 4> {};
template<>
struct vector_size<uchar8> : public std::integral_constant<size_t, 8> {};
template<>
struct vector_size<uchar16> : public std::integral_constant<size_t, 16> {};

template<>
struct vector_size<short2> : public std::integral_constant<size_t, 2> {};
template<>
struct vector_size<short3> : public std::integral_constant<size_t, 3> {};
template<>
struct vector_size<short4> : public std::integral_constant<size_t, 4> {};
template<>
struct vector_size<short8> : public std::integral_constant<size_t, 8> {};
template<>
struct vector_size<short16> : public std::integral_constant<size_t, 16> {};

template<>
struct vector_size<ushort2> : public std::integral_constant<size_t, 2> {};
template<>
struct vector_size<ushort3> : public std::integral_constant<size_t, 3> {};
template<>
struct vector_size<ushort4> : public std::integral_constant<size_t, 4> {};
template<>
struct vector_size<ushort8> : public std::integral_constant<size_t, 8> {};
template<>
struct vector_size<ushort16> : public std::integral_constant<size_t, 16> {};

template<>
struct vector_size<long2> : public std::integral_constant<size_t, 2> {};
template<>
struct vector_size<long3> : public std::integral_constant<size_t, 3> {};
template<>
struct vector_size<long4> : public std::integral_constant<size_t, 4> {};
template<>
struct vector_size<long8> : public std::integral_constant<size_t, 8> {};
template<>
struct vector_size<long16> : public std::integral_constant<size_t, 16> {};

template<>
struct vector_size<ulong2> : public std::integral_constant<size_t, 2> {};
template<>
struct vector_size<ulong3> : public std::integral_constant<size_t, 3> {};
template<>
struct vector_size<ulong4> : public std::integral_constant<size_t, 4> {};
template<>
struct vector_size<ulong8> : public std::integral_constant<size_t, 8> {};
template<>
struct vector_size<ulong16> : public std::integral_constant<size_t, 16> {};

template<>
struct vector_size<float2> : public std::integral_constant<size_t, 2> {};
template<>
struct vector_size<float3> : public std::integral_constant<size_t, 3> {};
template<>
struct vector_size<float4> : public std::integral_constant<size_t, 4> {};
template<>
struct vector_size<float8> : public std::integral_constant<size_t, 8> {};
template<>
struct vector_size<float16> : public std::integral_constant<size_t, 16> {};

template<>
struct vector_size<double2> : public std::integral_constant<size_t, 2> {};
template<>
struct vector_size<double3> : public std::integral_constant<size_t, 3> {};
template<>
struct vector_size<double4> : public std::integral_constant<size_t, 4> {};
template<>
struct vector_size<double8> : public std::integral_constant<size_t, 8> {};
template<>
struct vector_size<double16> : public std::integral_constant<size_t, 16> {};


template<typename T>
struct scalar_type {typedef T type;};

template<>
struct scalar_type<int2> {typedef int type;};
template<>
struct scalar_type<int3> {typedef int type;};
template<>
struct scalar_type<int4> {typedef int type;};
template<>
struct scalar_type<int8> {typedef int type;};
template<>
struct scalar_type<int16> {typedef int type;};

template<>
struct scalar_type<uint2> {typedef uint type;};
template<>
struct scalar_type<uint3> {typedef uint type;};
template<>
struct scalar_type<uint4> {typedef uint type;};
template<>
struct scalar_type<uint8> {typedef uint type;};
template<>
struct scalar_type<uint16> {typedef uint type;};

template<>
struct scalar_type<char2> {typedef char type;};
template<>
struct scalar_type<char3> {typedef char type;};
template<>
struct scalar_type<char4> {typedef char type;};
template<>
struct scalar_type<char8> {typedef char type;};
template<>
struct scalar_type<char16> {typedef char type;};

template<>
struct scalar_type<uchar2> {typedef uchar type;};
template<>
struct scalar_type<uchar3> {typedef uchar type;};
template<>
struct scalar_type<uchar4> {typedef uchar type;};
template<>
struct scalar_type<uchar8> {typedef uchar type;};
template<>
struct scalar_type<uchar16> {typedef uchar type;};

template<>
struct scalar_type<short2> {typedef short type;};
template<>
struct scalar_type<short3> {typedef short type;};
template<>
struct scalar_type<short4> {typedef short type;};
template<>
struct scalar_type<short8> {typedef short type;};
template<>
struct scalar_type<short16> {typedef short type;};

template<>
struct scalar_type<ushort2> {typedef ushort type;};
template<>
struct scalar_type<ushort3> {typedef ushort type;};
template<>
struct scalar_type<ushort4> {typedef ushort type;};
template<>
struct scalar_type<ushort8> {typedef ushort type;};
template<>
struct scalar_type<ushort16> {typedef ushort type;};

template<>
struct scalar_type<long2> {typedef long type;};
template<>
struct scalar_type<long3> {typedef long type;};
template<>
struct scalar_type<long4> {typedef long type;};
template<>
struct scalar_type<long8> {typedef long type;};
template<>
struct scalar_type<long16> {typedef long type;};

template<>
struct scalar_type<ulong2> {typedef ulong type;};
template<>
struct scalar_type<ulong3> {typedef ulong type;};
template<>
struct scalar_type<ulong4> {typedef ulong type;};
template<>
struct scalar_type<ulong8> {typedef ulong type;};
template<>
struct scalar_type<ulong16> {typedef ulong type;};

template<>
struct scalar_type<float2> {typedef float type;};
template<>
struct scalar_type<float3> {typedef float type;};
template<>
struct scalar_type<float4> {typedef float type;};
template<>
struct scalar_type<float8> {typedef float type;};
template<>
struct scalar_type<float16> {typedef float type;};

template<>
struct scalar_type<double2> {typedef double type;};
template<>
struct scalar_type<double3> {typedef double type;};
template<>
struct scalar_type<double4> {typedef double type;};
template<>
struct scalar_type<double8> {typedef double type;};
template<>
struct scalar_type<double16> {typedef double type;};


template<typename T, unsigned N>
struct vector_n {typedef void type;};

template<>
struct vector_n<int, 2> {typedef int2 type;};
template<>
struct vector_n<int, 3> {typedef int3 type;};
template<>
struct vector_n<int, 4> {typedef int4 type;};
template<>
struct vector_n<int, 8> {typedef int8 type;};
template<>
struct vector_n<int, 16> {typedef int16 type;};

template<>
struct vector_n<uint, 2> {typedef uint2 type;};
template<>
struct vector_n<uint, 3> {typedef uint3 type;};
template<>
struct vector_n<uint, 4> {typedef uint4 type;};
template<>
struct vector_n<uint, 8> {typedef uint8 type;};
template<>
struct vector_n<uint, 16> {typedef uint16 type;};

template<>
struct vector_n<char, 2> {typedef char2 type;};
template<>
struct vector_n<char, 3> {typedef char3 type;};
template<>
struct vector_n<char, 4> {typedef char4 type;};
template<>
struct vector_n<char, 8> {typedef char8 type;};
template<>
struct vector_n<char, 16> {typedef char16 type;};

template<>
struct vector_n<uchar, 2> {typedef uchar2 type;};
template<>
struct vector_n<uchar, 3> {typedef uchar3 type;};
template<>
struct vector_n<uchar, 4> {typedef uchar4 type;};
template<>
struct vector_n<uchar, 8> {typedef uchar8 type;};
template<>
struct vector_n<uchar, 16> {typedef uchar16 type;};

template<>
struct vector_n<short, 2> {typedef short2 type;};
template<>
struct vector_n<short, 3> {typedef short3 type;};
template<>
struct vector_n<short, 4> {typedef short4 type;};
template<>
struct vector_n<short, 8> {typedef short8 type;};
template<>
struct vector_n<short, 16> {typedef short16 type;};

template<>
struct vector_n<ushort, 2> {typedef ushort2 type;};
template<>
struct vector_n<ushort, 3> {typedef ushort3 type;};
template<>
struct vector_n<ushort, 4> {typedef ushort4 type;};
template<>
struct vector_n<ushort, 8> {typedef ushort8 type;};
template<>
struct vector_n<ushort, 16> {typedef ushort16 type;};

template<>
struct vector_n<long, 2> {typedef long2 type;};
template<>
struct vector_n<long, 3> {typedef long3 type;};
template<>
struct vector_n<long, 4> {typedef long4 type;};
template<>
struct vector_n<long, 8> {typedef long8 type;};
template<>
struct vector_n<long, 16> {typedef long16 type;};

template<>
struct vector_n<ulong, 2> {typedef ulong2 type;};
template<>
struct vector_n<ulong, 3> {typedef ulong3 type;};
template<>
struct vector_n<ulong, 4> {typedef ulong4 type;};
template<>
struct vector_n<ulong, 8> {typedef ulong8 type;};
template<>
struct vector_n<ulong, 16> {typedef ulong16 type;};

template<>
struct vector_n<float, 2> {typedef float2 type;};
template<>
struct vector_n<float, 3> {typedef float3 type;};
template<>
struct vector_n<float, 4> {typedef float4 type;};
template<>
struct vector_n<float, 8> {typedef float8 type;};
template<>
struct vector_n<float, 16> {typedef float16 type;};

template<>
struct vector_n<double, 2> {typedef double2 type;};
template<>
struct vector_n<double, 3> {typedef double3 type;};
template<>
struct vector_n<double, 4> {typedef double4 type;};
template<>
struct vector_n<double, 8> {typedef double8 type;};
template<>
struct vector_n<double, 16> {typedef double16 type;};


template<typename T>
struct add_generic {typedef __generic T type;};
template<typename T>
struct add_global {typedef __global T type;};
template<typename T>
struct add_private {typedef __private T type;};
template<typename T>
struct add_local {typedef __local T type;};
template<typename T>
struct add_constant {typedef __constant T type;};


template<typename T>
struct has_address_space : public std::false_type {};

template<typename T>
struct has_address_space<__generic T> : public std::true_type {};
template<typename T>
struct has_address_space<__global T> : public std::true_type {};
template<typename T>
struct has_address_space<__private T> : public std::true_type {};
template<typename T>
struct has_address_space<__local T> : public std::true_type {};
template<typename T>
struct has_address_space<__constant T> : public std::true_type {};


template<typename T>
struct is_generic : public std::false_type {};
template<typename T>
struct is_generic<__generic T> : public std::true_type {};

template<typename T>
struct is_global : public std::false_type {};
template<typename T>
struct is_global<__global T> : public std::true_type {};

template<typename T>
struct is_private : public std::false_type {};
template<typename T>
struct is_private<__private T> : public std::true_type {};

template<typename T>
struct is_local : public std::false_type {};
template<typename T>
struct is_local<__local T> : public std::true_type {};

template<typename T>
struct is_constant : public std::false_type {};
template<typename T>
struct is_constant<__constant T> : public std::true_type {};


template<typename T>
struct remove_address_space {typedef T type;};

template<typename T>
struct remove_address_space<__generic T> {typedef T type;};
template<typename T>
struct remove_address_space<__global T> {typedef T type;};
template<typename T>
struct remove_address_space<__private T> {typedef T type;};
template<typename T>
struct remove_address_space<__local T> {typedef T type;};
template<typename T>
struct remove_address_space<__constant T> {typedef T type;};
