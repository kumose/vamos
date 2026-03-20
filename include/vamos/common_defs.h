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
#ifndef VAMOS_COMMON_DEFS_H
#define VAMOS_COMMON_DEFS_H

#include <vamos/portability.h>
#include <vamos/avx512.h>

#if defined(VAMOS_REGULAR_VISUAL_STUDIO)
  #define VAMOS_DEPRECATED __declspec(deprecated)

  #define vamos_really_inline __forceinline // really inline in release mode
  #define vamos_always_inline __forceinline // always inline, no matter what
  #define vamos_never_inline __declspec(noinline)

  #define vamos_unused
  #define vamos_warn_unused

  #ifndef vamos_likely
    #define vamos_likely(x) x
  #endif
  #ifndef vamos_unlikely
    #define vamos_unlikely(x) x
  #endif

  #define VAMOS_PUSH_DISABLE_WARNINGS __pragma(warning(push))
  #define VAMOS_PUSH_DISABLE_ALL_WARNINGS __pragma(warning(push, 0))
  #define VAMOS_DISABLE_VS_WARNING(WARNING_NUMBER)                           \
    __pragma(warning(disable : WARNING_NUMBER))
  // Get rid of Intellisense-only warnings (Code Analysis)
  // Though __has_include is C++17, it is supported in Visual Studio 2017 or
  // better (_MSC_VER>=1910).
  #ifdef __has_include
    #if __has_include(<CppCoreCheck\Warnings.h>)
      #include <CppCoreCheck\Warnings.h>
      #define VAMOS_DISABLE_UNDESIRED_WARNINGS                               \
        VAMOS_DISABLE_VS_WARNING(ALL_CPPCORECHECK_WARNINGS)
    #endif
  #endif

  #ifndef VAMOS_DISABLE_UNDESIRED_WARNINGS
    #define VAMOS_DISABLE_UNDESIRED_WARNINGS
  #endif

  #define VAMOS_DISABLE_DEPRECATED_WARNING VAMOS_DISABLE_VS_WARNING(4996)
  #define VAMOS_DISABLE_STRICT_OVERFLOW_WARNING
  #define VAMOS_POP_DISABLE_WARNINGS __pragma(warning(pop))

#else // VAMOS_REGULAR_VISUAL_STUDIO
  #if defined(__OPTIMIZE__) || defined(NDEBUG)
    #define vamos_really_inline inline __attribute__((always_inline))
  #else
    #define vamos_really_inline inline
  #endif
  #define vamos_always_inline                                                \
    inline __attribute__((always_inline)) // always inline, no matter what
  #define VAMOS_DEPRECATED __attribute__((deprecated))
  #define vamos_never_inline inline __attribute__((noinline))

  #define vamos_unused __attribute__((unused))
  #define vamos_warn_unused __attribute__((warn_unused_result))

  #ifndef vamos_likely
    #define vamos_likely(x) __builtin_expect(!!(x), 1)
  #endif
  #ifndef vamos_unlikely
    #define vamos_unlikely(x) __builtin_expect(!!(x), 0)
  #endif

  // clang-format off
  #define VAMOS_PUSH_DISABLE_WARNINGS _Pragma("GCC diagnostic push")
  // gcc doesn't seem to disable all warnings with all and extra, add warnings
  // here as necessary
  #define VAMOS_PUSH_DISABLE_ALL_WARNINGS                                    \
    VAMOS_PUSH_DISABLE_WARNINGS                                              \
    VAMOS_DISABLE_GCC_WARNING(-Weffc++)                                      \
    VAMOS_DISABLE_GCC_WARNING(-Wall)                                         \
    VAMOS_DISABLE_GCC_WARNING(-Wconversion)                                  \
    VAMOS_DISABLE_GCC_WARNING(-Wextra)                                       \
    VAMOS_DISABLE_GCC_WARNING(-Wattributes)                                  \
    VAMOS_DISABLE_GCC_WARNING(-Wimplicit-fallthrough)                        \
    VAMOS_DISABLE_GCC_WARNING(-Wnon-virtual-dtor)                            \
    VAMOS_DISABLE_GCC_WARNING(-Wreturn-type)                                 \
    VAMOS_DISABLE_GCC_WARNING(-Wshadow)                                      \
    VAMOS_DISABLE_GCC_WARNING(-Wunused-parameter)                            \
    VAMOS_DISABLE_GCC_WARNING(-Wunused-variable)
  #define VAMOS_PRAGMA(P) _Pragma(#P)
  #define VAMOS_DISABLE_GCC_WARNING(WARNING)                                 \
    VAMOS_PRAGMA(GCC diagnostic ignored #WARNING)
  #if defined(VAMOS_CLANG_VISUAL_STUDIO)
    #define VAMOS_DISABLE_UNDESIRED_WARNINGS                                 \
      VAMOS_DISABLE_GCC_WARNING(-Wmicrosoft-include)
  #else
    #define VAMOS_DISABLE_UNDESIRED_WARNINGS
  #endif
  #define VAMOS_DISABLE_DEPRECATED_WARNING                                   \
    VAMOS_DISABLE_GCC_WARNING(-Wdeprecated-declarations)
  #define VAMOS_DISABLE_STRICT_OVERFLOW_WARNING                              \
    VAMOS_DISABLE_GCC_WARNING(-Wstrict-overflow)
  #define VAMOS_POP_DISABLE_WARNINGS _Pragma("GCC diagnostic pop")
  // clang-format on

#endif // MSC_VER

#ifndef VAMOS_DLLIMPORTEXPORT
  #if defined(VAMOS_VISUAL_STUDIO)
    /**
     * It does not matter here whether you are using
     * the regular visual studio or clang under visual
     * studio.
     */
    #if VAMOS_USING_LIBRARY
      #define VAMOS_DLLIMPORTEXPORT __declspec(dllimport)
    #else
      #define VAMOS_DLLIMPORTEXPORT __declspec(dllexport)
    #endif
  #else
    #define VAMOS_DLLIMPORTEXPORT
  #endif
#endif

#define vamos_array_size(array) (sizeof(array) / sizeof((array)[0]))

#endif // VAMOS_COMMON_DEFS_H
