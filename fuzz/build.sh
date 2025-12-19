#!/bin/sh
#
# this is the entry point for oss-fuzz.
#
# it can be invoked locally for development purposes as well
#

set -e

fuzzer_src_files=

if [ -z $SRC ] ; then
    echo "development mode"
    set -ux

    SCRIPTDIR=$(dirname "$0")
    cd "$SCRIPTDIR/.."

    export CXX=/usr/lib/ccache/clang++-18
    export CXXFLAGS="-fsanitize=fuzzer-no-link,address,undefined -g -O1 -fsanitize-trap=undefined"
    export LIB_FUZZING_ENGINE="-fsanitize=fuzzer"
    export OUT=fuzz/out
    export WORK=fuzz/work
    mkdir -p $OUT $WORK
else
    # invoked from oss fuzz
    cd $SRC/vamos
fi

fuzzer_src_files=$(ls fuzz/*.cpp|grep -v -E "fuzz/(reproducer.|main)")



cmake -B build -S . \
      -DVAMOS_TESTS=Off \
      -DVAMOS_TOOLS=Off \
      -DVAMOS_FUZZERS=Off \
      -DCMAKE_BUILD_TYPE=Debug \
      -DVAMOS_CXX_STANDARD=20 \
      -DVAMOS_ALWAYS_INCLUDE_FALLBACK=On

cmake --build build -j$(nproc)
cmake --install build --prefix $WORK

CXXFLAGSEXTRA=-std=c++20

for fuzzersrc in $fuzzer_src_files ; do
    fuzzer=$(basename $fuzzersrc .cpp)

    $CXX $CXXFLAGS $CXXFLAGSEXTRA\
         -I $WORK/include \
         -c $fuzzersrc -o $fuzzer.o

    $CXX $CXXFLAGS $LIB_FUZZING_ENGINE \
         $fuzzer.o \
         $WORK/lib/libvamos.a \
         -o $OUT/$fuzzer
done
