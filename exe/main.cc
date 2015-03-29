// Copyright (c) 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <windows.h>

#include <string>

#define IS_DLL_RUNNER 1
#include "exe/main_dll.h"
#undef IS_DLL_RUNNER


int APIENTRY wWinMain(HINSTANCE instance, HINSTANCE prev, wchar_t* cmdline, int) {
  if (std::wstring(cmdline).empty()) {
    // wbrowser.dll is not meant to be unloaded.
    auto module = ::LoadLibrary(L"wbrowser.dll");
    if (!module)
      return static_cast<int>(ExitCodes::kMissingMainDll);
    auto WRunFn = reinterpret_cast<Dll_WRunFn>(
        ::GetProcAddress(module, Dll_WRunFnName));
    if (!WRunFn)
      return static_cast<int>(ExitCodes::kMissingEntryPoint);
    // Call into the browser DLL.
    return WRunFn(ProcessType::kBrowser, nullptr);
  }

  return static_cast<int>(ExitCodes::kAllOk);
}
