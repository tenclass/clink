/* 
 * Clink
 * Copyright (C) 2023 cair <rui.cai@tenclass.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include "common/global.h"
#include "socket.h"
#include "export.h"
#include "utilities.h"
#include "driver_api.h"
#include <map>
#include <queue>
#include <thread>
#include <unordered_set>
#include <boost/asio/io_context.hpp>

#define RENDER_CUDA 0

#pragma pack(1)
struct RenderRequestHeader {
  bool sync;
  uint8_t render;
  uint8_t compress;
  uint32_t pid;
  uint32_t tid;
  uint32_t size;
};

struct RenderResponseHeader {
  uint8_t decompress;
  uint32_t pid;
  uint32_t tid;
  uint32_t result;
  uint32_t size;
};

struct CudaRequest {
  uint32_t version;
  uint32_t api_index;
  uint32_t param_count;
  uint64_t params[0];
};
#pragma pack()

struct RenderRequest {
  struct RenderRequestHeader header;
  std::vector<std::string> datas;
};

struct RenderResponse {
  struct RenderResponseHeader header;
  std::string data;
};

struct Response {
  HANDLE event;
  RenderResponse* render_response;
};

struct CuFunctionInfo {
  CUmodule module;
  std::string name;
};

class Render {
public:
  static Render& getInstance() {
    static Render instance;
    return instance;
  }

  Render(const Render&) = delete;
  Render& operator=(const Render&) = delete;

  void Run(std::string host, std::string port);
  void Quit();

  CUresult Dispatch(uint32_t index, uint32_t count, ...);

private:
  uint32_t pid_;
  bool finalized_;
  Socket* socket_ = nullptr;
  ZSTDUtil* zstd_ = nullptr;
  boost::asio::io_context io_context_;

  std::thread response_loop_;
  std::map<uint32_t, Response> responses_;

  std::map<void*, void*> host_guest_memory_;
  std::map<void*, void*> guest_host_memory_;

  std::map<CUmodule, void*> module_images_;
  std::map<void*, CUlinkState> image_links_;
  std::map<CUlinkState, std::unordered_set<size_t>> link_hashs_;
  std::map<size_t, std::map<std::string, std::deque<size_t>>> hash_function_params_;
  std::map<CUfunction, CuFunctionInfo> function_infos_;

  Render();
  ~Render();

  void ResponseLoop();
  bool LoadCudaKernelFunctionsFromCuBin(CUlinkState link_state, void* bin, size_t size);
  CUresult PrepareRequest(RenderRequest* request);
  CUresult HandleResponse(RenderRequest* request, RenderResponse* response);

  inline const char* ErrorDescription(CUresult result) {
    switch (result) {
      case CUDA_SUCCESS: return "no error";
      case CUDA_ERROR_INVALID_VALUE: return "invalid argument";
      case CUDA_ERROR_OUT_OF_MEMORY: return "out of memory";
      case CUDA_ERROR_NOT_INITIALIZED: return "initialization error";
      case CUDA_ERROR_DEINITIALIZED: return "driver shutting down";
      case CUDA_ERROR_PROFILER_DISABLED: return "profiler disabled while using external profiling tool";
      case CUDA_ERROR_PROFILER_NOT_INITIALIZED: return "profiler not initialized: call cudaProfilerInitialize()";
      case CUDA_ERROR_PROFILER_ALREADY_STARTED: return "profiler already started";
      case CUDA_ERROR_PROFILER_ALREADY_STOPPED: return "profiler already stopped";
      case CUDA_ERROR_STUB_LIBRARY: return "CUDA driver is a stub library";
      case CUDA_ERROR_DEVICE_UNAVAILABLE: return "CUDA-capable device(s) is/are busy or unavailable";
      case CUDA_ERROR_NO_DEVICE: return "no CUDA-capable device is detected";
      case CUDA_ERROR_INVALID_DEVICE: return "invalid device ordinal";
      case CUDA_ERROR_DEVICE_NOT_LICENSED: return "device doesn't have valid Grid license";
      case CUDA_ERROR_INVALID_IMAGE: return "device kernel image is invalid";
      case CUDA_ERROR_INVALID_CONTEXT: return "invalid device context";
      case CUDA_ERROR_CONTEXT_ALREADY_CURRENT: return "context already current";
      case CUDA_ERROR_MAP_FAILED: return "mapping of buffer object failed";
      case CUDA_ERROR_UNMAP_FAILED: return "unmapping of buffer object failed";
      case CUDA_ERROR_ARRAY_IS_MAPPED: return "array is mapped";
      case CUDA_ERROR_ALREADY_MAPPED: return "resource already mapped";
      case CUDA_ERROR_NO_BINARY_FOR_GPU: return "no kernel image is available for execution on the device";
      case CUDA_ERROR_ALREADY_ACQUIRED: return "resource already acquired";
      case CUDA_ERROR_NOT_MAPPED: return "resource not mapped";
      case CUDA_ERROR_NOT_MAPPED_AS_ARRAY: return "resource not mapped as array";
      case CUDA_ERROR_NOT_MAPPED_AS_POINTER: return "resource not mapped as pointer";
      case CUDA_ERROR_ECC_UNCORRECTABLE: return "uncorrectable ECC error encountered";
      case CUDA_ERROR_UNSUPPORTED_LIMIT: return "limit is not supported on this architecture";
      case CUDA_ERROR_CONTEXT_ALREADY_IN_USE: return "exclusive-thread device already in use by a different thread";
      case CUDA_ERROR_PEER_ACCESS_UNSUPPORTED: return "peer access is not supported between these two devices";
      case CUDA_ERROR_INVALID_PTX: return "a PTX JIT compilation failed";
      case CUDA_ERROR_INVALID_GRAPHICS_CONTEXT: return "invalid OpenGL or DirectX context";
      case CUDA_ERROR_NVLINK_UNCORRECTABLE: return "uncorrectable NVLink error detected during the execution";
      case CUDA_ERROR_JIT_COMPILER_NOT_FOUND: return "PTX JIT compiler library not found";
      case CUDA_ERROR_UNSUPPORTED_PTX_VERSION: return "the provided PTX was compiled with an unsupported toolchain.";
      case CUDA_ERROR_JIT_COMPILATION_DISABLED: return "PTX JIT compilation was disabled";
      case CUDA_ERROR_UNSUPPORTED_EXEC_AFFINITY: return "the provided execution affinity is not supported";
      case CUDA_ERROR_INVALID_SOURCE: return "device kernel image is invalid";
      case CUDA_ERROR_FILE_NOT_FOUND: return "file not found";
      case CUDA_ERROR_SHARED_OBJECT_SYMBOL_NOT_FOUND: return "shared object symbol not found";
      case CUDA_ERROR_SHARED_OBJECT_INIT_FAILED: return "shared object initialization failed";
      case CUDA_ERROR_OPERATING_SYSTEM: return "OS call failed or operation not supported on this OS";
      case CUDA_ERROR_INVALID_HANDLE: return "invalid resource handle";
      case CUDA_ERROR_ILLEGAL_STATE: return "the operation cannot be performed in the present state";
      case CUDA_ERROR_NOT_FOUND: return "named symbol not found";
      case CUDA_ERROR_NOT_READY: return "device not ready";
      case CUDA_ERROR_ILLEGAL_ADDRESS: return "an illegal memory access was encountered";
      case CUDA_ERROR_LAUNCH_OUT_OF_RESOURCES: return "too many resources requested for launch";
      case CUDA_ERROR_LAUNCH_TIMEOUT: return "the launch timed out and was terminated";
      case CUDA_ERROR_LAUNCH_INCOMPATIBLE_TEXTURING: return "launch uses incompatible texturing mode";
      case CUDA_ERROR_PEER_ACCESS_ALREADY_ENABLED: return "peer access is already enabled";
      case CUDA_ERROR_PEER_ACCESS_NOT_ENABLED: return "peer access has not been enabled";
      case CUDA_ERROR_PRIMARY_CONTEXT_ACTIVE: return "cannot set while device is active in this process";
      case CUDA_ERROR_CONTEXT_IS_DESTROYED: return "context is destroyed";
      case CUDA_ERROR_ASSERT: return "device-side assert triggered";
      case CUDA_ERROR_TOO_MANY_PEERS: return "peer mapping resources exhausted";
      case CUDA_ERROR_HOST_MEMORY_ALREADY_REGISTERED: return "part or all of the requested memory range is already mapped";
      case CUDA_ERROR_HOST_MEMORY_NOT_REGISTERED: return "pointer does not correspond to a registered memory region";
      case CUDA_ERROR_HARDWARE_STACK_ERROR: return "hardware stack error";
      case CUDA_ERROR_ILLEGAL_INSTRUCTION: return "an illegal instruction was encountered";
      case CUDA_ERROR_MISALIGNED_ADDRESS: return "misaligned address";
      case CUDA_ERROR_INVALID_ADDRESS_SPACE: return "operation not supported on global/shared address space";
      case CUDA_ERROR_INVALID_PC: return "invalid program counter";
      case CUDA_ERROR_LAUNCH_FAILED: return "unspecified launch failure";
      case CUDA_ERROR_COOPERATIVE_LAUNCH_TOO_LARGE: return "too many blocks in cooperative launch";
      case CUDA_ERROR_NOT_PERMITTED: return "operation not permitted";
      case CUDA_ERROR_NOT_SUPPORTED: return "operation not supported";
      case CUDA_ERROR_SYSTEM_NOT_READY: return "system not yet initialized";
      case CUDA_ERROR_SYSTEM_DRIVER_MISMATCH: return "system has unsupported display driver / cuda driver combination";
      case CUDA_ERROR_COMPAT_NOT_SUPPORTED_ON_DEVICE: return "forward compatibility was attempted on non supported HW";
      case CUDA_ERROR_MPS_CONNECTION_FAILED: return "MPS client failed to connect to the MPS control daemon or the MPS server";
      case CUDA_ERROR_MPS_RPC_FAILURE: return "the remote procedural call between the MPS server and the MPS client failed";
      case CUDA_ERROR_MPS_SERVER_NOT_READY: return "MPS server is not ready to accept new MPS client requests";
      case CUDA_ERROR_MPS_MAX_CLIENTS_REACHED: return "the hardware resources required to create MPS client have been exhausted";
      case CUDA_ERROR_MPS_MAX_CONNECTIONS_REACHED: return "the hardware resources required to support device connections have been exhausted";
      case CUDA_ERROR_STREAM_CAPTURE_UNSUPPORTED: return "operation not permitted when stream is capturing";
      case CUDA_ERROR_STREAM_CAPTURE_INVALIDATED: return "operation failed due to a previous error during capture";
      case CUDA_ERROR_STREAM_CAPTURE_MERGE: return "operation would result in a merge of separate capture sequences";
      case CUDA_ERROR_STREAM_CAPTURE_UNMATCHED: return "capture was not ended in the same stream as it began";
      case CUDA_ERROR_STREAM_CAPTURE_UNJOINED: return "capturing stream has unjoined work";
      case CUDA_ERROR_STREAM_CAPTURE_ISOLATION: return "dependency created on uncaptured work in another stream";
      case CUDA_ERROR_STREAM_CAPTURE_IMPLICIT: return "operation would make the legacy stream depend on a capturing blocking stream";
      case CUDA_ERROR_CAPTURED_EVENT: return "operation not permitted on an event last recorded in a capturing stream";
      case CUDA_ERROR_STREAM_CAPTURE_WRONG_THREAD: return "attempt to terminate a thread-local capture sequence from another thread";
      case CUDA_ERROR_TIMEOUT: return "wait operation timed out";
      case CUDA_ERROR_GRAPH_EXEC_UPDATE_FAILURE: return "the graph update was not performed because it included changes which violated constraints specific to instantiated graph update";
      case CUDA_ERROR_EXTERNAL_DEVICE: return "an async error has occured in external entity outside of CUDA";
      case CUDA_ERROR_UNKNOWN:
      default:
        return "unknown error";
    }
  }

  inline const char* GetCudaFunctionName(uint32_t index) {
    switch (index){
      case CUGETERRORSTRING: return "cuGetErrorString";
      case CUGETERRORNAME: return "cuGetErrorName";
      case CUINIT: return "cuInit";
      case CUDRIVERGETVERSION: return "cuDriverGetVersion";
      case CUDEVICEGET: return "cuDeviceGet";
      case CUDEVICEGETCOUNT: return "cuDeviceGetCount";
      case CUDEVICEGETNAME: return "cuDeviceGetName";
      case CUDEVICEGETUUID: return "cuDeviceGetUuid";
      case CUDEVICEGETUUID_V2: return "cuDeviceGetUuid_v2";
      case CUDEVICEGETLUID: return "cuDeviceGetLuid";
      case CUDEVICETOTALMEM: return "cuDeviceTotalMem";
      case CUDEVICEGETTEXTURE1DLINEARMAXWIDTH: return "cuDeviceGetTexture1DLinearMaxWidth";
      case CUDEVICEGETATTRIBUTE: return "cuDeviceGetAttribute";
      case CUDEVICEGETNVSCISYNCATTRIBUTES: return "cuDeviceGetNvSciSyncAttributes";
      case CUDEVICESETMEMPOOL: return "cuDeviceSetMemPool";
      case CUDEVICEGETMEMPOOL: return "cuDeviceGetMemPool";
      case CUDEVICEGETDEFAULTMEMPOOL: return "cuDeviceGetDefaultMemPool";
      case CUDEVICEGETEXECAFFINITYSUPPORT: return "cuDeviceGetExecAffinitySupport";
      case CUFLUSHGPUDIRECTRDMAWRITES: return "cuFlushGPUDirectRDMAWrites";
      case CUDEVICEGETPROPERTIES: return "cuDeviceGetProperties";
      case CUDEVICECOMPUTECAPABILITY: return "cuDeviceComputeCapability";
      case CUDEVICEPRIMARYCTXRETAIN: return "cuDevicePrimaryCtxRetain";
      case CUDEVICEPRIMARYCTXRELEASE: return "cuDevicePrimaryCtxRelease";
      case CUDEVICEPRIMARYCTXSETFLAGS: return "cuDevicePrimaryCtxSetFlags";
      case CUDEVICEPRIMARYCTXGETSTATE: return "cuDevicePrimaryCtxGetState";
      case CUDEVICEPRIMARYCTXRESET: return "cuDevicePrimaryCtxReset";
      case CUCTXCREATE: return "cuCtxCreate";
      case CUCTXCREATE_V3: return "cuCtxCreate_v3";
      case CUCTXDESTROY: return "cuCtxDestroy";
      case CUCTXPUSHCURRENT: return "cuCtxPushCurrent";
      case CUCTXPOPCURRENT: return "cuCtxPopCurrent";
      case CUCTXSETCURRENT: return "cuCtxSetCurrent";
      case CUCTXGETCURRENT: return "cuCtxGetCurrent";
      case CUCTXGETDEVICE: return "cuCtxGetDevice";
      case CUCTXGETFLAGS: return "cuCtxGetFlags";
      case CUCTXSETFLAGS: return "cuCtxSetFlags";
      case CUCTXGETID: return "cuCtxGetId";
      case CUCTXSYNCHRONIZE: return "cuCtxSynchronize";
      case CUCTXSETLIMIT: return "cuCtxSetLimit";
      case CUCTXGETLIMIT: return "cuCtxGetLimit";
      case CUCTXGETCACHECONFIG: return "cuCtxGetCacheConfig";
      case CUCTXSETCACHECONFIG: return "cuCtxSetCacheConfig";
      case CUCTXGETSHAREDMEMCONFIG: return "cuCtxGetSharedMemConfig";
      case CUCTXSETSHAREDMEMCONFIG: return "cuCtxSetSharedMemConfig";
      case CUCTXGETAPIVERSION: return "cuCtxGetApiVersion";
      case CUCTXGETSTREAMPRIORITYRANGE: return "cuCtxGetStreamPriorityRange";
      case CUCTXRESETPERSISTINGL2CACHE: return "cuCtxResetPersistingL2Cache";
      case CUCTXGETEXECAFFINITY: return "cuCtxGetExecAffinity";
      case CUCTXATTACH: return "cuCtxAttach";
      case CUCTXDETACH: return "cuCtxDetach";
      case CUMODULELOAD: return "cuModuleLoad";
      case CUMODULELOADDATA: return "cuModuleLoadData";
      case CUMODULELOADDATAEX: return "cuModuleLoadDataEx";
      case CUMODULELOADFATBINARY: return "cuModuleLoadFatBinary";
      case CUMODULEUNLOAD: return "cuModuleUnload";
      case CUMODULEGETLOADINGMODE: return "cuModuleGetLoadingMode";
      case CUMODULEGETFUNCTION: return "cuModuleGetFunction";
      case CUMODULEGETGLOBAL: return "cuModuleGetGlobal";
      case CULINKCREATE: return "cuLinkCreate";
      case CULINKADDDATA: return "cuLinkAddData";
      case CULINKADDFILE: return "cuLinkAddFile";
      case CULINKCOMPLETE: return "cuLinkComplete";
      case CULINKDESTROY: return "cuLinkDestroy";
      case CUMODULEGETTEXREF: return "cuModuleGetTexRef";
      case CUMODULEGETSURFREF: return "cuModuleGetSurfRef";
      case CULIBRARYLOADDATA: return "cuLibraryLoadData";
      case CULIBRARYLOADFROMFILE: return "cuLibraryLoadFromFile";
      case CULIBRARYUNLOAD: return "cuLibraryUnload";
      case CULIBRARYGETKERNEL: return "cuLibraryGetKernel";
      case CULIBRARYGETMODULE: return "cuLibraryGetModule";
      case CUKERNELGETFUNCTION: return "cuKernelGetFunction";
      case CULIBRARYGETGLOBAL: return "cuLibraryGetGlobal";
      case CULIBRARYGETMANAGED: return "cuLibraryGetManaged";
      case CULIBRARYGETUNIFIEDFUNCTION: return "cuLibraryGetUnifiedFunction";
      case CUKERNELGETATTRIBUTE: return "cuKernelGetAttribute";
      case CUKERNELSETATTRIBUTE: return "cuKernelSetAttribute";
      case CUKERNELSETCACHECONFIG: return "cuKernelSetCacheConfig";
      case CUMEMGETINFO: return "cuMemGetInfo";
      case CUMEMALLOC: return "cuMemAlloc";
      case CUMEMALLOCPITCH: return "cuMemAllocPitch";
      case CUMEMFREE: return "cuMemFree";
      case CUMEMGETADDRESSRANGE: return "cuMemGetAddressRange";
      case CUMEMALLOCHOST: return "cuMemAllocHost";
      case CUMEMFREEHOST: return "cuMemFreeHost";
      case CUMEMHOSTALLOC: return "cuMemHostAlloc";
      case CUMEMHOSTGETDEVICEPOINTER: return "cuMemHostGetDevicePointer";
      case CUMEMHOSTGETFLAGS: return "cuMemHostGetFlags";
      case CUMEMALLOCMANAGED: return "cuMemAllocManaged";
      case CUDEVICEGETBYPCIBUSID: return "cuDeviceGetByPCIBusId";
      case CUDEVICEGETPCIBUSID: return "cuDeviceGetPCIBusId";
      case CUIPCGETEVENTHANDLE: return "cuIpcGetEventHandle";
      case CUIPCOPENEVENTHANDLE: return "cuIpcOpenEventHandle";
      case CUIPCGETMEMHANDLE: return "cuIpcGetMemHandle";
      case CUIPCOPENMEMHANDLE: return "cuIpcOpenMemHandle";
      case CUIPCCLOSEMEMHANDLE: return "cuIpcCloseMemHandle";
      case CUMEMHOSTREGISTER: return "cuMemHostRegister";
      case CUMEMHOSTUNREGISTER: return "cuMemHostUnregister";
      case CUMEMCPY: return "cuMemcpy";
      case CUMEMCPYPEER: return "cuMemcpyPeer";
      case CUMEMCPYHTOD: return "cuMemcpyHtoD";
      case CUMEMCPYDTOH: return "cuMemcpyDtoH";
      case CUMEMCPYDTOD: return "cuMemcpyDtoD";
      case CUMEMCPYDTOA: return "cuMemcpyDtoA";
      case CUMEMCPYATOD: return "cuMemcpyAtoD";
      case CUMEMCPYHTOA: return "cuMemcpyHtoA";
      case CUMEMCPYATOH: return "cuMemcpyAtoH";
      case CUMEMCPYATOA: return "cuMemcpyAtoA";
      case CUMEMCPY2D: return "cuMemcpy2D";
      case CUMEMCPY2DUNALIGNED: return "cuMemcpy2DUnaligned";
      case CUMEMCPY3D: return "cuMemcpy3D";
      case CUMEMCPY3DPEER: return "cuMemcpy3DPeer";
      case CUMEMCPYASYNC: return "cuMemcpyAsync";
      case CUMEMCPYPEERASYNC: return "cuMemcpyPeerAsync";
      case CUMEMCPYHTODASYNC: return "cuMemcpyHtoDAsync";
      case CUMEMCPYDTOHASYNC: return "cuMemcpyDtoHAsync";
      case CUMEMCPYDTODASYNC: return "cuMemcpyDtoDAsync";
      case CUMEMCPYHTOAASYNC: return "cuMemcpyHtoAAsync";
      case CUMEMCPYATOHASYNC: return "cuMemcpyAtoHAsync";
      case CUMEMCPY2DASYNC: return "cuMemcpy2DAsync";
      case CUMEMCPY3DASYNC: return "cuMemcpy3DAsync";
      case CUMEMCPY3DPEERASYNC: return "cuMemcpy3DPeerAsync";
      case CUMEMSETD8: return "cuMemsetD8";
      case CUMEMSETD16: return "cuMemsetD16";
      case CUMEMSETD32: return "cuMemsetD32";
      case CUMEMSETD2D8: return "cuMemsetD2D8";
      case CUMEMSETD2D16: return "cuMemsetD2D16";
      case CUMEMSETD2D32: return "cuMemsetD2D32";
      case CUMEMSETD8ASYNC: return "cuMemsetD8Async";
      case CUMEMSETD16ASYNC: return "cuMemsetD16Async";
      case CUMEMSETD32ASYNC: return "cuMemsetD32Async";
      case CUMEMSETD2D8ASYNC: return "cuMemsetD2D8Async";
      case CUMEMSETD2D16ASYNC: return "cuMemsetD2D16Async";
      case CUMEMSETD2D32ASYNC: return "cuMemsetD2D32Async";
      case CUARRAYCREATE: return "cuArrayCreate";
      case CUARRAYGETDESCRIPTOR: return "cuArrayGetDescriptor";
      case CUARRAYGETSPARSEPROPERTIES: return "cuArrayGetSparseProperties";
      case CUMIPMAPPEDARRAYGETSPARSEPROPERTIES: return "cuMipmappedArrayGetSparseProperties";
      case CUARRAYGETMEMORYREQUIREMENTS: return "cuArrayGetMemoryRequirements";
      case CUMIPMAPPEDARRAYGETMEMORYREQUIREMENTS: return "cuMipmappedArrayGetMemoryRequirements";
      case CUARRAYGETPLANE: return "cuArrayGetPlane";
      case CUARRAYDESTROY: return "cuArrayDestroy";
      case CUARRAY3DCREATE: return "cuArray3DCreate";
      case CUARRAY3DGETDESCRIPTOR: return "cuArray3DGetDescriptor";
      case CUMIPMAPPEDARRAYCREATE: return "cuMipmappedArrayCreate";
      case CUMIPMAPPEDARRAYGETLEVEL: return "cuMipmappedArrayGetLevel";
      case CUMIPMAPPEDARRAYDESTROY: return "cuMipmappedArrayDestroy";
      case CUMEMGETHANDLEFORADDRESSRANGE: return "cuMemGetHandleForAddressRange";
      case CUMEMADDRESSRESERVE: return "cuMemAddressReserve";
      case CUMEMADDRESSFREE: return "cuMemAddressFree";
      case CUMEMCREATE: return "cuMemCreate";
      case CUMEMRELEASE: return "cuMemRelease";
      case CUMEMMAP: return "cuMemMap";
      case CUMEMMAPARRAYASYNC: return "cuMemMapArrayAsync";
      case CUMEMUNMAP: return "cuMemUnmap";
      case CUMEMSETACCESS: return "cuMemSetAccess";
      case CUMEMGETACCESS: return "cuMemGetAccess";
      case CUMEMEXPORTTOSHAREABLEHANDLE: return "cuMemExportToShareableHandle";
      case CUMEMIMPORTFROMSHAREABLEHANDLE: return "cuMemImportFromShareableHandle";
      case CUMEMGETALLOCATIONGRANULARITY: return "cuMemGetAllocationGranularity";
      case CUMEMGETALLOCATIONPROPERTIESFROMHANDLE: return "cuMemGetAllocationPropertiesFromHandle";
      case CUMEMRETAINALLOCATIONHANDLE: return "cuMemRetainAllocationHandle";
      case CUMEMFREEASYNC: return "cuMemFreeAsync";
      case CUMEMALLOCASYNC: return "cuMemAllocAsync";
      case CUMEMPOOLTRIMTO: return "cuMemPoolTrimTo";
      case CUMEMPOOLSETATTRIBUTE: return "cuMemPoolSetAttribute";
      case CUMEMPOOLGETATTRIBUTE: return "cuMemPoolGetAttribute";
      case CUMEMPOOLSETACCESS: return "cuMemPoolSetAccess";
      case CUMEMPOOLGETACCESS: return "cuMemPoolGetAccess";
      case CUMEMPOOLCREATE: return "cuMemPoolCreate";
      case CUMEMPOOLDESTROY: return "cuMemPoolDestroy";
      case CUMEMALLOCFROMPOOLASYNC: return "cuMemAllocFromPoolAsync";
      case CUMEMPOOLEXPORTTOSHAREABLEHANDLE: return "cuMemPoolExportToShareableHandle";
      case CUMEMPOOLIMPORTFROMSHAREABLEHANDLE: return "cuMemPoolImportFromShareableHandle";
      case CUMEMPOOLEXPORTPOINTER: return "cuMemPoolExportPointer";
      case CUMEMPOOLIMPORTPOINTER: return "cuMemPoolImportPointer";
      case CUMULTICASTCREATE: return "cuMulticastCreate";
      case CUMULTICASTADDDEVICE: return "cuMulticastAddDevice";
      case CUMULTICASTBINDMEM: return "cuMulticastBindMem";
      case CUMULTICASTBINDADDR: return "cuMulticastBindAddr";
      case CUMULTICASTUNBIND: return "cuMulticastUnbind";
      case CUMULTICASTGETGRANULARITY: return "cuMulticastGetGranularity";
      case CUPOINTERGETATTRIBUTE: return "cuPointerGetAttribute";
      case CUMEMPREFETCHASYNC: return "cuMemPrefetchAsync";
      case CUMEMADVISE: return "cuMemAdvise";
      case CUMEMRANGEGETATTRIBUTE: return "cuMemRangeGetAttribute";
      case CUMEMRANGEGETATTRIBUTES: return "cuMemRangeGetAttributes";
      case CUPOINTERSETATTRIBUTE: return "cuPointerSetAttribute";
      case CUPOINTERGETATTRIBUTES: return "cuPointerGetAttributes";
      case CUSTREAMCREATE: return "cuStreamCreate";
      case CUSTREAMCREATEWITHPRIORITY: return "cuStreamCreateWithPriority";
      case CUSTREAMGETPRIORITY: return "cuStreamGetPriority";
      case CUSTREAMGETFLAGS: return "cuStreamGetFlags";
      case CUSTREAMGETID: return "cuStreamGetId";
      case CUSTREAMGETCTX: return "cuStreamGetCtx";
      case CUSTREAMWAITEVENT: return "cuStreamWaitEvent";
      case CUSTREAMADDCALLBACK: return "cuStreamAddCallback";
      case CUSTREAMBEGINCAPTURE: return "cuStreamBeginCapture";
      case CUTHREADEXCHANGESTREAMCAPTUREMODE: return "cuThreadExchangeStreamCaptureMode";
      case CUSTREAMENDCAPTURE: return "cuStreamEndCapture";
      case CUSTREAMISCAPTURING: return "cuStreamIsCapturing";
      case CUSTREAMGETCAPTUREINFO: return "cuStreamGetCaptureInfo";
      case CUSTREAMUPDATECAPTUREDEPENDENCIES: return "cuStreamUpdateCaptureDependencies";
      case CUSTREAMATTACHMEMASYNC: return "cuStreamAttachMemAsync";
      case CUSTREAMQUERY: return "cuStreamQuery";
      case CUSTREAMSYNCHRONIZE: return "cuStreamSynchronize";
      case CUSTREAMDESTROY: return "cuStreamDestroy";
      case CUSTREAMCOPYATTRIBUTES: return "cuStreamCopyAttributes";
      case CUSTREAMGETATTRIBUTE: return "cuStreamGetAttribute";
      case CUSTREAMSETATTRIBUTE: return "cuStreamSetAttribute";
      case CUEVENTCREATE: return "cuEventCreate";
      case CUEVENTRECORD: return "cuEventRecord";
      case CUEVENTRECORDWITHFLAGS: return "cuEventRecordWithFlags";
      case CUEVENTQUERY: return "cuEventQuery";
      case CUEVENTSYNCHRONIZE: return "cuEventSynchronize";
      case CUEVENTDESTROY: return "cuEventDestroy";
      case CUEVENTELAPSEDTIME: return "cuEventElapsedTime";
      case CUIMPORTEXTERNALMEMORY: return "cuImportExternalMemory";
      case CUEXTERNALMEMORYGETMAPPEDBUFFER: return "cuExternalMemoryGetMappedBuffer";
      case CUEXTERNALMEMORYGETMAPPEDMIPMAPPEDARRAY: return "cuExternalMemoryGetMappedMipmappedArray";
      case CUDESTROYEXTERNALMEMORY: return "cuDestroyExternalMemory";
      case CUIMPORTEXTERNALSEMAPHORE: return "cuImportExternalSemaphore";
      case CUSIGNALEXTERNALSEMAPHORESASYNC: return "cuSignalExternalSemaphoresAsync";
      case CUWAITEXTERNALSEMAPHORESASYNC: return "cuWaitExternalSemaphoresAsync";
      case CUDESTROYEXTERNALSEMAPHORE: return "cuDestroyExternalSemaphore";
      case CUSTREAMWAITVALUE32: return "cuStreamWaitValue32";
      case CUSTREAMWAITVALUE64: return "cuStreamWaitValue64";
      case CUSTREAMWRITEVALUE32: return "cuStreamWriteValue32";
      case CUSTREAMWRITEVALUE64: return "cuStreamWriteValue64";
      case CUSTREAMBATCHMEMOP: return "cuStreamBatchMemOp";
      case CUFUNCGETATTRIBUTE: return "cuFuncGetAttribute";
      case CUFUNCSETATTRIBUTE: return "cuFuncSetAttribute";
      case CUFUNCSETCACHECONFIG: return "cuFuncSetCacheConfig";
      case CUFUNCSETSHAREDMEMCONFIG: return "cuFuncSetSharedMemConfig";
      case CUFUNCGETMODULE: return "cuFuncGetModule";
      case CULAUNCHKERNEL: return "cuLaunchKernel";
      case CULAUNCHKERNELEX: return "cuLaunchKernelEx";
      case CULAUNCHCOOPERATIVEKERNEL: return "cuLaunchCooperativeKernel";
      case CULAUNCHCOOPERATIVEKERNELMULTIDEVICE: return "cuLaunchCooperativeKernelMultiDevice";
      case CULAUNCHHOSTFUNC: return "cuLaunchHostFunc";
      case CUFUNCSETBLOCKSHAPE: return "cuFuncSetBlockShape";
      case CUFUNCSETSHAREDSIZE: return "cuFuncSetSharedSize";
      case CUPARAMSETSIZE: return "cuParamSetSize";
      case CUPARAMSETI: return "cuParamSeti";
      case CUPARAMSETF: return "cuParamSetf";
      case CUPARAMSETV: return "cuParamSetv";
      case CULAUNCH: return "cuLaunch";
      case CULAUNCHGRID: return "cuLaunchGrid";
      case CULAUNCHGRIDASYNC: return "cuLaunchGridAsync";
      case CUPARAMSETTEXREF: return "cuParamSetTexRef";
      case CUGRAPHCREATE: return "cuGraphCreate";
      case CUGRAPHADDKERNELNODE: return "cuGraphAddKernelNode";
      case CUGRAPHKERNELNODEGETPARAMS: return "cuGraphKernelNodeGetParams";
      case CUGRAPHKERNELNODESETPARAMS: return "cuGraphKernelNodeSetParams";
      case CUGRAPHADDMEMCPYNODE: return "cuGraphAddMemcpyNode";
      case CUGRAPHMEMCPYNODEGETPARAMS: return "cuGraphMemcpyNodeGetParams";
      case CUGRAPHMEMCPYNODESETPARAMS: return "cuGraphMemcpyNodeSetParams";
      case CUGRAPHADDMEMSETNODE: return "cuGraphAddMemsetNode";
      case CUGRAPHMEMSETNODEGETPARAMS: return "cuGraphMemsetNodeGetParams";
      case CUGRAPHMEMSETNODESETPARAMS: return "cuGraphMemsetNodeSetParams";
      case CUGRAPHADDHOSTNODE: return "cuGraphAddHostNode";
      case CUGRAPHHOSTNODEGETPARAMS: return "cuGraphHostNodeGetParams";
      case CUGRAPHHOSTNODESETPARAMS: return "cuGraphHostNodeSetParams";
      case CUGRAPHADDCHILDGRAPHNODE: return "cuGraphAddChildGraphNode";
      case CUGRAPHCHILDGRAPHNODEGETGRAPH: return "cuGraphChildGraphNodeGetGraph";
      case CUGRAPHADDEMPTYNODE: return "cuGraphAddEmptyNode";
      case CUGRAPHADDEVENTRECORDNODE: return "cuGraphAddEventRecordNode";
      case CUGRAPHEVENTRECORDNODEGETEVENT: return "cuGraphEventRecordNodeGetEvent";
      case CUGRAPHEVENTRECORDNODESETEVENT: return "cuGraphEventRecordNodeSetEvent";
      case CUGRAPHADDEVENTWAITNODE: return "cuGraphAddEventWaitNode";
      case CUGRAPHEVENTWAITNODEGETEVENT: return "cuGraphEventWaitNodeGetEvent";
      case CUGRAPHEVENTWAITNODESETEVENT: return "cuGraphEventWaitNodeSetEvent";
      case CUGRAPHADDEXTERNALSEMAPHORESSIGNALNODE: return "cuGraphAddExternalSemaphoresSignalNode";
      case CUGRAPHEXTERNALSEMAPHORESSIGNALNODEGETPARAMS: return "cuGraphExternalSemaphoresSignalNodeGetParams";
      case CUGRAPHEXTERNALSEMAPHORESSIGNALNODESETPARAMS: return "cuGraphExternalSemaphoresSignalNodeSetParams";
      case CUGRAPHADDEXTERNALSEMAPHORESWAITNODE: return "cuGraphAddExternalSemaphoresWaitNode";
      case CUGRAPHEXTERNALSEMAPHORESWAITNODEGETPARAMS: return "cuGraphExternalSemaphoresWaitNodeGetParams";
      case CUGRAPHEXTERNALSEMAPHORESWAITNODESETPARAMS: return "cuGraphExternalSemaphoresWaitNodeSetParams";
      case CUGRAPHADDBATCHMEMOPNODE: return "cuGraphAddBatchMemOpNode";
      case CUGRAPHBATCHMEMOPNODEGETPARAMS: return "cuGraphBatchMemOpNodeGetParams";
      case CUGRAPHBATCHMEMOPNODESETPARAMS: return "cuGraphBatchMemOpNodeSetParams";
      case CUGRAPHEXECBATCHMEMOPNODESETPARAMS: return "cuGraphExecBatchMemOpNodeSetParams";
      case CUGRAPHADDMEMALLOCNODE: return "cuGraphAddMemAllocNode";
      case CUGRAPHMEMALLOCNODEGETPARAMS: return "cuGraphMemAllocNodeGetParams";
      case CUGRAPHADDMEMFREENODE: return "cuGraphAddMemFreeNode";
      case CUGRAPHMEMFREENODEGETPARAMS: return "cuGraphMemFreeNodeGetParams";
      case CUDEVICEGRAPHMEMTRIM: return "cuDeviceGraphMemTrim";
      case CUDEVICEGETGRAPHMEMATTRIBUTE: return "cuDeviceGetGraphMemAttribute";
      case CUDEVICESETGRAPHMEMATTRIBUTE: return "cuDeviceSetGraphMemAttribute";
      case CUGRAPHCLONE: return "cuGraphClone";
      case CUGRAPHNODEFINDINCLONE: return "cuGraphNodeFindInClone";
      case CUGRAPHNODEGETTYPE: return "cuGraphNodeGetType";
      case CUGRAPHGETNODES: return "cuGraphGetNodes";
      case CUGRAPHGETROOTNODES: return "cuGraphGetRootNodes";
      case CUGRAPHGETEDGES: return "cuGraphGetEdges";
      case CUGRAPHNODEGETDEPENDENCIES: return "cuGraphNodeGetDependencies";
      case CUGRAPHNODEGETDEPENDENTNODES: return "cuGraphNodeGetDependentNodes";
      case CUGRAPHADDDEPENDENCIES: return "cuGraphAddDependencies";
      case CUGRAPHREMOVEDEPENDENCIES: return "cuGraphRemoveDependencies";
      case CUGRAPHDESTROYNODE: return "cuGraphDestroyNode";
      case CUGRAPHINSTANTIATE: return "cuGraphInstantiate";
      case CUGRAPHINSTANTIATEWITHPARAMS: return "cuGraphInstantiateWithParams";
      case CUGRAPHEXECGETFLAGS: return "cuGraphExecGetFlags";
      case CUGRAPHEXECKERNELNODESETPARAMS: return "cuGraphExecKernelNodeSetParams";
      case CUGRAPHEXECMEMCPYNODESETPARAMS: return "cuGraphExecMemcpyNodeSetParams";
      case CUGRAPHEXECMEMSETNODESETPARAMS: return "cuGraphExecMemsetNodeSetParams";
      case CUGRAPHEXECHOSTNODESETPARAMS: return "cuGraphExecHostNodeSetParams";
      case CUGRAPHEXECCHILDGRAPHNODESETPARAMS: return "cuGraphExecChildGraphNodeSetParams";
      case CUGRAPHEXECEVENTRECORDNODESETEVENT: return "cuGraphExecEventRecordNodeSetEvent";
      case CUGRAPHEXECEVENTWAITNODESETEVENT: return "cuGraphExecEventWaitNodeSetEvent";
      case CUGRAPHEXECEXTERNALSEMAPHORESSIGNALNODESETPARAMS: return "cuGraphExecExternalSemaphoresSignalNodeSetParams";
      case CUGRAPHEXECEXTERNALSEMAPHORESWAITNODESETPARAMS: return "cuGraphExecExternalSemaphoresWaitNodeSetParams";
      case CUGRAPHNODESETENABLED: return "cuGraphNodeSetEnabled";
      case CUGRAPHNODEGETENABLED: return "cuGraphNodeGetEnabled";
      case CUGRAPHUPLOAD: return "cuGraphUpload";
      case CUGRAPHLAUNCH: return "cuGraphLaunch";
      case CUGRAPHEXECDESTROY: return "cuGraphExecDestroy";
      case CUGRAPHDESTROY: return "cuGraphDestroy";
      case CUGRAPHEXECUPDATE: return "cuGraphExecUpdate";
      case CUGRAPHKERNELNODECOPYATTRIBUTES: return "cuGraphKernelNodeCopyAttributes";
      case CUGRAPHKERNELNODEGETATTRIBUTE: return "cuGraphKernelNodeGetAttribute";
      case CUGRAPHKERNELNODESETATTRIBUTE: return "cuGraphKernelNodeSetAttribute";
      case CUGRAPHDEBUGDOTPRINT: return "cuGraphDebugDotPrint";
      case CUUSEROBJECTCREATE: return "cuUserObjectCreate";
      case CUUSEROBJECTRETAIN: return "cuUserObjectRetain";
      case CUUSEROBJECTRELEASE: return "cuUserObjectRelease";
      case CUGRAPHRETAINUSEROBJECT: return "cuGraphRetainUserObject";
      case CUGRAPHRELEASEUSEROBJECT: return "cuGraphReleaseUserObject";
      case CUOCCUPANCYMAXACTIVEBLOCKSPERMULTIPROCESSOR: return "cuOccupancyMaxActiveBlocksPerMultiprocessor";
      case CUOCCUPANCYMAXACTIVEBLOCKSPERMULTIPROCESSORWITHFLAGS: return "cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags";
      case CUOCCUPANCYMAXPOTENTIALBLOCKSIZE: return "cuOccupancyMaxPotentialBlockSize";
      case CUOCCUPANCYMAXPOTENTIALBLOCKSIZEWITHFLAGS: return "cuOccupancyMaxPotentialBlockSizeWithFlags";
      case CUOCCUPANCYAVAILABLEDYNAMICSMEMPERBLOCK: return "cuOccupancyAvailableDynamicSMemPerBlock";
      case CUOCCUPANCYMAXPOTENTIALCLUSTERSIZE: return "cuOccupancyMaxPotentialClusterSize";
      case CUOCCUPANCYMAXACTIVECLUSTERS: return "cuOccupancyMaxActiveClusters";
      case CUTEXREFSETARRAY: return "cuTexRefSetArray";
      case CUTEXREFSETMIPMAPPEDARRAY: return "cuTexRefSetMipmappedArray";
      case CUTEXREFSETADDRESS: return "cuTexRefSetAddress";
      case CUTEXREFSETADDRESS2D: return "cuTexRefSetAddress2D";
      case CUTEXREFSETFORMAT: return "cuTexRefSetFormat";
      case CUTEXREFSETADDRESSMODE: return "cuTexRefSetAddressMode";
      case CUTEXREFSETFILTERMODE: return "cuTexRefSetFilterMode";
      case CUTEXREFSETMIPMAPFILTERMODE: return "cuTexRefSetMipmapFilterMode";
      case CUTEXREFSETMIPMAPLEVELBIAS: return "cuTexRefSetMipmapLevelBias";
      case CUTEXREFSETMIPMAPLEVELCLAMP: return "cuTexRefSetMipmapLevelClamp";
      case CUTEXREFSETMAXANISOTROPY: return "cuTexRefSetMaxAnisotropy";
      case CUTEXREFSETBORDERCOLOR: return "cuTexRefSetBorderColor";
      case CUTEXREFSETFLAGS: return "cuTexRefSetFlags";
      case CUTEXREFGETADDRESS: return "cuTexRefGetAddress";
      case CUTEXREFGETARRAY: return "cuTexRefGetArray";
      case CUTEXREFGETMIPMAPPEDARRAY: return "cuTexRefGetMipmappedArray";
      case CUTEXREFGETADDRESSMODE: return "cuTexRefGetAddressMode";
      case CUTEXREFGETFILTERMODE: return "cuTexRefGetFilterMode";
      case CUTEXREFGETFORMAT: return "cuTexRefGetFormat";
      case CUTEXREFGETMIPMAPFILTERMODE: return "cuTexRefGetMipmapFilterMode";
      case CUTEXREFGETMIPMAPLEVELBIAS: return "cuTexRefGetMipmapLevelBias";
      case CUTEXREFGETMIPMAPLEVELCLAMP: return "cuTexRefGetMipmapLevelClamp";
      case CUTEXREFGETMAXANISOTROPY: return "cuTexRefGetMaxAnisotropy";
      case CUTEXREFGETBORDERCOLOR: return "cuTexRefGetBorderColor";
      case CUTEXREFGETFLAGS: return "cuTexRefGetFlags";
      case CUTEXREFCREATE: return "cuTexRefCreate";
      case CUTEXREFDESTROY: return "cuTexRefDestroy";
      case CUSURFREFSETARRAY: return "cuSurfRefSetArray";
      case CUSURFREFGETARRAY: return "cuSurfRefGetArray";
      case CUTEXOBJECTCREATE: return "cuTexObjectCreate";
      case CUTEXOBJECTDESTROY: return "cuTexObjectDestroy";
      case CUTEXOBJECTGETRESOURCEDESC: return "cuTexObjectGetResourceDesc";
      case CUTEXOBJECTGETTEXTUREDESC: return "cuTexObjectGetTextureDesc";
      case CUTEXOBJECTGETRESOURCEVIEWDESC: return "cuTexObjectGetResourceViewDesc";
      case CUSURFOBJECTCREATE: return "cuSurfObjectCreate";
      case CUSURFOBJECTDESTROY: return "cuSurfObjectDestroy";
      case CUSURFOBJECTGETRESOURCEDESC: return "cuSurfObjectGetResourceDesc";
      case CUTENSORMAPENCODETILED: return "cuTensorMapEncodeTiled";
      case CUTENSORMAPENCODEIM2COL: return "cuTensorMapEncodeIm2col";
      case CUTENSORMAPREPLACEADDRESS: return "cuTensorMapReplaceAddress";
      case CUDEVICECANACCESSPEER: return "cuDeviceCanAccessPeer";
      case CUCTXENABLEPEERACCESS: return "cuCtxEnablePeerAccess";
      case CUCTXDISABLEPEERACCESS: return "cuCtxDisablePeerAccess";
      case CUDEVICEGETP2PATTRIBUTE: return "cuDeviceGetP2PAttribute";
      case CUGRAPHICSUNREGISTERRESOURCE: return "cuGraphicsUnregisterResource";
      case CUGRAPHICSSUBRESOURCEGETMAPPEDARRAY: return "cuGraphicsSubResourceGetMappedArray";
      case CUGRAPHICSRESOURCEGETMAPPEDMIPMAPPEDARRAY: return "cuGraphicsResourceGetMappedMipmappedArray";
      case CUGRAPHICSRESOURCEGETMAPPEDPOINTER: return "cuGraphicsResourceGetMappedPointer";
      case CUGRAPHICSRESOURCESETMAPFLAGS: return "cuGraphicsResourceSetMapFlags";
      case CUGRAPHICSMAPRESOURCES: return "cuGraphicsMapResources";
      case CUGRAPHICSUNMAPRESOURCES: return "cuGraphicsUnmapResources";
      case CUGETPROCADDRESS: return "cuGetProcAddress";
      case CUCOREDUMPGETATTRIBUTE: return "cuCoredumpGetAttribute";
      case CUCOREDUMPGETATTRIBUTEGLOBAL: return "cuCoredumpGetAttributeGlobal";
      case CUCOREDUMPSETATTRIBUTE: return "cuCoredumpSetAttribute";
      case CUCOREDUMPSETATTRIBUTEGLOBAL: return "cuCoredumpSetAttributeGlobal";
      case CUGETEXPORTTABLE: return "cuGetExportTable";
      default: return nullptr;
    }
  }
};
