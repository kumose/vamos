# Copyright 2020 The simdutf authors
# Copyright (C) 2026 Kumo inc. and its affiliates.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

add_library(vamos-include-source INTERFACE)
target_include_directories(vamos-include-source INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
add_library(vamos-source INTERFACE)
target_sources(vamos-source INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/vamos.cpp)
target_link_libraries(vamos-source INTERFACE vamos-include-source)
add_library(vamos vamos.cc unicode_view.cc unicode.cc unicodelib/unicode_ctype.cc unicodelib/unicode_data.cc unicodelib/uchar_util.cc unicodelib/unicode_normal_form.cc unicodelib/unicode_ops.cc)
target_include_directories(vamos PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> )
target_include_directories(vamos PUBLIC "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>")

if(MSVC)
  if("${MSVC_TOOLSET_VERSION}" STREQUAL "140")
    target_compile_options(vamos PRIVATE /W0 /sdl)
    set(VAMOS_LEGACY_VISUAL_STUDIO TRUE)
  else()
    target_compile_options(vamos PRIVATE /WX /W3 /sdl /w34714) # https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4714?view=vs-2019
  endif()
else(MSVC)
  if(NOT WIN32)
    target_compile_options(vamos INTERFACE -fPIC)
  endif()
  target_compile_options(vamos PRIVATE -Wall -Wextra -Weffc++)
  target_compile_options(vamos PRIVATE -Wsign-compare -Wshadow -Wwrite-strings -Wpointer-arith -Winit-self -Wconversion -Wno-sign-conversion -Wunused-function)
  #target_compile_options(vamos PRIVATE -Wfatal-errors)
endif(MSVC)

# workaround for GNU GCC poor AVX load/store code generation
if ((CMAKE_CXX_COMPILER_ID STREQUAL "GNU") AND (CMAKE_SYSTEM_PROCESSOR MATCHES "^(i.86|x86(_64)?)$"))
  target_compile_options(vamos PRIVATE -mno-avx256-split-unaligned-load -mno-avx256-split-unaligned-store)
endif()

if(VAMOS_ALWAYS_INCLUDE_FALLBACK)
  message(STATUS "VAMOS_ALWAYS_INCLUDE_FALLBACK is set to ${VAMOS_ALWAYS_INCLUDE_FALLBACK}")
  target_compile_definitions(vamos PRIVATE VAMOS_IMPLEMENTATION_FALLBACK=1)
endif()

if(VAMOS_SANITIZE)
  target_compile_options(vamos PUBLIC -fsanitize=address  -fno-omit-frame-pointer -fno-sanitize-recover=all)
  target_compile_definitions(vamos PUBLIC ASAN_OPTIONS=detect_leaks=1)
  target_link_libraries(vamos PUBLIC -fsanitize=address  -fno-omit-frame-pointer -fno-sanitize-recover=all)
endif()
if(VAMOS_SANITIZE_UNDEFINED)
  target_compile_options(vamos PUBLIC -fsanitize=undefined -fno-sanitize-recover=all)
  target_link_libraries(vamos PUBLIC -fsanitize=undefined)
endif()
if(VAMOS_SANITIZE_THREAD)
    target_compile_options(vamos PUBLIC -fsanitize=thread)
    target_link_libraries(vamos PUBLIC -fsanitize=thread)
endif()
if(MSVC AND BUILD_SHARED_LIBS)
  set(VAMOS_WINDOWS_DLL TRUE)
endif()
