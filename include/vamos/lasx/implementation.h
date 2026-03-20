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
#ifndef VAMOS_LASX_IMPLEMENTATION_H
#define VAMOS_LASX_IMPLEMENTATION_H

#include <vamos/vamos.h>
#include <vamos/internal/isadetection.h>

namespace vamos {
namespace lasx {

namespace {
using namespace vamos;
}

class implementation final : public vamos::implementation {
public:
  vamos_really_inline implementation()
      : vamos::implementation("lasx", "LOONGARCH ASX",
                                internal::instruction_set::LSX |
                                    internal::instruction_set::LASX) {}
  vamos_warn_unused int detect_encodings(const char *input,
                                           size_t length) const noexcept final;

  vamos_warn_unused bool validate_utf8(const char *buf,
                                         size_t len) const noexcept final;


  vamos_warn_unused result
  validate_utf8_with_errors(const char *buf, size_t len) const noexcept final;

  vamos_warn_unused bool validate_ascii(const char *buf,
                                          size_t len) const noexcept final;
  vamos_warn_unused result
  validate_ascii_with_errors(const char *buf, size_t len) const noexcept final;


  vamos_warn_unused bool validate_utf16le(const char16_t *buf,
                                            size_t len) const noexcept final;


  vamos_warn_unused bool validate_utf16be(const char16_t *buf,
                                            size_t len) const noexcept final;
  vamos_warn_unused result validate_utf16le_with_errors(
      const char16_t *buf, size_t len) const noexcept final;
  vamos_warn_unused result validate_utf16be_with_errors(
      const char16_t *buf, size_t len) const noexcept final;


  vamos_warn_unused bool validate_utf32(const char32_t *buf,
                                          size_t len) const noexcept final;


  vamos_warn_unused result validate_utf32_with_errors(
      const char32_t *buf, size_t len) const noexcept final;


  vamos_warn_unused size_t convert_latin1_to_utf8(
      const char *buf, size_t len, char *utf8_output) const noexcept final;


  vamos_warn_unused size_t convert_latin1_to_utf16le(
      const char *buf, size_t len, char16_t *utf16_buffer) const noexcept final;
  vamos_warn_unused size_t convert_latin1_to_utf16be(
      const char *buf, size_t len, char16_t *utf16_buffer) const noexcept final;


  vamos_warn_unused size_t convert_latin1_to_utf32(
      const char *buf, size_t len, char32_t *utf32_output) const noexcept final;


  vamos_warn_unused size_t convert_utf8_to_latin1(
      const char *buf, size_t len, char *latin1_output) const noexcept final;
  vamos_warn_unused result convert_utf8_to_latin1_with_errors(
      const char *buf, size_t len, char *latin1_buffer) const noexcept final;
  vamos_warn_unused size_t convert_valid_utf8_to_latin1(
      const char *buf, size_t len, char *latin1_output) const noexcept final;


  vamos_warn_unused size_t convert_utf8_to_utf16le(
      const char *buf, size_t len, char16_t *utf16_output) const noexcept final;
  vamos_warn_unused size_t convert_utf8_to_utf16be(
      const char *buf, size_t len, char16_t *utf16_output) const noexcept final;
  vamos_warn_unused result convert_utf8_to_utf16le_with_errors(
      const char *buf, size_t len, char16_t *utf16_output) const noexcept final;
  vamos_warn_unused result convert_utf8_to_utf16be_with_errors(
      const char *buf, size_t len, char16_t *utf16_output) const noexcept final;
  vamos_warn_unused size_t convert_valid_utf8_to_utf16le(
      const char *buf, size_t len, char16_t *utf16_buffer) const noexcept final;
  vamos_warn_unused size_t convert_valid_utf8_to_utf16be(
      const char *buf, size_t len, char16_t *utf16_buffer) const noexcept final;

