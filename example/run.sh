#!/bin/bash -v

# export your environmant PATH to the toolchain we built. e.g. <shore>/_install/bin
# export PATH=/home/<user>/SHORE/_install/bin

clang main.c -fsoftboundcets -c
clang main.c -fsoftboundcets -emit-llvm -fno-discard-value-names -S
clang main.c -fsoftboundcets -S
riscv64-unknown-linux-gnu-gcc main.o -o main -L ../shore-llvm/runtime -lsoftboundcets_rt -lm -static -march=rv64imac -mabi=lp64
spike pk ./main helloworld 5
llvm-objdump -source -disassemble-all main > dump
