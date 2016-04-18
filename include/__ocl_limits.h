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
#include <opencl_relational>
#include "__ocl_limits_values.h"
#include "__ocl_limits_enums.h"
#include "__ocl_type_traits_vectors.h"

namespace cl
{

//Forward declaration
template<class T> class numeric_limits;

namespace __details
{

/// \brief Base class providing default values
///
template<class T>
struct __num_base
{
    static constexpr bool is_specialized = false;
    static constexpr int max_digits10 = 0;
    static constexpr bool is_signed = false;
    static constexpr bool is_integer = false;
    static constexpr bool is_exact = false;
    static constexpr int radix = 0;
    static constexpr int min_exponent = 0;
    static constexpr int min_exponent10 = 0;
    static constexpr int max_exponent = 0;
    static constexpr int max_exponent10 = 0;
    static constexpr bool has_infinity = false;
    static constexpr bool has_quiet_NaN = false;
    static constexpr bool has_signaling_NaN = false;
    static constexpr float_denorm_style has_denorm = denorm_absent;
    static constexpr bool has_denorm_loss = false;
    static constexpr bool is_iec559 = false;
    static constexpr bool is_bounded = false;
    static constexpr bool is_modulo = false;
    static constexpr bool traps = false;
    static constexpr bool tinyness_before = false;
    static constexpr float_round_style round_style = round_toward_zero;
    static constexpr bool is_scalar = false;
    static constexpr bool is_vector = false;
};

/// \brief Helper class for checking number of digits in integer types (that type T can represent without a change)
///
/// digits is number of digits in base 2
/// digits10 is number of digits in base 10
/// This specialization is for signed types
template<typename T, bool = cl::is_signed<T>::value>
struct __digits_helper
{
    static constexpr int digits = (CHAR_BIT * sizeof(T)-1);
    static constexpr int digits10 = digits * 301L / 1000; //301L / 1000 gives value of logarithm of 2 to base 10 (~0.30103...) - used to convert number of digits
                                                          //from base 2 to base 10. In our range of possible number of digits its precision is sufficient
};

/// \brief Helper class for checking number of digits in integer types (that type T can represent without a change)
///
/// digits is number of digits in base 2
/// digits10 is number of digits in base 10
/// This specialization is for unsigned types
template<typename T>
struct __digits_helper<T, false>
{
    static constexpr int digits = CHAR_BIT * sizeof(T);
    static constexpr int digits10 = digits * 301L / 1000; //301L / 1000 gives value of logarithm of 2 to base 10 (~0.30103...) - used to convert number of digits
                                                          //from base 2 to base 10. In our range of possible number of digits its precision is sufficient
};

/// \brief Helper class for integer types
///
template<class T, T Min, T Max>
struct __num_int_base : public __digits_helper<T>, public __num_base<T>
{
    inline static constexpr T min() __NOEXCEPT{ return Min; }
    inline static constexpr T max() __NOEXCEPT{ return Max; }
    inline static constexpr T lowest() __NOEXCEPT{ return Min; }

    static constexpr bool is_signed = (cl::is_signed<T>::value);
    static constexpr bool is_bounded = true;
    static constexpr bool is_exact = true;
    static constexpr bool is_integer = true;
    static constexpr bool is_modulo = true;
    static constexpr bool is_specialized = true;
    static constexpr int radix = 2;
};

/// \brief Helper class for floating point types
///
/// min, max, lowest, epsilon should be redeclared with proper values in specialization,
/// because C++ forbids to pass floating point values as non-type template parameters
template<class T, int Dig, int MantDig, int Max10Exp, int MaxExp, int Min10Exp, int MinExp>
struct __num_float_base : public __num_base<T>
{
    inline static constexpr T round_error() __NOEXCEPT{ return 0.5F; }

    static constexpr int digits = MantDig;
    static constexpr int digits10 = Dig;
    static constexpr int max_digits10 = 2 + MantDig * 301L / 1000;  //301L / 1000 gives value of logarithm of 2 to base 10 (~0.30103...)- used to convert number of digits
                                                                    //from base 2 to base 10. In our range of possible number of digits its precision is sufficient
    static constexpr int max_exponent = (int)MaxExp;
    static constexpr int max_exponent10 = (int)Max10Exp;
    static constexpr int min_exponent = (int)MinExp;
    static constexpr int min_exponent10 = (int)Min10Exp;

