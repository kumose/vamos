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
#ifndef VAMOS_COMPILER_CHECK_H
#define VAMOS_COMPILER_CHECK_H

#ifndef __cplusplus
  #error vamos requires a C++ compiler
#endif

#ifndef VAMOS_CPLUSPLUS
  #if defined(_MSVC_LANG) && !defined(__clang__)
    #define VAMOS_CPLUSPLUS (_MSC_VER == 1900 ? 201103L : _MSVC_LANG)
  #else
    #define VAMOS_CPLUSPLUS __cplusplus
  #endif
#endif

// C++ 23
#if !defined(VAMOS_CPLUSPLUS23) && (VAMOS_CPLUSPLUS >= 202302L)
  #define VAMOS_CPLUSPLUS23 1
#endif

// C++ 20
#if !defined(VAMOS_CPLUSPLUS20) && (VAMOS_CPLUSPLUS >= 202002L)
  #define VAMOS_CPLUSPLUS20 1
#endif

// C++ 17
#if !defined(VAMOS_CPLUSPLUS17) && (VAMOS_CPLUSPLUS >= 201703L)
  #define VAMOS_CPLUSPLUS17 1
#endif

// C++ 14
#if !defined(VAMOS_CPLUSPLUS14) && (VAMOS_CPLUSPLUS >= 201402L)
  #define VAMOS_CPLUSPLUS14 1
#endif

// C++ 11
#if !defined(VAMOS_CPLUSPLUS11) && (VAMOS_CPLUSPLUS >= 201103L)
  #define VAMOS_CPLUSPLUS11 1
#endif

#ifndef VAMOS_CPLUSPLUS11
  #error vamos requires a compiler compliant with the C++11 standard
#endif

#endif // VAMOS_COMPILER_CHECK_H
