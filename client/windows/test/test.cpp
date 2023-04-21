#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <cstdlib>
#include <deque>
#include <assert.h>
#include <map>
#include <string>
#include "../clink_cuda/export.h"
#include <iostream>
#include <cstdio>
#include <cstring>

typedef CUresult(__stdcall* CUINIT)(unsigned int);
std::map<std::string, std::deque<size_t>> function_params_;

int main()
{
  std::ifstream dump_file;
  dump_file.open("C:\\Users\\cair\\Desktop\\output139015.bin");
  if (!dump_file.is_open()) {
    return -1;
  }

  FILE* pipe = _popen("cmd /c d:\\cuobjdump.exe --dump-elf C:\\Users\\cair\\AppData\\Local\\Temp\\eGoRXOELN2_cu.bin", "r");
  if (!pipe)
  {
    std::cerr << "popen() failed!" << std::endl;
    return 1;
  }

  char stream[1024];
  bool stop = true;
  std::string func_name;
  while (!feof(pipe))
  {
    if (fgets(stream, 1024, pipe) != nullptr) {
      std::string str = stream;
      if (str.compare(0, 9, ".nv.info.") == 0) {
        func_name = str.substr(9);
        assert(function_params_.find(func_name) == function_params_.end());

        std::deque<size_t> param_sizes;
        function_params_.insert(std::make_pair(func_name, std::move(param_sizes)));
        stop = false;
      } else if (str.compare(0, 27, "\tValue:\tIndex : 0x0\tOrdinal") == 0) {
        str.pop_back();
        auto size = std::stoi(str.substr(str.size() - 3), nullptr, 16);
        function_params_[func_name].push_front(size);
      }

      if (str == ".nv.callgraph\n" && !stop) {
        break;
      }
    }
  }

  _pclose(pipe);

  std::string line;
  while (std::getline(dump_file, line)) {
    if (line.compare(0, 9, ".nv.info.") == 0) {
      auto func_name = line.substr(9);
      std::deque<size_t> param_sizes;
      while (std::getline(dump_file, line)) {
        if (line == "") {
          break;
        }

        if (line == "\tAttribute:\tEIATTR_KPARAM_INFO") {
          std::getline(dump_file, line);
          assert(line == "\tFormat:\tEIFMT_SVAL");

          std::getline(dump_file, line);
          auto size = std::stoi(line.substr(line.size() - 3), nullptr, 16);
          param_sizes.push_front(size);
        }
      }
      function_params_[func_name] = std::move(param_sizes);
    }
  }


  // 使用 VirtualAlloc 分配内存并启用 MEM_WRITE_WATCH
  void* buffer = VirtualAlloc(NULL, 4096 * 2, MEM_COMMIT | MEM_RESERVE | MEM_WRITE_WATCH, PAGE_READWRITE);
  if (!buffer) {
    std::cerr << "VirtualAlloc failed with error: " << GetLastError() << std::endl;
    return EXIT_FAILURE;
  }

  // 写入分配的内存区域
  char* ptr = (char*)(buffer);
  ptr[0] = 'A';
  ptr[3] = 'A';
  ptr[4096 - 1] = 'B';
  ptr[4099] = 'B';

  // 获取写操作的地址
  ULONG_PTR addresses[2];
  ULONG_PTR count = _countof(addresses);
  DWORD granularity;

  if (GetWriteWatch(0, buffer, 4096 * 2, (PVOID*)addresses, &count, &granularity) != 0) {
    std::cerr << "GetWriteWatch failed with error: " << GetLastError() << std::endl;
    VirtualFree(buffer, 0, MEM_RELEASE);
    return EXIT_FAILURE;
  }

  if (count > 0) {
    std::cout << "Detected " << count << " write(s) at the following addresses:" << std::endl;
    for (ULONG_PTR i = 0; i < count; ++i) {
      std::cout << "  " << (void*)addresses[i] << std::endl;
    }
  }
  else {
    std::cout << "No write operations detected." << std::endl;
  }

  // 释放分配的内存
  VirtualFree(buffer, 0, MEM_RELEASE);

  HMODULE handle = LoadLibrary(L"nvcuda.dll");

  if (handle)
  {
    printf("handle=%p\n", handle);

    //CUINIT cuinit = (CUINIT)GetProcAddress(handle, "cuInit");
    //if (cuinit)
    //{
    //  cuinit(0);
    //}

    Sleep(5000);
    FreeLibrary(handle);
  }
  else
  {
    printf("load failed\n");
  }
}