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
#ifndef VAMOS_LATIN1_TO_UTF32_H
#define VAMOS_LATIN1_TO_UTF32_H

namespace vamos {
namespace scalar {
namespace {
namespace latin1_to_utf32 {

inline size_t convert(const char *buf, size_t len, char32_t *utf32_output) {
  const unsigned char *data = reinterpret_cast<const unsigned char *>(buf);
  char32_t *start{utf32_output};
  for (size_t i = 0; i < len; i++) {
    *utf32_output++ = (char32_t)data[i];
  }
  return utf32_output - start;
}

} // namespace latin1_to_utf32
} // unnamed namespace
} // namespace scalar
} // namespace vamos

#endif
