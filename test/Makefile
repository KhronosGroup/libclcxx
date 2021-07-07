PATH_TO_LLVM_BUILD ?= ../llvm-project
libclcxx_include = -I../include/
build_include = -I${PATH_TO_LLVM_BUILD}/build/include/c++/v1/
test-all: *.bc

*.bc: *.clcpp
	clang ${libclcxx_include} ${build_include} -c *.clcpp --target=spir -emit-llvm

clean:
	rm *.bc

