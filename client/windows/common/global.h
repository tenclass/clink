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

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdarg.h>
#include <stdio.h>
#include <assert.h>
#include <random>
#include <string>

#pragma warning(disable:26812)
#pragma warning(disable:4200)

inline void DebugPrintf(const char* format, ...) {
  char buf[4096];

  va_list ap;
  va_start(ap, format);
  vsnprintf(buf, sizeof buf, format, ap);
  va_end(ap);

  OutputDebugStringA(buf);
}

inline bool IsAddressValid(void* address) {
  MEMORY_BASIC_INFORMATION info;
  if (VirtualQuery(address, &info, sizeof(info)) == 0) {
    return false;
  }
  return info.State == MEM_COMMIT || info.State == MEM_RESERVE;
}

inline std::string GenerateRandomString(size_t length) {
  const std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  std::mt19937 engine(std::random_device{}());
  std::uniform_int_distribution<unsigned> dist(0, (uint32_t)characters.size() - 1);

  std::string random_string;
  for (size_t i = 0; i < length; ++i) {
    random_string += characters[dist(engine)];
  }
  return random_string;
}

#define CL_UNUSED(x) (void)(x)
#define CL_ERROR(fmt, ...) DebugPrintf("[Clink] Func Error:%s Line:%d " fmt "\n", __FUNCTION__, __LINE__, __VA_ARGS__)

#ifdef _DEBUG
#define CL_TAG() DebugPrintf("[Clink] Func:%s Line:%d \n", __FUNCTION__, __LINE__)
#define CL_PRINT(string) DebugPrintf("[Clink] Func:%s Line:%d " string "\n", __FUNCTION__, __LINE__)
#define CL_LOG(fmt, ...) DebugPrintf("[Clink] Func:%s Line:%d " fmt "\n", __FUNCTION__, __LINE__, __VA_ARGS__)
#define CL_ASSERT(condition) assert(condition)
#define CL_PANIC(fmt, ...) do { DebugPrintf("[Clink] Func Panic:%s Line:%d " fmt "\n", __FUNCTION__, __LINE__, __VA_ARGS__); assert(false); } while (0)

#else
#define CL_TAG()
#define CL_DEBUG_PRINT(string)
#define CL_DEBUG_LOG(fmt, ...)
#define CL_ASSERT(condition)
#endif // _DEBUG

