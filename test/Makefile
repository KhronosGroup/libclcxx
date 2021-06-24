libclcxx_path = -I/home/ishwar01/llvm-project/libcxx/include/
build_path = -I/home/ishwar01/llvm-project/llvm/build/include/c++/v1/
test-all: type_traits.o test_vector_type_traits.o test_address_space_traits.o test_misc_type_traits.o test_float_traits.o
	clang-13 type_traits.o test_vector_type_traits.o test_address_space_traits.o test_misc_type_traits.o test_float_traits.o -c

type_traits.o: type_traits.clcpp
	clang-13 ${libclcxx_path} ${build_path} -I/home/ishwar01/libclcxx/include -c type_traits.clcpp

test_vector_type_traits.o: test_vector_type_traits.clcpp
	clang-13 ${libclcxx_path} ${build_path} -I/home/ishwar01/libclcxx/include -c test_vector_type_traits.clcpp

test_address_space_traits.o: test_address_space_traits.clcpp
	clang-13 ${libclcxx_path} ${build_path} -I/home/ishwar01/libclcxx/include -c test_address_space_traits.clcpp

test_misc_type_traits.o: test_misc_type_traits.clcpp
	clang-13 ${libclcxx_path} ${build_path} -I/home/ishwar01/libclcxx/include -c test_misc_type_traits.clcpp

test_float_traits.o: test_float_traits.clcpp
	clang-13 ${libclcxx_path} ${build_path} -I/home/ishwar01/libclcxx/include -c test_float_traits.clcpp

clean:
	rm *.o
