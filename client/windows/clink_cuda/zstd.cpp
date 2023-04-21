#include "../common/global.h"
#include <string>
#include <deque>
#include "utilities.h"

ZSTDUtil::ZSTDUtil(uint32_t thread_count, uint32_t compress_level, uint32_t window_size_power) {
  cctx_ = ZSTD_createCCtx();
  CL_ASSERT(cctx_ != nullptr);
  dctx_ = ZSTD_createDCtx();
  CL_ASSERT(dctx_ != nullptr);

  CL_ASSERT(ZSTD_isError(ZSTD_CCtx_setParameter(cctx_, ZSTD_c_nbWorkers, thread_count)) == 0);
  CL_ASSERT(ZSTD_isError(ZSTD_CCtx_setParameter(cctx_, ZSTD_c_compressionLevel, compress_level)) == 0);
  CL_ASSERT(ZSTD_isError(ZSTD_CCtx_setParameter(cctx_, ZSTD_c_windowLog, window_size_power)) == 0);
  CL_ASSERT(ZSTD_isError(ZSTD_DCtx_setMaxWindowSize(dctx_, 1LL << window_size_power)) == 0);
}

ZSTDUtil::~ZSTDUtil() {
  ZSTD_freeCCtx(cctx_);
  ZSTD_freeDCtx(dctx_);
}

std::string ZSTDUtil::Compress(std::string& data) {
  auto src_data_size = ZSTD_compressBound(data.size());
  std::string compressed_data(src_data_size, '\0');

  auto compress_size = ZSTD_compress2(cctx_, (void*)compressed_data.data(), compressed_data.size(), data.data(), data.size());
  if (compress_size < compressed_data.size()) {
    compressed_data.resize(compress_size);
  }
  return compressed_data;
}

std::string ZSTDUtil::Decompress(std::string& data) {
  size_t src_data_size = ZSTD_getFrameContentSize(data.data(), data.size());
  std::string decompressed_data(src_data_size, '\0');

  auto decompress_size = ZSTD_decompressDCtx(dctx_, (void*)decompressed_data.data(), decompressed_data.size(), data.data(), data.size());
  if (decompress_size < decompressed_data.size()) {
    decompressed_data.resize(decompress_size);
  }
  return decompressed_data;
}

std::string ZSTDUtil::Compress(std::vector<std::string>& datas) {
  size_t total_size = 0;
  for (const auto& data : datas) {
    total_size += data.size();
  }
  auto src_data_size = ZSTD_compressBound(total_size);
  std::string compressed_data(src_data_size, '\0');

  ZSTD_outBuffer out;
  out.dst = (void*)compressed_data.data();
  out.size = compressed_data.size();
  out.pos = 0;

  ZSTD_inBuffer in;
  for (const auto& data : datas) {
    in.src = data.data();
    in.size = data.size();
    in.pos = 0;
    CL_ASSERT(ZSTD_isError(ZSTD_compressStream2(cctx_, &out, &in, ZSTD_e_continue)) == 0);
  }

  CL_ASSERT(ZSTD_isError(ZSTD_compressStream2(cctx_, &out, &in, ZSTD_e_end)) == 0);
  compressed_data.resize(out.pos);

  return compressed_data;
}
