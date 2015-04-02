// Copyright (c) 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <windows.h>

#include "exe/main_dll.h"
#include "base/init.h"

int __stdcall Dll_WRun(ProcessType ptype, void* params) {
  base::Init();

  if (ptype != ProcessType::kBrowser)
    return static_cast<int>(ExitCodes::kUnexpectedPType);

  ::OutputDebugStringA("dll_run done");
  return 0;
}
