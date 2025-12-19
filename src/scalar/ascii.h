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
#ifndef VAMOS_ASCII_H
#define VAMOS_ASCII_H

namespace vamos {
namespace scalar {
namespace {
namespace ascii {
#if VAMOS_IMPLEMENTATION_FALLBACK
// Only used by the fallback kernel.
inline vamos_warn_unused bool validate(const char *buf, size_t len) noexcept {
  const uint8_t *data = reinterpret_cast<const uint8_t *>(buf);
  uint64_t pos = 0;
  // process in blocks of 16 bytes when possible
  for (; pos + 16 <= len; pos += 16) {
    uint64_t v1;
    std::memcpy(&v1, data + pos, sizeof(uint64_t));
    uint64_t v2;
    std::memcpy(&v2, data + pos + sizeof(uint64_t), sizeof(uint64_t));
    uint64_t v{v1 | v2};
    if ((v & 0x8080808080808080) != 0) {
      return false;
    }
  }
  // process the tail byte-by-byte
  for (; pos < len; pos++) {
    if (data[pos] >= 0b10000000) {
      return false;
    }
  }
  return true;
}
#endif

inline vamos_warn_unused result validate_with_errors(const char *buf,
                                                       size_t len) noexcept {
  const uint8_t *data = reinterpret_cast<const uint8_t *>(buf);
  size_t pos = 0;
  // process in blocks of 16 bytes when possible
  for (; pos + 16 <= len; pos += 16) {
    uint64_t v1;
    std::memcpy(&v1, data + pos, sizeof(uint64_t));
    uint64_t v2;
    std::memcpy(&v2, data + pos + sizeof(uint64_t), sizeof(uint64_t));
    uint64_t v{v1 | v2};
    if ((v & 0x8080808080808080) != 0) {
      for (; pos < len; pos++) {
        if (data[pos] >= 0b10000000) {
          return result(error_code::TOO_LARGE, pos);
        }
      }
    }
  }
  // process the tail byte-by-byte
  for (; pos < len; pos++) {
    if (data[pos] >= 0b10000000) {
      return result(error_code::TOO_LARGE, pos);
    }
  }
  return result(error_code::SUCCESS, pos);
}

} // namespace ascii
} // unnamed namespace
} // namespace scalar
} // namespace vamos

#endif
