Jeremy Wise Project B
bootload.asm is used and so are the commands in compileOS.sh from Project A. Project B replaces Project A's video-memory Hello World kernel with the Project B BIOS system call implementation.
The build script creates a fresh diskc.img.

RUN ./compileOS.sh The script assembles the bootloader, compiles and links the new kernel,
The bootloader's 10-sector 512K kernel limit is checked, writes the bootloader to sector 0, writes the kernel starting at sector 3, and writes message.txt to sector 30.

Load diskc.img as hard disk C using the settings from Project A and boot
Expected conditions: a ready message, a keyboard prompt, echoed input, and a message loaded from sector 30,
For a backspace test, enter abc, backspace, d, and Enter: the echoed result should be abd (not ad).


- printString: BIOS INT 10h video output, stopping at NUL.
- readString: Reads keyboard input using interrupt 0x16 and handles backspace.
- readSector: Reads a sector from the disk using interrupt 0x13.
- handleInterrupt21: Uses AX to determine which function to call. 0 prints a string, 1 reads keyboard input, and 2 reads a disk sector. Other values print an error.
