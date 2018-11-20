#include "ATen/cuda/CUDAContext.h"
#include "THC/THCGeneral.hpp"

namespace at { namespace cuda {

/* Device info */
int warp_size() {
  return getCurrentDeviceProperties()->warpSize;
}

cudaDeviceProp* getCurrentDeviceProperties() {
  return THCState_getCurrentDeviceProperties(at::globalContext().getTHCState());
}

cudaDeviceProp* getDeviceProperties(int64_t device) {
  return THCState_getDeviceProperties(at::globalContext().getTHCState(), (int)device);
}

/* Streams */
CUDAStream getStreamFromPool(
  const bool isHighPriority
, int64_t device) {
  return CUDAStream(detail::CUDAStream_getStreamFromPool(isHighPriority, device));
}

CUDAStream getDefaultCUDAStream(int64_t device) {
  return CUDAStream(detail::CUDAStream_getDefaultStream(device));
}
CUDAStream getCurrentCUDAStream(int64_t device) {
  return CUDAStream(detail::CUDAStream_getCurrentStream(device));
}

void setCurrentCUDAStream(CUDAStream stream) {
  detail::CUDAStream_setStream(stream.internals());
}
void uncheckedSetCurrentCUDAStream(CUDAStream stream) {
  detail::CUDAStream_uncheckedSetStream(stream.internals());
}

Allocator* getCUDADeviceAllocator() {
  return at::globalContext().getTHCState()->cudaDeviceAllocator;
}

/* Handles */
cusparseHandle_t getCurrentCUDASparseHandle() {
  return THCState_getCurrentSparseHandle(at::globalContext().getTHCState());
}

cublasHandle_t getCurrentCUDABlasHandle() {
  return THCState_getCurrentBlasHandle(at::globalContext().getTHCState());
}

} // namespace cuda

} // namespace at
