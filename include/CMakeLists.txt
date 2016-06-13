set(files
  opencl_array
  opencl_atomic
  opencl_common
  opencl_convert
  opencl_def
  opencl_device_queue
  opencl_functional
  opencl_geometric
  opencl_half
  opencl_image
  opencl_integer
  opencl_limits
  opencl_iterator
  opencl_math
  opencl_math_constants
  opencl_marker
  opencl_memory
  opencl_pipe
  opencl_printf
  opencl_range
  opencl_reinterpret
  opencl_relational
  opencl_synchronization
  opencl_tuple
  opencl_type_traits
  opencl_utility
  opencl_vec
  opencl_vector_load_store
  opencl_vector_utility
  opencl_work_group
  opencl_work_item
  __ocl_array.h
  __ocl_atomic.h
  __ocl_atomic_enum.h
  __ocl_atomic_impl.h
  __ocl_atomic_traits.h
  __ocl_config.h
  __ocl_convert.h
  __ocl_data.h
  __ocl_device_queue.h
  __ocl_enqueue_helpers.h
  __ocl_enqueue_verify.h
  __ocl_functions_macros.h
  __ocl_image_enums.h
  __ocl_image_traits.h
  __ocl_image_traits_helpers.h
  __ocl_images.h
  __ocl_iterator.h
  __ocl_images_forward.h
  __ocl_marker_type.h
  __ocl_limits.h
  __ocl_limits_values.h
  __ocl_limits_enums.h
  __ocl_memory.h
  __ocl_pipes.h
  __ocl_pipes_enums.h
  __ocl_range.h
  __ocl_reinterpret.h
  __ocl_sampler.h
  __ocl_spirv_access_opcodes.h
  __ocl_spirv_atomic_opcodes.h
  __ocl_spirv_common_opcodes.h
  __ocl_spirv_enqueue_opcodes.h
  __ocl_spirv_image_opcodes.h
  __ocl_spirv_memory_opcodes.h
  __ocl_spirv_pipe_opcodes.h
  __ocl_spirv_printf_opcode.h
  __ocl_spirv_sampler_opcodes.h
  __ocl_swizzle_engine.h
  __ocl_swizzle_macros.h
  __ocl_type_traits.h
  __ocl_type_traits_address_spaces.h
  __ocl_type_traits_base.h
  __ocl_type_traits_cv_ref_ptr.h
  __ocl_type_traits_declval.h
  __ocl_type_traits_extents.h
  __ocl_type_traits_helpers.h
  __ocl_type_traits_property_queries.h
  __ocl_type_traits_supported_operations.h
  __ocl_type_traits_type_categories.h
  __ocl_type_traits_type_generators.h
  __ocl_type_traits_type_manipulation.h
  __ocl_type_traits_type_properties.h
  __ocl_type_traits_type_relations.h
  __ocl_type_traits_vectors.h
  __ocl_utility.h
  __ocl_vec.h
  __ocl_vector_utility.h
  )

set(output_dir ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/include/openclc++)
set(out_files)
foreach( f ${files} )
  set( src ${CMAKE_CURRENT_SOURCE_DIR}/${f} )
  set( dst ${output_dir}/${f} )
  add_custom_command(OUTPUT ${dst}
    DEPENDS ${src}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${src} ${dst}
    COMMENT "Copying clang's ${f}...")
  list(APPEND out_files ${dst})
endforeach( f )


install(
  FILES ${files}
  PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
  DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/include/openclc++)