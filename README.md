<!--
Copyright (c) 2021 The Khronos Group Inc.
SPDX-License-Identifier: Apache-2.0
-->
 
This repository contains libraries for C++ for OpenCL Kernel Language published in releases of [OpenCL-Docs](https://github.com/KhronosGroup/OpenCL-Docs/releases/tag/cxxforopencl-docrev2021.12). The libraries can be used with kernels written in C++ for OpenCL and compiled by clang 12 onwards, refer to [clang manual](https://clang.llvm.org/docs/UsersManual.html#c-for-opencl) for more details.

This repository makes use of functionality from the [llvm-project](https://github.com/llvm/llvm-project) i.e. clang and libcxx.

### List of currently supported libraries

1. **Type traits**
    * standard C++ type traits, for more information refer to https://en.cppreference.com/w/cpp/header/type_traits.
    * OpenCL specific type traits for vector types, address spaces, images, etc, for more information refer to http://github.khronos.org/libclcxx/opencl__type__traits.html.

Example usage:
```
#include <opencl_type_traits>

using sint_type = std::make_signed<unsigned int>::type;
using sint4_type = std::make_signed<uint4>::type;


template<typename T>
void foo(T *par){
  typename std::remove_address_space<T>::type var;
}

__kernel void bar(__global int * ptr) {
  foo(ptr);
  static_assert(!std::is_same<sint_type, unsigned int>::value);
  static_assert(!std::is_same<sint4_type, uint4>::value);
}
```
This library is implamented fully in header file therefore only include file path need to be added during compilation.

```
$ clang -I<path to libclcxx build or install location>/include test.clcpp
```

2. **Placement new** from standard C++, for more information refer to https://en.cppreference.com/w/cpp/language/new.


Example usage:
```
#include <opencl_new>

class B{
public:
	B(int num = 24)
	: x(num) {}
private:
	int x;
};

void foo(B **b){
	*b = new (buffer) B;
}
```
This library is implamented fully in header file therefore only include file path need to be added during compilation.

```
$ clang -I<path to libclcxx build or install location>/include test.clcpp
```

### Repository structure

* ``include`` folder contains library headers.
* ``docs`` folder contains doxygen files.
* ``test`` folder contains tests for the libraries.

### Getting the source code and building libclcxx

1. Clone libclcxx:

	* ``git clone https://github.com/KhronosGroup/libclcxx.git``

2. Configure and build libclcxx and its dependencies:

	* ``cd libclcxx``

	* ``mkdir build && cd build``

	* ``cmake -G <generator> [config options] [build options] ..``

		Common build system generators include:

		* ``Ninja`` --- **recommended**.
		* ``Unix Makefiles``

		Config options include:

		* Ommiting the config options will build the ``default`` target which includes clang and libcxx.
		* ``-DDEFAULT_CLANG=ON`` --- Uses system installation of clang to build libcxx and compile tests. Note that this option only works if the environment variable for clang is ``clang`` and not ``clang-12`` or ``clang-13``, use ``-DCLANG_PATH=<path to clang executable>`` in those cases.
		* ``-DCLANG_PATH=<path to clang executable>`` --- Uses provided executable of clang to build libcxx and compile tests.
		* ``-DDEFAULT_LIBCXX=ON`` --- Uses system installation of libcxx to build clang and compile tests. Note that libcxx needs to be installed in the ``CMAKE_INSTALL_PREFIX`` directory for this option to work, otherwise use ``-DPATH_TO_LIBCXX=<path to libcxx>``. **Please note that you may need to use ``sudo`` when building ``tools`` for this option to work.**
		* ``-DLIBCXX_PATH=<path to libcxx>`` --- Uses the provided libcxx installation to build clang and compile tests. Note that the path needs to be to directory which has the ``include/c++/v1/`` directory within it. **Please omit the trailing '/' in the libcxx path.**
		* If both ``-DCLANG_PATH`` and ``-DLIBCXX_PATH`` are provided, the provided clang and libcxx installations are used to compile the tests only.
		* If both ``-DDEFAULT_CLANG`` and ``-DDEFAULT_LIBCXX`` are provided, the default clang and libcxx installations are used to compile the tests only.
		* If either ``-DCLANG_PATH`` and ``-DDEFAULT_LIBCXX`` or ``-DLIBCXX_PATH`` and ``-DDEFAULT_CLANG`` combinations are used then the relevant installations are used.

		Some common build options include:

		* ``-DLLVM_PARALLEL_LINK_JOBS=<number of link jobs>`` --- Specify the number of link jobs manually. This is useful when running into memory issues during the linking process of the LLVM executables.

		* ``-DLLVM_TARGETS_TO_BUILD="<target architecture>"`` --- Specifies which targets are enabled. If ommited, the default target is set to ``X86``.

	* ``<generator> build-all`` --- to build the ``tools``, tests and documentation.

	* ``<generator> tools`` --- to build llvm tools (clang or libcxx or both).

	* ``<generator> test`` --- to build libclcxx tests

	* ``<generator> docs`` --- to build Doxygen documentation for libclcxx.

		To clean the documentation built, you can run ``<generator> clean-docs``, this will delete the html documentation from the docs directory.

		To clean the test object files, you can run ``<generator> clean-test``, this will delete the compiled object files from the test source directory.

		To clean the copied ``opencl_<>`` libclcxx source files from your system libcxx installation (if relevant), you can run ``<generator> clean-libclcxx``.

		To clean everything, including build files, Doxygen documentation, compiled test objects and (if relevant) copied libclcxx source files, you can run ``<generator> clean-all``. **Warning, this will clean your build directory!**
