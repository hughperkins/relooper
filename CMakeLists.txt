cmake_minimum_required(VERSION 2.8)

option(BUILD_TESTS "Build tests" OFF)

set(CMAKE_CC_FLAGS "-fPIC")
set(LLVM_COMPILE_FLAGS "-fvisibility-inlines-hidden -ffunction-sections -fdata-sections")
set(CMAKE_CXX_FLAGS "-std=c++11 -fPIC ${LLVM_COMPILE_FLAGS}")
add_definitions(-DUSE_CLEW)  # turns off direct linking with libOpenCL.so, all goes via clew dynamic loader (no need to link with libOpenCL at build time)
# for llvm:
add_definitions(-D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS)

set (LLVM_LIBS /usr/lib/llvm-3.8/lib/libLLVM.so)

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-rpath,$ORIGIN")

add_library(relooper SHARED Relooper.cpp)
target_include_directories(relooper PRIVATE /usr/lib/llvm-3.8/include)
set_target_properties(relooper PROPERTIES
    LINK_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${LLVM_LDFLAGS}"
)
target_link_libraries(relooper "${LLVM_LIBS}")

if(BUILD_TESTS)
    add_executable(test1 test/test1.cpp third_party/argparsecpp/argparsecpp.cpp)
    target_include_directories(test1 PRIVATE third_party/argparsecpp)
    target_include_directories(test1 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    target_include_directories(test1 PRIVATE /usr/lib/llvm-3.8/include)
    target_link_libraries(test1 relooper)
endif()
