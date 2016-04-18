// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify
// expected-no-diagnostics

#include <opencl_type_traits>
using namespace cl; 

kernel void worker( )
{     
    // tests of helper classes
    static_assert( integral_constant<bool, true>::value == true, "" );
    static_assert( integral_constant<bool, false>::value == false, "" );

    static_assert( true_type::value == true, "" );
    static_assert( false_type::value == false, "" );
}
