# Usage: emcmake cmake -S . -B <builddir>

cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# Set the project name
project(vAmigaCore)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

# Set the optimization level (if not specified on the command line)
if(NOT CMAKE_BUILD_TYPE)
#  set(CMAKE_BUILD_TYPE Release)
endif()

# Add the emulator library
add_library(vAmigaCore Components/Amiga.cpp)

# Specify compile options
target_compile_definitions(vAmigaCore PUBLIC _USE_MATH_DEFINES)
target_compile_options(vAmigaCore PRIVATE -Wall -Werror)
target_compile_options(vAmigaCore PRIVATE -Wno-unused-parameter -Wno-unused-but-set-variable)
target_compile_options(vAmigaCore PRIVATE -O3 -mnontrapping-fptoint -fwasm-exceptions)
target_compile_options(vAmigaCore PRIVATE -Wfatal-errors)
target_compile_options(vAmigaCore PRIVATE -sWASM_WORKERS)
set_target_properties(vAmigaCore PROPERTIES LINK_FLAGS "-O1 -mnontrapping-fptoint -fwasm-exceptions" )

# Add include paths
target_include_directories(vAmigaCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Add sub directories
add_subdirectory(Base)
add_subdirectory(Components)
add_subdirectory(FileSystems)
add_subdirectory(Media)
add_subdirectory(Misc)
add_subdirectory(Peripherals)
add_subdirectory(ThirdParty)
add_subdirectory(Utilities)

# Add libraries
target_link_libraries(vAmigaCore xdms softfloat)
