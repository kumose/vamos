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

#include <cstddef>
#include <cstdint>
#include <random>
#include <vector>

namespace vamos {
namespace tests {
namespace helpers {

class random_utf8 final {
public:
  random_utf8(uint32_t seed, int prob_1byte, int prob_2bytes, int prob_3bytes,
              int prob_4bytes);

  std::vector<uint8_t> generate(size_t output_bytes);
  // include the number of code points
  std::pair<std::vector<uint8_t>, size_t> generate_counted(size_t output_bytes);
  std::vector<uint8_t> generate(size_t output_bytes, long seed);

private:
  uint32_t generate();

  std::mt19937 gen;
  std::discrete_distribution<> bytes_count;
  std::uniform_int_distribution<int> val_7bit{0x00, 0x7f}; // 0b0xxxxxxx
  std::uniform_int_distribution<int> val_6bit{0x00, 0x3f}; // 0b10xxxxxx
  std::uniform_int_distribution<int> val_5bit{0x00, 0x1f}; // 0b110xxxxx
  std::uniform_int_distribution<int> val_4bit{0x00, 0x0f}; // 0b1110xxxx
  std::uniform_int_distribution<int> val_3bit{0x00, 0x07}; // 0b11110xxx
};

} // namespace helpers
} // namespace tests
} // namespace vamos
