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
#include <vamos/vamos.h>

#include <tests/helpers/test.h>

// This is an attempt at reproducing an issue with the utf8 fuzzer
TEST(puzzler) {
  const char *bad64 =
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x1c\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x80\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
  size_t length = 64;
  ASSERT_FALSE(implementation.validate_utf8(bad64, length));
}

TEST(puzzler2) {
  // Interesting case where the error occurs in the first 64 bytes but is only
  // detected in the next 64 bytes.
  const char *bad102 =
      "\x0a\x04\x00\x00\xdb\xa1\xdd\xa1\xf1\xa0\xb6\x95\xe4\xb5\x89\xe7\x8f\x95"
      "\xe4\xa2\x83\xe7\x95\x89\xe7\x95\x91\xe7\x95\x89\x00\x01\x01\x1a\x20\x28"
      "\x00\x00\x60\x00\x00\x23\x00\xf1\xa0\xb6\x95\xe4\xb5\x89\xe7\x8f\x95\xe4"
      "\xa2\x83\xe7\x95\x89\xe7\x95\x91\xe7\x81\x00\x00\x01\x01\x1a\x20\x28\x00"
      "\x00\x60\x00\x00\x23\x00\x2f\x00\x00\x00\x00\x07\x04\x75\xc2\xa0\x34\x2f"
      "\x00\x00\x00\x00\x07\x04\x75\xc2\xa0\x33\x53\x2b";
  size_t length = 102;
  ASSERT_FALSE(implementation.validate_utf8(bad102, length));
  auto r = implementation.validate_utf8_with_errors(bad102, length);
  ASSERT_EQUAL(r.error, vamos::TOO_SHORT);
  ASSERT_EQUAL(r.count, 62);
}

TEST_MAIN
