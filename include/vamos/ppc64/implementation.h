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
#ifndef VAMOS_PPC64_IMPLEMENTATION_H
#define VAMOS_PPC64_IMPLEMENTATION_H

#include <vamos/vamos.h>
#include <vamos/internal/isadetection.h>

namespace vamos {
namespace ppc64 {

namespace {
using namespace vamos;
} // namespace

class implementation final : public vamos::implementation {
public:
  vamos_really_inline implementation()
      : vamos::implementation("ppc64", "PPC64 ALTIVEC",
                                internal::instruction_set::ALTIVEC) {}
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

} // namespace ppc64
} // namespace vamos

#endif // VAMOS_PPC64_IMPLEMENTATION_H
