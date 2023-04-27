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

#include <string>
#include <vector>

#define ZSTD_STATIC_LINKING_ONLY
#include <zstd.h>

#define NO_COMPRESS                 0
#define ZSTD_COMPRESS_TYPE          1
#define ZSTD_COMPRESS_LEVEL         ZSTD_fast
#define ZSTD_COMPRESS_WORKER_NUM    4
#define ZSTD_COMPRESS_DATA_MIN_SIZE 4096
#define ZSTD_COMPRESS_WINDOW_POWER  27

class ZSTDUtil {
private:
  ZSTD_CCtx* cctx_;
  ZSTD_DCtx* dctx_;
public:
  ZSTDUtil(uint32_t thread_count, uint32_t compress_level, uint32_t window_size_power);
  ~ZSTDUtil();

  std::string Compress(std::vector<std::string>& datas);
  std::string Compress(std::string& data);
  std::string Decompress(std::string& data);
};
