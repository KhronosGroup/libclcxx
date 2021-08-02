CMAKE_MINIMUM_REQUIRED(VERSION 3.20.5)

option(DEFAULT_CLANG "Use installation of clang in your system" OFF)
set(CLANG_PATH "" CACHE STRING "path/to/clang")
option(DEFAULT_LIBCXX "Use installation of libcxx in your system" OFF)
set(LIBCXX_PATH "" CACHE STRING "path/to/libcxx")

if (DEFAULT_CLANG)
  set(CMAKE_C_COMPILER "clang")
  set(CMAKE_CXX_COMPILER "clang")
endif()

if (NOT CLANG_PATH STREQUAL "")
  set(CMAKE_C_COMPILER "${CLANG_PATH}")
  set(CMAKE_CXX_COMPILER "${CLANG_PATH}")
endif()

project(libclcxx)

set(CUSTOM_COMMAND_USED OFF CACHE BOOL "A variable to see if a custom configuration command is called")
set(LLVM_TARGETS_TO_BUILD="X86" CACHE STRING "This is the default target build system type")
set(CMAKE_BUILD_TYPE "Debug")

# Default clang build; uses the command "clang" to call and use clang to compile libcxx and tests
# Note this option only works if the clang executable or symlink is called "clang" and not "clang-12" or "clang-13"
# In those cases it's recommended to use the CLANG_PATH option
if (DEFAULT_CLANG)
  if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 12)
    message(FATAL_ERROR "Libclcxx does not support clang versions older than clang-12")
  endif()
  set(CUSTOM_COMMAND_USED ON)
  set(LLVM_ENABLE_PROJECTS "libcxx;libcxxabi" CACHE STRING "Enable projects libcxx and libcxxabi" FORCE)
  set(LLVM_ENABLE_LIBCXX ON CACHE BOOL "This is required to allow libstdc++ tests to pass" FORCE)
  add_subdirectory(llvm-project/llvm)
  message(STATUS "Using default clang installation in system")
  message(STATUS "Configuring tests")
  if (CMAKE_CXX_COMPILER_VERSION EQUAL 12)
    set(EXTRA_CLANG_12_FLAGS "-x cl -Xclang -finclude-default-header -Xclang -fdeclare-opencl-builtins -cl-std=clc++")
  endif()
  add_custom_target(
    tools
    DEPENDS cxx
    )
  add_custom_command(
    TARGET tools
    POST_BUILD
    COMMAND cp ${CMAKE_SOURCE_DIR}/include/* ${CMAKE_BINARY_DIR}/llvm-project/llvm/include/c++/v1/
    COMMENT "Copying libclcxx include files into build include dir"
    )
  add_custom_target(
    test
    COMMAND cd ${CMAKE_SOURCE_DIR}/test/ && make PATH_TO_LIBCXX_INCLUDE=${CMAKE_BINARY_DIR}/llvm-project/llvm/include/c++/v1/ EXTRA_ARGS=${EXTRA_CLANG_12_FLAGS}
    )
  add_custom_target(
    clean_test
    COMMAND cd ${CMAKE_SOURCE_DIR}/test && make clean
    )
endif()

# Clang path given build; Builds libcxx and compiles tests using the clang executable path provided
if (NOT CLANG_PATH STREQUAL "")
  if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 12)
    message(FATAL_ERROR "Libclcxx does not support clang versions older than clang-12")
  endif()
  set(CUSTOM_COMMAND_USED ON)
  set(LLVM_ENABLE_PROJECTS "libcxx;libcxxabi" CACHE STRING "Enable projects libcxx and libcxxabi" FORCE)
  set(LLVM_ENABLE_LIBCXX ON CACHE BOOL "This is required to allow libstdc++ tests to pass" FORCE)
  add_subdirectory(llvm-project/llvm)
  message(STATUS "Using path to clang executable provided")
  message(STATUS "Configuring tests")
  if (CMAKE_CXX_COMPILER_VERSION EQUAL 12)
    set(EXTRA_CLANG_12_FLAGS "-x cl -Xclang -finclude-default-header -Xclang -fdeclare-opencl-builtins -cl-std=clc++")
  endif()
  add_custom_target(
    tools
    DEPENDS cxx
    )
  add_custom_command(
    TARGET tools
    POST_BUILD
    COMMAND cp ${CMAKE_SOURCE_DIR}/include/* ${CMAKE_BINARY_DIR}/llvm-project/llvm/include/c++/v1/
    COMMENT "Copying libclcxx include files into build include dir"
    )
  add_custom_target(
    test
    COMMAND cd ${CMAKE_SOURCE_DIR}/test/ && make PATH_TO_LIBCXX_INCLUDE=${CMAKE_BINARY_DIR}/llvm-project/llvm/include/c++/v1/ CLANG_PATH=${CLANG_PATH} EXTRA_ARGS=${EXTRA_CLANG_12_FLAGS}
    )
  add_custom_target(
    clean_test
    COMMAND cd ${CMAKE_SOURCE_DIR}/test && make clean
    )
endif()

# Default libcxx build; uses default installation of libcxx in system
if (DEFAULT_LIBCXX)
  set(CUSTOM_COMMAND_USED ON)
  set(LLVM_ENABLE_PROJECTS "clang" CACHE STRING "Enable project clang")
  add_subdirectory(llvm-project/llvm)
  message(STATUS "Using default libcxx installation in system")
  message(STATUS "Configuring tests")
  add_custom_target(
    tools
    DEPENDS clang
    )
  add_custom_command(
    TARGET tools
    POST_BUILD
    COMMAND cp ${CMAKE_SOURCE_DIR}/include/* ${CMAKE_INSTALL_PREFIX}/include/c++/v1/
    COMMENT "Copying libclcxx include files into build include dir"
    )
  add_custom_target(
    test
    COMMAND cd ${CMAKE_SOURCE_DIR}/test/ && make PATH_TO_LIBCXX_INCLUDE=${CMAKE_INSTALL_PREFIX}/include/c++/v1/ CLANG_PATH=${CMAKE_BINARY_DIR}/llvm-project/llvm/bin/clang-13
    )
  add_custom_target(
    clean_test
    COMMAND cd ${CMAKE_SOURCE_DIR}/test && make clean
    )
  add_custom_target(
    remove_libclcxx
    command cd ${CMAKE_INSTALL_PREFIX}/include/c++/v1/ && rm opencl_*
    )
endif()

# Libcxx path given build; builds clang using default system compiler and compiles tests using built clang and libcxx library path provided
if (NOT LIBCXX_PATH STREQUAL "")
  set(CUSTOM_COMMAND_USED ON)
  #set(LLVM_ENABLE_LIBCXX ON CACHE BOOL "This is required to allow libstdc++ tests to pass" FORCE)
  set(LLVM_ENABLE_PROJECTS "clang" CACHE STRING "Enable project clang")
  add_subdirectory(llvm-project/llvm)
  message(STATUS "Using path to libcxx provided")
  message(STATUS "Configuring tests")
  add_custom_target(
    tools
    DEPENDS clang
    )
  add_custom_command(
    TARGET tools
    POST_BUILD
    COMMAND cp ${CMAKE_SOURCE_DIR}/include/* ${LIBCXX_PATH}/include/c++/v1/
    COMMENT "Copying libclcxx include files into build include dir"
    )
  add_custom_target(
    test
    COMMAND cd ${CMAKE_SOURCE_DIR}/test/ && make PATH_TO_LIBCXX_INCLUDE=${LIBCXX_PATH}/include/c++/v1/ CLANG_PATH=${CMAKE_BINARY_DIR}/llvm-project/llvm/bin/clang-13
    )
  add_custom_target(
    clean_test
    COMMAND cd ${CMAKE_SOURCE_DIR}/test && make clean
    )
  add_custom_target(
    remove_libclcxx
    command cd ${LIBCXX_PATH}/include/c++/v1/ && rm opencl_*
    )
endif()

# Default build; builds clang and libcxx and uses the newly built clang to compile tests
if (NOT CUSTOM_COMMAND_USED)
  set(LLVM_ENABLE_PROJECTS "clang;libcxx;libcxxabi" CACHE STRING "Enable projects clang, libcxx and libcxxabi" FORCE)
  set(LLVM_ENABLE_LIBCXX ON CACHE BOOL "This is required to allow libstdc++ tests to pass" FORCE)
  add_subdirectory(llvm-project/llvm)
  message(STATUS "Configuring builds of clang, libcxx and libcxxabi into build folder")
  message(STATUS "Configuring tests")
  add_custom_target(
    tools
    DEPENDS clang cxx
    )
  add_custom_command(
    TARGET tools
    POST_BUILD
    COMMAND cp ${CMAKE_SOURCE_DIR}/include/* ${CMAKE_BINARY_DIR}/llvm-project/llvm/include/c++/v1/
    COMMENT "Copying libclcxx include files into build include dir"
    )
  add_custom_target(
    test
    COMMAND cd ${CMAKE_SOURCE_DIR}/test/ && make PATH_TO_LIBCXX_INCLUDE=${CMAKE_BINARY_DIR}/llvm-project/llvm/include/c++/v1/ CLANG_PATH=${CMAKE_BINARY_DIR}/llvm-project/llvm/bin/clang-13
    )
  add_custom_target(
    clean_test
    COMMAND cd ${CMAKE_SOURCE_DIR}/test && make clean
    )
endif()

