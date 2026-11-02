/*Jeremy Wise Project B*/
void printString(char *);
void printChar(char);
void readString(char *);
void readSector(char *, int);
void handleInterrupt21(int, int, int, int);
int interrupt(int, int, int, int, int);
void makeInterrupt21(void);

int main(void) {
    char line[80];
    char buffer[512];
    int i;

    makeInterrupt21();
    interrupt(0x21, 0, (int)"Project B: system calls ready\r\n", 0, 0);
    interrupt(0x21, 0, (int)"Enter a line: ", 0, 0);
    interrupt(0x21, 1, (int)line, 0, 0);
    interrupt(0x21, 0, (int)"You typed: ", 0, 0);
    interrupt(0x21, 0, (int)line, 0, 0);

    for (i = 0; i < 512; ++i) buffer[i] = 0;
    interrupt(0x21, 2, (int)buffer, 30, 0);
    buffer[511] = 0;
    interrupt(0x21, 0, (int)buffer, 0, 0);

    while (1) { }
    return 0;
}

void printChar(char c) {
    interrupt(0x10, 0x0e00 + (unsigned char)c, 0, 0, 0);
}

void printString(char *chars) {
    int i = 0;
    while (chars[i] != 0) {
        printChar(chars[i]);
        ++i;
    }
}

void readString(char *line) {
    int i = 0;
    int c;
    while (1) {
        c = interrupt(0x16, 0, 0, 0, 0) & 0xff;
        if (c == 0x0d) {
            printChar(0x0d);
            printChar(0x0a);
            line[i++] = 0x0a;
            line[i] = 0;
            return;
        }
        if (c == 0x08) {
            if (i > 0) {
                --i;
                printChar(0x08);
                printChar(' ');
                printChar(0x08);
            }
        } else if (c >= 0x20 && c <= 0x7e && i < 78) {
            line[i++] = (char)c;
            printChar((char)c);
        }
    }
}

void readSector(char *buffer, int sector) {
    if (sector < 0 || sector > 62) {
        printString("Invalid sector\r\n");
        return;
    }
    interrupt(0x13, 0x0201, (int)buffer, sector + 1, 0x0080);
}

void handleInterrupt21(int ax, int bx, int cx, int dx) {
    if (ax == 0) {
        printString((char *)bx);
    } else if (ax == 1) {
        readString((char *)bx);
    } else if (ax == 2) {
        readSector((char *)bx, cx);
    } else {
        printString("unknown interrupt 0x21 service\r\n");
    }
}
