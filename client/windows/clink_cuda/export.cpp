#include "../common/global.h"
#include "driver_api.h"
#include "export.h"
#include "render.h"

CUresult CUDAAPI cuGetErrorString(CUresult error, const char** pStr) { return Render::getInstance().Dispatch(CUGETERRORSTRING, 2, error, pStr); }
CUresult CUDAAPI cuGetErrorName(CUresult error, const char** pStr) { return Render::getInstance().Dispatch(CUGETERRORNAME, 2, error, pStr); }
CUresult CUDAAPI cuInit(unsigned int Flags) { return Render::getInstance().Dispatch(CUINIT, 1, Flags); }
CUresult CUDAAPI cuDriverGetVersion(int* driverVersion) { return Render::getInstance().Dispatch(CUDRIVERGETVERSION, 1, driverVersion); }
CUresult CUDAAPI cuDeviceGet(CUdevice* device, int ordinal) { return Render::getInstance().Dispatch(CUDEVICEGET, 2, device, ordinal); }
CUresult CUDAAPI cuDeviceGetCount(int* count) { return Render::getInstance().Dispatch(CUDEVICEGETCOUNT, 1, count); }
CUresult CUDAAPI cuDeviceGetName(char* name, int len, CUdevice dev) { return Render::getInstance().Dispatch(CUDEVICEGETNAME, 3, name, len, dev); }
CUresult CUDAAPI cuDeviceGetUuid(CUuuid* uuid, CUdevice dev) { return Render::getInstance().Dispatch(CUDEVICEGETUUID, 2, uuid, dev); }
CUresult CUDAAPI cuDeviceGetUuid_v2(CUuuid* uuid, CUdevice dev) { return Render::getInstance().Dispatch(CUDEVICEGETUUID_V2, 2, uuid, dev); }
CUresult CUDAAPI cuDeviceGetLuid(char* luid, unsigned int* deviceNodeMask, CUdevice dev) { return Render::getInstance().Dispatch(CUDEVICEGETLUID, 3, luid, deviceNodeMask, dev); }
CUresult CUDAAPI cuDeviceTotalMem(size_t* bytes, CUdevice dev) { return Render::getInstance().Dispatch(CUDEVICETOTALMEM, 2, bytes, dev); }
CUresult CUDAAPI cuDeviceGetTexture1DLinearMaxWidth(size_t* maxWidthInElements, CUarray_format format, unsigned numChannels, CUdevice dev) { return Render::getInstance().Dispatch(CUDEVICEGETTEXTURE1DLINEARMAXWIDTH, 4, maxWidthInElements, format, numChannels, dev); }
CUresult CUDAAPI cuDeviceGetAttribute(int* pi, CUdevice_attribute attrib, CUdevice dev) { return Render::getInstance().Dispatch(CUDEVICEGETATTRIBUTE, 3, pi, attrib, dev); }
CUresult CUDAAPI cuDeviceGetNvSciSyncAttributes(void* nvSciSyncAttrList, CUdevice dev, int flags) { return Render::getInstance().Dispatch(CUDEVICEGETNVSCISYNCATTRIBUTES, 3, nvSciSyncAttrList, dev, flags); }
CUresult CUDAAPI cuDeviceSetMemPool(CUdevice dev, CUmemoryPool pool) { return Render::getInstance().Dispatch(CUDEVICESETMEMPOOL, 2, dev, pool); }
CUresult CUDAAPI cuDeviceGetMemPool(CUmemoryPool* pool, CUdevice dev) { return Render::getInstance().Dispatch(CUDEVICEGETMEMPOOL, 2, pool, dev); }
CUresult CUDAAPI cuDeviceGetDefaultMemPool(CUmemoryPool* pool_out, CUdevice dev) { return Render::getInstance().Dispatch(CUDEVICEGETDEFAULTMEMPOOL, 2, pool_out, dev); }
CUresult CUDAAPI cuDeviceGetExecAffinitySupport(int* pi, CUexecAffinityType type, CUdevice dev) { return Render::getInstance().Dispatch(CUDEVICEGETEXECAFFINITYSUPPORT, 3, pi, type, dev); }
CUresult CUDAAPI cuFlushGPUDirectRDMAWrites(CUflushGPUDirectRDMAWritesTarget target, CUflushGPUDirectRDMAWritesScope scope) { return Render::getInstance().Dispatch(CUFLUSHGPUDIRECTRDMAWRITES, 2, target, scope); }
CUresult CUDAAPI cuDeviceGetProperties(CUdevprop* prop, CUdevice dev) { return Render::getInstance().Dispatch(CUDEVICEGETPROPERTIES, 2, prop, dev); }
CUresult CUDAAPI cuDeviceComputeCapability(int* major, int* minor, CUdevice dev) { return Render::getInstance().Dispatch(CUDEVICECOMPUTECAPABILITY, 3, major, minor, dev); }
CUresult CUDAAPI cuDevicePrimaryCtxRetain(CUcontext* pctx, CUdevice dev) { return Render::getInstance().Dispatch(CUDEVICEPRIMARYCTXRETAIN, 2, pctx, dev); }
CUresult CUDAAPI cuDevicePrimaryCtxRelease(CUdevice dev) { return Render::getInstance().Dispatch(CUDEVICEPRIMARYCTXRELEASE, 1, dev); }
CUresult CUDAAPI cuDevicePrimaryCtxSetFlags(CUdevice dev, unsigned int flags) { return Render::getInstance().Dispatch(CUDEVICEPRIMARYCTXSETFLAGS, 2, dev, flags); }
CUresult CUDAAPI cuDevicePrimaryCtxGetState(CUdevice dev, unsigned int* flags, int* active) { return Render::getInstance().Dispatch(CUDEVICEPRIMARYCTXGETSTATE, 3, dev, flags, active); }
CUresult CUDAAPI cuDevicePrimaryCtxReset(CUdevice dev) { return Render::getInstance().Dispatch(CUDEVICEPRIMARYCTXRESET, 1, dev); }
CUresult CUDAAPI cuCtxCreate(CUcontext* pctx, unsigned int flags, CUdevice dev) { return Render::getInstance().Dispatch(CUCTXCREATE, 3, pctx, flags, dev); }
CUresult CUDAAPI cuCtxCreate_v3(CUcontext* pctx, CUexecAffinityParam* paramsArray, int numParams, unsigned int flags, CUdevice dev) { return Render::getInstance().Dispatch(CUCTXCREATE_V3, 5, pctx, paramsArray, numParams, flags, dev); }
CUresult CUDAAPI cuCtxDestroy(CUcontext ctx) { return Render::getInstance().Dispatch(CUCTXDESTROY, 1, ctx); }
CUresult CUDAAPI cuCtxPushCurrent(CUcontext ctx) { return Render::getInstance().Dispatch(CUCTXPUSHCURRENT, 1, ctx); }
CUresult CUDAAPI cuCtxPopCurrent(CUcontext* pctx) { return Render::getInstance().Dispatch(CUCTXPOPCURRENT, 1, pctx); }
CUresult CUDAAPI cuCtxSetCurrent(CUcontext ctx) { return Render::getInstance().Dispatch(CUCTXSETCURRENT, 1, ctx); }
CUresult CUDAAPI cuCtxGetCurrent(CUcontext* pctx) { return Render::getInstance().Dispatch(CUCTXGETCURRENT, 1, pctx); }
CUresult CUDAAPI cuCtxGetDevice(CUdevice* device) { return Render::getInstance().Dispatch(CUCTXGETDEVICE, 1, device); }
CUresult CUDAAPI cuCtxGetFlags(unsigned int* flags) { return Render::getInstance().Dispatch(CUCTXGETFLAGS, 1, flags); }
CUresult CUDAAPI cuCtxSetFlags(unsigned int flags) { return Render::getInstance().Dispatch(CUCTXSETFLAGS, 1, flags); }
CUresult CUDAAPI cuCtxGetId(CUcontext ctx, unsigned long long* ctxId) { return Render::getInstance().Dispatch(CUCTXGETID, 2, ctx, ctxId); }
CUresult CUDAAPI cuCtxSynchronize(void) { return Render::getInstance().Dispatch(CUCTXSYNCHRONIZE, 0); }
CUresult CUDAAPI cuCtxSetLimit(CUlimit limit, size_t value) { return Render::getInstance().Dispatch(CUCTXSETLIMIT, 2, limit, value); }
CUresult CUDAAPI cuCtxGetLimit(size_t* pvalue, CUlimit limit) { return Render::getInstance().Dispatch(CUCTXGETLIMIT, 2, pvalue, limit); }
CUresult CUDAAPI cuCtxGetCacheConfig(CUfunc_cache* pconfig) { return Render::getInstance().Dispatch(CUCTXGETCACHECONFIG, 1, pconfig); }
CUresult CUDAAPI cuCtxSetCacheConfig(CUfunc_cache config) { return Render::getInstance().Dispatch(CUCTXSETCACHECONFIG, 1, config); }
CUresult CUDAAPI cuCtxGetSharedMemConfig(CUsharedconfig* pConfig) { return Render::getInstance().Dispatch(CUCTXGETSHAREDMEMCONFIG, 1, pConfig); }
CUresult CUDAAPI cuCtxSetSharedMemConfig(CUsharedconfig config) { return Render::getInstance().Dispatch(CUCTXSETSHAREDMEMCONFIG, 1, config); }
CUresult CUDAAPI cuCtxGetApiVersion(CUcontext ctx, unsigned int* version) { return Render::getInstance().Dispatch(CUCTXGETAPIVERSION, 2, ctx, version); }
CUresult CUDAAPI cuCtxGetStreamPriorityRange(int* leastPriority, int* greatestPriority) { return Render::getInstance().Dispatch(CUCTXGETSTREAMPRIORITYRANGE, 2, leastPriority, greatestPriority); }
CUresult CUDAAPI cuCtxResetPersistingL2Cache(void) { return Render::getInstance().Dispatch(CUCTXRESETPERSISTINGL2CACHE, 0); }
CUresult CUDAAPI cuCtxGetExecAffinity(CUexecAffinityParam* pExecAffinity, CUexecAffinityType type) { return Render::getInstance().Dispatch(CUCTXGETEXECAFFINITY, 2, pExecAffinity, type); }
CUresult CUDAAPI cuCtxAttach(CUcontext* pctx, unsigned int flags) { return Render::getInstance().Dispatch(CUCTXATTACH, 2, pctx, flags); }
CUresult CUDAAPI cuCtxDetach(CUcontext ctx) { return Render::getInstance().Dispatch(CUCTXDETACH, 1, ctx); }
CUresult CUDAAPI cuModuleLoad(CUmodule* module, const char* fname) { return Render::getInstance().Dispatch(CUMODULELOAD, 2, module, fname); }
CUresult CUDAAPI cuModuleLoadData(CUmodule* module, const void* image) { return Render::getInstance().Dispatch(CUMODULELOADDATA, 2, module, image); }
CUresult CUDAAPI cuModuleLoadDataEx(CUmodule* module, const void* image, unsigned int numOptions, CUjit_option* options, void** optionValues) { return Render::getInstance().Dispatch(CUMODULELOADDATAEX, 5, module, image, numOptions, options, optionValues); }
CUresult CUDAAPI cuModuleLoadFatBinary(CUmodule* module, const void* fatCubin) { return Render::getInstance().Dispatch(CUMODULELOADFATBINARY, 2, module, fatCubin); }
CUresult CUDAAPI cuModuleUnload(CUmodule hmod) { return Render::getInstance().Dispatch(CUMODULEUNLOAD, 1, hmod); }
CUresult CUDAAPI cuModuleGetLoadingMode(CUmoduleLoadingMode* mode) { return Render::getInstance().Dispatch(CUMODULEGETLOADINGMODE, 1, mode); }
CUresult CUDAAPI cuModuleGetFunction(CUfunction* hfunc, CUmodule hmod, const char* name) { return Render::getInstance().Dispatch(CUMODULEGETFUNCTION, 3, hfunc, hmod, name); }
CUresult CUDAAPI cuModuleGetGlobal(CUdeviceptr* dptr, size_t* bytes, CUmodule hmod, const char* name) { return Render::getInstance().Dispatch(CUMODULEGETGLOBAL, 4, dptr, bytes, hmod, name); }
CUresult CUDAAPI cuLinkCreate(unsigned int numOptions, CUjit_option* options, void** optionValues, CUlinkState* stateOut) { return Render::getInstance().Dispatch(CULINKCREATE, 4, numOptions, options, optionValues, stateOut); }
CUresult CUDAAPI cuLinkAddData(CUlinkState state, CUjitInputType type, void* data, size_t size, const char* name, unsigned int numOptions, CUjit_option* options, void** optionValues) { return Render::getInstance().Dispatch(CULINKADDDATA, 8, state, type, data, size, name, numOptions, options, optionValues); }
CUresult CUDAAPI cuLinkAddFile(CUlinkState state, CUjitInputType type, const char* path, unsigned int numOptions, CUjit_option* options, void** optionValues) { return Render::getInstance().Dispatch(CULINKADDFILE, 6, state, type, path, numOptions, options, optionValues); }
CUresult CUDAAPI cuLinkComplete(CUlinkState state, void** cubinOut, size_t* sizeOut) { return Render::getInstance().Dispatch(CULINKCOMPLETE, 3, state, cubinOut, sizeOut); }
CUresult CUDAAPI cuLinkDestroy(CUlinkState state) { return Render::getInstance().Dispatch(CULINKDESTROY, 1, state); }
CUresult CUDAAPI cuModuleGetTexRef(CUtexref* pTexRef, CUmodule hmod, const char* name) { return Render::getInstance().Dispatch(CUMODULEGETTEXREF, 3, pTexRef, hmod, name); }
CUresult CUDAAPI cuModuleGetSurfRef(CUsurfref* pSurfRef, CUmodule hmod, const char* name) { return Render::getInstance().Dispatch(CUMODULEGETSURFREF, 3, pSurfRef, hmod, name); }
CUresult CUDAAPI cuLibraryLoadData(CUlibrary* library, const void* code, CUjit_option* jitOptions, void** jitOptionsValues, unsigned int numJitOptions, CUlibraryOption* libraryOptions, void** libraryOptionValues, unsigned int numLibraryOptions) { return Render::getInstance().Dispatch(CULIBRARYLOADDATA, 8, library, code, jitOptions, jitOptionsValues, numJitOptions, libraryOptions, libraryOptionValues, numLibraryOptions); }
CUresult CUDAAPI cuLibraryLoadFromFile(CUlibrary* library, const char* fileName, CUjit_option* jitOptions, void** jitOptionsValues, unsigned int numJitOptions, CUlibraryOption* libraryOptions, void** libraryOptionValues, unsigned int numLibraryOptions) { return Render::getInstance().Dispatch(CULIBRARYLOADFROMFILE, 8, library, fileName, jitOptions, jitOptionsValues, numJitOptions, libraryOptions, libraryOptionValues, numLibraryOptions); }
CUresult CUDAAPI cuLibraryUnload(CUlibrary library) { return Render::getInstance().Dispatch(CULIBRARYUNLOAD, 1, library); }
CUresult CUDAAPI cuLibraryGetKernel(CUkernel* pKernel, CUlibrary library, const char* name) { return Render::getInstance().Dispatch(CULIBRARYGETKERNEL, 3, pKernel, library, name); }
CUresult CUDAAPI cuLibraryGetModule(CUmodule* pMod, CUlibrary library) { return Render::getInstance().Dispatch(CULIBRARYGETMODULE, 2, pMod, library); }
CUresult CUDAAPI cuKernelGetFunction(CUfunction* pFunc, CUkernel kernel) { return Render::getInstance().Dispatch(CUKERNELGETFUNCTION, 2, pFunc, kernel); }
CUresult CUDAAPI cuLibraryGetGlobal(CUdeviceptr* dptr, size_t* bytes, CUlibrary library, const char* name) { return Render::getInstance().Dispatch(CULIBRARYGETGLOBAL, 4, dptr, bytes, library, name); }
CUresult CUDAAPI cuLibraryGetManaged(CUdeviceptr* dptr, size_t* bytes, CUlibrary library, const char* name) { return Render::getInstance().Dispatch(CULIBRARYGETMANAGED, 4, dptr, bytes, library, name); }
CUresult CUDAAPI cuLibraryGetUnifiedFunction(void** fptr, CUlibrary library, const char* symbol) { return Render::getInstance().Dispatch(CULIBRARYGETUNIFIEDFUNCTION, 3, fptr, library, symbol); }
CUresult CUDAAPI cuKernelGetAttribute(int* pi, CUfunction_attribute attrib, CUkernel kernel, CUdevice dev) { return Render::getInstance().Dispatch(CUKERNELGETATTRIBUTE, 4, pi, attrib, kernel, dev); }
CUresult CUDAAPI cuKernelSetAttribute(CUfunction_attribute attrib, int val, CUkernel kernel, CUdevice dev) { return Render::getInstance().Dispatch(CUKERNELSETATTRIBUTE, 4, attrib, val, kernel, dev); }
CUresult CUDAAPI cuKernelSetCacheConfig(CUkernel kernel, CUfunc_cache config, CUdevice dev) { return Render::getInstance().Dispatch(CUKERNELSETCACHECONFIG, 3, kernel, config, dev); }
CUresult CUDAAPI cuMemGetInfo(size_t* free, size_t* total) { return Render::getInstance().Dispatch(CUMEMGETINFO, 2, free, total); }
CUresult CUDAAPI cuMemAlloc(CUdeviceptr* dptr, size_t bytesize) { return Render::getInstance().Dispatch(CUMEMALLOC, 2, dptr, bytesize); }
CUresult CUDAAPI cuMemAllocPitch(CUdeviceptr* dptr, size_t* pPitch, size_t WidthInBytes, size_t Height, unsigned int ElementSizeBytes) { return Render::getInstance().Dispatch(CUMEMALLOCPITCH, 5, dptr, pPitch, WidthInBytes, Height, ElementSizeBytes); }
CUresult CUDAAPI cuMemFree(CUdeviceptr dptr) { return Render::getInstance().Dispatch(CUMEMFREE, 1, dptr); }
CUresult CUDAAPI cuMemGetAddressRange(CUdeviceptr* pbase, size_t* psize, CUdeviceptr dptr) { return Render::getInstance().Dispatch(CUMEMGETADDRESSRANGE, 3, pbase, psize, dptr); }
CUresult CUDAAPI cuMemAllocHost(void** pp, size_t bytesize) { return Render::getInstance().Dispatch(CUMEMALLOCHOST, 2, pp, bytesize); }
CUresult CUDAAPI cuMemFreeHost(void* p) { return Render::getInstance().Dispatch(CUMEMFREEHOST, 1, p); }
CUresult CUDAAPI cuMemHostAlloc(void** pp, size_t bytesize, unsigned int Flags) { return Render::getInstance().Dispatch(CUMEMHOSTALLOC, 3, pp, bytesize, Flags); }
CUresult CUDAAPI cuMemHostGetDevicePointer(CUdeviceptr* pdptr, void* p, unsigned int Flags) { return Render::getInstance().Dispatch(CUMEMHOSTGETDEVICEPOINTER, 3, pdptr, p, Flags); }
CUresult CUDAAPI cuMemHostGetFlags(unsigned int* pFlags, void* p) { return Render::getInstance().Dispatch(CUMEMHOSTGETFLAGS, 2, pFlags, p); }
CUresult CUDAAPI cuMemAllocManaged(CUdeviceptr* dptr, size_t bytesize, unsigned int flags) { return Render::getInstance().Dispatch(CUMEMALLOCMANAGED, 3, dptr, bytesize, flags); }
CUresult CUDAAPI cuDeviceGetByPCIBusId(CUdevice* dev, const char* pciBusId) { return Render::getInstance().Dispatch(CUDEVICEGETBYPCIBUSID, 2, dev, pciBusId); }
CUresult CUDAAPI cuDeviceGetPCIBusId(char* pciBusId, int len, CUdevice dev) { return Render::getInstance().Dispatch(CUDEVICEGETPCIBUSID, 3, pciBusId, len, dev); }
CUresult CUDAAPI cuIpcGetEventHandle(CUipcEventHandle* pHandle, CUevent event) { return Render::getInstance().Dispatch(CUIPCGETEVENTHANDLE, 2, pHandle, event); }
CUresult CUDAAPI cuIpcOpenEventHandle(CUevent* phEvent, CUipcEventHandle handle) { return Render::getInstance().Dispatch(CUIPCOPENEVENTHANDLE, 2, phEvent, handle); }
CUresult CUDAAPI cuIpcGetMemHandle(CUipcMemHandle* pHandle, CUdeviceptr dptr) { return Render::getInstance().Dispatch(CUIPCGETMEMHANDLE, 2, pHandle, dptr); }
CUresult CUDAAPI cuIpcOpenMemHandle(CUdeviceptr* pdptr, CUipcMemHandle handle, unsigned int Flags) { return Render::getInstance().Dispatch(CUIPCOPENMEMHANDLE, 3, pdptr, handle, Flags); }
CUresult CUDAAPI cuIpcCloseMemHandle(CUdeviceptr dptr) { return Render::getInstance().Dispatch(CUIPCCLOSEMEMHANDLE, 1, dptr); }
CUresult CUDAAPI cuMemHostRegister(void* p, size_t bytesize, unsigned int Flags) { return Render::getInstance().Dispatch(CUMEMHOSTREGISTER, 3, p, bytesize, Flags); }
CUresult CUDAAPI cuMemHostUnregister(void* p) { return Render::getInstance().Dispatch(CUMEMHOSTUNREGISTER, 1, p); }
CUresult CUDAAPI cuMemcpy(CUdeviceptr dst, CUdeviceptr src, size_t ByteCount) { return Render::getInstance().Dispatch(CUMEMCPY, 3, dst, src, ByteCount); }
CUresult CUDAAPI cuMemcpyPeer(CUdeviceptr dstDevice, CUcontext dstContext, CUdeviceptr srcDevice, CUcontext srcContext, size_t ByteCount) { return Render::getInstance().Dispatch(CUMEMCPYPEER, 5, dstDevice, dstContext, srcDevice, srcContext, ByteCount); }
CUresult CUDAAPI cuMemcpyHtoD(CUdeviceptr dstDevice, const void* srcHost, size_t ByteCount) { return Render::getInstance().Dispatch(CUMEMCPYHTOD, 3, dstDevice, srcHost, ByteCount); }
CUresult CUDAAPI cuMemcpyDtoH(void* dstHost, CUdeviceptr srcDevice, size_t ByteCount) { return Render::getInstance().Dispatch(CUMEMCPYDTOH, 3, dstHost, srcDevice, ByteCount); }
CUresult CUDAAPI cuMemcpyDtoD(CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount) { return Render::getInstance().Dispatch(CUMEMCPYDTOD, 3, dstDevice, srcDevice, ByteCount); }
CUresult CUDAAPI cuMemcpyDtoA(CUarray dstArray, size_t dstOffset, CUdeviceptr srcDevice, size_t ByteCount) { return Render::getInstance().Dispatch(CUMEMCPYDTOA, 4, dstArray, dstOffset, srcDevice, ByteCount); }
CUresult CUDAAPI cuMemcpyAtoD(CUdeviceptr dstDevice, CUarray srcArray, size_t srcOffset, size_t ByteCount) { return Render::getInstance().Dispatch(CUMEMCPYATOD, 4, dstDevice, srcArray, srcOffset, ByteCount); }
CUresult CUDAAPI cuMemcpyHtoA(CUarray dstArray, size_t dstOffset, const void* srcHost, size_t ByteCount) { return Render::getInstance().Dispatch(CUMEMCPYHTOA, 4, dstArray, dstOffset, srcHost, ByteCount); }
CUresult CUDAAPI cuMemcpyAtoH(void* dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount) { return Render::getInstance().Dispatch(CUMEMCPYATOH, 4, dstHost, srcArray, srcOffset, ByteCount); }
CUresult CUDAAPI cuMemcpyAtoA(CUarray dstArray, size_t dstOffset, CUarray srcArray, size_t srcOffset, size_t ByteCount) { return Render::getInstance().Dispatch(CUMEMCPYATOA, 5, dstArray, dstOffset, srcArray, srcOffset, ByteCount); }
CUresult CUDAAPI cuMemcpy2D(const CUDA_MEMCPY2D* pCopy) { return Render::getInstance().Dispatch(CUMEMCPY2D, 1, pCopy); }
CUresult CUDAAPI cuMemcpy2DUnaligned(const CUDA_MEMCPY2D* pCopy) { return Render::getInstance().Dispatch(CUMEMCPY2DUNALIGNED, 1, pCopy); }
CUresult CUDAAPI cuMemcpy3D(const CUDA_MEMCPY3D* pCopy) { return Render::getInstance().Dispatch(CUMEMCPY3D, 1, pCopy); }
CUresult CUDAAPI cuMemcpy3DPeer(const CUDA_MEMCPY3D_PEER* pCopy) { return Render::getInstance().Dispatch(CUMEMCPY3DPEER, 1, pCopy); }
CUresult CUDAAPI cuMemcpyAsync(CUdeviceptr dst, CUdeviceptr src, size_t ByteCount, CUstream hStream) { return Render::getInstance().Dispatch(CUMEMCPYASYNC, 4, dst, src, ByteCount, hStream); }
CUresult CUDAAPI cuMemcpyPeerAsync(CUdeviceptr dstDevice, CUcontext dstContext, CUdeviceptr srcDevice, CUcontext srcContext, size_t ByteCount, CUstream hStream) { return Render::getInstance().Dispatch(CUMEMCPYPEERASYNC, 6, dstDevice, dstContext, srcDevice, srcContext, ByteCount, hStream); }
CUresult CUDAAPI cuMemcpyHtoDAsync(CUdeviceptr dstDevice, const void* srcHost, size_t ByteCount, CUstream hStream) { return Render::getInstance().Dispatch(CUMEMCPYHTODASYNC, 4, dstDevice, srcHost, ByteCount, hStream); }
CUresult CUDAAPI cuMemcpyDtoHAsync(void* dstHost, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream) { return Render::getInstance().Dispatch(CUMEMCPYDTOHASYNC, 4, dstHost, srcDevice, ByteCount, hStream); }
CUresult CUDAAPI cuMemcpyDtoDAsync(CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream) { return Render::getInstance().Dispatch(CUMEMCPYDTODASYNC, 4, dstDevice, srcDevice, ByteCount, hStream); }
CUresult CUDAAPI cuMemcpyHtoAAsync(CUarray dstArray, size_t dstOffset, const void* srcHost, size_t ByteCount, CUstream hStream) { return Render::getInstance().Dispatch(CUMEMCPYHTOAASYNC, 5, dstArray, dstOffset, srcHost, ByteCount, hStream); }
CUresult CUDAAPI cuMemcpyAtoHAsync(void* dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount, CUstream hStream) { return Render::getInstance().Dispatch(CUMEMCPYATOHASYNC, 5, dstHost, srcArray, srcOffset, ByteCount, hStream); }
CUresult CUDAAPI cuMemcpy2DAsync(const CUDA_MEMCPY2D* pCopy, CUstream hStream) { return Render::getInstance().Dispatch(CUMEMCPY2DASYNC, 2, pCopy, hStream); }
CUresult CUDAAPI cuMemcpy3DAsync(const CUDA_MEMCPY3D* pCopy, CUstream hStream) { return Render::getInstance().Dispatch(CUMEMCPY3DASYNC, 2, pCopy, hStream); }
CUresult CUDAAPI cuMemcpy3DPeerAsync(const CUDA_MEMCPY3D_PEER* pCopy, CUstream hStream) { return Render::getInstance().Dispatch(CUMEMCPY3DPEERASYNC, 2, pCopy, hStream); }
CUresult CUDAAPI cuMemsetD8(CUdeviceptr dstDevice, unsigned char uc, size_t N) { return Render::getInstance().Dispatch(CUMEMSETD8, 3, dstDevice, uc, N); }
CUresult CUDAAPI cuMemsetD16(CUdeviceptr dstDevice, unsigned short us, size_t N) { return Render::getInstance().Dispatch(CUMEMSETD16, 3, dstDevice, us, N); }
CUresult CUDAAPI cuMemsetD32(CUdeviceptr dstDevice, unsigned int ui, size_t N) { return Render::getInstance().Dispatch(CUMEMSETD32, 3, dstDevice, ui, N); }
CUresult CUDAAPI cuMemsetD2D8(CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height) { return Render::getInstance().Dispatch(CUMEMSETD2D8, 5, dstDevice, dstPitch, uc, Width, Height); }
CUresult CUDAAPI cuMemsetD2D16(CUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height) { return Render::getInstance().Dispatch(CUMEMSETD2D16, 5, dstDevice, dstPitch, us, Width, Height); }
CUresult CUDAAPI cuMemsetD2D32(CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height) { return Render::getInstance().Dispatch(CUMEMSETD2D32, 5, dstDevice, dstPitch, ui, Width, Height); }
CUresult CUDAAPI cuMemsetD8Async(CUdeviceptr dstDevice, unsigned char uc, size_t N, CUstream hStream) { return Render::getInstance().Dispatch(CUMEMSETD8ASYNC, 4, dstDevice, uc, N, hStream); }
CUresult CUDAAPI cuMemsetD16Async(CUdeviceptr dstDevice, unsigned short us, size_t N, CUstream hStream) { return Render::getInstance().Dispatch(CUMEMSETD16ASYNC, 4, dstDevice, us, N, hStream); }
CUresult CUDAAPI cuMemsetD32Async(CUdeviceptr dstDevice, unsigned int ui, size_t N, CUstream hStream) { return Render::getInstance().Dispatch(CUMEMSETD32ASYNC, 4, dstDevice, ui, N, hStream); }
CUresult CUDAAPI cuMemsetD2D8Async(CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height, CUstream hStream) { return Render::getInstance().Dispatch(CUMEMSETD2D8ASYNC, 6, dstDevice, dstPitch, uc, Width, Height, hStream); }
CUresult CUDAAPI cuMemsetD2D16Async(CUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height, CUstream hStream) { return Render::getInstance().Dispatch(CUMEMSETD2D16ASYNC, 6, dstDevice, dstPitch, us, Width, Height, hStream); }
CUresult CUDAAPI cuMemsetD2D32Async(CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height, CUstream hStream) { return Render::getInstance().Dispatch(CUMEMSETD2D32ASYNC, 6, dstDevice, dstPitch, ui, Width, Height, hStream); }
CUresult CUDAAPI cuArrayCreate(CUarray* pHandle, const CUDA_ARRAY_DESCRIPTOR* pAllocateArray) { return Render::getInstance().Dispatch(CUARRAYCREATE, 2, pHandle, pAllocateArray); }
CUresult CUDAAPI cuArrayGetDescriptor(CUDA_ARRAY_DESCRIPTOR* pArrayDescriptor, CUarray hArray) { return Render::getInstance().Dispatch(CUARRAYGETDESCRIPTOR, 2, pArrayDescriptor, hArray); }
CUresult CUDAAPI cuArrayGetSparseProperties(CUDA_ARRAY_SPARSE_PROPERTIES* sparseProperties, CUarray array) { return Render::getInstance().Dispatch(CUARRAYGETSPARSEPROPERTIES, 2, sparseProperties, array); }
CUresult CUDAAPI cuMipmappedArrayGetSparseProperties(CUDA_ARRAY_SPARSE_PROPERTIES* sparseProperties, CUmipmappedArray mipmap) { return Render::getInstance().Dispatch(CUMIPMAPPEDARRAYGETSPARSEPROPERTIES, 2, sparseProperties, mipmap); }
CUresult CUDAAPI cuArrayGetMemoryRequirements(CUDA_ARRAY_MEMORY_REQUIREMENTS* memoryRequirements, CUarray array, CUdevice device) { return Render::getInstance().Dispatch(CUARRAYGETMEMORYREQUIREMENTS, 3, memoryRequirements, array, device); }
CUresult CUDAAPI cuMipmappedArrayGetMemoryRequirements(CUDA_ARRAY_MEMORY_REQUIREMENTS* memoryRequirements, CUmipmappedArray mipmap, CUdevice device) { return Render::getInstance().Dispatch(CUMIPMAPPEDARRAYGETMEMORYREQUIREMENTS, 3, memoryRequirements, mipmap, device); }
CUresult CUDAAPI cuArrayGetPlane(CUarray* pPlaneArray, CUarray hArray, unsigned int planeIdx) { return Render::getInstance().Dispatch(CUARRAYGETPLANE, 3, pPlaneArray, hArray, planeIdx); }
CUresult CUDAAPI cuArrayDestroy(CUarray hArray) { return Render::getInstance().Dispatch(CUARRAYDESTROY, 1, hArray); }
CUresult CUDAAPI cuArray3DCreate(CUarray* pHandle, const CUDA_ARRAY3D_DESCRIPTOR* pAllocateArray) { return Render::getInstance().Dispatch(CUARRAY3DCREATE, 2, pHandle, pAllocateArray); }
CUresult CUDAAPI cuArray3DGetDescriptor(CUDA_ARRAY3D_DESCRIPTOR* pArrayDescriptor, CUarray hArray) { return Render::getInstance().Dispatch(CUARRAY3DGETDESCRIPTOR, 2, pArrayDescriptor, hArray); }
CUresult CUDAAPI cuMipmappedArrayCreate(CUmipmappedArray* pHandle, const CUDA_ARRAY3D_DESCRIPTOR* pMipmappedArrayDesc, unsigned int numMipmapLevels) { return Render::getInstance().Dispatch(CUMIPMAPPEDARRAYCREATE, 3, pHandle, pMipmappedArrayDesc, numMipmapLevels); }
CUresult CUDAAPI cuMipmappedArrayGetLevel(CUarray* pLevelArray, CUmipmappedArray hMipmappedArray, unsigned int level) { return Render::getInstance().Dispatch(CUMIPMAPPEDARRAYGETLEVEL, 3, pLevelArray, hMipmappedArray, level); }
CUresult CUDAAPI cuMipmappedArrayDestroy(CUmipmappedArray hMipmappedArray) { return Render::getInstance().Dispatch(CUMIPMAPPEDARRAYDESTROY, 1, hMipmappedArray); }
CUresult CUDAAPI cuMemGetHandleForAddressRange(void* handle, CUdeviceptr dptr, size_t size, CUmemRangeHandleType handleType, unsigned long long flags) { return Render::getInstance().Dispatch(CUMEMGETHANDLEFORADDRESSRANGE, 5, handle, dptr, size, handleType, flags); }
CUresult CUDAAPI cuMemAddressReserve(CUdeviceptr* ptr, size_t size, size_t alignment, CUdeviceptr addr, unsigned long long flags) { return Render::getInstance().Dispatch(CUMEMADDRESSRESERVE, 5, ptr, size, alignment, addr, flags); }
CUresult CUDAAPI cuMemAddressFree(CUdeviceptr ptr, size_t size) { return Render::getInstance().Dispatch(CUMEMADDRESSFREE, 2, ptr, size); }
CUresult CUDAAPI cuMemCreate(CUmemGenericAllocationHandle* handle, size_t size, const CUmemAllocationProp* prop, unsigned long long flags) { return Render::getInstance().Dispatch(CUMEMCREATE, 4, handle, size, prop, flags); }
CUresult CUDAAPI cuMemRelease(CUmemGenericAllocationHandle handle) { return Render::getInstance().Dispatch(CUMEMRELEASE, 1, handle); }
CUresult CUDAAPI cuMemMap(CUdeviceptr ptr, size_t size, size_t offset, CUmemGenericAllocationHandle handle, unsigned long long flags) { return Render::getInstance().Dispatch(CUMEMMAP, 5, ptr, size, offset, handle, flags); }
CUresult CUDAAPI cuMemMapArrayAsync(CUarrayMapInfo* mapInfoList, unsigned int count, CUstream hStream) { return Render::getInstance().Dispatch(CUMEMMAPARRAYASYNC, 3, mapInfoList, count, hStream); }
CUresult CUDAAPI cuMemUnmap(CUdeviceptr ptr, size_t size) { return Render::getInstance().Dispatch(CUMEMUNMAP, 2, ptr, size); }
CUresult CUDAAPI cuMemSetAccess(CUdeviceptr ptr, size_t size, const CUmemAccessDesc* desc, size_t count) { return Render::getInstance().Dispatch(CUMEMSETACCESS, 4, ptr, size, desc, count); }
CUresult CUDAAPI cuMemGetAccess(unsigned long long* flags, const CUmemLocation* location, CUdeviceptr ptr) { return Render::getInstance().Dispatch(CUMEMGETACCESS, 3, flags, location, ptr); }
CUresult CUDAAPI cuMemExportToShareableHandle(void* shareableHandle, CUmemGenericAllocationHandle handle, CUmemAllocationHandleType handleType, unsigned long long flags) { return Render::getInstance().Dispatch(CUMEMEXPORTTOSHAREABLEHANDLE, 4, shareableHandle, handle, handleType, flags); }
CUresult CUDAAPI cuMemImportFromShareableHandle(CUmemGenericAllocationHandle* handle, void* osHandle, CUmemAllocationHandleType shHandleType) { return Render::getInstance().Dispatch(CUMEMIMPORTFROMSHAREABLEHANDLE, 3, handle, osHandle, shHandleType); }
CUresult CUDAAPI cuMemGetAllocationGranularity(size_t* granularity, const CUmemAllocationProp* prop, CUmemAllocationGranularity_flags option) { return Render::getInstance().Dispatch(CUMEMGETALLOCATIONGRANULARITY, 3, granularity, prop, option); }
CUresult CUDAAPI cuMemGetAllocationPropertiesFromHandle(CUmemAllocationProp* prop, CUmemGenericAllocationHandle handle) { return Render::getInstance().Dispatch(CUMEMGETALLOCATIONPROPERTIESFROMHANDLE, 2, prop, handle); }
CUresult CUDAAPI cuMemRetainAllocationHandle(CUmemGenericAllocationHandle* handle, void* addr) { return Render::getInstance().Dispatch(CUMEMRETAINALLOCATIONHANDLE, 2, handle, addr); }
CUresult CUDAAPI cuMemFreeAsync(CUdeviceptr dptr, CUstream hStream) { return Render::getInstance().Dispatch(CUMEMFREEASYNC, 2, dptr, hStream); }
CUresult CUDAAPI cuMemAllocAsync(CUdeviceptr* dptr, size_t bytesize, CUstream hStream) { return Render::getInstance().Dispatch(CUMEMALLOCASYNC, 3, dptr, bytesize, hStream); }
CUresult CUDAAPI cuMemPoolTrimTo(CUmemoryPool pool, size_t minBytesToKeep) { return Render::getInstance().Dispatch(CUMEMPOOLTRIMTO, 2, pool, minBytesToKeep); }
CUresult CUDAAPI cuMemPoolSetAttribute(CUmemoryPool pool, CUmemPool_attribute attr, void* value) { return Render::getInstance().Dispatch(CUMEMPOOLSETATTRIBUTE, 3, pool, attr, value); }
CUresult CUDAAPI cuMemPoolGetAttribute(CUmemoryPool pool, CUmemPool_attribute attr, void* value) { return Render::getInstance().Dispatch(CUMEMPOOLGETATTRIBUTE, 3, pool, attr, value); }
CUresult CUDAAPI cuMemPoolSetAccess(CUmemoryPool pool, const CUmemAccessDesc* map, size_t count) { return Render::getInstance().Dispatch(CUMEMPOOLSETACCESS, 3, pool, map, count); }
CUresult CUDAAPI cuMemPoolGetAccess(CUmemAccess_flags* flags, CUmemoryPool memPool, CUmemLocation* location) { return Render::getInstance().Dispatch(CUMEMPOOLGETACCESS, 3, flags, memPool, location); }
CUresult CUDAAPI cuMemPoolCreate(CUmemoryPool* pool, const CUmemPoolProps* poolProps) { return Render::getInstance().Dispatch(CUMEMPOOLCREATE, 2, pool, poolProps); }
CUresult CUDAAPI cuMemPoolDestroy(CUmemoryPool pool) { return Render::getInstance().Dispatch(CUMEMPOOLDESTROY, 1, pool); }
CUresult CUDAAPI cuMemAllocFromPoolAsync(CUdeviceptr* dptr, size_t bytesize, CUmemoryPool pool, CUstream hStream) { return Render::getInstance().Dispatch(CUMEMALLOCFROMPOOLASYNC, 4, dptr, bytesize, pool, hStream); }
CUresult CUDAAPI cuMemPoolExportToShareableHandle(void* handle_out, CUmemoryPool pool, CUmemAllocationHandleType handleType, unsigned long long flags) { return Render::getInstance().Dispatch(CUMEMPOOLEXPORTTOSHAREABLEHANDLE, 4, handle_out, pool, handleType, flags); }
CUresult CUDAAPI cuMemPoolImportFromShareableHandle(CUmemoryPool* pool_out, void* handle, CUmemAllocationHandleType handleType, unsigned long long flags) { return Render::getInstance().Dispatch(CUMEMPOOLIMPORTFROMSHAREABLEHANDLE, 4, pool_out, handle, handleType, flags); }
CUresult CUDAAPI cuMemPoolExportPointer(CUmemPoolPtrExportData* shareData_out, CUdeviceptr ptr) { return Render::getInstance().Dispatch(CUMEMPOOLEXPORTPOINTER, 2, shareData_out, ptr); }
CUresult CUDAAPI cuMemPoolImportPointer(CUdeviceptr* ptr_out, CUmemoryPool pool, CUmemPoolPtrExportData* shareData) { return Render::getInstance().Dispatch(CUMEMPOOLIMPORTPOINTER, 3, ptr_out, pool, shareData); }
CUresult CUDAAPI cuMulticastCreate(CUmemGenericAllocationHandle* mcHandle, const CUmulticastObjectProp* prop) { return Render::getInstance().Dispatch(CUMULTICASTCREATE, 2, mcHandle, prop); }
CUresult CUDAAPI cuMulticastAddDevice(CUmemGenericAllocationHandle mcHandle, CUdevice dev) { return Render::getInstance().Dispatch(CUMULTICASTADDDEVICE, 2, mcHandle, dev); }
CUresult CUDAAPI cuMulticastBindMem(CUmemGenericAllocationHandle mcHandle, size_t mcOffset, CUmemGenericAllocationHandle memHandle, size_t memOffset, size_t size, unsigned long long flags) { return Render::getInstance().Dispatch(CUMULTICASTBINDMEM, 6, mcHandle, mcOffset, memHandle, memOffset, size, flags); }
CUresult CUDAAPI cuMulticastBindAddr(CUmemGenericAllocationHandle mcHandle, size_t mcOffset, CUdeviceptr memptr, size_t size, unsigned long long flags) { return Render::getInstance().Dispatch(CUMULTICASTBINDADDR, 5, mcHandle, mcOffset, memptr, size, flags); }
CUresult CUDAAPI cuMulticastUnbind(CUmemGenericAllocationHandle mcHandle, CUdevice dev, size_t mcOffset, size_t size) { return Render::getInstance().Dispatch(CUMULTICASTUNBIND, 4, mcHandle, dev, mcOffset, size); }
CUresult CUDAAPI cuMulticastGetGranularity(size_t* granularity, const CUmulticastObjectProp* prop, CUmulticastGranularity_flags option) { return Render::getInstance().Dispatch(CUMULTICASTGETGRANULARITY, 3, granularity, prop, option); }
CUresult CUDAAPI cuPointerGetAttribute(void* data, CUpointer_attribute attribute, CUdeviceptr ptr) { return Render::getInstance().Dispatch(CUPOINTERGETATTRIBUTE, 3, data, attribute, ptr); }
CUresult CUDAAPI cuMemPrefetchAsync(CUdeviceptr devPtr, size_t count, CUdevice dstDevice, CUstream hStream) { return Render::getInstance().Dispatch(CUMEMPREFETCHASYNC, 4, devPtr, count, dstDevice, hStream); }
CUresult CUDAAPI cuMemAdvise(CUdeviceptr devPtr, size_t count, CUmem_advise advice, CUdevice device) { return Render::getInstance().Dispatch(CUMEMADVISE, 4, devPtr, count, advice, device); }
CUresult CUDAAPI cuMemRangeGetAttribute(void* data, size_t dataSize, CUmem_range_attribute attribute, CUdeviceptr devPtr, size_t count) { return Render::getInstance().Dispatch(CUMEMRANGEGETATTRIBUTE, 5, data, dataSize, attribute, devPtr, count); }
CUresult CUDAAPI cuMemRangeGetAttributes(void** data, size_t* dataSizes, CUmem_range_attribute* attributes, size_t numAttributes, CUdeviceptr devPtr, size_t count) { return Render::getInstance().Dispatch(CUMEMRANGEGETATTRIBUTES, 6, data, dataSizes, attributes, numAttributes, devPtr, count); }
CUresult CUDAAPI cuPointerSetAttribute(const void* value, CUpointer_attribute attribute, CUdeviceptr ptr) { return Render::getInstance().Dispatch(CUPOINTERSETATTRIBUTE, 3, value, attribute, ptr); }
CUresult CUDAAPI cuPointerGetAttributes(unsigned int numAttributes, CUpointer_attribute* attributes, void** data, CUdeviceptr ptr) { return Render::getInstance().Dispatch(CUPOINTERGETATTRIBUTES, 4, numAttributes, attributes, data, ptr); }
CUresult CUDAAPI cuStreamCreate(CUstream* phStream, unsigned int Flags) { return Render::getInstance().Dispatch(CUSTREAMCREATE, 2, phStream, Flags); }
CUresult CUDAAPI cuStreamCreateWithPriority(CUstream* phStream, unsigned int flags, int priority) { return Render::getInstance().Dispatch(CUSTREAMCREATEWITHPRIORITY, 3, phStream, flags, priority); }
CUresult CUDAAPI cuStreamGetPriority(CUstream hStream, int* priority) { return Render::getInstance().Dispatch(CUSTREAMGETPRIORITY, 2, hStream, priority); }
CUresult CUDAAPI cuStreamGetFlags(CUstream hStream, unsigned int* flags) { return Render::getInstance().Dispatch(CUSTREAMGETFLAGS, 2, hStream, flags); }
CUresult CUDAAPI cuStreamGetId(CUstream hStream, unsigned long long* streamId) { return Render::getInstance().Dispatch(CUSTREAMGETID, 2, hStream, streamId); }
CUresult CUDAAPI cuStreamGetCtx(CUstream hStream, CUcontext* pctx) { return Render::getInstance().Dispatch(CUSTREAMGETCTX, 2, hStream, pctx); }
CUresult CUDAAPI cuStreamWaitEvent(CUstream hStream, CUevent hEvent, unsigned int Flags) { return Render::getInstance().Dispatch(CUSTREAMWAITEVENT, 3, hStream, hEvent, Flags); }
CUresult CUDAAPI cuStreamAddCallback(CUstream hStream, CUstreamCallback callback, void* userData, unsigned int flags) { return Render::getInstance().Dispatch(CUSTREAMADDCALLBACK, 4, hStream, callback, userData, flags); }
CUresult CUDAAPI cuStreamBeginCapture(CUstream hStream, CUstreamCaptureMode mode) { return Render::getInstance().Dispatch(CUSTREAMBEGINCAPTURE, 2, hStream, mode); }
CUresult CUDAAPI cuThreadExchangeStreamCaptureMode(CUstreamCaptureMode* mode) { return Render::getInstance().Dispatch(CUTHREADEXCHANGESTREAMCAPTUREMODE, 1, mode); }
CUresult CUDAAPI cuStreamEndCapture(CUstream hStream, CUgraph* phGraph) { return Render::getInstance().Dispatch(CUSTREAMENDCAPTURE, 2, hStream, phGraph); }
CUresult CUDAAPI cuStreamIsCapturing(CUstream hStream, CUstreamCaptureStatus* captureStatus) { return Render::getInstance().Dispatch(CUSTREAMISCAPTURING, 2, hStream, captureStatus); }
CUresult CUDAAPI cuStreamGetCaptureInfo(CUstream hStream, CUstreamCaptureStatus* captureStatus_out, cuuint64_t* id_out, CUgraph* graph_out, const CUgraphNode** dependencies_out, size_t* numDependencies_out) { return Render::getInstance().Dispatch(CUSTREAMGETCAPTUREINFO, 6, hStream, captureStatus_out, id_out, graph_out, dependencies_out, numDependencies_out); }
CUresult CUDAAPI cuStreamUpdateCaptureDependencies(CUstream hStream, CUgraphNode* dependencies, size_t numDependencies, unsigned int flags) { return Render::getInstance().Dispatch(CUSTREAMUPDATECAPTUREDEPENDENCIES, 4, hStream, dependencies, numDependencies, flags); }
CUresult CUDAAPI cuStreamAttachMemAsync(CUstream hStream, CUdeviceptr dptr, size_t length, unsigned int flags) { return Render::getInstance().Dispatch(CUSTREAMATTACHMEMASYNC, 4, hStream, dptr, length, flags); }
CUresult CUDAAPI cuStreamQuery(CUstream hStream) { return Render::getInstance().Dispatch(CUSTREAMQUERY, 1, hStream); }
CUresult CUDAAPI cuStreamSynchronize(CUstream hStream) { return Render::getInstance().Dispatch(CUSTREAMSYNCHRONIZE, 1, hStream); }
CUresult CUDAAPI cuStreamDestroy(CUstream hStream) { return Render::getInstance().Dispatch(CUSTREAMDESTROY, 1, hStream); }
CUresult CUDAAPI cuStreamCopyAttributes(CUstream dst, CUstream src) { return Render::getInstance().Dispatch(CUSTREAMCOPYATTRIBUTES, 2, dst, src); }
CUresult CUDAAPI cuStreamGetAttribute(CUstream hStream, CUstreamAttrID attr, CUstreamAttrValue* value_out) { return Render::getInstance().Dispatch(CUSTREAMGETATTRIBUTE, 3, hStream, attr, value_out); }
CUresult CUDAAPI cuStreamSetAttribute(CUstream hStream, CUstreamAttrID attr, const CUstreamAttrValue* value) { return Render::getInstance().Dispatch(CUSTREAMSETATTRIBUTE, 3, hStream, attr, value); }
CUresult CUDAAPI cuEventCreate(CUevent* phEvent, unsigned int Flags) { return Render::getInstance().Dispatch(CUEVENTCREATE, 2, phEvent, Flags); }
CUresult CUDAAPI cuEventRecord(CUevent hEvent, CUstream hStream) { return Render::getInstance().Dispatch(CUEVENTRECORD, 2, hEvent, hStream); }
CUresult CUDAAPI cuEventRecordWithFlags(CUevent hEvent, CUstream hStream, unsigned int flags) { return Render::getInstance().Dispatch(CUEVENTRECORDWITHFLAGS, 3, hEvent, hStream, flags); }
CUresult CUDAAPI cuEventQuery(CUevent hEvent) { return Render::getInstance().Dispatch(CUEVENTQUERY, 1, hEvent); }
CUresult CUDAAPI cuEventSynchronize(CUevent hEvent) { return Render::getInstance().Dispatch(CUEVENTSYNCHRONIZE, 1, hEvent); }
CUresult CUDAAPI cuEventDestroy(CUevent hEvent) { return Render::getInstance().Dispatch(CUEVENTDESTROY, 1, hEvent); }
CUresult CUDAAPI cuEventElapsedTime(float* pMilliseconds, CUevent hStart, CUevent hEnd) { return Render::getInstance().Dispatch(CUEVENTELAPSEDTIME, 3, pMilliseconds, hStart, hEnd); }
CUresult CUDAAPI cuImportExternalMemory(CUexternalMemory* extMem_out, const CUDA_EXTERNAL_MEMORY_HANDLE_DESC* memHandleDesc) { return Render::getInstance().Dispatch(CUIMPORTEXTERNALMEMORY, 2, extMem_out, memHandleDesc); }
CUresult CUDAAPI cuExternalMemoryGetMappedBuffer(CUdeviceptr* devPtr, CUexternalMemory extMem, const CUDA_EXTERNAL_MEMORY_BUFFER_DESC* bufferDesc) { return Render::getInstance().Dispatch(CUEXTERNALMEMORYGETMAPPEDBUFFER, 3, devPtr, extMem, bufferDesc); }
CUresult CUDAAPI cuExternalMemoryGetMappedMipmappedArray(CUmipmappedArray* mipmap, CUexternalMemory extMem, const CUDA_EXTERNAL_MEMORY_MIPMAPPED_ARRAY_DESC* mipmapDesc) { return Render::getInstance().Dispatch(CUEXTERNALMEMORYGETMAPPEDMIPMAPPEDARRAY, 3, mipmap, extMem, mipmapDesc); }
CUresult CUDAAPI cuDestroyExternalMemory(CUexternalMemory extMem) { return Render::getInstance().Dispatch(CUDESTROYEXTERNALMEMORY, 1, extMem); }
CUresult CUDAAPI cuImportExternalSemaphore(CUexternalSemaphore* extSem_out, const CUDA_EXTERNAL_SEMAPHORE_HANDLE_DESC* semHandleDesc) { return Render::getInstance().Dispatch(CUIMPORTEXTERNALSEMAPHORE, 2, extSem_out, semHandleDesc); }
CUresult CUDAAPI cuSignalExternalSemaphoresAsync(const CUexternalSemaphore* extSemArray, const CUDA_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS* paramsArray, unsigned int numExtSems, CUstream stream) { return Render::getInstance().Dispatch(CUSIGNALEXTERNALSEMAPHORESASYNC, 4, extSemArray, paramsArray, numExtSems, stream); }
CUresult CUDAAPI cuWaitExternalSemaphoresAsync(const CUexternalSemaphore* extSemArray, const CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS* paramsArray, unsigned int numExtSems, CUstream stream) { return Render::getInstance().Dispatch(CUWAITEXTERNALSEMAPHORESASYNC, 4, extSemArray, paramsArray, numExtSems, stream); }
CUresult CUDAAPI cuDestroyExternalSemaphore(CUexternalSemaphore extSem) { return Render::getInstance().Dispatch(CUDESTROYEXTERNALSEMAPHORE, 1, extSem); }
CUresult CUDAAPI cuStreamWaitValue32(CUstream stream, CUdeviceptr addr, cuuint32_t value, unsigned int flags) { return Render::getInstance().Dispatch(CUSTREAMWAITVALUE32, 4, stream, addr, value, flags); }
CUresult CUDAAPI cuStreamWaitValue64(CUstream stream, CUdeviceptr addr, cuuint64_t value, unsigned int flags) { return Render::getInstance().Dispatch(CUSTREAMWAITVALUE64, 4, stream, addr, value, flags); }
CUresult CUDAAPI cuStreamWriteValue32(CUstream stream, CUdeviceptr addr, cuuint32_t value, unsigned int flags) { return Render::getInstance().Dispatch(CUSTREAMWRITEVALUE32, 4, stream, addr, value, flags); }
CUresult CUDAAPI cuStreamWriteValue64(CUstream stream, CUdeviceptr addr, cuuint64_t value, unsigned int flags) { return Render::getInstance().Dispatch(CUSTREAMWRITEVALUE64, 4, stream, addr, value, flags); }
CUresult CUDAAPI cuStreamBatchMemOp(CUstream stream, unsigned int count, CUstreamBatchMemOpParams* paramArray, unsigned int flags) { return Render::getInstance().Dispatch(CUSTREAMBATCHMEMOP, 4, stream, count, paramArray, flags); }
CUresult CUDAAPI cuFuncGetAttribute(int* pi, CUfunction_attribute attrib, CUfunction hfunc) { return Render::getInstance().Dispatch(CUFUNCGETATTRIBUTE, 3, pi, attrib, hfunc); }
CUresult CUDAAPI cuFuncSetAttribute(CUfunction hfunc, CUfunction_attribute attrib, int value) { return Render::getInstance().Dispatch(CUFUNCSETATTRIBUTE, 3, hfunc, attrib, value); }
CUresult CUDAAPI cuFuncSetCacheConfig(CUfunction hfunc, CUfunc_cache config) { return Render::getInstance().Dispatch(CUFUNCSETCACHECONFIG, 2, hfunc, config); }
CUresult CUDAAPI cuFuncSetSharedMemConfig(CUfunction hfunc, CUsharedconfig config) { return Render::getInstance().Dispatch(CUFUNCSETSHAREDMEMCONFIG, 2, hfunc, config); }
CUresult CUDAAPI cuFuncGetModule(CUmodule* hmod, CUfunction hfunc) { return Render::getInstance().Dispatch(CUFUNCGETMODULE, 2, hmod, hfunc); }
CUresult CUDAAPI cuLaunchKernel(CUfunction f, unsigned int gridDimX, unsigned int gridDimY, unsigned int gridDimZ, unsigned int blockDimX, unsigned int blockDimY, unsigned int blockDimZ, unsigned int sharedMemBytes, CUstream hStream, void** kernelParams, void** extra) { return Render::getInstance().Dispatch(CULAUNCHKERNEL, 11, f, gridDimX, gridDimY, gridDimZ, blockDimX, blockDimY, blockDimZ, sharedMemBytes, hStream, kernelParams, extra); }
CUresult CUDAAPI cuLaunchKernelEx(const CUlaunchConfig* config, CUfunction f, void** kernelParams, void** extra) { return Render::getInstance().Dispatch(CULAUNCHKERNELEX, 4, config, f, kernelParams, extra); }
CUresult CUDAAPI cuLaunchCooperativeKernel(CUfunction f, unsigned int gridDimX, unsigned int gridDimY, unsigned int gridDimZ, unsigned int blockDimX, unsigned int blockDimY, unsigned int blockDimZ, unsigned int sharedMemBytes, CUstream hStream, void** kernelParams) { return Render::getInstance().Dispatch(CULAUNCHCOOPERATIVEKERNEL, 10, f, gridDimX, gridDimY, gridDimZ, blockDimX, blockDimY, blockDimZ, sharedMemBytes, hStream, kernelParams); }
CUresult CUDAAPI cuLaunchCooperativeKernelMultiDevice(CUDA_LAUNCH_PARAMS* launchParamsList, unsigned int numDevices, unsigned int flags) { return Render::getInstance().Dispatch(CULAUNCHCOOPERATIVEKERNELMULTIDEVICE, 3, launchParamsList, numDevices, flags); }
CUresult CUDAAPI cuLaunchHostFunc(CUstream hStream, CUhostFn fn, void* userData) { return Render::getInstance().Dispatch(CULAUNCHHOSTFUNC, 3, hStream, fn, userData); }
CUresult CUDAAPI cuFuncSetBlockShape(CUfunction hfunc, int x, int y, int z) { return Render::getInstance().Dispatch(CUFUNCSETBLOCKSHAPE, 4, hfunc, x, y, z); }
CUresult CUDAAPI cuFuncSetSharedSize(CUfunction hfunc, unsigned int bytes) { return Render::getInstance().Dispatch(CUFUNCSETSHAREDSIZE, 2, hfunc, bytes); }
CUresult CUDAAPI cuParamSetSize(CUfunction hfunc, unsigned int numbytes) { return Render::getInstance().Dispatch(CUPARAMSETSIZE, 2, hfunc, numbytes); }
CUresult CUDAAPI cuParamSeti(CUfunction hfunc, int offset, unsigned int value) { return Render::getInstance().Dispatch(CUPARAMSETI, 3, hfunc, offset, value); }
CUresult CUDAAPI cuParamSetf(CUfunction hfunc, int offset, float value) { return Render::getInstance().Dispatch(CUPARAMSETF, 3, hfunc, offset, value); }
CUresult CUDAAPI cuParamSetv(CUfunction hfunc, int offset, void* ptr, unsigned int numbytes) { return Render::getInstance().Dispatch(CUPARAMSETV, 4, hfunc, offset, ptr, numbytes); }
CUresult CUDAAPI cuLaunch(CUfunction f) { return Render::getInstance().Dispatch(CULAUNCH, 1, f); }
CUresult CUDAAPI cuLaunchGrid(CUfunction f, int grid_width, int grid_height) { return Render::getInstance().Dispatch(CULAUNCHGRID, 3, f, grid_width, grid_height); }
CUresult CUDAAPI cuLaunchGridAsync(CUfunction f, int grid_width, int grid_height, CUstream hStream) { return Render::getInstance().Dispatch(CULAUNCHGRIDASYNC, 4, f, grid_width, grid_height, hStream); }
CUresult CUDAAPI cuParamSetTexRef(CUfunction hfunc, int texunit, CUtexref hTexRef) { return Render::getInstance().Dispatch(CUPARAMSETTEXREF, 3, hfunc, texunit, hTexRef); }
CUresult CUDAAPI cuGraphCreate(CUgraph* phGraph, unsigned int flags) { return Render::getInstance().Dispatch(CUGRAPHCREATE, 2, phGraph, flags); }
CUresult CUDAAPI cuGraphAddKernelNode(CUgraphNode* phGraphNode, CUgraph hGraph, const CUgraphNode* dependencies, size_t numDependencies, const CUDA_KERNEL_NODE_PARAMS* nodeParams) { return Render::getInstance().Dispatch(CUGRAPHADDKERNELNODE, 5, phGraphNode, hGraph, dependencies, numDependencies, nodeParams); }
CUresult CUDAAPI cuGraphKernelNodeGetParams(CUgraphNode hNode, CUDA_KERNEL_NODE_PARAMS* nodeParams) { return Render::getInstance().Dispatch(CUGRAPHKERNELNODEGETPARAMS, 2, hNode, nodeParams); }
CUresult CUDAAPI cuGraphKernelNodeSetParams(CUgraphNode hNode, const CUDA_KERNEL_NODE_PARAMS* nodeParams) { return Render::getInstance().Dispatch(CUGRAPHKERNELNODESETPARAMS, 2, hNode, nodeParams); }
CUresult CUDAAPI cuGraphAddMemcpyNode(CUgraphNode* phGraphNode, CUgraph hGraph, const CUgraphNode* dependencies, size_t numDependencies, const CUDA_MEMCPY3D* copyParams, CUcontext ctx) { return Render::getInstance().Dispatch(CUGRAPHADDMEMCPYNODE, 6, phGraphNode, hGraph, dependencies, numDependencies, copyParams, ctx); }
CUresult CUDAAPI cuGraphMemcpyNodeGetParams(CUgraphNode hNode, CUDA_MEMCPY3D* nodeParams) { return Render::getInstance().Dispatch(CUGRAPHMEMCPYNODEGETPARAMS, 2, hNode, nodeParams); }
CUresult CUDAAPI cuGraphMemcpyNodeSetParams(CUgraphNode hNode, const CUDA_MEMCPY3D* nodeParams) { return Render::getInstance().Dispatch(CUGRAPHMEMCPYNODESETPARAMS, 2, hNode, nodeParams); }
CUresult CUDAAPI cuGraphAddMemsetNode(CUgraphNode* phGraphNode, CUgraph hGraph, const CUgraphNode* dependencies, size_t numDependencies, const CUDA_MEMSET_NODE_PARAMS* memsetParams, CUcontext ctx) { return Render::getInstance().Dispatch(CUGRAPHADDMEMSETNODE, 6, phGraphNode, hGraph, dependencies, numDependencies, memsetParams, ctx); }
CUresult CUDAAPI cuGraphMemsetNodeGetParams(CUgraphNode hNode, CUDA_MEMSET_NODE_PARAMS* nodeParams) { return Render::getInstance().Dispatch(CUGRAPHMEMSETNODEGETPARAMS, 2, hNode, nodeParams); }
CUresult CUDAAPI cuGraphMemsetNodeSetParams(CUgraphNode hNode, const CUDA_MEMSET_NODE_PARAMS* nodeParams) { return Render::getInstance().Dispatch(CUGRAPHMEMSETNODESETPARAMS, 2, hNode, nodeParams); }
CUresult CUDAAPI cuGraphAddHostNode(CUgraphNode* phGraphNode, CUgraph hGraph, const CUgraphNode* dependencies, size_t numDependencies, const CUDA_HOST_NODE_PARAMS* nodeParams) { return Render::getInstance().Dispatch(CUGRAPHADDHOSTNODE, 5, phGraphNode, hGraph, dependencies, numDependencies, nodeParams); }
CUresult CUDAAPI cuGraphHostNodeGetParams(CUgraphNode hNode, CUDA_HOST_NODE_PARAMS* nodeParams) { return Render::getInstance().Dispatch(CUGRAPHHOSTNODEGETPARAMS, 2, hNode, nodeParams); }
CUresult CUDAAPI cuGraphHostNodeSetParams(CUgraphNode hNode, const CUDA_HOST_NODE_PARAMS* nodeParams) { return Render::getInstance().Dispatch(CUGRAPHHOSTNODESETPARAMS, 2, hNode, nodeParams); }
CUresult CUDAAPI cuGraphAddChildGraphNode(CUgraphNode* phGraphNode, CUgraph hGraph, const CUgraphNode* dependencies, size_t numDependencies, CUgraph childGraph) { return Render::getInstance().Dispatch(CUGRAPHADDCHILDGRAPHNODE, 5, phGraphNode, hGraph, dependencies, numDependencies, childGraph); }
CUresult CUDAAPI cuGraphChildGraphNodeGetGraph(CUgraphNode hNode, CUgraph* phGraph) { return Render::getInstance().Dispatch(CUGRAPHCHILDGRAPHNODEGETGRAPH, 2, hNode, phGraph); }
CUresult CUDAAPI cuGraphAddEmptyNode(CUgraphNode* phGraphNode, CUgraph hGraph, const CUgraphNode* dependencies, size_t numDependencies) { return Render::getInstance().Dispatch(CUGRAPHADDEMPTYNODE, 4, phGraphNode, hGraph, dependencies, numDependencies); }
CUresult CUDAAPI cuGraphAddEventRecordNode(CUgraphNode* phGraphNode, CUgraph hGraph, const CUgraphNode* dependencies, size_t numDependencies, CUevent event) { return Render::getInstance().Dispatch(CUGRAPHADDEVENTRECORDNODE, 5, phGraphNode, hGraph, dependencies, numDependencies, event); }
CUresult CUDAAPI cuGraphEventRecordNodeGetEvent(CUgraphNode hNode, CUevent* event_out) { return Render::getInstance().Dispatch(CUGRAPHEVENTRECORDNODEGETEVENT, 2, hNode, event_out); }
CUresult CUDAAPI cuGraphEventRecordNodeSetEvent(CUgraphNode hNode, CUevent event) { return Render::getInstance().Dispatch(CUGRAPHEVENTRECORDNODESETEVENT, 2, hNode, event); }
CUresult CUDAAPI cuGraphAddEventWaitNode(CUgraphNode* phGraphNode, CUgraph hGraph, const CUgraphNode* dependencies, size_t numDependencies, CUevent event) { return Render::getInstance().Dispatch(CUGRAPHADDEVENTWAITNODE, 5, phGraphNode, hGraph, dependencies, numDependencies, event); }
CUresult CUDAAPI cuGraphEventWaitNodeGetEvent(CUgraphNode hNode, CUevent* event_out) { return Render::getInstance().Dispatch(CUGRAPHEVENTWAITNODEGETEVENT, 2, hNode, event_out); }
CUresult CUDAAPI cuGraphEventWaitNodeSetEvent(CUgraphNode hNode, CUevent event) { return Render::getInstance().Dispatch(CUGRAPHEVENTWAITNODESETEVENT, 2, hNode, event); }
CUresult CUDAAPI cuGraphAddExternalSemaphoresSignalNode(CUgraphNode* phGraphNode, CUgraph hGraph, const CUgraphNode* dependencies, size_t numDependencies, const CUDA_EXT_SEM_SIGNAL_NODE_PARAMS* nodeParams) { return Render::getInstance().Dispatch(CUGRAPHADDEXTERNALSEMAPHORESSIGNALNODE, 5, phGraphNode, hGraph, dependencies, numDependencies, nodeParams); }
CUresult CUDAAPI cuGraphExternalSemaphoresSignalNodeGetParams(CUgraphNode hNode, CUDA_EXT_SEM_SIGNAL_NODE_PARAMS* params_out) { return Render::getInstance().Dispatch(CUGRAPHEXTERNALSEMAPHORESSIGNALNODEGETPARAMS, 2, hNode, params_out); }
CUresult CUDAAPI cuGraphExternalSemaphoresSignalNodeSetParams(CUgraphNode hNode, const CUDA_EXT_SEM_SIGNAL_NODE_PARAMS* nodeParams) { return Render::getInstance().Dispatch(CUGRAPHEXTERNALSEMAPHORESSIGNALNODESETPARAMS, 2, hNode, nodeParams); }
CUresult CUDAAPI cuGraphAddExternalSemaphoresWaitNode(CUgraphNode* phGraphNode, CUgraph hGraph, const CUgraphNode* dependencies, size_t numDependencies, const CUDA_EXT_SEM_WAIT_NODE_PARAMS* nodeParams) { return Render::getInstance().Dispatch(CUGRAPHADDEXTERNALSEMAPHORESWAITNODE, 5, phGraphNode, hGraph, dependencies, numDependencies, nodeParams); }
CUresult CUDAAPI cuGraphExternalSemaphoresWaitNodeGetParams(CUgraphNode hNode, CUDA_EXT_SEM_WAIT_NODE_PARAMS* params_out) { return Render::getInstance().Dispatch(CUGRAPHEXTERNALSEMAPHORESWAITNODEGETPARAMS, 2, hNode, params_out); }
CUresult CUDAAPI cuGraphExternalSemaphoresWaitNodeSetParams(CUgraphNode hNode, const CUDA_EXT_SEM_WAIT_NODE_PARAMS* nodeParams) { return Render::getInstance().Dispatch(CUGRAPHEXTERNALSEMAPHORESWAITNODESETPARAMS, 2, hNode, nodeParams); }
CUresult CUDAAPI cuGraphAddBatchMemOpNode(CUgraphNode* phGraphNode, CUgraph hGraph, const CUgraphNode* dependencies, size_t numDependencies, const CUDA_BATCH_MEM_OP_NODE_PARAMS* nodeParams) { return Render::getInstance().Dispatch(CUGRAPHADDBATCHMEMOPNODE, 5, phGraphNode, hGraph, dependencies, numDependencies, nodeParams); }
CUresult CUDAAPI cuGraphBatchMemOpNodeGetParams(CUgraphNode hNode, CUDA_BATCH_MEM_OP_NODE_PARAMS* nodeParams_out) { return Render::getInstance().Dispatch(CUGRAPHBATCHMEMOPNODEGETPARAMS, 2, hNode, nodeParams_out); }
CUresult CUDAAPI cuGraphBatchMemOpNodeSetParams(CUgraphNode hNode, const CUDA_BATCH_MEM_OP_NODE_PARAMS* nodeParams) { return Render::getInstance().Dispatch(CUGRAPHBATCHMEMOPNODESETPARAMS, 2, hNode, nodeParams); }
CUresult CUDAAPI cuGraphExecBatchMemOpNodeSetParams(CUgraphExec hGraphExec, CUgraphNode hNode, const CUDA_BATCH_MEM_OP_NODE_PARAMS* nodeParams) { return Render::getInstance().Dispatch(CUGRAPHEXECBATCHMEMOPNODESETPARAMS, 3, hGraphExec, hNode, nodeParams); }
CUresult CUDAAPI cuGraphAddMemAllocNode(CUgraphNode* phGraphNode, CUgraph hGraph, const CUgraphNode* dependencies, size_t numDependencies, CUDA_MEM_ALLOC_NODE_PARAMS* nodeParams) { return Render::getInstance().Dispatch(CUGRAPHADDMEMALLOCNODE, 5, phGraphNode, hGraph, dependencies, numDependencies, nodeParams); }
CUresult CUDAAPI cuGraphMemAllocNodeGetParams(CUgraphNode hNode, CUDA_MEM_ALLOC_NODE_PARAMS* params_out) { return Render::getInstance().Dispatch(CUGRAPHMEMALLOCNODEGETPARAMS, 2, hNode, params_out); }
CUresult CUDAAPI cuGraphAddMemFreeNode(CUgraphNode* phGraphNode, CUgraph hGraph, const CUgraphNode* dependencies, size_t numDependencies, CUdeviceptr dptr) { return Render::getInstance().Dispatch(CUGRAPHADDMEMFREENODE, 5, phGraphNode, hGraph, dependencies, numDependencies, dptr); }
CUresult CUDAAPI cuGraphMemFreeNodeGetParams(CUgraphNode hNode, CUdeviceptr* dptr_out) { return Render::getInstance().Dispatch(CUGRAPHMEMFREENODEGETPARAMS, 2, hNode, dptr_out); }
CUresult CUDAAPI cuDeviceGraphMemTrim(CUdevice device) { return Render::getInstance().Dispatch(CUDEVICEGRAPHMEMTRIM, 1, device); }
CUresult CUDAAPI cuDeviceGetGraphMemAttribute(CUdevice device, CUgraphMem_attribute attr, void* value) { return Render::getInstance().Dispatch(CUDEVICEGETGRAPHMEMATTRIBUTE, 3, device, attr, value); }
CUresult CUDAAPI cuDeviceSetGraphMemAttribute(CUdevice device, CUgraphMem_attribute attr, void* value) { return Render::getInstance().Dispatch(CUDEVICESETGRAPHMEMATTRIBUTE, 3, device, attr, value); }
CUresult CUDAAPI cuGraphClone(CUgraph* phGraphClone, CUgraph originalGraph) { return Render::getInstance().Dispatch(CUGRAPHCLONE, 2, phGraphClone, originalGraph); }
CUresult CUDAAPI cuGraphNodeFindInClone(CUgraphNode* phNode, CUgraphNode hOriginalNode, CUgraph hClonedGraph) { return Render::getInstance().Dispatch(CUGRAPHNODEFINDINCLONE, 3, phNode, hOriginalNode, hClonedGraph); }
CUresult CUDAAPI cuGraphNodeGetType(CUgraphNode hNode, CUgraphNodeType* type) { return Render::getInstance().Dispatch(CUGRAPHNODEGETTYPE, 2, hNode, type); }
CUresult CUDAAPI cuGraphGetNodes(CUgraph hGraph, CUgraphNode* nodes, size_t* numNodes) { return Render::getInstance().Dispatch(CUGRAPHGETNODES, 3, hGraph, nodes, numNodes); }
CUresult CUDAAPI cuGraphGetRootNodes(CUgraph hGraph, CUgraphNode* rootNodes, size_t* numRootNodes) { return Render::getInstance().Dispatch(CUGRAPHGETROOTNODES, 3, hGraph, rootNodes, numRootNodes); }
CUresult CUDAAPI cuGraphGetEdges(CUgraph hGraph, CUgraphNode* from, CUgraphNode* to, size_t* numEdges) { return Render::getInstance().Dispatch(CUGRAPHGETEDGES, 4, hGraph, from, to, numEdges); }
CUresult CUDAAPI cuGraphNodeGetDependencies(CUgraphNode hNode, CUgraphNode* dependencies, size_t* numDependencies) { return Render::getInstance().Dispatch(CUGRAPHNODEGETDEPENDENCIES, 3, hNode, dependencies, numDependencies); }
CUresult CUDAAPI cuGraphNodeGetDependentNodes(CUgraphNode hNode, CUgraphNode* dependentNodes, size_t* numDependentNodes) { return Render::getInstance().Dispatch(CUGRAPHNODEGETDEPENDENTNODES, 3, hNode, dependentNodes, numDependentNodes); }
CUresult CUDAAPI cuGraphAddDependencies(CUgraph hGraph, const CUgraphNode* from, const CUgraphNode* to, size_t numDependencies) { return Render::getInstance().Dispatch(CUGRAPHADDDEPENDENCIES, 4, hGraph, from, to, numDependencies); }
CUresult CUDAAPI cuGraphRemoveDependencies(CUgraph hGraph, const CUgraphNode* from, const CUgraphNode* to, size_t numDependencies) { return Render::getInstance().Dispatch(CUGRAPHREMOVEDEPENDENCIES, 4, hGraph, from, to, numDependencies); }
CUresult CUDAAPI cuGraphDestroyNode(CUgraphNode hNode) { return Render::getInstance().Dispatch(CUGRAPHDESTROYNODE, 1, hNode); }
CUresult CUDAAPI cuGraphInstantiate(CUgraphExec* phGraphExec, CUgraph hGraph, unsigned long long flags) { return Render::getInstance().Dispatch(CUGRAPHINSTANTIATE, 3, phGraphExec, hGraph, flags); }
CUresult CUDAAPI cuGraphInstantiateWithParams(CUgraphExec* phGraphExec, CUgraph hGraph, CUDA_GRAPH_INSTANTIATE_PARAMS* instantiateParams) { return Render::getInstance().Dispatch(CUGRAPHINSTANTIATEWITHPARAMS, 3, phGraphExec, hGraph, instantiateParams); }
CUresult CUDAAPI cuGraphExecGetFlags(CUgraphExec hGraphExec, cuuint64_t* flags) { return Render::getInstance().Dispatch(CUGRAPHEXECGETFLAGS, 2, hGraphExec, flags); }
CUresult CUDAAPI cuGraphExecKernelNodeSetParams(CUgraphExec hGraphExec, CUgraphNode hNode, const CUDA_KERNEL_NODE_PARAMS* nodeParams) { return Render::getInstance().Dispatch(CUGRAPHEXECKERNELNODESETPARAMS, 3, hGraphExec, hNode, nodeParams); }
CUresult CUDAAPI cuGraphExecMemcpyNodeSetParams(CUgraphExec hGraphExec, CUgraphNode hNode, const CUDA_MEMCPY3D* copyParams, CUcontext ctx) { return Render::getInstance().Dispatch(CUGRAPHEXECMEMCPYNODESETPARAMS, 4, hGraphExec, hNode, copyParams, ctx); }
CUresult CUDAAPI cuGraphExecMemsetNodeSetParams(CUgraphExec hGraphExec, CUgraphNode hNode, const CUDA_MEMSET_NODE_PARAMS* memsetParams, CUcontext ctx) { return Render::getInstance().Dispatch(CUGRAPHEXECMEMSETNODESETPARAMS, 4, hGraphExec, hNode, memsetParams, ctx); }
CUresult CUDAAPI cuGraphExecHostNodeSetParams(CUgraphExec hGraphExec, CUgraphNode hNode, const CUDA_HOST_NODE_PARAMS* nodeParams) { return Render::getInstance().Dispatch(CUGRAPHEXECHOSTNODESETPARAMS, 3, hGraphExec, hNode, nodeParams); }
CUresult CUDAAPI cuGraphExecChildGraphNodeSetParams(CUgraphExec hGraphExec, CUgraphNode hNode, CUgraph childGraph) { return Render::getInstance().Dispatch(CUGRAPHEXECCHILDGRAPHNODESETPARAMS, 3, hGraphExec, hNode, childGraph); }
CUresult CUDAAPI cuGraphExecEventRecordNodeSetEvent(CUgraphExec hGraphExec, CUgraphNode hNode, CUevent event) { return Render::getInstance().Dispatch(CUGRAPHEXECEVENTRECORDNODESETEVENT, 3, hGraphExec, hNode, event); }
CUresult CUDAAPI cuGraphExecEventWaitNodeSetEvent(CUgraphExec hGraphExec, CUgraphNode hNode, CUevent event) { return Render::getInstance().Dispatch(CUGRAPHEXECEVENTWAITNODESETEVENT, 3, hGraphExec, hNode, event); }
CUresult CUDAAPI cuGraphExecExternalSemaphoresSignalNodeSetParams(CUgraphExec hGraphExec, CUgraphNode hNode, const CUDA_EXT_SEM_SIGNAL_NODE_PARAMS* nodeParams) { return Render::getInstance().Dispatch(CUGRAPHEXECEXTERNALSEMAPHORESSIGNALNODESETPARAMS, 3, hGraphExec, hNode, nodeParams); }
CUresult CUDAAPI cuGraphExecExternalSemaphoresWaitNodeSetParams(CUgraphExec hGraphExec, CUgraphNode hNode, const CUDA_EXT_SEM_WAIT_NODE_PARAMS* nodeParams) { return Render::getInstance().Dispatch(CUGRAPHEXECEXTERNALSEMAPHORESWAITNODESETPARAMS, 3, hGraphExec, hNode, nodeParams); }
CUresult CUDAAPI cuGraphNodeSetEnabled(CUgraphExec hGraphExec, CUgraphNode hNode, unsigned int isEnabled) { return Render::getInstance().Dispatch(CUGRAPHNODESETENABLED, 3, hGraphExec, hNode, isEnabled); }
CUresult CUDAAPI cuGraphNodeGetEnabled(CUgraphExec hGraphExec, CUgraphNode hNode, unsigned int* isEnabled) { return Render::getInstance().Dispatch(CUGRAPHNODEGETENABLED, 3, hGraphExec, hNode, isEnabled); }
CUresult CUDAAPI cuGraphUpload(CUgraphExec hGraphExec, CUstream hStream) { return Render::getInstance().Dispatch(CUGRAPHUPLOAD, 2, hGraphExec, hStream); }
CUresult CUDAAPI cuGraphLaunch(CUgraphExec hGraphExec, CUstream hStream) { return Render::getInstance().Dispatch(CUGRAPHLAUNCH, 2, hGraphExec, hStream); }
CUresult CUDAAPI cuGraphExecDestroy(CUgraphExec hGraphExec) { return Render::getInstance().Dispatch(CUGRAPHEXECDESTROY, 1, hGraphExec); }
CUresult CUDAAPI cuGraphDestroy(CUgraph hGraph) { return Render::getInstance().Dispatch(CUGRAPHDESTROY, 1, hGraph); }
CUresult CUDAAPI cuGraphExecUpdate(CUgraphExec hGraphExec, CUgraph hGraph, CUgraphExecUpdateResultInfo* resultInfo) { return Render::getInstance().Dispatch(CUGRAPHEXECUPDATE, 3, hGraphExec, hGraph, resultInfo); }
CUresult CUDAAPI cuGraphKernelNodeCopyAttributes(CUgraphNode dst, CUgraphNode src) { return Render::getInstance().Dispatch(CUGRAPHKERNELNODECOPYATTRIBUTES, 2, dst, src); }
CUresult CUDAAPI cuGraphKernelNodeGetAttribute(CUgraphNode hNode, CUkernelNodeAttrID attr, CUkernelNodeAttrValue* value_out) { return Render::getInstance().Dispatch(CUGRAPHKERNELNODEGETATTRIBUTE, 3, hNode, attr, value_out); }
CUresult CUDAAPI cuGraphKernelNodeSetAttribute(CUgraphNode hNode, CUkernelNodeAttrID attr, const CUkernelNodeAttrValue* value) { return Render::getInstance().Dispatch(CUGRAPHKERNELNODESETATTRIBUTE, 3, hNode, attr, value); }
CUresult CUDAAPI cuGraphDebugDotPrint(CUgraph hGraph, const char* path, unsigned int flags) { return Render::getInstance().Dispatch(CUGRAPHDEBUGDOTPRINT, 3, hGraph, path, flags); }
CUresult CUDAAPI cuUserObjectCreate(CUuserObject* object_out, void* ptr, CUhostFn destroy, unsigned int initialRefcount, unsigned int flags) { return Render::getInstance().Dispatch(CUUSEROBJECTCREATE, 5, object_out, ptr, destroy, initialRefcount, flags); }
CUresult CUDAAPI cuUserObjectRetain(CUuserObject object, unsigned int count) { return Render::getInstance().Dispatch(CUUSEROBJECTRETAIN, 2, object, count); }
CUresult CUDAAPI cuUserObjectRelease(CUuserObject object, unsigned int count) { return Render::getInstance().Dispatch(CUUSEROBJECTRELEASE, 2, object, count); }
CUresult CUDAAPI cuGraphRetainUserObject(CUgraph graph, CUuserObject object, unsigned int count, unsigned int flags) { return Render::getInstance().Dispatch(CUGRAPHRETAINUSEROBJECT, 4, graph, object, count, flags); }
CUresult CUDAAPI cuGraphReleaseUserObject(CUgraph graph, CUuserObject object, unsigned int count) { return Render::getInstance().Dispatch(CUGRAPHRELEASEUSEROBJECT, 3, graph, object, count); }
CUresult CUDAAPI cuOccupancyMaxActiveBlocksPerMultiprocessor(int* numBlocks, CUfunction func, int blockSize, size_t dynamicSMemSize) { return Render::getInstance().Dispatch(CUOCCUPANCYMAXACTIVEBLOCKSPERMULTIPROCESSOR, 4, numBlocks, func, blockSize, dynamicSMemSize); }
CUresult CUDAAPI cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags(int* numBlocks, CUfunction func, int blockSize, size_t dynamicSMemSize, unsigned int flags) { return Render::getInstance().Dispatch(CUOCCUPANCYMAXACTIVEBLOCKSPERMULTIPROCESSORWITHFLAGS, 5, numBlocks, func, blockSize, dynamicSMemSize, flags); }
CUresult CUDAAPI cuOccupancyMaxPotentialBlockSize(int* minGridSize, int* blockSize, CUfunction func, CUoccupancyB2DSize blockSizeToDynamicSMemSize, size_t dynamicSMemSize, int blockSizeLimit) { return Render::getInstance().Dispatch(CUOCCUPANCYMAXPOTENTIALBLOCKSIZE, 6, minGridSize, blockSize, func, blockSizeToDynamicSMemSize, dynamicSMemSize, blockSizeLimit); }
CUresult CUDAAPI cuOccupancyMaxPotentialBlockSizeWithFlags(int* minGridSize, int* blockSize, CUfunction func, CUoccupancyB2DSize blockSizeToDynamicSMemSize, size_t dynamicSMemSize, int blockSizeLimit, unsigned int flags) { return Render::getInstance().Dispatch(CUOCCUPANCYMAXPOTENTIALBLOCKSIZEWITHFLAGS, 7, minGridSize, blockSize, func, blockSizeToDynamicSMemSize, dynamicSMemSize, blockSizeLimit, flags); }
CUresult CUDAAPI cuOccupancyAvailableDynamicSMemPerBlock(size_t* dynamicSmemSize, CUfunction func, int numBlocks, int blockSize) { return Render::getInstance().Dispatch(CUOCCUPANCYAVAILABLEDYNAMICSMEMPERBLOCK, 4, dynamicSmemSize, func, numBlocks, blockSize); }
CUresult CUDAAPI cuOccupancyMaxPotentialClusterSize(int* clusterSize, CUfunction func, const CUlaunchConfig* config) { return Render::getInstance().Dispatch(CUOCCUPANCYMAXPOTENTIALCLUSTERSIZE, 3, clusterSize, func, config); }
CUresult CUDAAPI cuOccupancyMaxActiveClusters(int* numClusters, CUfunction func, const CUlaunchConfig* config) { return Render::getInstance().Dispatch(CUOCCUPANCYMAXACTIVECLUSTERS, 3, numClusters, func, config); }
CUresult CUDAAPI cuTexRefSetArray(CUtexref hTexRef, CUarray hArray, unsigned int Flags) { return Render::getInstance().Dispatch(CUTEXREFSETARRAY, 3, hTexRef, hArray, Flags); }
CUresult CUDAAPI cuTexRefSetMipmappedArray(CUtexref hTexRef, CUmipmappedArray hMipmappedArray, unsigned int Flags) { return Render::getInstance().Dispatch(CUTEXREFSETMIPMAPPEDARRAY, 3, hTexRef, hMipmappedArray, Flags); }
CUresult CUDAAPI cuTexRefSetAddress(size_t* ByteOffset, CUtexref hTexRef, CUdeviceptr dptr, size_t bytes) { return Render::getInstance().Dispatch(CUTEXREFSETADDRESS, 4, ByteOffset, hTexRef, dptr, bytes); }
CUresult CUDAAPI cuTexRefSetAddress2D(CUtexref hTexRef, const CUDA_ARRAY_DESCRIPTOR* desc, CUdeviceptr dptr, size_t Pitch) { return Render::getInstance().Dispatch(CUTEXREFSETADDRESS2D, 4, hTexRef, desc, dptr, Pitch); }
CUresult CUDAAPI cuTexRefSetFormat(CUtexref hTexRef, CUarray_format fmt, int NumPackedComponents) { return Render::getInstance().Dispatch(CUTEXREFSETFORMAT, 3, hTexRef, fmt, NumPackedComponents); }
CUresult CUDAAPI cuTexRefSetAddressMode(CUtexref hTexRef, int dim, CUaddress_mode am) { return Render::getInstance().Dispatch(CUTEXREFSETADDRESSMODE, 3, hTexRef, dim, am); }
CUresult CUDAAPI cuTexRefSetFilterMode(CUtexref hTexRef, CUfilter_mode fm) { return Render::getInstance().Dispatch(CUTEXREFSETFILTERMODE, 2, hTexRef, fm); }
CUresult CUDAAPI cuTexRefSetMipmapFilterMode(CUtexref hTexRef, CUfilter_mode fm) { return Render::getInstance().Dispatch(CUTEXREFSETMIPMAPFILTERMODE, 2, hTexRef, fm); }
CUresult CUDAAPI cuTexRefSetMipmapLevelBias(CUtexref hTexRef, float bias) { return Render::getInstance().Dispatch(CUTEXREFSETMIPMAPLEVELBIAS, 2, hTexRef, bias); }
CUresult CUDAAPI cuTexRefSetMipmapLevelClamp(CUtexref hTexRef, float minMipmapLevelClamp, float maxMipmapLevelClamp) { return Render::getInstance().Dispatch(CUTEXREFSETMIPMAPLEVELCLAMP, 3, hTexRef, minMipmapLevelClamp, maxMipmapLevelClamp); }
CUresult CUDAAPI cuTexRefSetMaxAnisotropy(CUtexref hTexRef, unsigned int maxAniso) { return Render::getInstance().Dispatch(CUTEXREFSETMAXANISOTROPY, 2, hTexRef, maxAniso); }
CUresult CUDAAPI cuTexRefSetBorderColor(CUtexref hTexRef, float* pBorderColor) { return Render::getInstance().Dispatch(CUTEXREFSETBORDERCOLOR, 2, hTexRef, pBorderColor); }
CUresult CUDAAPI cuTexRefSetFlags(CUtexref hTexRef, unsigned int Flags) { return Render::getInstance().Dispatch(CUTEXREFSETFLAGS, 2, hTexRef, Flags); }
CUresult CUDAAPI cuTexRefGetAddress(CUdeviceptr* pdptr, CUtexref hTexRef) { return Render::getInstance().Dispatch(CUTEXREFGETADDRESS, 2, pdptr, hTexRef); }
CUresult CUDAAPI cuTexRefGetArray(CUarray* phArray, CUtexref hTexRef) { return Render::getInstance().Dispatch(CUTEXREFGETARRAY, 2, phArray, hTexRef); }
CUresult CUDAAPI cuTexRefGetMipmappedArray(CUmipmappedArray* phMipmappedArray, CUtexref hTexRef) { return Render::getInstance().Dispatch(CUTEXREFGETMIPMAPPEDARRAY, 2, phMipmappedArray, hTexRef); }
CUresult CUDAAPI cuTexRefGetAddressMode(CUaddress_mode* pam, CUtexref hTexRef, int dim) { return Render::getInstance().Dispatch(CUTEXREFGETADDRESSMODE, 3, pam, hTexRef, dim); }
CUresult CUDAAPI cuTexRefGetFilterMode(CUfilter_mode* pfm, CUtexref hTexRef) { return Render::getInstance().Dispatch(CUTEXREFGETFILTERMODE, 2, pfm, hTexRef); }
CUresult CUDAAPI cuTexRefGetFormat(CUarray_format* pFormat, int* pNumChannels, CUtexref hTexRef) { return Render::getInstance().Dispatch(CUTEXREFGETFORMAT, 3, pFormat, pNumChannels, hTexRef); }
CUresult CUDAAPI cuTexRefGetMipmapFilterMode(CUfilter_mode* pfm, CUtexref hTexRef) { return Render::getInstance().Dispatch(CUTEXREFGETMIPMAPFILTERMODE, 2, pfm, hTexRef); }
CUresult CUDAAPI cuTexRefGetMipmapLevelBias(float* pbias, CUtexref hTexRef) { return Render::getInstance().Dispatch(CUTEXREFGETMIPMAPLEVELBIAS, 2, pbias, hTexRef); }
CUresult CUDAAPI cuTexRefGetMipmapLevelClamp(float* pminMipmapLevelClamp, float* pmaxMipmapLevelClamp, CUtexref hTexRef) { return Render::getInstance().Dispatch(CUTEXREFGETMIPMAPLEVELCLAMP, 3, pminMipmapLevelClamp, pmaxMipmapLevelClamp, hTexRef); }
CUresult CUDAAPI cuTexRefGetMaxAnisotropy(int* pmaxAniso, CUtexref hTexRef) { return Render::getInstance().Dispatch(CUTEXREFGETMAXANISOTROPY, 2, pmaxAniso, hTexRef); }
CUresult CUDAAPI cuTexRefGetBorderColor(float* pBorderColor, CUtexref hTexRef) { return Render::getInstance().Dispatch(CUTEXREFGETBORDERCOLOR, 2, pBorderColor, hTexRef); }
CUresult CUDAAPI cuTexRefGetFlags(unsigned int* pFlags, CUtexref hTexRef) { return Render::getInstance().Dispatch(CUTEXREFGETFLAGS, 2, pFlags, hTexRef); }
CUresult CUDAAPI cuTexRefCreate(CUtexref* pTexRef) { return Render::getInstance().Dispatch(CUTEXREFCREATE, 1, pTexRef); }
CUresult CUDAAPI cuTexRefDestroy(CUtexref hTexRef) { return Render::getInstance().Dispatch(CUTEXREFDESTROY, 1, hTexRef); }
CUresult CUDAAPI cuSurfRefSetArray(CUsurfref hSurfRef, CUarray hArray, unsigned int Flags) { return Render::getInstance().Dispatch(CUSURFREFSETARRAY, 3, hSurfRef, hArray, Flags); }
CUresult CUDAAPI cuSurfRefGetArray(CUarray* phArray, CUsurfref hSurfRef) { return Render::getInstance().Dispatch(CUSURFREFGETARRAY, 2, phArray, hSurfRef); }
CUresult CUDAAPI cuTexObjectCreate(CUtexObject* pTexObject, const CUDA_RESOURCE_DESC* pResDesc, const CUDA_TEXTURE_DESC* pTexDesc, const CUDA_RESOURCE_VIEW_DESC* pResViewDesc) { return Render::getInstance().Dispatch(CUTEXOBJECTCREATE, 4, pTexObject, pResDesc, pTexDesc, pResViewDesc); }
CUresult CUDAAPI cuTexObjectDestroy(CUtexObject texObject) { return Render::getInstance().Dispatch(CUTEXOBJECTDESTROY, 1, texObject); }
CUresult CUDAAPI cuTexObjectGetResourceDesc(CUDA_RESOURCE_DESC* pResDesc, CUtexObject texObject) { return Render::getInstance().Dispatch(CUTEXOBJECTGETRESOURCEDESC, 2, pResDesc, texObject); }
CUresult CUDAAPI cuTexObjectGetTextureDesc(CUDA_TEXTURE_DESC* pTexDesc, CUtexObject texObject) { return Render::getInstance().Dispatch(CUTEXOBJECTGETTEXTUREDESC, 2, pTexDesc, texObject); }
CUresult CUDAAPI cuTexObjectGetResourceViewDesc(CUDA_RESOURCE_VIEW_DESC* pResViewDesc, CUtexObject texObject) { return Render::getInstance().Dispatch(CUTEXOBJECTGETRESOURCEVIEWDESC, 2, pResViewDesc, texObject); }
CUresult CUDAAPI cuSurfObjectCreate(CUsurfObject* pSurfObject, const CUDA_RESOURCE_DESC* pResDesc) { return Render::getInstance().Dispatch(CUSURFOBJECTCREATE, 2, pSurfObject, pResDesc); }
CUresult CUDAAPI cuSurfObjectDestroy(CUsurfObject surfObject) { return Render::getInstance().Dispatch(CUSURFOBJECTDESTROY, 1, surfObject); }
CUresult CUDAAPI cuSurfObjectGetResourceDesc(CUDA_RESOURCE_DESC* pResDesc, CUsurfObject surfObject) { return Render::getInstance().Dispatch(CUSURFOBJECTGETRESOURCEDESC, 2, pResDesc, surfObject); }
CUresult CUDAAPI cuTensorMapEncodeTiled(CUtensorMap* tensorMap, CUtensorMapDataType tensorDataType, cuuint32_t tensorRank, void* globalAddress, const cuuint64_t* globalDim, const cuuint64_t* globalStrides, const cuuint32_t* boxDim, const cuuint32_t* elementStrides, CUtensorMapInterleave interleave, CUtensorMapSwizzle swizzle, CUtensorMapL2promotion l2Promotion, CUtensorMapFloatOOBfill oobFill) { return Render::getInstance().Dispatch(CUTENSORMAPENCODETILED, 12, tensorMap, tensorDataType, tensorRank, globalAddress, globalDim, globalStrides, boxDim, elementStrides, interleave, swizzle, l2Promotion, oobFill); }
CUresult CUDAAPI cuTensorMapEncodeIm2col(CUtensorMap* tensorMap, CUtensorMapDataType tensorDataType, cuuint32_t tensorRank, void* globalAddress, const cuuint64_t* globalDim, const cuuint64_t* globalStrides, const int* pixelBoxLowerCorner, const int* pixelBoxUpperCorner, cuuint32_t channelsPerPixel, cuuint32_t pixelsPerColumn, const cuuint32_t* elementStrides, CUtensorMapInterleave interleave, CUtensorMapSwizzle swizzle, CUtensorMapL2promotion l2Promotion, CUtensorMapFloatOOBfill oobFill) { return Render::getInstance().Dispatch(CUTENSORMAPENCODEIM2COL, 15, tensorMap, tensorDataType, tensorRank, globalAddress, globalDim, globalStrides, pixelBoxLowerCorner, pixelBoxUpperCorner, channelsPerPixel, pixelsPerColumn, elementStrides, interleave, swizzle, l2Promotion, oobFill); }
CUresult CUDAAPI cuTensorMapReplaceAddress(CUtensorMap* tensorMap, void* globalAddress) { return Render::getInstance().Dispatch(CUTENSORMAPREPLACEADDRESS, 2, tensorMap, globalAddress); }
CUresult CUDAAPI cuDeviceCanAccessPeer(int* canAccessPeer, CUdevice dev, CUdevice peerDev) { return Render::getInstance().Dispatch(CUDEVICECANACCESSPEER, 3, canAccessPeer, dev, peerDev); }
CUresult CUDAAPI cuCtxEnablePeerAccess(CUcontext peerContext, unsigned int Flags) { return Render::getInstance().Dispatch(CUCTXENABLEPEERACCESS, 2, peerContext, Flags); }
CUresult CUDAAPI cuCtxDisablePeerAccess(CUcontext peerContext) { return Render::getInstance().Dispatch(CUCTXDISABLEPEERACCESS, 1, peerContext); }
CUresult CUDAAPI cuDeviceGetP2PAttribute(int* value, CUdevice_P2PAttribute attrib, CUdevice srcDevice, CUdevice dstDevice) { return Render::getInstance().Dispatch(CUDEVICEGETP2PATTRIBUTE, 4, value, attrib, srcDevice, dstDevice); }
CUresult CUDAAPI cuGraphicsUnregisterResource(CUgraphicsResource resource) { return Render::getInstance().Dispatch(CUGRAPHICSUNREGISTERRESOURCE, 1, resource); }
CUresult CUDAAPI cuGraphicsSubResourceGetMappedArray(CUarray* pArray, CUgraphicsResource resource, unsigned int arrayIndex, unsigned int mipLevel) { return Render::getInstance().Dispatch(CUGRAPHICSSUBRESOURCEGETMAPPEDARRAY, 4, pArray, resource, arrayIndex, mipLevel); }
CUresult CUDAAPI cuGraphicsResourceGetMappedMipmappedArray(CUmipmappedArray* pMipmappedArray, CUgraphicsResource resource) { return Render::getInstance().Dispatch(CUGRAPHICSRESOURCEGETMAPPEDMIPMAPPEDARRAY, 2, pMipmappedArray, resource); }
CUresult CUDAAPI cuGraphicsResourceGetMappedPointer(CUdeviceptr* pDevPtr, size_t* pSize, CUgraphicsResource resource) { return Render::getInstance().Dispatch(CUGRAPHICSRESOURCEGETMAPPEDPOINTER, 3, pDevPtr, pSize, resource); }
CUresult CUDAAPI cuGraphicsResourceSetMapFlags(CUgraphicsResource resource, unsigned int flags) { return Render::getInstance().Dispatch(CUGRAPHICSRESOURCESETMAPFLAGS, 2, resource, flags); }
CUresult CUDAAPI cuGraphicsMapResources(unsigned int count, CUgraphicsResource* resources, CUstream hStream) { return Render::getInstance().Dispatch(CUGRAPHICSMAPRESOURCES, 3, count, resources, hStream); }
CUresult CUDAAPI cuGraphicsUnmapResources(unsigned int count, CUgraphicsResource* resources, CUstream hStream) { return Render::getInstance().Dispatch(CUGRAPHICSUNMAPRESOURCES, 3, count, resources, hStream); }
CUresult CUDAAPI cuGetProcAddress(const char* symbol, void** pfn, int cudaVersion, cuuint64_t flags, CUdriverProcAddressQueryResult* symbolStatus) { return Render::getInstance().Dispatch(CUGETPROCADDRESS, 5, symbol, pfn, cudaVersion, flags, symbolStatus); }
CUresult CUDAAPI cuCoredumpGetAttribute(CUcoredumpSettings attrib, void* value, size_t* size) { return Render::getInstance().Dispatch(CUCOREDUMPGETATTRIBUTE, 3, attrib, value, size); }
CUresult CUDAAPI cuCoredumpGetAttributeGlobal(CUcoredumpSettings attrib, void* value, size_t* size) { return Render::getInstance().Dispatch(CUCOREDUMPGETATTRIBUTEGLOBAL, 3, attrib, value, size); }
CUresult CUDAAPI cuCoredumpSetAttribute(CUcoredumpSettings attrib, void* value, size_t* size) { return Render::getInstance().Dispatch(CUCOREDUMPSETATTRIBUTE, 3, attrib, value, size); }
CUresult CUDAAPI cuCoredumpSetAttributeGlobal(CUcoredumpSettings attrib, void* value, size_t* size) { return Render::getInstance().Dispatch(CUCOREDUMPSETATTRIBUTEGLOBAL, 3, attrib, value, size); }
CUresult CUDAAPI cuGetExportTable(const void** ppExportTable, const CUuuid* pExportTableId) { return Render::getInstance().Dispatch(CUGETEXPORTTABLE, 2, ppExportTable, pExportTableId); }
