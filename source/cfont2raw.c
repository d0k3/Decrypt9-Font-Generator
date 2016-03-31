#include <stdio.h>
#include "font.h"

int main (int argc, char* argv[]) {
    FILE* fp = fopen("font.raw", "wb");
    if (fp == NULL) {
        printf("could not open font.raw");
        return 1;
    }
    fwrite(font, font_size, 1, fp);
    fclose(fp);
    printf("font to raw conversion complete!");
    return 0;
}