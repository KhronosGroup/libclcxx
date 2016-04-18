//
// Copyright (c) 2015-2016 The Khronos Group Inc.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and/or associated documentation files (the
// "Materials"), to deal in the Materials without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Materials, and to
// permit persons to whom the Materials are furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Materials.
//
// THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
//

#pragma once

#include <__ocl_config.h>
#include <__ocl_spirv_common_opcodes.h>
#include <opencl_type_traits>

#define MAKE_SPIRV_CONVERSION(spirv_name) \
    template <typename Ret, typename... Args> Ret spirv_name(Args...) __NOEXCEPT; \
    template <rounding_mode rmode, typename Ret, typename... Args> Ret spirv_name(Args...) __NOEXCEPT; \
    template <saturate smode, typename Ret, typename... Args> Ret spirv_name(Args...) __NOEXCEPT; \
    template <rounding_mode rmode, saturate smode, typename Ret, typename... Args> Ret spirv_name(Args...) __NOEXCEPT;

namespace cl
{

enum class rounding_mode    { rte, rtz, rtp, rtn };
enum class saturate         { off, on };

namespace __spirv
{
    MAKE_SPIRV_CALLABLE(OpINotEqual)

    MAKE_SPIRV_CONVERSION(OpConvertFToU)
    MAKE_SPIRV_CONVERSION(OpConvertFToS)
    MAKE_SPIRV_CONVERSION(OpConvertSToF)
    MAKE_SPIRV_CONVERSION(OpConvertUToF)
    MAKE_SPIRV_CONVERSION(OpUConvert)
    MAKE_SPIRV_CONVERSION(OpSConvert)
    MAKE_SPIRV_CONVERSION(OpFConvert)
    MAKE_SPIRV_CONVERSION(OpSatConvertUToS)
    MAKE_SPIRV_CONVERSION(OpSatConvertSToU)

    enum
    {
        SaturatedConversion = 28,
        FP_Rounding_Mode = 39
    };
}

/// \brief check if convert_cast is used to convert between types with matching elements count
///
#define _CHECK_VECTOR_SIZE static_assert(vector_size<To>::value == vector_size<From>::value, "convert_cast may be used only to convert between types with matching elements count")

/// \brief check if passed type can be used with convert_cast
///
#define _CHECK_TYPE(T) static_assert(is_integral<T>::value || is_floating_point<T>::value, \
    "convert_cast is avaliable for conversions between: (u)char, (u)short, (u)int, (u)long, float, half (if present), double (if present) and bool scalar and vector types.")

namespace __details
{
    /// \brief enum with possible conversion types, used by __choose_convert and __is_* structures.
    ///  any combination of these values OR-ed together should be outside of this enum
    ///
    enum __convert_type : ushort
    {
        uint_to_fp      = 0x001,
        sint_to_fp      = 0x002,
        fp_to_uint      = 0x004,
        fp_to_sint      = 0x008,
        uint_to_uint    = 0x010,
        sint_to_sint    = 0x020,
        fp_to_fp        = 0x040,
        sint_to_uint    = 0x080,
        uint_to_sint    = 0x100,
        bool_to_num     = 0x200,
        int_to_bool     = 0x400,
        fp_to_bool      = 0x800
    };

    /// \brief struct which provide '__make_call' wrapper function with call to appropriate spirv conversion instruction.
    ///   3rd parameter should map to one of __convert_type values, if it doesn't something has gone wrong in convert_cast function (probably type checking missed some case)
    ///   4th parameter is used to determinate if saturation is enabled for conversion (in case of U/S conversions when we have separete opcode for this)
    ///
    template <typename To, typename From, ushort ConversionType, rounding_mode Rounding, saturate Saturation, bool EqualSize = (sizeof(To) == sizeof(From))>
    struct __choose_convert
    { static_assert(__always_false<To>::value, "Internal error: invalid or unhandled __convert_type value"); };

    // ints to floating points
    template <typename To, typename From, rounding_mode Rmode, saturate Smode, bool EqualSize>
    struct __choose_convert<To, From, uint_to_fp, Rmode, Smode, EqualSize>
    {
        static __ALWAYS_INLINE To __make_call(From const& arg)      { return __spirv::OpConvertUToF<Rmode, To>(arg); }
    };

