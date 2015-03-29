// Copyright (c) 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

enum class ProcessType : int {
  kBrowser,
  kRenderer,
  kUtility,
};

enum class ExitCodes : int {
  kAllOk,
  kMissingDll,
  kMissingEntryPoint,
};


#if defined(IS_DLL_RUNNER)
typedef int(_stdcall *Dll_InitFn) (ProcessType ptype, void* params);
const char Dll_InitFnName[] = "?Dll_Init@@YAHW4ProcessType@@PEAX@Z";
#else
__declspec(dllexport)
int __stdcall Dll_Init(ProcessType ptype, void* params);
#endif
