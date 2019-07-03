
# ----------------------------------------------------------------------------------------
#                         ===== CUDA Configuration =====

if (CMAKE_CUDA_COMPILER)
  set(CMAKE_CUDA_STANDARD 14)
  find_library(CUDART_LIBRARY cudart ${CMAKE_CUDA_IMPLICIT_LINK_DIRECTORIES})
  include_directories(${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES})
  set(CUDA_SEPARABLE_COMPILATION ON)
  set(CUDA_RESOLVE_DEVICE_SYMBOLS ON)
  set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} --expt-relaxed-constexpr -lineinfo")
  set(CMAKE_CUDA_FLAGS_RELEASE "${CMAKE_CUDA_FLAGS_RELEASE}")
  set(CUDA_GENCODE_FLAGS "${CUDA_GENCODE_FLAGS} -gencode arch=compute_60,code=sm_70")
  set(CUDA_GENCODE_FLAGS "${CUDA_GENCODE_FLAGS} -gencode arch=compute_61,code=sm_61")
  set(CUDA_GENCODE_FLAGS "${CUDA_GENCODE_FLAGS} -gencode arch=compute_60,code=sm_60")
  set(CUDA_GENCODE_FLAGS "${CUDA_GENCODE_FLAGS} -gencode arch=compute_50,code=sm_50")
  set(CUDA_GENCODE_FLAGS "${CUDA_GENCODE_FLAGS} -gencode arch=compute_37,code=sm_37")
  set(CUDA_GENCODE_FLAGS "${CUDA_GENCODE_FLAGS} -gencode arch=compute_35,code=sm_35")
  set(CUDA_GENCODE_FLAGS "${CUDA_GENCODE_FLAGS} -gencode arch=compute_30,code=sm_30")
endif()

####################### TODOJ: Check these flags ##############################
#
## optimize in release
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -march=native -O3")
#
## build debug with sanitizer
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer")
#
#if(${COMPILER_ID} MATCHES "GNU") # gcc specific flags
#    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -funroll-loops")
#    add_definitions("-Wextra -Wpedantic")
#elseif(${COMPILER_ID} MATCHES "clang") # clang specific flags
#    add_definitions("-Weverything")
#endif()
##############################################################################

# ----------------------------------------------------------------------------------------
#                              ===== Build targets =====

add_library(common SCAMP/src/common.cpp)

if (CMAKE_CUDA_COMPILER)
  add_library(qt_kernels SCAMP/src/qt_kernels.cu)
  set_target_properties(qt_kernels
                      PROPERTIES
                      POSITION_INDEPENDENT_CODE ON
					  COMPILE_FLAGS "${COMPILE_FLAGS} ${CUDA_GENCODE_FLAGS}") 


  add_library(gpu_kernels SCAMP/src/kernels.cu)
  target_link_libraries(gpu_kernels common)
  set_target_properties(gpu_kernels
                      PROPERTIES
                      POSITION_INDEPENDENT_CODE ON
					  COMPILE_FLAGS "${COMPILE_FLAGS} ${CUDA_GENCODE_FLAGS}") 

endif()

add_library(qt_helper SCAMP/src/qt_helper.cpp) 
target_link_libraries(qt_helper 
					common
					$<$<BOOL:${CMAKE_CUDA_COMPILER}>:cufft>
					$<$<BOOL:${CMAKE_CUDA_COMPILER}>:qt_kernels>)


add_library(cpu_stats SCAMP/src/cpu_stats.cpp)
target_link_libraries(cpu_stats common)

add_library(cpu_kernels SCAMP/src/cpu_kernels.cpp)
target_link_libraries(cpu_kernels common)

add_library(tile SCAMP/src/tile.cpp) 
target_link_libraries(tile 
					$<$<BOOL:${CMAKE_CUDA_COMPILER}>:gpu_kernels>
					cpu_kernels 
					qt_helper) 


add_library(scamp SCAMP/src/SCAMP.cpp) 
target_link_libraries(scamp PRIVATE tile cpu_stats)


set_target_properties(scamp
	PROPERTIES
	POSITION_INDEPENDENT_CODE ON) 

set_target_properties(common
                      PROPERTIES
                      POSITION_INDEPENDENT_CODE ON) 

set_target_properties(qt_helper
                      PROPERTIES
                      POSITION_INDEPENDENT_CODE ON) 

set_target_properties(cpu_stats
                      PROPERTIES
                      POSITION_INDEPENDENT_CODE ON) 

set_target_properties(cpu_kernels
                      PROPERTIES
                      POSITION_INDEPENDENT_CODE ON) 

set_target_properties(tile
                      PROPERTIES
                      POSITION_INDEPENDENT_CODE ON) 

set(SCAMP_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)

