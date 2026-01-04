cmake_minimum_required(VERSION 2.8...3.5)
project (ae-smi)

# CMP0048 error.
if (CMAKE_VERSION VERSION_LESS 3.0)
    cmake_policy(SET CMP0048 OLD)
else()
    cmake_policy(SET CMP0048 NEW)
endif()


set (AESMI_MAJOR 3)
set (AESMI_MINOR 0)
set (AESMI_PATCH 3)
set (AESMI_BUILD 17)

add_definitions(-DAESMI_MAJOR=${AESMI_MAJOR} -DAESMI_MINOR=${AESMI_MINOR} -DAESMI_PATCH=${AESMI_PATCH} -DAESMI_BUILD=${AESMI_BUILD})


# build in different platform, according to cmake marco
message(STATUS "Config Environment: ${CMAKE_SYSTEM_NAME}")
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
        # set binary install directories
        set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR}/install CACHE STRING "install directory")
        set(CMAKE_C_FLAGS_RELEASE "/MD /Od /Ob2 /DNDEBUG")
        set(CMAKE_CXX_FLAGS_RELEASE "/MD /Od /Ob2 /DNDEBUG")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # set binary install directories
	if(NOT CMAKE_BUILD_TYPE)
  		set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
	endif()
    set(CMAKE_INSTALL_PREFIX "/usr/local/rpp" CACHE PATH "" FORCE)
    # if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    #     message(STATUS "Enable AddressSanitizer for Debug build")
    #     set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer -g -Wall -Wextra")
    #     set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer -g -Wall -Wextra")
    #     set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -fsanitize=address -static-libasan -Wl,-z,defs -Wl,--as-needed")
    #     set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} -fsanitize=address -static-libasan")
    # endif()
else()
	message(STATUS "Error Config Environment: ${CMAKE_SYSTEM_NAME}")
endif()



# build
add_subdirectory(demo)

#