    template <typename To, typename From, rounding_mode Rmode, saturate Smode, bool EqualSize>
    struct __choose_convert<To, From, sint_to_fp, Rmode, Smode, EqualSize>
    {
        static __ALWAYS_INLINE To __make_call(From const& arg)      { return __spirv::OpConvertSToF<Rmode, To>(arg); }
    };

    // floating points to ints
    template <typename To, typename From, rounding_mode Rmode, saturate Smode, bool EqualSize>
    struct __choose_convert<To, From, fp_to_uint, Rmode, Smode, EqualSize>
    {
        static __ALWAYS_INLINE To __make_call(From const& arg)      { return __spirv::OpConvertFToU<Rmode, Smode, To>(arg); }
    };

    template <typename To, typename From, rounding_mode Rmode, saturate Smode, bool EqualSize>
    struct __choose_convert<To, From, fp_to_sint, Rmode, Smode, EqualSize>
    {
        static __ALWAYS_INLINE To __make_call(From const& arg)      { return __spirv::OpConvertFToS<Rmode, Smode, To>(arg); }
    };

    // ints to ints (sign preserving)
    template <typename To, typename From, rounding_mode Rmode, saturate Smode, bool EqualSize>
    struct __choose_convert<To, From, uint_to_uint, Rmode, Smode, EqualSize>
    {
        static __ALWAYS_INLINE To __make_call(From const& arg) { return __spirv::OpUConvert<Smode, To>(arg); }
    };

    template <typename To, typename From, rounding_mode Rmode, saturate Smode, bool EqualSize>
    struct __choose_convert<To, From, sint_to_sint, Rmode, Smode, EqualSize>
    {
        static __ALWAYS_INLINE To __make_call(From const& arg) { return __spirv::OpSConvert<Smode, To>(arg); }
    };

    //floating points to floating points
    template <typename To, typename From, rounding_mode Rmode, saturate Smode, bool EqualSize>
    struct __choose_convert<To, From, fp_to_fp, Rmode, Smode, EqualSize>
    {
        static __ALWAYS_INLINE To __make_call(From const& arg) { return __spirv::OpFConvert<Rmode, To>(arg); }
    };

    // ints to ints (with sign change)

    // without saturation and with different sizes => treat argument as signed/unsigned (regardless original type) and widen/narrow it to match destination type's size
    template <typename To, typename From, rounding_mode Rmode>
    struct __choose_convert<To, From, uint_to_sint, Rmode, saturate::off, false>
    {
        static __ALWAYS_INLINE To __make_call(From const& arg) { return __spirv::OpSConvert<To>(arg); }
    };

    // without saturation but types has equal size => just reinterpret with OpBitcast
    template <typename To, typename From, rounding_mode Rmode>
    struct __choose_convert<To, From, uint_to_sint, Rmode, saturate::off, true>
    {
        static __ALWAYS_INLINE To __make_call(From const& arg) { return __spirv::__make_OpBitcast_call<To>(arg); }
    };

    // without saturation and with different sizes => treat argument as signed/unsigned (regardless original type) and widen/narrow it to match destination type's size
    template <typename To, typename From, rounding_mode Rmode>
    struct __choose_convert<To, From, sint_to_uint, Rmode, saturate::off, false>
    {
        static __ALWAYS_INLINE To __make_call(From const& arg) { return __spirv::OpUConvert<To>(arg); }
    };

    // without saturation but types has equal size => just reinterpret with OpBitcast
    template <typename To, typename From, rounding_mode Rmode>
    struct __choose_convert<To, From, sint_to_uint, Rmode, saturate::off, true>
    {
        static __ALWAYS_INLINE To __make_call(From const& arg) { return __spirv::__make_OpBitcast_call<To>(arg); }
    };

    template <typename To, typename From, rounding_mode Rmode, bool EqualSize>
    struct __choose_convert<To, From, uint_to_sint, Rmode, saturate::on, EqualSize>
    {
        static __ALWAYS_INLINE To __make_call(From const& arg) { return __spirv::OpSatConvertUToS<To>(arg); }
    };

