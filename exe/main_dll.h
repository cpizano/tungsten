// Copyright (c) 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

enum class ProcessType : int {
  kBrowser,
  kRenderer,
  kUtility,
  kLast,
};

// Do not reorder.
enum class ExitCodes : int {
  kAllOk,
  kErrorKernel,
  kMissingMainDll,
  kMissingOtherDll,
  kMissingEntryPoint,
  kUnexpectedPType,
  kLast,
};

#if defined(IS_DLL_RUNNER)
typedef int (_stdcall *Dll_WRunFn) (ProcessType ptype, void* params);
const char Dll_WRunFnName[] = "?Dll_WRun@@YAHW4ProcessType@@PEAX@Z";
#else
__declspec(dllexport)
int __stdcall Dll_WRun(ProcessType ptype, void* params);
#endif
