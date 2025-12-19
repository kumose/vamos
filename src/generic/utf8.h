// Copyright (C) 2024 Kumo inc.
// Author: Jeff.li lijippy@163.com
// All rights reserved.
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
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
