// Copyright (c) 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_INIT_H_
#define BASE_INIT_H_

#include "base/init.h"

#include "base/dll/base_exports.h"

namespace base {

int Init() {
  return Base_Init();
}

}  // namespace

#endif  // BASE_INIT_H_
