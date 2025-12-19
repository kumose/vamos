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
