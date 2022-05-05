## Requirements
- Ubuntu 20.04
- LLVM 14.0.3 with NVPTX. See [here](https://gist.github.com/anjohan/9ee746295ea1a00d9ca69415f40fafc9) for installtion instructions.
- Cmake 3.23.1
- CUDA 11.4.3

## Direct execution
- C++ file:

```bash
# source: https://gist.github.com/anjohan/9ee746295ea1a00d9ca69415f40fafc9
# one CPU
clang++ run.cpp -o run
# multi CPU
clang++ -fopenmp run.cpp -o run
# GPU
clang++ -fopenmp -fopenmp-targets=nvptx64 run.cpp -o run
```
- .cu file
```bash
# source: https://llvm.org/docs/CompileCudaWithLLVM.html 
clang++ axpy.cu -o axpy --cuda-gpu-arch=sm_75 -L/usr/local/cuda/lib64 -lcudart_static -ldl -lrt -pthread
```

## With Cmake
- prerequisite
```bash
mkdir build
cd build
```
- C++ file
```bash
# one CPU
rm -rf * && MY_MAIN=cpp MY_DEVICE=CPU cmake .. && make && ./offload
# multi CPU
rm -rf * && MY_MAIN=cpp MY_DEVICE=multiCPU cmake .. && make && ./offload
# GPU
rm -rf * && MY_MAIN=cpp MY_DEVICE=GPU cmake .. && make && ./offload
```
- .cu file
```bash
# one CPU
rm -rf * && MY_MAIN=cu MY_DEVICE=CPU cmake .. && make && ./offload
# multi CPU
rm -rf * && MY_MAIN=cu MY_DEVICE=multiCPU cmake .. && make && ./offload
# GPU
rm -rf * && MY_MAIN=cu MY_DEVICE=GPU cmake .. && make && ./offload
```