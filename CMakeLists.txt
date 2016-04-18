cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME "libclcxx")
project(${PROJECT_NAME})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

if ( CMAKE_INSTALL_PREFIX )
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX})
else()
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
endif()

# Lib OpenCL C++ headers
add_subdirectory(include)

# Lib OpenCL C++ tests
add_subdirectory(test)
