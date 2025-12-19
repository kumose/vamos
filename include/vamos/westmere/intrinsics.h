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
#ifndef VAMOS_WESTMERE_INTRINSICS_H
#define VAMOS_WESTMERE_INTRINSICS_H

#ifdef VAMOS_VISUAL_STUDIO
  // under clang within visual studio, this will include <x86intrin.h>
  #include <intrin.h> // visual studio or clang
#else

  #if VAMOS_GCC11ORMORE
// We should not get warnings while including <x86intrin.h> yet we do
// under some versions of GCC.
// If the x86intrin.h header has uninitialized values that are problematic,
// it is a GCC issue, we want to ignore these warnings.
VAMOS_DISABLE_GCC_WARNING(-Wuninitialized)
  #endif

  #include <x86intrin.h> // elsewhere

  #if VAMOS_GCC11ORMORE
// cancels the suppression of the -Wuninitialized
VAMOS_POP_DISABLE_WARNINGS
  #endif

#endif // VAMOS_VISUAL_STUDIO

#ifdef VAMOS_CLANG_VISUAL_STUDIO
  /**
   * You are not supposed, normally, to include these
   * headers directly. Instead you should either include intrin.h
   * or x86intrin.h. However, when compiling with clang
   * under Windows (i.e., when _MSC_VER is set), these headers
   * only get included *if* the corresponding features are detected
   * from macros:
   */
  #include <smmintrin.h> // for _mm_alignr_epi8
#endif

#endif // VAMOS_WESTMERE_INTRINSICS_H
