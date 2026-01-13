/usr/lib/llvm18/bin/clang-18 -S --target=riscv32-unknown-elf -O2 -fno-builtin-printf -fno-builtin-memcpy builtin.c -o.s
#sed 's/ptr_/ptr./g;s/builtin_/builtin./g' builtin_intermediate.ll > builtin.ll