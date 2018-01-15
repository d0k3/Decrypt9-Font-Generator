#define PBM // write 1x256 char PBM file if this is defined
// #define PBMS // write 16x16 char PBM file if this is defined
#define FONT "font_6x10.h"
#define PBMCMT "Created by cfont2img.c (C) d0k3"


#if defined PBM || defined PBMS
#define FONT_IMG FONT ".pbm"
#else
#define FONT_IMG FONT ".raw"
#endif

#include <stdio.h>
#include FONT

int main (int argc, char* argv[]) {
    FILE* fp = fopen(FONT_IMG, "wb");
    if (fp == NULL) {
        printf("could not open: %s\n", FONT_IMG);
        return 1;
    }
    
    #ifdef PBMS
        #define SQUARE_SIZE (16 * 16 * FONT_HEIGHT * FONT_WIDTH / 8)
        fprintf(fp, "P4\n# %s\n%i %i\n", PBMCMT, FONT_WIDTH * 16, FONT_HEIGHT * 16);
        unsigned char img[SQUARE_SIZE];
        int img_size = SQUARE_SIZE;
        unsigned char* ptr = img;
        for (int i = 0; i < SQUARE_SIZE; i++) img[i] = 0;
        for (int cy = 0; cy < 16; cy++) {
            for (int row = 0; row < FONT_HEIGHT; row++) {
                for (int cx = 0; cx < 16; cx++) {
                    int bp0 = (cx * FONT_WIDTH) >> 3;
                    int bm0 = (cx * FONT_WIDTH) % 8;
                    unsigned char byte = font[(((cy << 4) + cx) * FONT_HEIGHT) + row];
                    unsigned char byte0 = byte >> bm0;
                    unsigned char byte1 = byte << (8 - bm0);
                    ptr[bp0] |= byte0;
                    ptr[bp0+1] |= byte1;
                }
                ptr += FONT_WIDTH << 1;
            }
        }
    #else
        const unsigned char* img = font;
        int img_size = font_size;
        #ifdef PBM
        fprintf(fp, "P4\n# %s\n%i %i\n", PBMCMT, FONT_WIDTH, FONT_HEIGHT * 256);
        #endif
    #endif
    
    fwrite(img, img_size, 1, fp);
    fclose(fp);
    printf("%s\nfont to image conversion complete!\n", FONT_IMG);
    return 0;
}