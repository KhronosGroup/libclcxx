// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -verify -O0 -o /dev/null
// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -emit-llvm -pedantic -verify -O3 -o /dev/null

#include <opencl_memory>
using namespace cl;

kernel void worker()
{
    local_ptr<int[]> uba;
    uba[10] = 5;
    uba.get()[10] = 5;
    
    local_ptr<int[5]> ba;
    ba[10] = 5; //expected-error {{type 'local_ptr<int [5]>' does not provide a subscript operator}}
    (*ba)[10] = 5; //expected-warning {{array index 10 is past the end of the array (which contains 5 elements)}}
    
    private_ptr<int[][10][5]> uba2;
    uba2[18][2][3] = 1;
    uba2.get()[18][2][3] = 1;
    
    private_ptr<int[15][10][5]> ba2;
    ba2[1][1][1] = 2; //expected-error {{type 'private_ptr<int [15][10][5]>' does not provide a subscript operator}}
    (*ba2)[1][1][1] = 2;
}
