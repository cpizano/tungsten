// Copyright (c) 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <windows.h>

#include <string>

#define IS_DLL_RUNNER 1
#include "exe/main_dll.h"
#undef IS_DLL_RUNNER

std::wstring GetRootPath(const std::wstring& full_path) {
  auto pos = full_path.find_last_of(L'\\');
  return full_path.substr(0, pos);
}

std::wstring GetVolumePath(const wchar_t* file_name) {
  wchar_t vol_root[MAX_PATH];
  if (!::GetVolumePathName(file_name, vol_root, _countof(vol_root)))
    return std::wstring();
  return std::wstring(vol_root);
}

bool IsVersionName(const wchar_t* name) {
  // TODO(cpu): Improve this. Maybe check for "app/".
  return (wcsstr(name, L".0.") != nullptr);
}

std::wstring GetVersionedPath(const wchar_t* file_name) {
  if (IsVersionName(file_name))
    return GetRootPath(file_name);
  auto vol_root = GetVolumePath(file_name);
  wchar_t link[MAX_PATH];
  DWORD link_sz = _countof(link);
  HANDLE fffn = ::FindFirstFileNameW(file_name, 0, &link_sz, link);
  if (fffn == INVALID_HANDLE_VALUE)
    return std::wstring();
  std::wstring ver_path;
  if (IsVersionName(link)) {
    ver_path = GetRootPath(vol_root.append(link));
  } else {
    while (true) {
      link_sz = _countof(link);
      if (!::FindNextFileNameW(fffn, &link_sz, link))
        break;
      if (IsVersionName(link)) {
        ver_path = GetRootPath(vol_root.append(link));
        break;
      }
    }
  }
  ::FindClose(fffn);
  return ver_path;
}

int APIENTRY wWinMain(HINSTANCE instance, HINSTANCE, wchar_t* cmdline, int) {
  if (!std::wstring(cmdline).empty())
    return static_cast<int>(ExitCodes::kUnexpectedPType);

  auto path = GetVersionedPath(_wpgmptr);
  if (!path.empty()) {
    ::SetDllDirectory(path.c_str());
    ::OutputDebugString(path.c_str());
  } else {
    ::OutputDebugStringA("no versioned path found");
  }
  // wbrowser.dll is not meant to be unloaded.
  auto module = ::LoadLibrary(L"wbrowser");
  if (!module) {
    ::OutputDebugString(L"no wbrowser found");
    return static_cast<int>(ExitCodes::kMissingMainDll);
  }
  auto WRunFn = reinterpret_cast<Dll_WRunFn>(
      ::GetProcAddress(module, Dll_WRunFnName));
  if (!WRunFn)
    return static_cast<int>(ExitCodes::kMissingEntryPoint);
  // Call into the browser DLL.
  return WRunFn(ProcessType::kBrowser, nullptr);
}
