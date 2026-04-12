#!/usr/bin/env bash

set -e

CXX="g++"

CXXFLAGS=(
-g -O2 -fno-omit-frame-pointer
-fno-optimize-sibling-calls
-Iinclude -Isrc
-Wall -Wextra -Waggressive-loop-optimizations -Wc++14-compat
-Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts
-Wconditionally-supported -Wconversion -Wctor-dtor-privacy
-Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security
-Wformat-signedness -Wformat=2 -Winline -Wlogical-op
-Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked
-Wpointer-arith -Winit-self -Wredundant-decls -Wshadow
-Wsign-conversion -Wsign-promo -Wstrict-null-sentinel
-Wstrict-overflow=2 -Wsuggest-attribute=noreturn
-Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override
-Wswitch-default -Wsync-nand -Wundef -Wunreachable-code
-Wunused -Wuseless-cast -Wvariadic-macros
-Wno-literal-suffix -Wno-missing-field-initializers
-Wno-narrowing -Wno-old-style-cast -Wno-varargs
-Werror=vla 
)

LDFLAGS=(
-fcheck-new -fsized-deallocation -fstack-protector
-fstrict-overflow
)

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

OUT="hashTable.out"

echo "Compiling..."

$CXX "${CXXFLAGS[@]}" "${SRC[@]}" \
-o "$OUT" "${LDFLAGS[@]}"

echo "Done: $OUT"
