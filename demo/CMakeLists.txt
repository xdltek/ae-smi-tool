cmake_minimum_required(VERSION 2.8...3.5)

set(TARGET ae-smi-fan-demo)

file(GLOB common_src "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
add_executable(${TARGET} ${common_src})

# common link
# Link against the static library librpp_smi.a and its dependencies
# librpp_smi.a depends on libuv (for mutex functions) and librpp_osal (for HAL functions)

# Try to find the dependency libraries
# You can set these variables if libraries are in non-standard locations:
# set(UV_A_LIB_PATH "/path/to/libuv_a.a")
# set(RPP_OSAL_A_LIB_PATH "/path/to/librpp_osal_a.a")

if(UV_A_LIB_PATH)
    set(UV_LIB ${UV_A_LIB_PATH})
else()
    find_library(UV_LIB NAMES uv_a libuv_a PATHS 
        /usr/local/lib 
        /usr/local/rpp/lib
        ${CMAKE_CURRENT_SOURCE_DIR}/../../rpp_llm/rpp/lib
        ${CMAKE_CURRENT_SOURCE_DIR}/../../rpp_osal/build
        NO_DEFAULT_PATH
    )
    if(NOT UV_LIB)
        # Try system-wide
        find_library(UV_LIB NAMES uv_a libuv_a)
    endif()
endif()

if(RPP_OSAL_A_LIB_PATH)
    set(RPP_OSAL_LIB ${RPP_OSAL_A_LIB_PATH})
else()
    find_library(RPP_OSAL_LIB NAMES rpp_osal_a librpp_osal_a PATHS 
        /usr/local/lib 
        /usr/local/rpp/lib
        ${CMAKE_CURRENT_SOURCE_DIR}/../../rpp_llm/rpp/lib
        ${CMAKE_CURRENT_SOURCE_DIR}/../../rpp_osal/build
        NO_DEFAULT_PATH
    )
    if(NOT RPP_OSAL_LIB)
        # Try system-wide
        find_library(RPP_OSAL_LIB NAMES rpp_osal_a librpp_osal_a)
    endif()
endif()

# Link libraries
# libuv_a.a requires pthread and dl system libraries
# For static libraries, link order matters: link dependencies after the libraries that need them
# librpp_osal_a.a depends on libuv_a.a, so link libuv_a.a after librpp_osal_a.a
if(UV_LIB AND RPP_OSAL_LIB)
    target_link_libraries(${TARGET} 
        ${CMAKE_CURRENT_SOURCE_DIR}/../lib/librpp_smi.a
        ${RPP_OSAL_LIB}
        ${UV_LIB}
        pthread
        dl
        rt
    )
else()
    # Fallback: try linking by name (if libraries are in system path)
    target_link_libraries(${TARGET} 
        ${CMAKE_CURRENT_SOURCE_DIR}/../lib/librpp_smi.a
        rpp_osal_a
        uv_a
        pthread
        dl
        rt
    )
    if(NOT UV_LIB)
        message(WARNING "libuv_a not found. You may need to set UV_A_LIB_PATH")
    endif()
    if(NOT RPP_OSAL_LIB)
        message(WARNING "librpp_osal_a not found. You may need to set RPP_OSAL_A_LIB_PATH")
    endif()
endif()

target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../inc
                                     PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../lib ${CMAKE_CURRENT_SOURCE_DIR})

