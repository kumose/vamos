add_library(vamos_tests_reference STATIC
  encode_utf8.h
  encode_utf8.cc
  encode_utf16.h
  encode_utf16.cc
  encode_utf32.h
  encode_utf32.cc
  encode_latin1.h
  encode_latin1.cc
  validate_utf8_to_latin1.h
  validate_utf8_to_latin1.cc
  validate_utf16_to_latin1.h
  validate_utf16_to_latin1.cc
  validate_utf32_to_latin1.h
  validate_utf32_to_latin1.cc
  validate_utf8.h
  validate_utf8.cc
  validate_utf16.h
  validate_utf16.cc
  validate_utf32.h
  validate_utf32.cc)
add_library(vamos::tests::reference ALIAS vamos_tests_reference)
target_link_libraries(vamos_tests_reference PRIVATE vamos)