    static constexpr float_denorm_style has_denorm = denorm_present;
    static constexpr bool has_denorm_loss = true;
    static constexpr bool has_infinity = true;
    static constexpr bool has_quiet_NaN = true;
    static constexpr bool has_signaling_NaN = true;
    static constexpr bool is_bounded = true;
    static constexpr bool is_exact = false;
    static constexpr bool is_iec559 = true;
    static constexpr bool is_integer = false;
    static constexpr bool is_modulo = false;
    static constexpr bool is_signed = true;
    static constexpr bool is_specialized = true;
    static constexpr bool tinyness_before = true;
    static constexpr bool traps = false;
    static constexpr float_round_style round_style = round_to_nearest;
    static constexpr int radix = 2;
};


/// \brief Helper class containing all values for coresponding numeric limits specializations
///
template<class T, bool  A = __is_one_of<typename vector_element<T>::type, bool, int, char, short, long, uint, uchar, ulong, ushort, float
#ifdef cl_khr_fp16
    , half
#endif
#ifdef cl_khr_fp64
    , double
#endif
>::value>
struct __numeric_limits_base;


template<> class __numeric_limits_base<int>    : public __num_int_base<int, INT_MIN, INT_MAX> { };
template<> class __numeric_limits_base<char>   : public __num_int_base<char, CHAR_MIN, CHAR_MAX> { };
template<> class __numeric_limits_base<short>  : public __num_int_base<short, SHRT_MIN, SHRT_MAX> { };
template<> class __numeric_limits_base<long>   : public __num_int_base<long, LONG_MIN, LONG_MAX> { };
template<> class __numeric_limits_base<uint>   : public __num_int_base<uint, 0, UINT_MAX> { };
template<> class __numeric_limits_base<uchar>  : public __num_int_base<uchar, 0, UCHAR_MAX> { };
template<> class __numeric_limits_base<ulong>  : public __num_int_base<ulong, 0, ULONG_MAX> { };
template<> class __numeric_limits_base<ushort> : public __num_int_base<ushort, 0, USHRT_MAX> { };

#ifdef cl_khr_fp16
/// \brief Numeric limits specialization for half
///
template<> class __numeric_limits_base<half> : public __num_float_base <half, HALF_DIG, HALF_MANT_DIG, HALF_MAX_10_EXP, HALF_MAX_EXP, HALF_MIN_10_EXP, HALF_MIN_EXP>
{
public:
    inline static constexpr half min() __NOEXCEPT{ return HALF_MIN; }
    inline static constexpr half max() __NOEXCEPT{ return HALF_MAX; }
    inline static constexpr half lowest() __NOEXCEPT{ return -max(); }
    inline static constexpr half epsilon() __NOEXCEPT{ return HALF_EPSILON; }
    inline static constexpr half infinity() __NOEXCEPT{ return __builtin_huge_valf(); }
    inline static constexpr half signaling_NaN() __NOEXCEPT{ return __builtin_nansf(""); }
    inline static constexpr half quiet_NaN() __NOEXCEPT{ return __builtin_nanf(""); }
    inline static constexpr half denorm_min() __NOEXCEPT{ if (has_denorm) return HALF_DENORM_MIN; return min(); }

#ifdef HAS_HALF_FP_DENORM
    static constexpr float_denorm_style has_denorm = denorm_present;
#else
    static constexpr float_denorm_style has_denorm = denorm_absent;
#endif
};
#endif

/// \brief Numeric limits specialization for float
///
template<> class __numeric_limits_base<float> : public __num_float_base <float, FLT_DIG, FLT_MANT_DIG, FLT_MAX_10_EXP, FLT_MAX_EXP, FLT_MIN_10_EXP, FLT_MIN_EXP>
{
public:
    inline static constexpr float min() __NOEXCEPT{ return FLT_MIN; }
    inline static constexpr float max() __NOEXCEPT{ return FLT_MAX; }
    inline static constexpr float lowest() __NOEXCEPT{ return -max(); }
    inline static constexpr float epsilon() __NOEXCEPT{ return FLT_EPSILON; }
    inline static constexpr float infinity() __NOEXCEPT{ return __builtin_huge_valf(); }
    inline static constexpr float quiet_NaN() __NOEXCEPT{ return __builtin_nanf(""); }
    inline static constexpr float signaling_NaN() __NOEXCEPT{ return __builtin_nansf(""); }
    inline static constexpr float denorm_min() __NOEXCEPT{ if (has_denorm) return FLT_DENORM_MIN; return min(); }

#ifdef HAS_SINGLE_FP_DENORM
    static constexpr float_denorm_style has_denorm = denorm_present;
#else
    static constexpr float_denorm_style has_denorm = denorm_absent;
#endif
};

#ifdef cl_khr_fp64
/// \brief Numeric limits specialization for double
///
template<> class __numeric_limits_base<double> : public __num_float_base <double, DBL_DIG, DBL_MANT_DIG, DBL_MAX_10_EXP, DBL_MAX_EXP, DBL_MIN_10_EXP, DBL_MIN_EXP>
{
public:
    inline static constexpr double min() __NOEXCEPT{ return DBL_MIN; }
    inline static constexpr double max() __NOEXCEPT{ return DBL_MAX; }
    inline static constexpr double lowest() __NOEXCEPT{ return -max(); }
    inline static constexpr double epsilon() __NOEXCEPT{ return DBL_EPSILON; }
    inline static constexpr double infinity() __NOEXCEPT{ return __builtin_huge_val(); }
    inline static constexpr double quiet_NaN() __NOEXCEPT{ return __builtin_nan(""); }
    inline static constexpr double signaling_NaN() __NOEXCEPT{ return __builtin_nans(""); }
    inline static constexpr double denorm_min() __NOEXCEPT{ if (has_denorm) return DBL_DENORM_MIN; return min(); }

#ifdef HAS_DOUBLE_FP_DENORM
    static constexpr float_denorm_style has_denorm = denorm_present;
#else
    static constexpr float_denorm_style has_denorm = denorm_absent;
#endif
};
#endif

/// \brief Numeric limits specialization for bool
///
template<> class __numeric_limits_base<bool> {
public:
    static constexpr bool is_specialized = true;
    static constexpr bool min() __NOEXCEPT{ return false; }
    static constexpr bool max() __NOEXCEPT{ return true; }
    static constexpr bool lowest() __NOEXCEPT{ return false; }
    static constexpr int digits = 1;
    static constexpr int digits10 = 0;
    static constexpr int max_digits10 = 0;
    static constexpr bool is_signed = false;
    static constexpr bool is_integer = true;
    static constexpr bool is_exact = true;
    static constexpr int radix = 2;
    static constexpr bool epsilon() __NOEXCEPT{ return 0; }
    static constexpr bool round_error() __NOEXCEPT{ return 0; }
    static constexpr int min_exponent = 0;
    static constexpr int min_exponent10 = 0;
    static constexpr int max_exponent = 0;
    static constexpr int max_exponent10 = 0;
    static constexpr bool has_infinity = false;
    static constexpr bool has_quiet_NaN = false;
    static constexpr bool has_signaling_NaN = false;
    static constexpr float_denorm_style has_denorm = denorm_absent;
    static constexpr bool has_denorm_loss = false;
    static constexpr bool infinity() __NOEXCEPT{ return 0; }
    static constexpr bool quiet_NaN() __NOEXCEPT{ return 0; }
    static constexpr bool signaling_NaN() __NOEXCEPT{ return 0; }
    static constexpr bool denorm_min() __NOEXCEPT{ return 0; }
    static constexpr bool is_iec559 = false;
    static constexpr bool is_bounded = true;
    static constexpr bool is_modulo = false;
    static constexpr bool traps = false;
    static constexpr bool tinyness_before = false;
    static constexpr float_round_style round_style = round_toward_zero;

    static constexpr bool is_scalar = false;
    static constexpr bool is_vector = false;
};

/// \brief Helper class containing all values for coresponding numeric limits specialization
///
/// This specialization catches not supported types
template<class T>
struct __numeric_limits_base<T, false>
{
    static_assert(__always_false<T>::value, "Invalid specialization - type not supported.");
};

/// \brief Helper class for numeric_limit
///
/// This is specialization is for scalar types
template<class T, bool = is_vector_type<T>::value>
struct __numeric_limits_helper : public __numeric_limits_base<T> {
    static constexpr bool is_scalar = true;
    static constexpr bool is_vector = false;
};

/// \brief Helper class for numeric_limits
///
/// This specialization is for vector types
template<class T>
struct __numeric_limits_helper<T, true> : public __numeric_limits_base<typename vector_element<T>::type>
{
    inline static constexpr T min() __NOEXCEPT{ return { numeric_limits<typename vector_element<T>::type>::min() }; }
    inline static constexpr T max() __NOEXCEPT{ return { numeric_limits<typename vector_element<T>::type>::max() }; }
    inline static constexpr T lowest() __NOEXCEPT{ return{ numeric_limits<typename vector_element<T>::type>::lowest() }; }

