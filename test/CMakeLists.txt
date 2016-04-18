set(LIT_EXECUTABLE "" CACHE FILEPATH "Path to LLVM's llvm-lit.")
set(LIBCLCXX_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(LIBCLCXX_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

include(FindPythonInterp)
if(PYTHONINTERP_FOUND)
  set(clHeadersDir ${CMAKE_SOURCE_DIR}/include)
  
  #generating OpenCL C++ tests
  FILE(GLOB_RECURSE pyFiles *.py)
  set(outPyFiles)
  foreach( pyFile ${pyFiles} )
    set(WORKING_DIR "")
	get_filename_component(WORKING_DIR ${pyFile} DIRECTORY)
    execute_process(
      WORKING_DIRECTORY ${WORKING_DIR}
      COMMAND ${PYTHON_EXECUTABLE} ${pyFile} ${clHeadersDir}
      RESULT_VARIABLE result)
    if (NOT ${result} EQUAL 0)
      message( FATAL_ERROR " Test generator ${pyFile} returned error code:" ${result} )
    endif()
  endforeach( pyFile )
  
  #copying all OpenCL C++ files to destination directory
  set(outputDirectory ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/tests)
  set(outOpenCLFiles)
  
  FILE(GLOB_RECURSE clFiles RELATIVE ${CMAKE_SOURCE_DIR}/test *.cl)
  foreach( clFile ${clFiles} )
    set(filePath "")
    get_filename_component(cl_file ${clFile} REALPATH)
    get_filename_component(cl_path ${clFile} DIRECTORY)
    install (FILES ${cl_file} DESTINATION ${outputDirectory}/${cl_path})
  endforeach( clFile )
  install (FILES ${CMAKE_SOURCE_DIR}/test/libclcxx/lit.cfg DESTINATION ${outputDirectory}/libclcxx)
  install (FILES ${CMAKE_SOURCE_DIR}/test/libclcxx/lit.site.cfg DESTINATION ${outputDirectory}/libclcxx)
    
  #creating LIT target
  set(LIT_ARGS_DEFAULT "-sv --show-unsupported --show-xfail")
  if (MSVC OR XCODE)
    set(LIT_ARGS_DEFAULT "${LIT_ARGS_DEFAULT} --no-progress-bar")
  endif()
  set(LLVM_LIT_ARGS "${LIT_ARGS_DEFAULT}"
      CACHE STRING "Default options for lit")
  set(LIT_ARGS "${LLVM_LIT_ARGS}")
  separate_arguments(LIT_ARGS)
  
  add_custom_target(check-libclcxx
    COMMAND ${LIT_EXECUTABLE}
            ${LIT_ARGS}
            .
    WORKING_DIRECTORY ${outputDirectory}/libclcxx
    COMMENT "Running libclcxx tests")
else()
  message(ERROR "Could not find Python")
endif()
