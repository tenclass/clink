#include "common/global.h"
#include "render.h"
#include <cstdlib> 

#pragma warning( disable : 4996)

BOOL APIENTRY DllMain(
  HMODULE hModule,
  DWORD  ul_reason_for_call,
  LPVOID lpReserved)
{
  auto host = std::getenv("CLINK_HOST");
  auto port = std::getenv("CLINK_PORT");

  switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
      CL_LOG("DLL_PROCESS_ATTACH ul_reason_for_call=%d", ul_reason_for_call);
      Render::getInstance().Run(host, port);
      break;
    case DLL_THREAD_ATTACH:
      break;
    case DLL_THREAD_DETACH:
      break;
    case DLL_PROCESS_DETACH:
      Render::getInstance().Quit();
      CL_LOG("DLL_PROCESS_DETACH ul_reason_for_call=%d", ul_reason_for_call);
      break;
  }
  return TRUE;
}

