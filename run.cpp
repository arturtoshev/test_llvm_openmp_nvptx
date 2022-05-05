// source: https://gist.github.com/anjohan/9ee746295ea1a00d9ca69415f40fafc9
// clang++ -fopenmp -fopenmp-targets=nvptx64 run.cpp -o run # GPU
// clang++ -fopenmp run.cpp -o run # multiCPU
// clang++ run.cpp -o run # 1 CPU

#include <cstdio>

int main(){
  int N = 1e8;
  float *x = new float[N];
  float *y = new float[N];

  #pragma omp target teams distribute parallel for map(to: x[0:N]) map(from: y[0:N])
  for(int i = 0; i < N; i++){
    for(int j = 0; j < 1000; j++){
      y[i] += 3*x[i];
    }
  }

  printf("%g\n", y[5]);

  delete [] x;
  delete [] y;
}