#ifndef _CLINK_UTILITIES_H
#define _CLINK_UTILITIES_H

#include <vector>
#include <string>

#define ZSTD_STATIC_LINKING_ONLY
#include <zstd.h>

#define NO_COMPRESS                 0
#define ZSTD_COMPRESS_TYPE          1
#define ZSTD_COMPRESS_LEVEL         ZSTD_greedy
#define ZSTD_COMPRESS_WORKER_NUM    8
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

#endif
