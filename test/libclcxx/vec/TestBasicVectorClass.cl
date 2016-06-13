// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -pedantic -O0 -Wall -Wno-unused-variable -verify -emit-llvm -o -
// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -pedantic -O0 -Wall -Wno-unused-variable -verify -emit-llvm -o - -cl-fp16-enable
// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -pedantic -O0 -Wall -Wno-unused-variable -verify -emit-llvm -o - -cl-fp64-enable
// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -pedantic -O0 -Wall -Wno-unused-variable -verify -emit-llvm -o - -cl-fp64-enable
// expected-no-diagnostics

#include <opencl_vec>
using namespace cl;

kernel void worker()
{
    vec<bool, 2> t1;
    vec<bool, 3> t2;
    vec<bool, 4> t3;
    vec<bool, 8> t4;
    vec<bool, 16> t5;
    
    vec<char, 2> t6;
    vec<char, 3> t7;
    vec<char, 4> t8;
    vec<char, 8> t9;
    vec<char, 16> t10;
    
    vec<short, 2> t11;
    vec<short, 3> t12;
    vec<short, 4> t13;
    vec<short, 8> t14;
    vec<short, 16> t15;
    
    vec<int, 2> t16;
    vec<int, 3> t17;
    vec<int, 4> t18;
    vec<int, 8> t19;
    vec<int, 16> t20;
    
    vec<long, 2> t21;
    vec<long, 3> t22;
    vec<long, 4> t23;
    vec<long, 8> t24;
    vec<long, 16> t25;
    
    vec<uchar, 2> t26;
    vec<uchar, 3> t27;
    vec<uchar, 4> t28;
    vec<uchar, 8> t29;
    vec<uchar, 16> t30;
    
    vec<ushort, 2> t31;
    vec<ushort, 3> t32;
    vec<ushort, 4> t33;
    vec<ushort, 8> t34;
    vec<ushort, 16> t35;
    
    vec<uint, 2> t36;
    vec<uint, 3> t37;
    vec<uint, 4> t38;
    vec<uint, 8> t39;
    vec<uint, 16> t40;
    
    vec<ulong, 2> t41;
    vec<ulong, 3> t42;
    vec<ulong, 4> t43;
    vec<ulong, 8> t44;
    vec<ulong, 16> t45;
    
    vec<float, 2> t46;
    vec<float, 3> t47;
    vec<float, 4> t48;
    vec<float, 8> t49;
    vec<float, 16> t50;
    
#ifdef cl_khr_fp16
    vec<half, 2> t51;
    vec<half, 3> t52;
    vec<half, 4> t53;
    vec<half, 8> t54;
    vec<half, 16> t55;
#endif
    
#ifdef cl_khr_fp64
    vec<double, 2> t56;
    vec<double, 3> t57;
    vec<double, 4> t58;
    vec<double, 8> t59;
    vec<double, 16> t60;
#endif
}
