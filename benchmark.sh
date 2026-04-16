#!/usr/bin/env bash

set -e

CXX="g++"

CXXFLAGS=(
-O3                
-DNDEBUG           
-march=native      
-std=c++17
-Iinclude -Isrc

-fno-omit-frame-pointer
)

LDFLAGS=()

SRC=(
include/cashFriendlyList/list.cpp
include/cashFriendlyList/general_list.cpp
include/cashFriendlyList/protection_list.cpp

include/general/debug.cpp
include/general/encode.cpp
include/general/file.cpp
include/general/hash.cpp
include/general/poison.cpp
include/general/strFunc.cpp

src/main.cpp
src/hashTable.cpp

src/measures/handler.cpp
)

OUT="hashTableBench.out"

$CXX "${CXXFLAGS[@]}" "${SRC[@]}" -o "$OUT" "${LDFLAGS[@]}"

echo "Done: $OUT"