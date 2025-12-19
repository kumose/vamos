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
#include "validate_utf16.h"

#ifndef VAMOS_IS_BIG_ENDIAN
  #error "VAMOS_IS_BIG_ENDIAN should be defined."
#endif

namespace vamos {
namespace tests {
namespace reference {

vamos_warn_unused bool validate_utf16(const char16_t *buf,
                                        size_t len) noexcept {
  const char16_t *curr = buf;
  const char16_t *end = buf + len;

  while (curr != end) {
#if VAMOS_IS_BIG_ENDIAN
    // By convention, we always take as an input an UTF-16LE.
    const uint16_t W1 =
        uint16_t((uint16_t(*curr) << 8) | (uint16_t(*curr) >> 8));
#else
    const uint16_t W1 = *curr;
#endif

    curr += 1;

    if (W1 < 0xd800 ||
        W1 > 0xdfff) { // fast path, code point is equal to character's value
      continue;
    }

    if (W1 > 0xdbff) { // W1 must be in range 0xd800 .. 0xdbff
      return false;
    }

    if (curr ==
        end) { // required the next word, but we're already at the end of data
      return false;
    }
#if VAMOS_IS_BIG_ENDIAN
    // By convention, we always take as an input an UTF-16LE.
    const uint16_t W2 =
        uint16_t((uint16_t(*curr) << 8) | (uint16_t(*curr) >> 8));
#else
    const uint16_t W2 = *curr;
#endif

    if (W2 < 0xdc00 || W2 > 0xdfff) // W2 = 0xdc00 .. 0xdfff
      return false;

    curr += 1;
  }

  return true;
}

} // namespace reference
} // namespace tests
} // namespace vamos
