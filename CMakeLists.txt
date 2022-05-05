### How to execute
# rm -rf * && MY_MAIN=cpp MY_DEVICE=CPU cmake .. && make && ./offload
# rm -rf * && MY_MAIN=cpp MY_DEVICE=multiCPU cmake .. && make && ./offload
# rm -rf * && MY_MAIN=cpp MY_DEVICE=GPU cmake .. && make && ./offload
# rm -rf * && MY_MAIN=cu MY_DEVICE=CPU cmake .. && make && ./offload
# rm -rf * && MY_MAIN=cu MY_DEVICE=multiCPU cmake .. && make && ./offload
# rm -rf * && MY_MAIN=cu MY_DEVICE=GPU cmake .. && make && ./offload

cmake_minimum_required(VERSION 3.20)
project(offloadTest VERSION 1.0 LANGUAGES CXX CUDA)

# find_package(CUDA)
# message(STATUS "end FindCUDA.cmake")

if($ENV{MY_DEVICE} STREQUAL "multiCPU")  ### multi-CPU with OpenMP
    find_package(OpenMP)  # https://cliutils.gitlab.io/modern-cmake/chapters/packages/OpenMP.html
    link_libraries(OpenMP::OpenMP_CXX)
elseif($ENV{MY_DEVICE} STREQUAL "GPU")  ### GPU
    list(APPEND CMAKE_MODULE_PATH "/usr/local/llvm-14.0.3/install/lib/cmake/openmp") # path $ENV{CMAKE_MODULE_PATH}
    find_package(OpenMPTarget REQUIRED NVPTX)
    link_libraries(OpenMPTarget::OpenMPTarget_NVPTX)
endif()  # in case $ENV{MY_DEVICE}="multiCPU" we don't need to do anything

if($ENV{MY_MAIN} STREQUAL "cu")  # run .cu file
    add_executable(offload ${CMAKE_CURRENT_SOURCE_DIR}/axpy.cu)  # 1 CPU
elseif($ENV{MY_MAIN} STREQUAL "cpp")  # run .cpp file
    add_executable(offload ${CMAKE_CURRENT_SOURCE_DIR}/run.cpp)  # 1 CPU
endif()

### other sources https://www.nersc.gov/assets/GPUs-for-Science-Day/jonathan-madsen.pdf
