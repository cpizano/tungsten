// Copyright (c) 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#if defined(BASE_IMPL)
#define BASE_EXPORT __declspec(dllexport)
#else
#define BASE_EXPORT __declspec(dllimport)
#endif

// base.dll is not designed to unload so there is no 'uninit' of base.
BASE_EXPORT int __stdcall Base_Init();
