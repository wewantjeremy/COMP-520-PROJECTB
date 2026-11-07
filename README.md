PROJECT C - README

1. WHAT I DID

For Project C, I extended my operating system from Project B to support a basic file system and program execution.

I implemented three additional system calls:

AX=3: Read a file from disk using its filename.
AX=4: Load and execute a program.
AX=5: Terminate a program and restart the shell.

I also implemented a shell supporting the commands "type" and "exec", and a loadFile utility that places files onto the disk image.

2. HOW TO VERIFY

Compile the operating system on the Linux server:

cd ~/seanjeremy/project_c
./compileOS.sh

This generates diskc.img.

Open EmuMaker86 on the Mac, select diskc.img as Hard Disk C, and boot from Disk C.

The operating system should display a shell prompt.

TEST 1: FILE READING

Enter:

type messag

Expected result: The contents of message.txt appear on the screen.

TEST 2: PROGRAM EXECUTION

Enter:

exec tstpr1

Expected result: The message "tstpr1 is working!" appears. The original program then enters an intentional infinite loop. Reboot to return to the shell.

TEST 3: PROGRAM TERMINATION

Enter:

exec tstpr2

Expected result: The program executes and returns to the shell using system call AX=5.

3. FILES

bootload.asm - Bootloader
kernel.c - Kernel functions
kernel.asm - Assembly routines
shell.c - Command shell
userlib.asm - System call interface
loadFile.c - File loading utility
tstpr1.c - Program execution test
tstpr2.c - Program termination test
compileOS.sh - Build script
diskc.img - Bootable disk image
