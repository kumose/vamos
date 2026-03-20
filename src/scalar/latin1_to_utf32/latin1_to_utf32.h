// Copyright 2020 The simdutf authors
// Copyright (C) 2026 Kumo inc. and its affiliates. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#ifndef VAMOS_LATIN1_TO_UTF32_H
#define VAMOS_LATIN1_TO_UTF32_H

namespace vamos {
namespace scalar {
namespace {
namespace latin1_to_utf32 {

inline size_t convert(const char *buf, size_t len, char32_t *utf32_output) {
  const unsigned char *data = reinterpret_cast<const unsigned char *>(buf);
  char32_t *start{utf32_output};
  for (size_t i = 0; i < len; i++) {
    *utf32_output++ = (char32_t)data[i];
  }
  return utf32_output - start;
}

} // namespace latin1_to_utf32
} // unnamed namespace
} // namespace scalar
} // namespace vamos

#endif
