cmake_minimum_required(VERSION 3.15)

project(WebGPUWinRT VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add WebGPU-distribution as subdirectory
add_subdirectory(WebGPU-distribution)

# Create your main library
add_library(WebGPUWinRT STATIC)

# Add source files
target_sources(WebGPUWinRT
    PRIVATE
        src/WebGPUDevice.cpp
)

# Link against WebGPU
target_link_libraries(WebGPUWinRT 
    PUBLIC 
        webgpu
)

# Include directories
target_include_directories(WebGPUWinRT
    PUBLIC
        include
    PRIVATE
        src
)

# Set target properties for Windows
if(WIN32)
    target_compile_definitions(WebGPUWinRT PRIVATE 
        NOMINMAX
        WIN32_LEAN_AND_MEAN
    )
endif()

# Optional: Create an example executable
option(BUILD_EXAMPLES "Build example applications" ON)

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Optional: Create tests
option(BUILD_TESTS "Build tests" OFF)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
