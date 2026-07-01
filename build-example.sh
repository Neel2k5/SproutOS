#!/usr/bin/env bash
set -e

CROSS="<Path to Cross Compiler's Binary>"

CC="${CROSS}i686-elf-gcc"
AS="nasm"

ASFLAGS="-f elf32"

CFLAGS="-ffreestanding -O2 -g -Wall -Wextra -Ikernel/include"
LDFLAGS="-T kernel/arch/i386/linker.ld -ffreestanding -nostdlib"

echo "[1/7] Creating build directories..."
rm -rf build
mkdir -p build
mkdir -p build/iso/boot/grub

echo "[2/7] Assembling boot and cpu specific files..."
$AS $ASFLAGS kernel/arch/i386/boot/boot.s -o build/boot.o
$AS $ASFLAGS kernel/arch/i386/cpu/io.s -o build/io.o
echo "[3/7] Compiling kernel..."
$CC $CFLAGS -c kernel/kernel.c -o build/kernel.o

echo "[4/7] Compiling Drivers..."
$CC $CFLAGS -c kernel/drivers/vga/vga.c -o build/vga.o
$CC $CFLAGS -c kernel/drivers/serial/serial.c -o build/serial.o

echo "[5/7] Compiling libk..."
$CC $CFLAGS -c kernel/libk/kprintf.c -o build/kprintf.o

echo "[6/7] Linking kernel..."
$CC \
    $LDFLAGS \
    build/boot.o \
    build/io.o\
    build/kernel.o \
    build/vga.o \
    build/serial.o\
    build/kprintf.o \
    -o build/kernel.elf

echo "[7/7] Creating bootable ISO..."
cp build/kernel.elf build/iso/boot/kernel.elf
cp boot/grub/grub.cfg build/iso/boot/grub/grub.cfg

grub-mkrescue -o build/SproutOS.iso build/iso

echo
echo "=================================="
echo "Build completed successfully!"
echo "Kernel : build/kernel.elf"
echo "ISO    : build/SproutOS.iso"
echo "=================================="
echo
echo "Run with:"
echo "qemu-system-i386 -cdrom build/SproutOS.iso"