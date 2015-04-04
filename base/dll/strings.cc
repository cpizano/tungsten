// Copyright (c) 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#define BASE_IMPL 1
#include "base/dll/base_exports.h"

template<typename STR>
bool ReplaceCharsT(const STR& input,
                   const STR& replace_chars,
                   const STR& replace_with,
                   STR* output) {
  bool removed = false;
  size_t replace_length = replace_with.length();

  *output = input;

  size_t found = output->find_first_of(replace_chars);
  while (found != STR::npos) {
    removed = true;
    output->replace(found, 1, replace_with);
    found = output->find_first_of(replace_chars, found + replace_length);
  }

  return removed;
}

template<typename STR>
base::TrimPositions TrimStringT(
    const STR& input,
    const STR& trim_chars,
    base::TrimPositions positions,
    STR* output) {
  // Find the edges of leading/trailing whitespace as desired.
  const size_t last_char = input.length() - 1;
  const size_t first_good_char = (positions & base::TRIM_LEADING) ?
      input.find_first_not_of(trim_chars) : 0;
  const size_t last_good_char = (positions & base::TRIM_TRAILING) ?
      input.find_last_not_of(trim_chars) : last_char;

  // When the string was all whitespace, report that we stripped off whitespace
  // from whichever position the caller was interested in.  For empty input, we
  // stripped no whitespace, but we still need to clear |output|.
  if (input.empty() ||
      (first_good_char == STR::npos) || (last_good_char == STR::npos)) {
    bool input_was_empty = input.empty();  // in case output == &input
    output->clear();
    return input_was_empty ? base::TRIM_NONE : positions;
  }

  // Trim the whitespace.
  *output =
      input.substr(first_good_char, last_good_char - first_good_char + 1);

  // Return where we trimmed from.
  return static_cast<base::TrimPositions>(
      ((first_good_char == 0) ? base::TRIM_NONE : base::TRIM_LEADING) |
      ((last_good_char == last_char) ? base::TRIM_NONE : base::TRIM_TRAILING));
}

bool xReplaceChars(const base::string16& input,
                   const base::StringPiece16& replace_chars,
                   const base::string16& replace_with,
                   base::string16* output) {
  return ReplaceCharsT(input, replace_chars.as_string(), replace_with, output);
}

bool xReplaceChars(const std::string& input,
                   const base::StringPiece& replace_chars,
                   const std::string& replace_with,
                   std::string* output) {
  return ReplaceCharsT(input, replace_chars.as_string(), replace_with, output);
}

base::TrimPositions xTrimString(
    const base::string16& input,
    const base::StringPiece16& trim_chars,
    base::TrimPositions positions,
    base::string16* output) {
  return TrimStringT(input, trim_chars.as_string(), positions, output);
}

base::TrimPositions xTrimString(
    const std::string& input,
    const base::StringPiece& trim_chars,
    base::TrimPositions positions,
    std::string* output) {
  return TrimStringT(input, trim_chars.as_string(), positions, output);
}

