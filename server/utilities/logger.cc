/* 
 * CCLink
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

#include "logger.h"
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <cerrno>
#include <cstdlib>
#include <cstdint>
#include <chrono>
#include <sys/prctl.h>
#include <csignal>

void Log(LogType type, const char* file, int line, const char* function, const char* format, ...) {
  char message[512];
  va_list args;
  va_start(args, format);
  vsnprintf(message, 512, format, args);
  va_end(args);

  static auto program_start_time = std::chrono::steady_clock::now();
  auto delta_us = std::chrono::duration_cast<std::chrono::microseconds>(
    std::chrono::steady_clock::now() - program_start_time).count();
  char timestr[100];
  sprintf(timestr, "%.3lf", double(delta_us) / 1000);

  switch (type) {
    case kLogTypeDebug:
      fprintf(stdout, "[%s] %s:%d %s() debug: %s\n", timestr, file, line, function, message);
      fflush(stdout);
      break;
    case kLogTypeWarn:
      fprintf(stderr, "[%s] %s:%d %s() warn: %s\n", timestr, file, line, function, message);
      fflush(stderr);
      break;
    case kLogTypeError:
    case kLogTypePanic:
      if (!errno) {
        fprintf(stderr,"[%s] %s:%d %s() %serror: %s\n", timestr, file, line, function, type == kLogTypePanic ? "panic-" : "", message);
      } else {
        fprintf(stderr,"[%s] %s:%d %s() %serror: %s errno=%d, %s\n", 
          timestr, file, line, function, type == kLogTypePanic ? "panic-" : "", message, errno, strerror(errno));
      }
      fflush(stderr);
      break;
  }

  if (type == kLogTypePanic) {
    std::raise(SIGINT);
    exit(1);
  }
}

void SaveToFile(const char* path, void* data, size_t size) {
  FILE* fp = fopen(path, "wb");
  fwrite(data, size, 1, fp);
  fclose(fp);
}

void DumpHex(const void* data, size_t size) {
  uint8_t* ptr = (uint8_t*)data;
  printf("%08x  ", 0);
  for (size_t i = 0; i < size;) {
    printf("%02x ", ptr[i++]);
    if (i % 16 == 0) {
      printf("\n%08lx  ", i);
    } else if (i % 8 == 0) {
      printf(" ");
    }
  }
  printf("\n");
}

void SetThreadName(const char* name) {
  prctl(PR_SET_NAME, name);
}
