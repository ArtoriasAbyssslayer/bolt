cmake_minimum_required(VERSION 3.12)
project(objectVis)

option(BOLT_BUILD_EXAMPLES "Build examples" ON)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
   add_compile_options (-fdiagnostics-color=always)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
   add_compile_options (-fcolor-diagnostics)
endif ()

# Enable ASan in Debug builds
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Building with AddressSanitizer (ASan)")

    set(SANITIZER_FLAGS "-fsanitize=address -fno-omit-frame-pointer -g")

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${SANITIZER_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SANITIZER_FLAGS}")

    # ASan needs special linker flags on some platforms
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fsanitize=address")
endif()

# Main library
add_subdirectory(bolt)

if(BOLT_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
