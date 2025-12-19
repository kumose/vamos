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
#pragma once

#include <vamos/vamos.h>
#include <algorithm>
#include <sstream>
#include <string>
#include <list>

namespace vamos {
namespace test {

int main(int argc, char *argv[]);
using test_procedure = void (*)(const vamos::implementation &impl);
struct test_entry {
  std::string name;
  test_procedure procedure;

  void operator()(const vamos::implementation &impl) { procedure(impl); }
};

std::list<test_entry> &test_procedures();

struct register_test {
  register_test(const char *name, test_procedure proc);
};

} // namespace test
} // namespace vamos

#define TEST(name)                                                             \
  void test_impl_##name(const vamos::implementation &impl);                  \
  void name(const vamos::implementation &impl) {                             \
    vamos::get_active_implementation() = &impl;                              \
    std::string title = #name;                                                 \
    std::replace(title.begin(), title.end(), '_', ' ');                        \
    printf("Running '%s'... ", title.c_str());                                 \
    fflush(stdout);                                                            \
    test_impl_##name(impl);                                                    \
    puts(" OK");                                                               \
  }                                                                            \
  static vamos::test::register_test test_register_##name(#name, name);       \
  void test_impl_##name(                                                       \
      [[maybe_unused]] const vamos::implementation &implementation)

#define TEST_LOOP(trials, name)                                                \
  void test_impl_##name(const vamos::implementation &impl, uint32_t seed);   \
  void name(const vamos::implementation &impl) {                             \
    std::string title = #name;                                                 \
    std::replace(title.begin(), title.end(), '_', ' ');                        \
    printf("Running '%s'... ", title.c_str());                                 \
    fflush(stdout);                                                            \
    for (size_t trial = 0; trial < (trials); trial++) {                        \
      const uint32_t seed{1234 + uint32_t(trial)};                             \
      if ((trial % 100) == 0) {                                                \
        putchar('.');                                                          \
        fflush(stdout);                                                        \
      }                                                                        \
      test_impl_##name(impl, seed);                                            \
    }                                                                          \
    puts(" OK");                                                               \
  }                                                                            \
  static vamos::test::register_test test_register_##name(#name, name);       \
  void test_impl_##name(const vamos::implementation &implementation,         \
                        [[maybe_unused]] uint32_t seed)

#define ASSERT_EQUAL(a, b)                                                     \
  {                                                                            \
    const auto lhs = (a);                                                      \
    const auto rhs = (b);                                                      \
    if (lhs != rhs) {                                                          \
      std::stringstream lhs_str;                                               \
      lhs_str << lhs;                                                          \
      std::stringstream rhs_str;                                               \
      rhs_str << rhs;                                                          \
      printf("lhs: %s = %s\n", #a, lhs_str.str().c_str());                     \
      printf("rhs: %s = %s\n", #b, rhs_str.str().c_str());                     \
      printf("%s \n", #a);                                                     \
      printf("file %s:%d, function %s  \n", __FILE__, __LINE__, __func__);     \
      exit(1);                                                                 \
    }                                                                          \
  }

#define ASSERT_TRUE(cond)                                                      \
  {                                                                            \
    const bool expr = (cond);                                                  \
    if (!expr) {                                                               \
      printf("expected %s to be true, it's false\n", #cond);                   \
      printf("file %s:%d, function %s  \n", __FILE__, __LINE__, __func__);     \
      exit(1);                                                                 \
    }                                                                          \
  }

#define ASSERT_FALSE(cond)                                                     \
  {                                                                            \
    const bool expr = !(cond);                                                 \
    if (!expr) {                                                               \
      printf("expected %s to be false, it's true\n", #cond);                   \
      printf("file %s:%d, function %s  \n", __FILE__, __LINE__, __func__);     \
      exit(1);                                                                 \
    }                                                                          \
  }

#define TEST_MAIN                                                              \
  int main(int argc, char *argv[]) { return vamos::test::main(argc, argv); }
