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
#include <vamos/unicodelib/unicode_normal_form.h>

namespace vamos::unicode {

    namespace UnicodeNormalForm {

        int32_t FromStr(std::string_view form) noexcept {
            if (form == "NFC") {
                return NFC;
            }
            if (form == "NFKC") {
                return NFKC;
            }
            if (form == "NFD") {
                return NFD;
            }
            if (form == "NFKD") {
                return NFKD;
            }
            return Invalid;
        }

        std::string_view ToStr(int32_t form) noexcept {
            switch (form) {
                case NFC: {
                    return "NFC";
                }
                    break;
                case NFKC: {
                    return "NFKC";
                }
                    break;
                case NFD: {
                    return "NFD";
                }
                    break;
                case NFKD: {
                    return "NFKD";
                }
                    break;
                default: {
                    return "Invalid";
                }
                    break;
            }
        }

    }  // namespace UnicodeNormalForm

}  // namespace vamos::unicode