  vamos_warn_unused size_t convert_utf8_to_utf32(
      const char *buf, size_t len, char32_t *utf32_output) const noexcept final;
  vamos_warn_unused result convert_utf8_to_utf32_with_errors(
      const char *buf, size_t len, char32_t *utf32_output) const noexcept final;
  vamos_warn_unused size_t convert_valid_utf8_to_utf32(
      const char *buf, size_t len, char32_t *utf32_buffer) const noexcept final;


  vamos_warn_unused size_t
  convert_utf16le_to_latin1(const char16_t *buf, size_t len,
                            char *latin1_buffer) const noexcept final;
  vamos_warn_unused size_t
  convert_utf16be_to_latin1(const char16_t *buf, size_t len,
                            char *latin1_buffer) const noexcept final;
  vamos_warn_unused result convert_utf16le_to_latin1_with_errors(
      const char16_t *buf, size_t len,
      char *latin1_buffer) const noexcept final;
  vamos_warn_unused result convert_utf16be_to_latin1_with_errors(
      const char16_t *buf, size_t len,
      char *latin1_buffer) const noexcept final;
  vamos_warn_unused size_t
  convert_valid_utf16le_to_latin1(const char16_t *buf, size_t len,
                                  char *latin1_buffer) const noexcept final;
  vamos_warn_unused size_t
  convert_valid_utf16be_to_latin1(const char16_t *buf, size_t len,
                                  char *latin1_buffer) const noexcept final;


  vamos_warn_unused size_t convert_utf16le_to_utf8(
      const char16_t *buf, size_t len, char *utf8_buffer) const noexcept final;
  vamos_warn_unused size_t convert_utf16be_to_utf8(
      const char16_t *buf, size_t len, char *utf8_buffer) const noexcept final;
  vamos_warn_unused result convert_utf16le_to_utf8_with_errors(
      const char16_t *buf, size_t len, char *utf8_buffer) const noexcept final;
  vamos_warn_unused result convert_utf16be_to_utf8_with_errors(
      const char16_t *buf, size_t len, char *utf8_buffer) const noexcept final;
  vamos_warn_unused size_t convert_valid_utf16le_to_utf8(
      const char16_t *buf, size_t len, char *utf8_buffer) const noexcept final;
  vamos_warn_unused size_t convert_valid_utf16be_to_utf8(
      const char16_t *buf, size_t len, char *utf8_buffer) const noexcept final;


  vamos_warn_unused size_t
  convert_utf32_to_latin1(const char32_t *buf, size_t len,
                          char *latin1_output) const noexcept final;
  vamos_warn_unused result
  convert_utf32_to_latin1_with_errors(const char32_t *buf, size_t len,
                                      char *latin1_output) const noexcept final;
  vamos_warn_unused size_t
  convert_valid_utf32_to_latin1(const char32_t *buf, size_t len,
                                char *latin1_output) const noexcept final;


  vamos_warn_unused size_t convert_utf32_to_utf8(
      const char32_t *buf, size_t len, char *utf8_buffer) const noexcept final;
  vamos_warn_unused result convert_utf32_to_utf8_with_errors(
      const char32_t *buf, size_t len, char *utf8_buffer) const noexcept final;
  vamos_warn_unused size_t convert_valid_utf32_to_utf8(
      const char32_t *buf, size_t len, char *utf8_buffer) const noexcept final;


