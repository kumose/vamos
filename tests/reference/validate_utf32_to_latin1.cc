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
#include "validate_utf32.h"

namespace vamos {
namespace tests {
namespace reference {

vamos_warn_unused bool validate_utf32_to_latin1(const char32_t *buf,
                                                  size_t len) noexcept {
  const char32_t *curr = buf;
  const char32_t *end = buf + len;

  while (curr != end) {
    const uint32_t word = *curr;

    if (word > 0xFF) {
      return false;
    }

    curr++;
  }

  return true;
}

} // namespace reference
} // namespace tests
} // namespace vamos
