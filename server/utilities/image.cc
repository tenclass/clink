#include "logger.h"
#include "utilities.h"
#include <filesystem>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

ImageUtil::ImageUtil() {
  auto openexr = getenv("OPENCV_IO_ENABLE_OPENEXR");
  if (!openexr || strcmp("true", openexr) != 0) {
    setenv("OPENCV_IO_ENABLE_OPENEXR", "true", 1);
  }
}

ImageUtil::~ImageUtil() {
}

void ImageUtil::Save(int width, int height, int type, void* data, std::string path) {
  try {
    cv::Mat image(height, width, type, data);
    cv::imwrite(path, image);
  } catch (const std::exception& e) {
    CL_ERROR("exception: %s", e.what());
  }
}

bool ImageUtil::SaveImage(int width, int height, int type, void* data, std::string path) {
  auto file_path = std::filesystem::path(path);
  if (file_path.extension() != ".exr" && file_path.extension() != ".png") {
    CL_PANIC("unsupport image type=%s", file_path.extension().string().c_str());
    return false;
  }

  if (std::filesystem::exists(file_path.parent_path())) {
    if (std::filesystem::exists(file_path)) {
      std::filesystem::remove(file_path);
    }
  } else {
    std::filesystem::create_directories(file_path.parent_path());
  }

  Save(width, height, type, data, path);
  return true;
}

std::string ImageUtil::SaveImage(int width, int height, int type, void* data, std::string directory_path, std::string extension) {
  if (extension != ".exr" && extension != ".png") {
    CL_PANIC("unsupport image type=%s", extension.c_str());
    return "err";
  }

  if (!std::filesystem::exists(directory_path)) {
    std::filesystem::create_directories(directory_path);
  }

  auto now = std::chrono::system_clock::now();
  auto milliseconds_since_epoch = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
  
  std::string path = directory_path + "/" + std::to_string(milliseconds_since_epoch) + extension;
  Save(width, height, type, data, path);
  return path;
}