  vamos_warn_unused size_t
  convert_utf32_to_utf16le(const char32_t *buf, size_t len,
                           char16_t *utf16_buffer) const noexcept final;
  vamos_warn_unused size_t
  convert_utf32_to_utf16be(const char32_t *buf, size_t len,
                           char16_t *utf16_buffer) const noexcept final;
  vamos_warn_unused result convert_utf32_to_utf16le_with_errors(
      const char32_t *buf, size_t len,
      char16_t *utf16_buffer) const noexcept final;
  vamos_warn_unused result convert_utf32_to_utf16be_with_errors(
      const char32_t *buf, size_t len,
      char16_t *utf16_buffer) const noexcept final;
  vamos_warn_unused size_t
  convert_valid_utf32_to_utf16le(const char32_t *buf, size_t len,
                                 char16_t *utf16_buffer) const noexcept final;
  vamos_warn_unused size_t
  convert_valid_utf32_to_utf16be(const char32_t *buf, size_t len,
                                 char16_t *utf16_buffer) const noexcept final;
  vamos_warn_unused size_t
  convert_utf16le_to_utf32(const char16_t *buf, size_t len,
                           char32_t *utf32_buffer) const noexcept final;
  vamos_warn_unused size_t
  convert_utf16be_to_utf32(const char16_t *buf, size_t len,
                           char32_t *utf32_buffer) const noexcept final;
  vamos_warn_unused result convert_utf16le_to_utf32_with_errors(
      const char16_t *buf, size_t len,
      char32_t *utf32_buffer) const noexcept final;
  vamos_warn_unused result convert_utf16be_to_utf32_with_errors(
      const char16_t *buf, size_t len,
      char32_t *utf32_buffer) const noexcept final;
  vamos_warn_unused size_t
  convert_valid_utf16le_to_utf32(const char16_t *buf, size_t len,
                                 char32_t *utf32_buffer) const noexcept final;
  vamos_warn_unused size_t
  convert_valid_utf16be_to_utf32(const char16_t *buf, size_t len,
                                 char32_t *utf32_buffer) const noexcept final;


  void change_endianness_utf16(const char16_t *buf, size_t length,
                               char16_t *output) const noexcept final;
  vamos_warn_unused size_t count_utf16le(const char16_t *buf,
                                           size_t length) const noexcept;
  vamos_warn_unused size_t count_utf16be(const char16_t *buf,
                                           size_t length) const noexcept;


  vamos_warn_unused size_t count_utf8(const char *buf,
                                        size_t length) const noexcept;

  vamos_warn_unused size_t
  utf8_length_from_utf16le(const char16_t *input, size_t length) const noexcept;
  vamos_warn_unused size_t
  utf8_length_from_utf16be(const char16_t *input, size_t length) const noexcept;


  vamos_warn_unused size_t utf32_length_from_utf16le(
      const char16_t *input, size_t length) const noexcept;
  vamos_warn_unused size_t utf32_length_from_utf16be(
      const char16_t *input, size_t length) const noexcept;

  vamos_warn_unused size_t
  utf16_length_from_utf8(const char *input, size_t length) const noexcept;

  vamos_warn_unused size_t
  utf8_length_from_utf32(const char32_t *input, size_t length) const noexcept;


  vamos_warn_unused size_t
  utf16_length_from_utf32(const char32_t *input, size_t length) const noexcept;


  vamos_warn_unused size_t
  utf32_length_from_utf8(const char *input, size_t length) const noexcept;


  vamos_warn_unused size_t
  latin1_length_from_utf8(const char *input, size_t length) const noexcept;


  vamos_warn_unused size_t
  utf8_length_from_latin1(const char *input, size_t length) const noexcept;


  vamos_warn_unused result base64_to_binary(
      const char *input, size_t length, char *output, base64_options options,
      last_chunk_handling_options last_chunk_options =
          last_chunk_handling_options::loose) const noexcept;
  vamos_warn_unused full_result base64_to_binary_details(
      const char *input, size_t length, char *output, base64_options options,
      last_chunk_handling_options last_chunk_options =
          last_chunk_handling_options::loose) const noexcept;
  vamos_warn_unused result
  base64_to_binary(const char16_t *input, size_t length, char *output,
                   base64_options options,
                   last_chunk_handling_options last_chunk_options =
                       last_chunk_handling_options::loose) const noexcept;
  vamos_warn_unused full_result base64_to_binary_details(
      const char16_t *input, size_t length, char *output,
      base64_options options,
      last_chunk_handling_options last_chunk_options =
          last_chunk_handling_options::loose) const noexcept;
  size_t binary_to_base64(const char *input, size_t length, char *output,
                          base64_options options) const noexcept;

};

} // namespace lasx
} // namespace vamos

#endif // VAMOS_LASX_IMPLEMENTATION_H
