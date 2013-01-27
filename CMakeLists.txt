project(dragonc)
cmake_minimum_required(VERSION 2.6)

execute_process(COMMAND llvm-config --cppflags
                OUTPUT_VARIABLE LLVM_FLAGS)

execute_process(COMMAND llvm-config --ldflags
                OUTPUT_STRIP_TRAILING_WHITESPACE      
                OUTPUT_VARIABLE LLVM_LD_FLAGS)

execute_process(COMMAND llvm-config --libs core
                OUTPUT_STRIP_TRAILING_WHITESPACE      
                OUTPUT_VARIABLE LLVM_LIBS)

set(CMAKE_C_COMPILER clang) 
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_LINKER llvm-link)
add_definitions("${LLVM_FLAGS}")


set(CMAKE_BUILD_TYPE Debug CACHE STRING "default to debug" FORCE)

aux_source_directory("${PROJECT_SOURCE_DIR}/src/." SRC_LIST)
file(GLOB INCLUDE_LIST "${PROJECT_SOURCE_DIR}/include/*.h")


include_directories("${PROJECT_SOURCE_DIR}/include/")

add_executable(${PROJECT_NAME} ${SRC_LIST} ${INCLUDE_LIST})
target_link_libraries(${PROJECT_NAME} ${LLVM_LD_FLAGS} ${LLVM_LIBS})
