#include <stdio.h>
#include <stdlib.h>

#define PIXEL_ARRAY_OFFSET 0x000A
#define WIDTH_OFFSET 0x12
#define HEIGHT_OFFSET 0x16
#define BITS_PER_PIXEL_OFFSET 0x1C
#define HEADER_SIZE_OFFSET 0x0E
#define IMAGE_SIZE_OFFSET 0x22
#define COMPRESSION_METHOD_OFFSET 0x30
#define BUFFER_SIZE 1024

typedef unsigned int int32;
typedef unsigned char byte;

typedef struct colours {
    float r, g, b;
} colours;

typedef struct bmp_info {
    int32 width;
    int32 height;
    int32 bpp;
    int32 image_size;
    int32 array_offset;
    byte pixel;
} bmp_info;

void read_bmp(char* path, bmp_info *infoPtr);

int main() {
    bmp_info *infoPtr, pic1;
    infoPtr = &pic1;
    read_bmp("../sample.bmp", infoPtr);
    return 0;
}

void read_bmp(char* path, bmp_info *infoPtr) {
    FILE *fp = fopen(path, "rb");
    if (fp == NULL) {
        printf("Error opening file");
        fclose(fp);
        exit(1);
    }

    // Reading basic file information
    fseek(fp, WIDTH_OFFSET, SEEK_SET);
    fread(&infoPtr->width, 4, 1, fp);
    fseek(fp, HEIGHT_OFFSET, SEEK_SET);
    fread(&infoPtr->height, 4, 1, fp);
    fseek(fp, BITS_PER_PIXEL_OFFSET, SEEK_SET);
    fread(&infoPtr->bpp, 2, 1, fp);
    fseek(fp, IMAGE_SIZE_OFFSET, SEEK_SET);
    fread(&infoPtr->image_size, 4, 1, fp);
    fseek(fp, PIXEL_ARRAY_OFFSET, SEEK_SET);
    fread(&infoPtr->array_offset, 4, 1, fp);

    // Reading pixel array
    const int padding_amount = ((4 - (infoPtr->width * 3) % 4) % 4);
    colours pixels[infoPtr->width * infoPtr-> height];

    for (int y = 0; y < infoPtr->width; y++){
        for (int x = 0; x < infoPtr->height; x++){
            byte colour[3];
            fread(colour, 3, 1, (void*)infoPtr->array_offset);

            pixels[y * infoPtr->width + x].r = (float)colour[3] / 255.0f;
            pixels[y * infoPtr->width + x].g = (float)colour[3] / 255.0f;
            pixels[y * infoPtr->width + x].b = (float)colour[3] / 255.0f;
        }
    }

    fclose(fp);

    printf("path: %s\n", path);
    printf("image size: %d bytes\n", infoPtr->image_size);
    printf("height: %d\n", infoPtr->height);
    printf("width: %d\n", infoPtr->width);
    printf("bits per pixel: %d\n", infoPtr->bpp);
    printf("pixel arrays starts at: %d (0x%X)\n", infoPtr->array_offset, infoPtr->array_offset);
}


