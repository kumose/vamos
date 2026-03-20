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
