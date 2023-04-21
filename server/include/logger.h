/* 
 * CLINK
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

#ifndef CLINK_LOGGER_H
#define CLINK_LOGGER_H

#include <stddef.h>

enum LogType {
  kLogTypeDebug,
  kLogTypeWarn,
  kLogTypeError,
  kLogTypePanic
};

#define CL_UNUSED(x) (void)(x)
#define CL_LOG(fmt, ...) Log(kLogTypeDebug, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)
#define CL_WARN(fmt, ...) Log(kLogTypeWarn, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)
#define CL_ERROR(fmt, ...) Log(kLogTypeError, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)
#define CL_PANIC(fmt, ...) Log(kLogTypePanic, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)
#define CL_ASSERT(condition) \
  (__builtin_expect(!!(condition), 1) ? (void)0 : CL_PANIC("Assertion failed, "#condition))

#define CL_HEXDUMP(description, data, size) Log(kLogTypeDebug, __FILE__, __LINE__, __func__, description); \
  DumpHex(data, size);

void Log(LogType type, const char* file, int line, const char* function, const char* format, ...);
void SaveToFile(const char* path, void* data, size_t size);
void DumpHex(const void* data, size_t size);
void SetThreadName(const char* name);

#endif // CLINK_LOGGER_H
