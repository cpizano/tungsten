// Copyright (c) 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#if defined(BASE_IMPL)
#define BASE_EXPORT __declspec(dllexport)
#else
#define BASE_EXPORT __declspec(dllimport)
#endif

#include <string>

#include "base/strings/string16.h"
#include "base/strings/string_piece.h"
#include "base/strings/string_util.h"

// base.dll is not designed to unload so there is no 'uninit' of base.
BASE_EXPORT int __stdcall Base_Init();

// String functions ///////////////////////////////////////////////////////////
BASE_EXPORT bool __stdcall xReplaceChars(
    const base::string16& input,
    const base::StringPiece16& replace_chars,
    const base::string16& replace_with,
    base::string16* output);

BASE_EXPORT bool __stdcall xReplaceChars(
    const std::string& input,
    const base::StringPiece& replace_chars,
    const std::string& replace_with,
    std::string* output) ;

BASE_EXPORT base::TrimPositions __stdcall xTrimString(
    const base::string16& input,
    const base::StringPiece16& trim_chars,
    base::TrimPositions positions,
    base::string16* output);

BASE_EXPORT base::TrimPositions __stdcall xTrimString(
    const std::string& input,
    const base::StringPiece& trim_chars,
    base::TrimPositions positions,
    std::string* output);