    inline static constexpr T epsilon() __NOEXCEPT{ return{ numeric_limits<typename vector_element<T>::type>::epsilon() }; }
    inline static constexpr T round_error() __NOEXCEPT{ return{ numeric_limits<typename vector_element<T>::type>::round_error() }; }
    inline static constexpr T infinity() __NOEXCEPT{ return{ numeric_limits<typename vector_element<T>::type>::infinity() }; }
    inline static constexpr T quiet_NaN() __NOEXCEPT{ return{ numeric_limits<typename vector_element<T>::type>::quiet_NaN() }; }
    inline static constexpr T signaling_NaN() __NOEXCEPT{ return{ numeric_limits<typename vector_element<T>::type>::signaling_NaN() }; }
    inline static constexpr T denorm_min() __NOEXCEPT{ return{ numeric_limits<typename vector_element<T>::type>::denorm_min() }; }

    static constexpr bool is_scalar = false;
    static constexpr bool is_vector = true;
};

/// \brief Helper class for numeric_limits
///
/// This is specialization for bool type
template<>
struct __numeric_limits_helper<bool, false> : public __numeric_limits_base<bool> { };

}

/// \Brief The numeric_limits class template provides a C++ program with information about various properties of
/// the implementation’s representation of the arithmetic types.
///
template<class T>
class numeric_limits : public __details::__numeric_limits_helper<remove_cv_t<T>> { };

//template<class T> class numeric_limits<const T> : public numeric_limits<remove_cv_t<T>> { };

}