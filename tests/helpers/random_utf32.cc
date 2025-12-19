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
#include "random_utf32.h"

#include <stdexcept>
#include <vector>

namespace vamos {
namespace tests {
namespace helpers {

std::vector<char32_t> random_utf32::generate(size_t size) {

  std::vector<char32_t> result;
  result.reserve(size);

  size_t count{0};
  for (; count < size; count++) {
    const uint32_t value = generate();
    result.push_back(value);
  }

  return result;
}

std::vector<char32_t> random_utf32::generate(size_t size, long seed) {
  gen.seed(seed);
  return generate(size);
}

uint32_t random_utf32::generate() {
  switch (range(gen)) {
  case 0:
    return first_range(gen);
  case 1:
    return second_range(gen);
  default:
    abort();
  }
}

} // namespace helpers
} // namespace tests
} // namespace vamos
