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
