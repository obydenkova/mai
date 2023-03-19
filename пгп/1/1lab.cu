#include <iostream>
#include <cstdio>
#include <chrono>

using namespace std;

__global__ void kernel(double *res, double *arr1, double *arr2, int n) {
    int idx = blockDim.x * blockIdx.x + threadIdx.x;			// Абсолютный номер потока
    int offset = blockDim.x * gridDim.x;						// Общее кол-во потоков
    for(int i = idx; i < n; i += offset) {
        res[i] = arr1[i] * arr2[i];
    }
}

int main() {
    int n;
    scanf("%d", &n);
    double *res = (double *)malloc(sizeof(double) * n);
    double *vec1 = (double *)malloc(sizeof(double) * n);
    double *vec2 = (double *)malloc(sizeof(double) * n);
    for(int i = 0; i < n; i++)
        scanf("%lf", &vec1[i]);
    for(int i = 0; i < n; i++)
        scanf("%lf", &vec2[i]);

    double *dev_res, *dev_vec1, *dev_vec2;
    cudaMalloc(&dev_res, sizeof(double) * n);
    cudaMemcpy(dev_res, res, sizeof(double) * n, cudaMemcpyHostToDevice);

    cudaMalloc(&dev_vec1, sizeof(double) * n);
    cudaMemcpy(dev_vec1, vec1, sizeof(double) * n, cudaMemcpyHostToDevice);

    cudaMalloc(&dev_vec2, sizeof(double) * n);
    cudaMemcpy(dev_vec2, vec2, sizeof(double) * n, cudaMemcpyHostToDevice);


    cudaEvent_t start, stop;
    float time;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start, 0);

    kernel<<<256, 256>>>(dev_res, dev_vec1, dev_vec2, n);

    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&time, start, stop);
    fprintf(stderr, "time = %f\n", time);
    cudaEventDestroy(stop);
    cudaEventDestroy(start);


    cudaMemcpy(res, dev_res, sizeof(double) * n, cudaMemcpyDeviceToHost);
    cudaFree(dev_res);
    cudaFree(dev_vec1);
    cudaFree(dev_vec2);
    for(int i = 0; i < n; i++) {
        printf("%f ", res[i]);
    }
    printf("\n");
    free(res);
    free(vec1);
    free(vec2);
    return 0;
}
