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

cmake_minimum_required(VERSION 3.15)

project(vamos
  DESCRIPTION "Fast Unicode validation, transcoding and processing"
  LANGUAGES CXX
  VERSION 6.2.0
)

include (TestBigEndian)
TEST_BIG_ENDIAN(IS_BIG_ENDIAN)
if(IS_BIG_ENDIAN)
  message(STATUS "Big-endian system detected.")
endif()

include(GNUInstallDirs)
# The following requires CMake 3.21.
# if(PROJECT_IS_TOP_LEVEL)
#  message(STATUS "Building vamos as a top-level project.")
#  include(CTest)
#else()
#  message(STATUS "Building vamos as a subproject.")
#endif(PROJECT_IS_TOP_LEVEL)
include(CTest)
include(cmake/vamos-flags.cmake)

set(VAMOS_LIB_VERSION "16.0.0" CACHE STRING "vamos library version")
set(VAMOS_LIB_SOVERSION "16" CACHE STRING "vamos library soversion")
option(VAMOS_TESTS "Whether the tests are included as part of the CMake Build." OFF)
option(VAMOS_BENCHMARKS "Whether the benchmarks are included as part of the CMake Build." OFF)
option(VAMOS_TOOLS "Whether the tools are included as part of the CMake build. Requires C++17 or better." OFF)
option(VAMOS_ICONV "Whether to use iconv as part of the CMake build if available." ON)
option(VAMOS_FUZZERS "Whether to build the fuzzers." Off)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

set(VAMOS_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(src)

if (VAMOS_TESTS)
  message(STATUS "The tests are enabled.")
  add_subdirectory(tests)
else(VAMOS_TESTS)
  message(STATUS "The tests are disabled.")
endif(VAMOS_TESTS)


if (VAMOS_TOOLS)
  if(CMAKE_CXX_COMPILER_ID MATCHES GNU AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 8.0)
    message(STATUS "The benchmark tool requires GCC 8.0 or better.")
  else()
    add_subdirectory(tools)
  endif()
endif()


if (VAMOS_BENCHMARKS)
  if(NOT VAMOS_TESTS)
    message(STATUS "You have enabled the benchmarks, but not the tests. We don't allow running the benchmarks without the tests.")
  elif((CMAKE_CXX_COMPILER_ID MATCHES GNU) AND (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "8.0"))
    message(STATUS "The benchmark tool requires GCC 8.0 or better.")
  else()
    message(STATUS "The benchmarks can be disabled by setting VAMOS_BENCHMARKS, e.g., -D VAMOS_BENCHMARKS=OFF.")
    add_subdirectory(benchmarks)
  endif()
else()
  message(STATUS "The benchmarks can be enabled by setting VAMOS_BENCHMARKS, e.g., -D VAMOS_BENCHMARKS=ON.")
endif()

message(STATUS "Compiling using the C++ standard:" ${CMAKE_CXX_STANDARD})
# ---- Install rules ----
add_library(vamos::vamos ALIAS vamos)

set_target_properties(
        vamos PROPERTIES
    VERSION "${VAMOS_LIB_VERSION}"
    SOVERSION "${VAMOS_LIB_SOVERSION}"
    WINDOWS_EXPORT_ALL_SYMBOLS YES
)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

install(
    DIRECTORY include/vamos
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT vamos_Development
)

install(
    TARGETS vamos
    EXPORT vamosTargets
    RUNTIME COMPONENT vamos_Runtime
    LIBRARY COMPONENT vamos_Runtime
    NAMELINK_COMPONENT vamos_Development
    ARCHIVE COMPONENT vamos_Development
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

configure_file(cmake/vamos-config.cmake.in vamos-config.cmake @ONLY)

write_basic_package_version_file(
        vamos-config-version.cmake
    COMPATIBILITY SameMinorVersion
)

set(
    VAMOS_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/vamos"
    CACHE STRING "CMake package config location relative to the install prefix"
)
mark_as_advanced(VAMOS_INSTALL_CMAKEDIR)

install(
    FILES
    "${PROJECT_BINARY_DIR}/vamos-config.cmake"
    "${PROJECT_BINARY_DIR}/vamos-config-version.cmake"
    DESTINATION "${VAMOS_INSTALL_CMAKEDIR}"
    COMPONENT vamos_Development
)

install(
    EXPORT vamosTargets
    NAMESPACE vamos::
    DESTINATION "${VAMOS_INSTALL_CMAKEDIR}"
    COMPONENT example_Development
)


# pkg-config
include(cmake/JoinPaths.cmake)
join_paths(PKGCONFIG_INCLUDEDIR "\${prefix}" "${CMAKE_INSTALL_INCLUDEDIR}")
join_paths(PKGCONFIG_LIBDIR "\${prefix}" "${CMAKE_INSTALL_LIBDIR}")

configure_file("vamos.pc.in" "vamos.pc" @ONLY)
install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/vamos.pc"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig"
)
#
# CPack
#
if(is_top_project)
  set(CPACK_PACKAGE_VENDOR "Daniel Lemire")
  set(CPACK_PACKAGE_CONTACT "lemire@gmail.com")
  set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE-MIT")
  set(CPACK_RPM_PACKAGE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE-MIT")
  set(CPACK_RESOURCE_FILE_README "${PROJECT_SOURCE_DIR}/README.md")
  set(CPACK_SOURCE_GENERATOR "TGZ;ZIP")
  include(CPack)
endif()

# ----



if(NOT VAMOS_SANITIZE)
  find_program(GREP grep)
  find_program(NM nm)
  if((NOT GREP) OR (NOT NM))
    message("grep and nm are unavailable on this system.")
  else()
    add_test(
      NAME "avoid_abort"
      # Under FreeBSD, the __cxa_guard_abort symbol may appear but it is fine.
      # So we want to look for <space><possibly _>abort as a test.
      COMMAND sh -c "${NM}  $<TARGET_FILE_NAME:vamos> |  ${GREP} ' _*abort' || exit 0  && exit 1"
      WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    )
    add_test(
      NAME "avoid_cout"
      COMMAND sh -c "${NM}  $<TARGET_FILE_NAME:vamos> |  ${GREP} ' _*cout' || exit 0  && exit 1"
      WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    )
    add_test(
      NAME "avoid_cerr"
      COMMAND sh -c "${NM}  $<TARGET_FILE_NAME:vamos> |  ${GREP} ' _*cerr' || exit 0  && exit 1"
      WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    )
    add_test(
      NAME "avoid_printf"
      COMMAND sh -c "${NM}  $<TARGET_FILE_NAME:vamos> |  ${GREP} ' _*printf' || exit 0  && exit 1"
      WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    )
    add_test(
      NAME "avoid_stdout"
      COMMAND sh -c "${NM}  $<TARGET_FILE_NAME:vamos> |  ${GREP} stdout || exit 0 && exit 1"
      WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    )
    add_test(
      NAME "avoid_stderr"
      COMMAND sh -c "${NM}  $<TARGET_FILE_NAME:vamos> |  ${GREP} stderr || exit 0 && exit 1"
      WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    )
  endif()
endif()

if(VAMOS_FUZZERS)
    add_subdirectory(fuzz)
endif()
