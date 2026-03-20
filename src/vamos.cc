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

// We include base64_tables once.
#include "vamos/tables/base64_tables.h"

#include "encoding_types.cpp"
#include "error.cpp"
// The large tables should be included once and they
// should not depend on a kernel.
#include "vamos/tables/utf8_to_utf16_tables.h"
#include "vamos/tables/utf16_to_utf8_tables.h"
// End of tables.

// Implementations: they need to be setup before including
// scalar/* code, as the scalar code is sometimes enabled
// only for peculiar build targets.

// The best choice should always come first!
#include "vamos/arm64.h"
#include "vamos/icelake.h"
#include "vamos/haswell.h"
#include "vamos/westmere.h"
#include "vamos/ppc64.h"
#include "vamos/rvv.h"
#include "vamos/lsx.h"
#include "vamos/lasx.h"
#include "vamos/fallback.h" // have it always last.

// The scalar routines should be included once.
#include "scalar/swap_bytes.h"
#include "scalar/ascii.h"
#include "scalar/utf8.h"

#include "scalar/utf16.h"

#include "scalar/utf32.h"
#include "scalar/latin1.h"
#include "scalar/base64.h"

#include "scalar/utf32_to_utf8/valid_utf32_to_utf8.h"
#include "scalar/utf32_to_utf8/utf32_to_utf8.h"

#include "scalar/utf32_to_utf16/valid_utf32_to_utf16.h"
#include "scalar/utf32_to_utf16/utf32_to_utf16.h"

#include "scalar/utf16_to_utf8/valid_utf16_to_utf8.h"
#include "scalar/utf16_to_utf8/utf16_to_utf8.h"

#include "scalar/utf16_to_utf32/valid_utf16_to_utf32.h"
#include "scalar/utf16_to_utf32/utf16_to_utf32.h"

#include "scalar/utf8_to_utf16/valid_utf8_to_utf16.h"
#include "scalar/utf8_to_utf16/utf8_to_utf16.h"

#include "scalar/utf8_to_utf32/valid_utf8_to_utf32.h"
#include "scalar/utf8_to_utf32/utf8_to_utf32.h"

#include "scalar/latin1_to_utf8/latin1_to_utf8.h"

#include "scalar/latin1_to_utf16/latin1_to_utf16.h"

#include "scalar/latin1_to_utf32/latin1_to_utf32.h"

#include "scalar/utf8_to_latin1/utf8_to_latin1.h"

#include "scalar/utf16_to_latin1/utf16_to_latin1.h"

#include "scalar/utf32_to_latin1/utf32_to_latin1.h"

#include "scalar/utf8_to_latin1/valid_utf8_to_latin1.h"

#include "scalar/utf16_to_latin1/valid_utf16_to_latin1.h"

#include "scalar/utf32_to_latin1/valid_utf32_to_latin1.h"

#include "implementation.cpp"

VAMOS_PUSH_DISABLE_WARNINGS
VAMOS_DISABLE_UNDESIRED_WARNINGS

#if VAMOS_IMPLEMENTATION_ARM64
  #include "arm64/implementation.cpp"
#endif
#if VAMOS_IMPLEMENTATION_FALLBACK
  #include "fallback/implementation.cpp"
#endif
#if VAMOS_IMPLEMENTATION_ICELAKE
  #include "icelake/implementation.cpp"
#endif
#if VAMOS_IMPLEMENTATION_HASWELL
  #include "haswell/implementation.cpp"
#endif
#if VAMOS_IMPLEMENTATION_PPC64
  #include "ppc64/implementation.cpp"
#endif
#if VAMOS_IMPLEMENTATION_RVV
  #include "rvv/implementation.cpp"
#endif
#if VAMOS_IMPLEMENTATION_WESTMERE
  #include "westmere/implementation.cpp"
#endif
#if VAMOS_IMPLEMENTATION_LSX
  #include "lsx/implementation.cpp"
#endif
#if VAMOS_IMPLEMENTATION_LASX
  #include "lasx/implementation.cpp"
#endif

VAMOS_POP_DISABLE_WARNINGS
