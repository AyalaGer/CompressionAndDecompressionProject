#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
void write16bits(FILE* output, int code) {
    int right = 0xFF;
    int left = 0xFF00;
    int bits = (left & code);
    bits = bits >> 8;
    fputc(bits, output);
    bits = right & code;
    fputc(bits, output);
}

int read16bits(FILE* output) {
    int left = fgetc(output);
    if (left == EOF)
        return -1;
    left = left << 8;
    int right = fgetc(output);
    if (right == EOF) return -1;
    return (left | right);

}


int leftover = 0;
int leftoverBits;

void writeBinary(FILE* output, int code) {
    if (leftover > 0) {
        int previousCode = (leftoverBits << 4) + (code >> 8);

        fputc(previousCode, output);
        fputc(code, output);

        leftover = 0; // no leftover now
    }
    else {
        leftoverBits = code & 0xF; // save leftover, the last 00001111
        leftover = 1;

        fputc(code >> 4, output);
    }
}

int readBinary(FILE* input) {
    int code = fgetc(input);
    if (code == EOF) return 0;

    if (leftover > 0) {
        code = (leftoverBits << 8) + code;

        leftover = 0;
    }
    else {
        int nextCode = fgetc(input);

        leftoverBits = nextCode & 0xF; // save leftover, the last 00001111
        leftover = 1;

        code = (code << 4) + (nextCode >> 4);
    }
    return code;
}