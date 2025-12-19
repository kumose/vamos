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
#ifndef VAMOS_RVV_INTRINSICS_H
#define VAMOS_RVV_INTRINSICS_H

#include <vamos/vamos.h>

#include <riscv_vector.h>

#if __riscv_v_intrinsic >= 1000000 || __GCC__ >= 14
  #define vamos_vrgather_u8m1x2(tbl, idx)                                    \
    __riscv_vcreate_v_u8m1_u8m2(                                               \
        __riscv_vrgather_vv_u8m1(tbl, __riscv_vget_v_u8m2_u8m1(idx, 0),        \
                                 __riscv_vsetvlmax_e8m1()),                    \
        __riscv_vrgather_vv_u8m1(tbl, __riscv_vget_v_u8m2_u8m1(idx, 1),        \
                                 __riscv_vsetvlmax_e8m1()));

  #define vamos_vrgather_u8m1x4(tbl, idx)                                    \
    __riscv_vcreate_v_u8m1_u8m4(                                               \
        __riscv_vrgather_vv_u8m1(tbl, __riscv_vget_v_u8m4_u8m1(idx, 0),        \
                                 __riscv_vsetvlmax_e8m1()),                    \
        __riscv_vrgather_vv_u8m1(tbl, __riscv_vget_v_u8m4_u8m1(idx, 1),        \
                                 __riscv_vsetvlmax_e8m1()),                    \
        __riscv_vrgather_vv_u8m1(tbl, __riscv_vget_v_u8m4_u8m1(idx, 2),        \
                                 __riscv_vsetvlmax_e8m1()),                    \
        __riscv_vrgather_vv_u8m1(tbl, __riscv_vget_v_u8m4_u8m1(idx, 3),        \
                                 __riscv_vsetvlmax_e8m1()));
#else
  // This has worse codegen on gcc
  #define vamos_vrgather_u8m1x2(tbl, idx)                                    \
    __riscv_vset_v_u8m1_u8m2(                                                  \
        __riscv_vlmul_ext_v_u8m1_u8m2(__riscv_vrgather_vv_u8m1(                \
            tbl, __riscv_vget_v_u8m2_u8m1(idx, 0), __riscv_vsetvlmax_e8m1())), \
        1,                                                                     \
        __riscv_vrgather_vv_u8m1(tbl, __riscv_vget_v_u8m2_u8m1(idx, 1),        \
                                 __riscv_vsetvlmax_e8m1()))

  #define vamos_vrgather_u8m1x4(tbl, idx)                                    \
    __riscv_vset_v_u8m1_u8m4(                                                  \
        __riscv_vset_v_u8m1_u8m4(                                              \
            __riscv_vset_v_u8m1_u8m4(                                          \
                __riscv_vlmul_ext_v_u8m1_u8m4(__riscv_vrgather_vv_u8m1(        \
                    tbl, __riscv_vget_v_u8m4_u8m1(idx, 0),                     \
                    __riscv_vsetvlmax_e8m1())),                                \
                1,                                                             \
                __riscv_vrgather_vv_u8m1(tbl,                                  \
                                         __riscv_vget_v_u8m4_u8m1(idx, 1),     \
                                         __riscv_vsetvlmax_e8m1())),           \
            2,                                                                 \
            __riscv_vrgather_vv_u8m1(tbl, __riscv_vget_v_u8m4_u8m1(idx, 2),    \
                                     __riscv_vsetvlmax_e8m1())),               \
        3,                                                                     \
        __riscv_vrgather_vv_u8m1(tbl, __riscv_vget_v_u8m4_u8m1(idx, 3),        \
                                 __riscv_vsetvlmax_e8m1()))
#endif

/* Zvbb adds dedicated support for endianness swaps with vrev8, but if we can't
 * use that, we have to emulate it with the standard V extension.
 * Using LMUL=1 vrgathers could be faster than the srl+macc variant, but that
 * would increase register pressure, and vrgather implementations performance
 * varies a lot. */
enum class vamos_ByteFlip { NONE, V, ZVBB };

template <vamos_ByteFlip method>
vamos_really_inline static uint16_t vamos_byteflip(uint16_t v) {
  if (method != vamos_ByteFlip::NONE)
    return (uint16_t)((v * 1u) << 8 | (v * 1u) >> 8);
  return v;
}

#ifdef VAMOS_TARGET_ZVBB
VAMOS_UNTARGET_REGION
VAMOS_TARGET_ZVBB
#endif

template <vamos_ByteFlip method>
vamos_really_inline static vuint16m1_t vamos_byteflip(vuint16m1_t v,
                                                          size_t vl) {
#if VAMOS_HAS_ZVBB_INTRINSICS
  if (method == vamos_ByteFlip::ZVBB)
    return __riscv_vrev8_v_u16m1(v, vl);
#endif
  if (method == vamos_ByteFlip::V)
    return __riscv_vmacc_vx_u16m1(__riscv_vsrl_vx_u16m1(v, 8, vl), 0x100, v,
                                  vl);
  return v;
}

template <vamos_ByteFlip method>
vamos_really_inline static vuint16m2_t vamos_byteflip(vuint16m2_t v,
                                                          size_t vl) {
#if VAMOS_HAS_ZVBB_INTRINSICS
  if (method == vamos_ByteFlip::ZVBB)
    return __riscv_vrev8_v_u16m2(v, vl);
#endif
  if (method == vamos_ByteFlip::V)
    return __riscv_vmacc_vx_u16m2(__riscv_vsrl_vx_u16m2(v, 8, vl), 0x100, v,
                                  vl);
  return v;
}

template <vamos_ByteFlip method>
vamos_really_inline static vuint16m4_t vamos_byteflip(vuint16m4_t v,
                                                          size_t vl) {
#if VAMOS_HAS_ZVBB_INTRINSICS
  if (method == vamos_ByteFlip::ZVBB)
    return __riscv_vrev8_v_u16m4(v, vl);
#endif
  if (method == vamos_ByteFlip::V)
    return __riscv_vmacc_vx_u16m4(__riscv_vsrl_vx_u16m4(v, 8, vl), 0x100, v,
                                  vl);
  return v;
}

template <vamos_ByteFlip method>
vamos_really_inline static vuint16m8_t vamos_byteflip(vuint16m8_t v,
                                                          size_t vl) {
#if VAMOS_HAS_ZVBB_INTRINSICS
  if (method == vamos_ByteFlip::ZVBB)
    return __riscv_vrev8_v_u16m8(v, vl);
#endif
  if (method == vamos_ByteFlip::V)
    return __riscv_vmacc_vx_u16m8(__riscv_vsrl_vx_u16m8(v, 8, vl), 0x100, v,
                                  vl);
  return v;
}

#ifdef VAMOS_TARGET_ZVBB
VAMOS_UNTARGET_REGION
VAMOS_TARGET_RVV
#endif

#endif //  VAMOS_RVV_INTRINSICS_H
