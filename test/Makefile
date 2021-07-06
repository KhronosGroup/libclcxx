libclcxx_include = -I../include/
build_include = -I../llvm_project/build/include/c++/v1/
test-all: *.bc

*.bc: *.clcpp
	clang-13 ${libclcxx_include} ${build_include} -c *.clcpp --target=spir -emit-llvm -D_LIBCPP_HAS_NO_THREADS

clean:
	rm *.bc

