#include <opencl_new.h>

class B{
    public:
    B(int num = 24)
    : x(num) {}

    public:
    int x;
};

void test_new_delete(void *buffer, B **b, B **b2){
    *b = new (buffer) B;
    *b2 = new (buffer) B[10];
	auto p1 = new (buffer) double[2][5];
	auto p2 = new (buffer) int;
}
