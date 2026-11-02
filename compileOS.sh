#!/bin/sh
#Jeremy Wise Project B

set -eu
nasm bootload.asm
bcc -ansi -c -o kernel_c.o kernel.c
as86 kernel.asm -o kernel_asm.o
ld86 -o kernel -d kernel_c.o kernel_asm.o
size=$(wc -c < kernel | tr -d ' ')
if [ "$size" -gt 5120 ]; then
  echo "ERROR: kernel is $size bytes; bootloader reads only 5120 bytes (10 sectors)." >&2
  exit 1
fi
dd if=/dev/zero of=diskc.img bs=512 count=1000
dd if=bootload of=diskc.img bs=512 count=1 conv=notrunc
dd if=kernel of=diskc.img bs=512 conv=notrunc seek=3
dd if=message.txt of=diskc.img bs=512 count=1 seek=30 conv=notrunc
printf 'Created diskc.img (kernel %s bytes).\n' "$size"