    template <typename To, typename From, rounding_mode Rmode, bool EqualSize>
    struct __choose_convert<To, From, sint_to_uint, Rmode, saturate::on, EqualSize>
    {
        static __ALWAYS_INLINE To __make_call(From const& arg) { return __spirv::OpSatConvertSToU<To>(arg); }
    };

    //to-from booleans
    template <typename To, typename From, rounding_mode Rmode, saturate Smode, bool EqualSize>
    struct __choose_convert<To, From, bool_to_num, Rmode, Smode, EqualSize>
    {
        static __ALWAYS_INLINE To __make_call(From const& arg) { return __spirv::__make_OpSelect_call<To>(arg, To{ 1 }, To{ 0 }); }
    };

    template <typename To, typename From, rounding_mode Rmode, saturate Smode, bool EqualSize>
    struct __choose_convert<To, From, int_to_bool, Rmode, Smode, EqualSize>
    {
        static __ALWAYS_INLINE To __make_call(From const& arg) { return __spirv::__make_OpINotEqual_call<To>(arg, From{ 0 }); }
    };

    template <typename To, typename From, rounding_mode Rmode, saturate Smode, bool EqualSize>
    struct __choose_convert<To, From, fp_to_bool, Rmode, Smode, EqualSize>
    {
        static __ALWAYS_INLINE To __make_call(From const& arg) { return __spirv::__make_OpFOrdNotEqual_call<To>(arg, From{ 0 }); }
    };

    /// \brief structures which expose __convert_type values if given types match kind of conversion or 0 otherwise.
    ///  for any valid pair of types only one of these structs should have value different than 0, so result of bitwise OR of all values should match one entry from __convert_type enum
    ///
    template <typename To, typename From> struct __is_utof : public integral_constant<ushort, is_floating_point<To>::value && __is_integral_not_bool<From>::value && is_unsigned<From>::value ? uint_to_fp : 0> {};
    template <typename To, typename From> struct __is_stof : public integral_constant<ushort, is_floating_point<To>::value && __is_integral_not_bool<From>::value && is_signed<From>::value ? sint_to_fp : 0> {};
    template <typename To, typename From> struct __is_ftou : public integral_constant<ushort, __is_integral_not_bool<To>::value && is_floating_point<From>::value && is_unsigned<To>::value ? fp_to_uint : 0> {};
    template <typename To, typename From> struct __is_ftos : public integral_constant<ushort, __is_integral_not_bool<To>::value && is_floating_point<From>::value && is_signed<To>::value ? fp_to_sint : 0> {};
    template <typename To, typename From> struct __is_utou : public integral_constant<ushort, __is_integral_not_bool<To>::value && __is_integral_not_bool<From>::value && is_unsigned<From>::value && is_unsigned<To>::value ? uint_to_uint : 0> {};
    template <typename To, typename From> struct __is_stos : public integral_constant<ushort, __is_integral_not_bool<To>::value && __is_integral_not_bool<From>::value && is_signed<From>::value && is_signed<To>::value ? sint_to_sint : 0> {};
    template <typename To, typename From> struct __is_ftof : public integral_constant<ushort, is_floating_point<To>::value && is_floating_point<From>::value ? fp_to_fp : 0> {};
    template <typename To, typename From> struct __is_stou : public integral_constant<ushort, __is_integral_not_bool<To>::value && __is_integral_not_bool<From>::value && is_signed<From>::value && is_unsigned<To>::value ? sint_to_uint : 0> {};
    template <typename To, typename From> struct __is_utos : public integral_constant<ushort, __is_integral_not_bool<To>::value && __is_integral_not_bool<From>::value && is_unsigned<From>::value && is_signed<To>::value ? uint_to_sint : 0> {};
    template <typename To, typename From> struct __is_bton : public integral_constant<ushort, !__is_bool<To>::value && __is_bool<From>::value ? bool_to_num : 0> {};
    template <typename To, typename From> struct __is_itob : public integral_constant<ushort, __is_bool<To>::value && __is_integral_not_bool<From>::value ? int_to_bool : 0> {};
    template <typename To, typename From> struct __is_ftob : public integral_constant<ushort, __is_bool<To>::value && is_floating_point<From>::value ? fp_to_bool : 0> {};

