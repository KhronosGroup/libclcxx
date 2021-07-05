libcxx_include = -I../llvm-project/libcxx/include/
libclcxx_include = -I../include/
build_include = -I../llvm_project/build/include/c++/v1/
test-all: type_traits.o vector_type_traits.o address_space_traits.o image_type_traits.o half_type_traits.o new.o
	clang-13 type_traits.o vector_type_traits.o address_space_traits.o image_type_traits.o half_type_traits.o new.o -c

type_traits.o: type_traits.clcpp
	clang-13 ${libclcxx_include} ${libcxx_include} ${build_include} -c type_traits.clcpp

vector_type_traits.o: vector_type_traits.clcpp
	clang-13 ${libclcxx_include} ${libcxx_include} ${build_include} -c vector_type_traits.clcpp

address_space_traits.o: address_space_traits.clcpp
	clang-13 ${libclcxx_include} ${libcxx_include} ${build_include} -c address_space_traits.clcpp

image_type_traits.o: image_type_traits.clcpp
	clang-13 ${libclcxx_include} ${libcxx_include} ${build_include} -c image_type_traits.clcpp

half_type_traits.o: half_type_traits.clcpp
	clang-13 ${libclcxx_include} ${libcxx_include} ${build_include} -c half_type_traits.clcpp

new.o: new.cl
	clang-13 ${libclcxx_include} ${libcxx_include} ${build_include} -c new.cl

clean:
	rm *.o

