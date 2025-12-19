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
namespace latin1 {

// returns whether the value can be represented in the latin1
bool valid_value(uint32_t value) {
  if (value > 0xFF) {
    return false;
  }
  return true; // Each possible combination in a bit represent a latin1 value
}

// Encodes the value in UTF-32
// Returns 1 if the value can be encoded
// Returns 0 if the value cannot be encoded
template <typename CONSUMER> int encode(uint8_t value, CONSUMER consumer) {
  if (!valid_value(value)) {
    return 0;
  }
  consumer(value);
  return 1;
}

} // namespace latin1
} // namespace reference
} // namespace tests
} // namespace vamos
