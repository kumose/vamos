add_library(vamos_tests_helpers STATIC
  test.h
  test.cc
  random_int.h
  random_int.cc
  transcode_test_base.h
  transcode_test_base.cc
  random_utf8.h
  random_utf8.cc
  random_utf16.h
  random_utf16.cc
  random_utf32.h
  random_utf32.cc)
target_include_directories(vamos_tests_helpers PUBLIC ${VAMOS_TEST_INCLUDE_DIR})
target_link_libraries(vamos_tests_helpers PUBLIC vamos vamos::tests::reference)

add_library(vamos::tests::helpers ALIAS vamos_tests_helpers)
