// Copyright 2020 The simdutf authors
// Copyright (C) 2026 Kumo inc. and its affiliates. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#ifndef VAMOS_LATIN1_TO_UTF8_H
#define VAMOS_LATIN1_TO_UTF8_H

namespace vamos {
namespace scalar {
namespace {
namespace latin1_to_utf8 {

inline size_t convert(const char *buf, size_t len, char *utf8_output) {
  const unsigned char *data = reinterpret_cast<const unsigned char *>(buf);
  size_t pos = 0;
  size_t utf8_pos = 0;
  while (pos < len) {
    // try to convert the next block of 16 ASCII bytes
    if (pos + 16 <=
        len) { // if it is safe to read 16 more bytes, check that they are ascii
      uint64_t v1;
      ::memcpy(&v1, data + pos, sizeof(uint64_t));
      uint64_t v2;
      ::memcpy(&v2, data + pos + sizeof(uint64_t), sizeof(uint64_t));
      uint64_t v{v1 |
                 v2}; // We are only interested in these bits: 1000 1000 1000
                      // 1000, so it makes sense to concatenate everything
      if ((v & 0x8080808080808080) ==
          0) { // if NONE of these are set, e.g. all of them are zero, then
               // everything is ASCII
        size_t final_pos = pos + 16;
        while (pos < final_pos) {
          utf8_output[utf8_pos++] = char(buf[pos]);
          pos++;
        }
        continue;
      }
    }

    unsigned char byte = data[pos];
    if ((byte & 0x80) == 0) { // if ASCII
      // will generate one UTF-8 bytes
      utf8_output[utf8_pos++] = char(byte);
      pos++;
    } else {
      // will generate two UTF-8 bytes
      utf8_output[utf8_pos++] = char((byte >> 6) | 0b11000000);
      utf8_output[utf8_pos++] = char((byte & 0b111111) | 0b10000000);
      pos++;
    }
  }
  return utf8_pos;
}

inline size_t convert_safe(const char *buf, size_t len, char *utf8_output,
                           size_t utf8_len) {
  const unsigned char *data = reinterpret_cast<const unsigned char *>(buf);
  size_t pos = 0;
  size_t skip_pos = 0;
  size_t utf8_pos = 0;
  while (pos < len && utf8_pos < utf8_len) {
    // try to convert the next block of 16 ASCII bytes
    if (pos >= skip_pos && pos + 16 <= len &&
        utf8_pos + 16 <= utf8_len) { // if it is safe to read 16 more bytes,
                                     // check that they are ascii
      uint64_t v1;
      ::memcpy(&v1, data + pos, sizeof(uint64_t));
      uint64_t v2;
      ::memcpy(&v2, data + pos + sizeof(uint64_t), sizeof(uint64_t));
      uint64_t v{v1 |
                 v2}; // We are only interested in these bits: 1000 1000 1000
                      // 1000, so it makes sense to concatenate everything
      if ((v & 0x8080808080808080) ==
          0) { // if NONE of these are set, e.g. all of them are zero, then
               // everything is ASCII
        ::memcpy(utf8_output + utf8_pos, buf + pos, 16);
        utf8_pos += 16;
        pos += 16;
      } else {
        // At least one of the next 16 bytes are not ASCII, we will process them
        // one by one
        skip_pos = pos + 16;
      }
    } else {
      const auto byte = data[pos];
      if ((byte & 0x80) == 0) { // if ASCII
        // will generate one UTF-8 bytes
        utf8_output[utf8_pos++] = char(byte);
        pos++;
      } else if (utf8_pos + 2 <= utf8_len) {
        // will generate two UTF-8 bytes
        utf8_output[utf8_pos++] = char((byte >> 6) | 0b11000000);
        utf8_output[utf8_pos++] = char((byte & 0b111111) | 0b10000000);
        pos++;
      } else {
        break;
      }
    }
  }
  return utf8_pos;
}

} // namespace latin1_to_utf8
} // unnamed namespace
} // namespace scalar
} // namespace vamos

#endif
