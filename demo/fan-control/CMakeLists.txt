cmake_minimum_required(VERSION 2.8...3.5)

set(TARGET ae-smi-fan-demo)

file(GLOB common_src "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
add_executable(${TARGET} ${common_src})

# Library directory - all libraries are in ../lib
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../lib)

# Link libraries (order matters: dependencies after libraries that need them)
target_link_libraries(${TARGET} 
    ${LIB_DIR}/librpp_smi.a
    ${LIB_DIR}/librpp_osal_a.a
    ${LIB_DIR}/libuv_a.a
    pthread
    dl
    rt
)

# Include directories
target_include_directories(${TARGET} 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../inc
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../lib ${CMAKE_CURRENT_SOURCE_DIR}
)

