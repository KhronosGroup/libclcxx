OpenCL C++ Standard Library Instructions
================================================

The instructions how to build SPIR-V generator/Clang can be found here:
  https://github.com/KhronosGroup/SPIR/tree/spirv-1.1

-----------------------------------
Step 1: OpenCL C++ standard library
-----------------------------------

To clone the OpenCL C++ standard libary use the following cmdline:

```bash
  git clone https://github.com/KhronosGroup/libclcxx.git master
```

--------------------------------
Step 2: Creating SPIR-V binaries
--------------------------------

To create a SPIR-V binary from a valid OpenCL-C file (.cl), use the following
command lines:

```bash
  clang -cc1 -emit-spirv -triple <triple> -cl-std=c++ -I <libclcxx dir> -x cl -o <output> <input>
```

Notes:

* `<triple>`: for 32 bit SPIR-V use spir-unknown-unknown, for 64 bit SPIR-V use spir64-unknown-unknown.
* -D<extension>: to enable support for extension. e.g. -Dcl_khr_mipmap_image compile option will enable mipmap support.
* -cl-fp16-enable: to enable half support and define cl_khr_fp16
* -cl-fp64-enable: to enable double support and define cl_khr_fp64
* -O<optimization level>: -O0 (default) is the only tested option value at the moment. It's assumed by design that all optimizations are executed by SPIR-V consumer
* `<libclcxx dir>`: path to include directory from libclcxx (https://github.com/KhronosGroup/libclcxx)
.

```bash
  clang -cc1 -emit-spirv -triple=spir-unknown-unknown -cl-std=c++ -I include kernel.cl -o kernel.spir
```

----------------
Reporting issues
----------------

Bugs/feature requests can be filed via [github](https://github.com/KhronosGroup/SPIR/issues) or [Khronos Bugzilla](https://www.khronos.org/bugzilla/) bug tracker.
