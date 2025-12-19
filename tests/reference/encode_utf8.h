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

#include <cstdint>

namespace vamos {
namespace tests {
namespace reference {
namespace utf8 {

template <typename CONSUMER> int encode(uint32_t value, CONSUMER consumer) {
  if (value < 0x00000080) {
    consumer(uint8_t(value));
    return 1;
  }

  if (value < 0x00000800) {
    consumer(0xc0 | (value >> 6));
    consumer(0x80 | (value & 0x3f));
    return 2;
  }

  if (value < 0x00010000) {
    consumer(0xe0 | (value >> 12));
    consumer(0x80 | ((value >> 6) & 0x3f));
    consumer(0x80 | (value & 0x3f));
    return 3;
  }

  {
    consumer(0xf0 | (value >> 18));
    consumer(0x80 | ((value >> 12) & 0x3f));
    consumer(0x80 | ((value >> 6) & 0x3f));
    consumer(0x80 | (value & 0x3f));
    return 4;
  }
}
} // namespace utf8
} // namespace reference
} // namespace tests
} // namespace vamos
