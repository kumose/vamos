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
/*
 * Acknowledgement: This file originates from CPython.
 * https://github.com/python/cpython/blob/3.8/Include/pyctype.h
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
#pragma once

#include <cstddef>
#include <cstdint>

namespace vamos::unicode {

/* Argument must be a char or an int in [-128, 127] or [0, 255]. */
#define UCHAR_MASK(c) ((unsigned char)((c)&0xff))

#define UCHAR_CTF_LOWER 0x01
#define UCHAR_CTF_UPPER 0x02
#define UCHAR_CTF_ALPHA (UCHAR_CTF_LOWER | UCHAR_CTF_UPPER)
#define UCHAR_CTF_DIGIT 0x04
#define UCHAR_CTF_ALNUM (UCHAR_CTF_ALPHA | UCHAR_CTF_DIGIT)
#define UCHAR_CTF_SPACE 0x08
#define UCHAR_CTF_XDIGIT 0x10

extern  const unsigned int __uchar_type_table[256];

/* Unlike their C counterparts, the following macros are not meant to
 * handle an int with any of the values [EOF, 0-UCHAR_MAX]. The argument
 * must be a signed/unsigned char. */
#define UCHAR_ISLOWER(c) (__uchar_type_table[UCHAR_MASK(c)] & UCHAR_CTF_LOWER)
#define UCHAR_ISUPPER(c) (__uchar_type_table[UCHAR_MASK(c)] & UCHAR_CTF_UPPER)
#define UCHAR_ISALPHA(c) (__uchar_type_table[UCHAR_MASK(c)] & UCHAR_CTF_ALPHA)
#define UCHAR_ISDIGIT(c) (__uchar_type_table[UCHAR_MASK(c)] & UCHAR_CTF_DIGIT)
#define UCHAR_ISXDIGIT(c) (__uchar_type_table[UCHAR_MASK(c)] & UCHAR_CTF_XDIGIT)
#define UCHAR_ISALNUM(c) (__uchar_type_table[UCHAR_MASK(c)] & UCHAR_CTF_ALNUM)
#define UCHAR_ISSPACE(c) (__uchar_type_table[UCHAR_MASK(c)] & UCHAR_CTF_SPACE)

extern  const unsigned char __uchar_tolower_index[256];
extern  const unsigned char __uchar_toupper_index[256];

#define UCHAR_TOLOWER(c) (__uchar_tolower_index[UCHAR_MASK(c)])
#define UCHAR_TOUPPER(c) (__uchar_toupper_index[UCHAR_MASK(c)])

}  // namespace vamos::unicode
