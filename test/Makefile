# To run: make PATH_TO_LLVM_BUILD=<Path to llvm build folder>
libclcxx_include = -I../include/
build_include = -I${PATH_TO_LLVM_BUILD}/include/c++/v1/
test-all: *.bc

*.bc: *.clcpp
	clang ${libclcxx_include} ${build_include} -c *.clcpp --target=spir -emit-llvm ${ARGS}

clean:
	rm *.bc

