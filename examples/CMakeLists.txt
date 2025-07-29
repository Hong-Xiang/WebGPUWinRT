add_executable(BasicExample basic_example.cpp)

target_link_libraries(BasicExample 
    PRIVATE 
        WebGPUWinRT
)

# Copy WebGPU binaries to the output directory
target_copy_webgpu_binaries(BasicExample)
