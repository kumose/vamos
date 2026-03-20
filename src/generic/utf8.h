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
namespace vamos {
namespace VAMOS_IMPLEMENTATION {
namespace {
namespace utf8 {

using namespace simd;

vamos_really_inline size_t count_code_points(const char *in, size_t size) {
  size_t pos = 0;
  size_t count = 0;
  for (; pos + 64 <= size; pos += 64) {
    simd8x64<int8_t> input(reinterpret_cast<const int8_t *>(in + pos));
    uint64_t utf8_continuation_mask = input.gt(-65);
    count += count_ones(utf8_continuation_mask);
  }
  return count + scalar::utf8::count_code_points(in + pos, size - pos);
}

vamos_really_inline size_t utf16_length_from_utf8(const char *in,
                                                    size_t size) {
  size_t pos = 0;
  size_t count = 0;
  // This algorithm could no doubt be improved!
  for (; pos + 64 <= size; pos += 64) {
    simd8x64<int8_t> input(reinterpret_cast<const int8_t *>(in + pos));
    uint64_t utf8_continuation_mask = input.lt(-65 + 1);
    // We count one word for anything that is not a continuation (so
    // leading bytes).
    count += 64 - count_ones(utf8_continuation_mask);
    int64_t utf8_4byte = input.gteq_unsigned(240);
    count += count_ones(utf8_4byte);
  }
  return count + scalar::utf8::utf16_length_from_utf8(in + pos, size - pos);
}
} // namespace utf8
} // unnamed namespace
} // namespace VAMOS_IMPLEMENTATION
} // namespace vamos
