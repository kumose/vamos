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

const char32_t *lasx_validate_utf32le(const char32_t *input, size_t size) {
  const char32_t *end = input + size;

  // Performance degradation when memory address is not 32-byte aligned
  while (((uint64_t)input & 0x1F) && input < end) {
    uint32_t word = *input++;
    if (word > 0x10FFFF || (word >= 0xD800 && word <= 0xDFFF)) {
      return nullptr;
    }
  }

  __m256i offset = __lasx_xvreplgr2vr_w(uint32_t(0xffff2000));
  __m256i standardoffsetmax = __lasx_xvreplgr2vr_w(uint32_t(0xfffff7ff));
  __m256i standardmax = __lasx_xvldi(-2288); /*0x10ffff*/
  __m256i currentmax = __lasx_xvldi(0x0);
  __m256i currentoffsetmax = __lasx_xvldi(0x0);

  while (input + 8 < end) {
    __m256i in = __lasx_xvld(reinterpret_cast<const uint32_t *>(input), 0);
    currentmax = __lasx_xvmax_wu(in, currentmax);
    // 0xD8__ + 0x2000 = 0xF8__ => 0xF8__ > 0xF7FF
    currentoffsetmax =
        __lasx_xvmax_wu(__lasx_xvadd_w(in, offset), currentoffsetmax);
    input += 8;
  }
  __m256i is_zero =
      __lasx_xvxor_v(__lasx_xvmax_wu(currentmax, standardmax), standardmax);
  if (__lasx_xbnz_v(is_zero)) {
    return nullptr;
  }

  is_zero = __lasx_xvxor_v(__lasx_xvmax_wu(currentoffsetmax, standardoffsetmax),
                           standardoffsetmax);
  if (__lasx_xbnz_v(is_zero)) {
    return nullptr;
  }
  return input;
}

const result lasx_validate_utf32le_with_errors(const char32_t *input,
                                               size_t size) {
  const char32_t *start = input;
  const char32_t *end = input + size;

  // Performance degradation when memory address is not 32-byte aligned
  while (((uint64_t)input & 0x1F) && input < end) {
    uint32_t word = *input;
    if (word > 0x10FFFF) {
      return result(error_code::TOO_LARGE, input - start);
    }
    if (word >= 0xD800 && word <= 0xDFFF) {
      return result(error_code::SURROGATE, input - start);
    }
    input++;
  }

  __m256i offset = __lasx_xvreplgr2vr_w(uint32_t(0xffff2000));
  __m256i standardoffsetmax = __lasx_xvreplgr2vr_w(uint32_t(0xfffff7ff));
  __m256i standardmax = __lasx_xvldi(-2288); /*0x10ffff*/
  __m256i currentmax = __lasx_xvldi(0x0);
  __m256i currentoffsetmax = __lasx_xvldi(0x0);

  while (input + 8 < end) {
    __m256i in = __lasx_xvld(reinterpret_cast<const uint32_t *>(input), 0);
    currentmax = __lasx_xvmax_wu(in, currentmax);
    currentoffsetmax =
        __lasx_xvmax_wu(__lasx_xvadd_w(in, offset), currentoffsetmax);

    __m256i is_zero =
        __lasx_xvxor_v(__lasx_xvmax_wu(currentmax, standardmax), standardmax);
    if (__lasx_xbnz_v(is_zero)) {
      return result(error_code::TOO_LARGE, input - start);
    }
    is_zero =
        __lasx_xvxor_v(__lasx_xvmax_wu(currentoffsetmax, standardoffsetmax),
                       standardoffsetmax);
    if (__lasx_xbnz_v(is_zero)) {
      return result(error_code::SURROGATE, input - start);
    }
    input += 8;
  }

  return result(error_code::SUCCESS, input - start);
}
