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
