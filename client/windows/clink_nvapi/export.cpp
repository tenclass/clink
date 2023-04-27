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

#include "common/global.h"
#include "export.h"

NVAPI_INTERFACE NvAPI_Initialize() {
  return NVAPI_OK;
}

NVAPI_INTERFACE NvAPI_Unload() {
  return NVAPI_OK;
}

NVAPI_INTERFACE NvAPI_EnumPhysicalGPUs(NvPhysicalGpuHandle nvGPUHandle[NVAPI_MAX_PHYSICAL_GPUS], NvU32* pGpuCount) {
  if (!nvGPUHandle) {
    return NVAPI_INVALID_ARGUMENT;
  }

  if (!pGpuCount) {
    return NVAPI_INVALID_ARGUMENT;
  }

  nvGPUHandle[0] = FAKE_PHYSICAL_GPU;
  *pGpuCount = 1;
  return NVAPI_OK;
}

// this undocumented api is used by octane to show gpu usage, we need to fix it, otherwise octane would crash itself.
NVAPI_INTERFACE NvAPI_GPU_GetUsages(NvPhysicalGpuHandle hPhysicalGpu, NV_USAGES_INFO* pUsagesInfo) {
  if (hPhysicalGpu != FAKE_PHYSICAL_GPU) {
    return NVAPI_EXPECTED_PHYSICAL_GPU_HANDLE;
  }

  if (pUsagesInfo->version != NV_USAGES_INFO_V1_VER) {
    return NVAPI_INCOMPATIBLE_STRUCT_VERSION;
  }

  // https://github.com/SveSop/nvapi_standalone/blob/master/dlls/nvapi/nvapi.c
  pUsagesInfo->flags = 1;
  pUsagesInfo->usages[0].bIsPresent = 1;
  pUsagesInfo->usages[0].percentage[0] = 0;	/* This is GPU usage % */
  pUsagesInfo->usages[0].percentage[4] = 0;	/* This is Memory controller usage % */
  return NVAPI_OK;
}

void* nvapi_QueryInterface(NvU32 id) {
  // CL_LOG("get func id=0x%lx", id);
  switch (id) {
  case 0x0150e828:
    return NvAPI_Initialize;
  case 0xd22bdd7e:
    return NvAPI_Unload;
  case 0xe5ac921f:
    return NvAPI_EnumPhysicalGPUs;
  case 0x189a1fdf:
    return NvAPI_GPU_GetUsages;
  default:
    break;
  }
  return nullptr;
}
