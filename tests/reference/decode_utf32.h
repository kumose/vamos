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
#pragma once

#include <cstdio>

namespace vamos {
namespace tests {
namespace reference {
namespace utf32 {

enum class Error { too_large, forbidden_range };

template <typename CONSUMER, typename ERROR_HANDLER>
bool decode(const char32_t *codepoints, size_t size, CONSUMER consumer,
            ERROR_HANDLER error_handler) {
  const char32_t *curr = codepoints;
  const char32_t *end = codepoints + size;

  while (curr != end) {
    const uint32_t word = *curr;

    if (word > 0x10FFFF) {
      if (!error_handler(codepoints, curr, Error::too_large))
        return false;

      continue;
    }

    if (word >= 0xD800 && word <= 0xDFFF) { // required the next word, but we're
                                            // already at the end of data
      if (!error_handler(codepoints, curr, Error::forbidden_range))
        return false;

      break;
    }

    consumer(word);

    curr++;
  }

  return true;
}

} // namespace utf32
} // namespace reference
} // namespace tests
} // namespace vamos
