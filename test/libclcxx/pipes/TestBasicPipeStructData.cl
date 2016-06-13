// RUN: %clang_cc1 %s -triple spir-unknown-unknown -cl-std=c++ -fsyntax-only -pedantic -verify -O0 -emit-llvm -o /dev/null
// expected-no-diagnostics

#include <opencl_pipe>

struct structType
{
    float a;
	int b;
	long long c;
};

cl::pipe_storage<structType, 10> programPipe;

kernel void worker3()
{
    cl::pipe<structType> in = programPipe.get();
	
    structType val;
	cl::pipe<structType, cl::pipe_access::read>::element_type val2;
	
    auto r1 = in.reserve(10);
	bool r1_valid = r1.is_valid();
	if(r1) { }
	r1.read(0, val2);
	r1.commit();
	
	auto r2 = in.work_group_reserve(10);
	bool r2_valid = r2.is_valid();
	if(r2) { }
    r2.read(0, val);
	r2.commit();
	
	auto r3 = in.sub_group_reserve(10);
	bool r3_valid = r3.is_valid();
	if(r3) { }
    r3.read(0, val);
	r3.commit();
	
	in.read(val);
	uint num = in.num_packets();
	uint max = in.max_packets();
}

kernel void worker4()
{
    cl::pipe<structType, cl::pipe_access::write> out = programPipe.get<cl::pipe_access::write>();
	
    const structType val = { 0 };
    const cl::pipe<structType, cl::pipe_access::write>::element_type val2 = { 0 };
	
    auto r4 = out.reserve(10);
	bool r4_valid = r4.is_valid();
	if(r4) { }
    r4.write(0, val2);
	r4.commit();
	
	auto r5 = out.work_group_reserve(10);
	bool r5_valid = r5.is_valid();
	if(r5) { }
    r5.write(0, val);
	r5.commit();
	
	auto r6 = out.sub_group_reserve(10);
	bool r6_valid = r6.is_valid();
	if(r6) { }
    r6.write(0, val);
	r6.commit();
	
	out.write(val);
	uint num = out.num_packets();
	uint max = out.max_packets();
}

kernel void worker5()
{
    cl::pipe<structType> in = cl::make_pipe(programPipe);
	
    structType val;
	cl::pipe<structType, cl::pipe_access::read>::element_type val2;
	
    auto r1 = in.reserve(10);
	bool r1_valid = r1.is_valid();
	if(r1) { }
	r1.read(0, val2);
	r1.commit();
	
	auto r2 = in.work_group_reserve(10);
	bool r2_valid = r2.is_valid();
	if(r2) { }
    r2.read(0, val);
	r2.commit();
	
	auto r3 = in.sub_group_reserve(10);
	bool r3_valid = r3.is_valid();
	if(r3) { }
    r3.read(0, val);
	r3.commit();
	
	in.read(val);
	uint num = in.num_packets();
	uint max = in.max_packets();
}

kernel void worker6()
{
    cl::pipe<structType, cl::pipe_access::write> out = cl::make_pipe<cl::pipe_access::write>(programPipe);
	
    const structType val = { 0 };
    const cl::pipe<structType, cl::pipe_access::write>::element_type val2 = { 0 };
	
    auto r4 = out.reserve(10);
	bool r4_valid = r4.is_valid();
	if(r4) { }
    r4.write(0, val2);
	r4.commit();
	
	auto r5 = out.work_group_reserve(10);
	bool r5_valid = r5.is_valid();
	if(r5) { }
    r5.write(0, val);
	r5.commit();
	
	auto r6 = out.sub_group_reserve(10);
	bool r6_valid = r6.is_valid();
	if(r6) { }
    r6.write(0, val);
	r6.commit();
	
	out.write(val);
	uint num = out.num_packets();
	uint max = out.max_packets();
}
