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
namespace utf16 {

// returns whether the value can be represented in the UTF-16
bool valid_value(uint32_t value);

// Encodes the value using either one or two code units (returns 1 or 2
// respectively) Returns 0 if the value cannot be encoded
int encode(uint32_t value, char16_t &W1, char16_t &W2);

} // namespace utf16
} // namespace reference
} // namespace tests
} // namespace vamos
