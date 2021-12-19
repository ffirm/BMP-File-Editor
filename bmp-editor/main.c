#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define PIXEL_ARRAY_OFFSET 0x000A
#define WIDTH_OFFSET 0x12
#define HEIGHT_OFFSET 0x16
#define BITS_PER_PIXEL_OFFSET 0x1C
#define IMAGE_SIZE_OFFSET 0x22

typedef unsigned int int32;
typedef unsigned char byte;

typedef struct bmp_info {
    int32 width;
    int32 height;
    int32 bpp;
    int32 image_size;
    int32 array_offset;
    byte *pixel_array;
} bmp_info;

void slice_str(const char *str, char *buffer, size_t start, size_t end);
void read_bmp(char *path, bmp_info *infoPtr);
void merge_bmp();

int main() {
//    bmp_info *infoPtr, pic1;
//    infoPtr = &pic1;
//    read_bmp("../sample.bmp", infoPtr);

    bmp_info *greenland, pic2;
    greenland = &pic2;
    bmp_info *deer, pic3;
    deer = &pic3;
    
    read_bmp("../greenland_grid_velo.bmp", greenland);
    read_bmp("../blackbuck.bmp", deer);

    free(greenland);
    free(deer);

    return 0;
}

void read_bmp(char* path, bmp_info *infoPtr) {
    FILE *fp = fopen(path, "rb");
    if (fp == NULL) {
        printf("Error opening file");
        fclose(fp);
        exit(1);
    }

    // Check if file is BMP or not
    byte file_sig[3];
    file_sig[2] = '\0';
    fseek(fp, 0, SEEK_SET);
    fread(file_sig, 2, 1, fp);
    if (strcmp("BM", file_sig) != 0){
        printf("Invalid BMP file");
        exit(1);
    }

    // file size
    fseek(fp, 0, SEEK_END);
    size_t f_size = ftell(fp);

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

    // fread pixel array from file into a malloced pointer called color_array
    infoPtr->pixel_array = (byte*)malloc(infoPtr->image_size);
    fseek(fp, infoPtr->array_offset, SEEK_SET);
    int res = fread(infoPtr->pixel_array, 1, infoPtr->image_size, fp);
    if (res != infoPtr->image_size){
        printf("fread pixel array error");
        exit(1);
    }

    fclose(fp);

    printf("path: %s\n", path);
    printf("image size: %d bytes\n", f_size);
    printf("height: %d\n", infoPtr->height);
    printf("width: %d\n", infoPtr->width);
    printf("bits per pixel: %d\n", infoPtr->bpp);
    printf("pixel arrays starts at: 0x%X\n", infoPtr->array_offset);

    byte temp[2];
    fseek(fp, BITS_PER_PIXEL_OFFSET, SEEK_SET);
    fread(temp, 2, 1, fp);
    printf("%d\n", temp);
}

