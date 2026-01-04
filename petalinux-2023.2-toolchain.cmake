# set cross-compiling to aarch64 for petalinux
set(TOOLCHAIN_DIR /tools/Xilinx/Vitis/2023.2/gnu/aarch64/lin/aarch64-linux/)
#set(CMAKE_SYSROOT ${TOOLCHAIN_DIR}/aarch64-xilinx-linux)

set(CMAKE_C_COMPILER ${TOOLCHAIN_DIR}/bin/aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_DIR}/bin/aarch64-linux-gnu-g++)

set(CMAKE_LINKER ${TOOLCHAIN_DIR}/bin/aarch64-linux-gnu-ld)
set(CMAKE_AR ${TOOLCHAIN_DIR}/bin/aarch64-linux-gnu-ar)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

#set(CMAKE_C_FLAGS "-march=armv7ve")
#set(CMAKE_CXX_FLAGS "-march=armv7ve")
