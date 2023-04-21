#pragma once

#include "nvapi.h"

typedef struct
{
  NvU32 version;
  NvU32 flags;
  struct {
    NvU32 bIsPresent;
    NvU32 percentage[5];
    NvU32 unknown : 2;
  } usages[8];
} NV_USAGES_INFO_V1;

typedef NV_USAGES_INFO_V1 NV_USAGES_INFO;

#define FAKE_PHYSICAL_GPU ((NvPhysicalGpuHandle)0xdead0110LL)
#define NV_USAGES_INFO_V1_VER MAKE_NVAPI_VERSION(NV_USAGES_INFO_V1, 1)

extern "C" __declspec(dllexport) void* nvapi_QueryInterface(NvU32 id);
