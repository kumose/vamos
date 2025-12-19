
option(VAMOS_SANITIZE "Sanitize addresses" OFF)
option(VAMOS_SANITIZE_UNDEFINED "Sanitize undefined behavior" OFF)
option(VAMOS_SANITIZE_THREAD "Sanitize threads" OFF)
option(VAMOS_ALWAYS_INCLUDE_FALLBACK "Always include fallback" OFF)

if (NOT CMAKE_BUILD_TYPE)
  message(STATUS "No build type selected, default to Release")
  if(VAMOS_SANITIZE OR VAMOS_SANITIZE_UNDEFINED)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
    # VAMOS_SANITIZE only applies to gcc/clang:
    message(STATUS "Setting debug optimization flag to -O1 -g.")
    set(CMAKE_CXX_FLAGS_DEBUG "-O1 -g" CACHE STRING "" FORCE)
  else()
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  endif()
endif()

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tools/cmake")

# We compile tools, tests, etc. with C++11 by default.
set(VAMOS_CXX_STANDARD 11 CACHE STRING "the C++ standard to use for vamos")

set(CMAKE_CXX_STANDARD ${VAMOS_CXX_STANDARD})
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