    /// \brief convert_cast base implementation which only chooses right spirv conversion instruction. Any decorations are handled outside of it
    ///
    template <typename To, typename From, rounding_mode Rmode, saturate Smode>
    To __ALWAYS_INLINE __convert_cast(From const& arg)
    {
        _CHECK_VECTOR_SIZE;
        _CHECK_TYPE(To);
        _CHECK_TYPE(From);

        return __details::__choose_convert<To, From,
            //calculate OR of all __is_* values and pass it as __choose_convert param
            //  -> if TO-FROM pair of types match more than one conversion type (which would be an error in implementation)
            //      OR-ed value will not match any of __convert_type values and __choose_convert will fire static_assert
            __details::__is_utof<To,From>::value |
            __details::__is_stof<To,From>::value |
            __details::__is_ftou<To,From>::value |
            __details::__is_ftos<To,From>::value |
            __details::__is_utou<To,From>::value |
            __details::__is_stos<To,From>::value |
            __details::__is_ftof<To,From>::value |
            __details::__is_stou<To,From>::value |
            __details::__is_utos<To,From>::value |
            __details::__is_bton<To,From>::value |
            __details::__is_itob<To,From>::value |
            __details::__is_ftob<To,From>::value,
            Rmode, Smode
        >::__make_call(arg);
    };

    /// \brief Target and destination types are the same => NoOp
    ///
    template <typename To, typename From, rounding_mode Rmode, saturate Smode>
    To __ALWAYS_INLINE __convert_cast(To const& t)
    {
        return t;
    }

    template <typename To, typename From>
    struct __default_rmode : public integral_constant<rounding_mode, (is_floating_point<To>::value ? rounding_mode::rte : rounding_mode::rtz)> { };

    template <typename To, typename From>
    struct __default_smode : public integral_constant<saturate, saturate::off> { };
}

template <typename To, typename From>
To __ALWAYS_INLINE convert_cast(From const& arg)
{
    // just plain convert_cast without decorations
    return __details::__convert_cast<remove_attrs_t<To>, remove_attrs_t<From>, __details::__default_rmode<To, From>::value, __details::__default_smode<To, From>::value>(arg);
}

template <typename To, rounding_mode Rmode, typename From>
To __ALWAYS_INLINE convert_cast(From const& arg)
{
    static_assert(is_floating_point<To>::value || is_floating_point<From>::value, "convert_cast with rounding mode option can be used only in conversions to/from floating point types.");
    static_assert(!__details::__is_bool<To>::value && !__details::__is_bool<From>::value, "rounding mode cannot be used while converting to/from bool.");

    return __details::__convert_cast<remove_attrs_t<To>, remove_attrs_t<From>, Rmode, __details::__default_smode<To, From>::value>(arg);
}

template <typename To, saturate Smode, typename From>
To __ALWAYS_INLINE convert_cast(From const& arg)
{
    static_assert(Smode == saturate::off || is_integral<To>::value, "convert_cast with saturate option can be used only in conversions to integer types.");
    static_assert(Smode == saturate::off || (!__details::__is_bool<To>::value && !__details::__is_bool<From>::value), "convert_cast with saturate option cannot be used in conversions to/from bool.");

    return __details::__convert_cast<remove_attrs_t<To>, remove_attrs_t<From>, __details::__default_rmode<To, From>::value, Smode>(arg);
}

template <typename To, rounding_mode Rmode, saturate Smode, typename From>
To __ALWAYS_INLINE convert_cast(From const& arg)
{
    static_assert(is_floating_point<To>::value || is_floating_point<From>::value, "convert_cast with rounding mode option can be used only in conversions to/from floating point types.");
    static_assert(!__details::__is_bool<To>::value && !__details::__is_bool<From>::value, "rounding mode cannot be used while converting to/from bool.");
    static_assert(Smode == saturate::off || is_integral<To>::value, "convert_cast with saturate option can be used only in conversions to integer types.");
    static_assert(Smode == saturate::off || (!__details::__is_bool<To>::value && !__details::__is_bool<From>::value), "convert_cast with saturate option cannot be used in conversions to/from bool.");

    return __details::__convert_cast<remove_attrs_t<To>, remove_attrs_t<From>, Rmode, Smode>(arg);
}

#undef _CHECK_VECTOR_SIZE
#undef _CHECK_TYPE
#undef MAKE_SPIRV_CONVERSION

}
