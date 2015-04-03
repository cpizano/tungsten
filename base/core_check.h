// Copyright (c) 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_CORE_CHECK_H_
#define BASE_CORE_CHECK_H_

#include "build/build_config.h"

#define CORE_CONDBREAK(c) (c)? (void) 0 : __debugbreak()

#if defined(OS_WIN)
// Windows
#if defined(NDEBUG)
// Release.
#define CORE_DCHECK(condition)
#else
// Debug
#define CORE_DCHECK(condition) CORE_CONDBREAK(condition)
#endif
// Both release and debug.
#define CORE_CHECK(condition) CORE_CONDBREAK(condition)
#else
// Mac & Linux.

#endif  

#endif  // BASE_CORE_CHECK_H_
