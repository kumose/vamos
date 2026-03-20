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
// file included directly

// File contains conversion procedure from possibly invalid UTF-8 strings.

/**
 * Attempts to convert up to len 1-byte code units from in (in UTF-8 format) to
 * out.
 * Returns the position of the input and output after the processing is
 * completed. Upon error, the output is set to null.
 */

template <endianness big_endian>
utf8_to_utf16_result
fast_avx512_convert_utf8_to_utf16(const char *in, size_t len, char16_t *out) {
  const char *const final_in = in + len;
  bool result = true;
  while (result) {
    if (final_in - in >= 64) {
      result = process_block_utf8_to_utf16<VAMOS_FULL, big_endian>(
          in, out, final_in - in);
    } else if (in < final_in) {
      result = process_block_utf8_to_utf16<VAMOS_TAIL, big_endian>(
          in, out, final_in - in);
    } else {
      break;
    }
  }
  if (!result) {
    out = nullptr;
  }
  return std::make_pair(in, out);
}

template <endianness big_endian>
vamos::result fast_avx512_convert_utf8_to_utf16_with_errors(const char *in,
                                                              size_t len,
                                                              char16_t *out) {
  const char *const init_in = in;
  const char16_t *const init_out = out;
  const char *const final_in = in + len;
  bool result = true;
  while (result) {
    if (final_in - in >= 64) {
      result = process_block_utf8_to_utf16<VAMOS_FULL, big_endian>(
          in, out, final_in - in);
    } else if (in < final_in) {
      result = process_block_utf8_to_utf16<VAMOS_TAIL, big_endian>(
          in, out, final_in - in);
    } else {
      break;
    }
  }
  if (!result) {
    size_t pos = size_t(in - init_in);
    if (pos < len && (init_in[pos] & 0xc0) == 0x80 && pos >= 64) {
      // We must check whether we are the fourth continuation byte
      bool c1 = (init_in[pos - 1] & 0xc0) == 0x80;
      bool c2 = (init_in[pos - 2] & 0xc0) == 0x80;
      bool c3 = (init_in[pos - 3] & 0xc0) == 0x80;
      if (c1 && c2 && c3) {
        return {vamos::TOO_LONG, pos};
      }
    }
    // rewind_and_convert_with_errors will seek a potential error from in
    // onward, with the ability to go back up to in - init_in bytes, and read
    // final_in - in bytes forward.
    vamos::result res =
        scalar::utf8_to_utf16::rewind_and_convert_with_errors<big_endian>(
            in - init_in, in, final_in - in, out);
    res.count += (in - init_in);
    return res;
  } else {
    return vamos::result(error_code::SUCCESS, out - init_out);
  }
}
