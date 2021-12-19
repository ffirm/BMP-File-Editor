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
void merge_bmp(bmp_info *p1, bmp_info *p2);
void copy_bmp(char *path);        // creating a duplicate bmp file

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

    merge_bmp(greenland, deer);

    free(greenland);
    free(deer);

    return 0;
}

void copy_bmp(char *path){
    FILE *read = fopen(path, "rb");
    if (read ==  NULL){
        printf("error fopen read");
        exit(1);
    }

    fseek(read, 0, SEEK_END);
    size_t f_size = ftell(read);

    byte *temp = (byte*)malloc(f_size);

    fseek(read, 0, SEEK_SET);
    int res = fread(temp, 1, f_size, read);
    printf("res=%d", res);

    FILE *write = fopen("duplicate.bmp", "wb");
    for (size_t i = 0; i < f_size; i++){
        fputc(temp[i], write);
    }
    
    fclose(read);
    fclose(write);
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
    printf("pixel arrays starts at: 0x%X\n\n", infoPtr->array_offset);

//    byte temp[2];
//    fseek(fp, BITS_PER_PIXEL_OFFSET, SEEK_SET);
//    fread(temp, 2, 1, fp);
//    printf("%d\n", temp);
}

void merge_bmp(bmp_info *p1, bmp_info *p2){
    // will create a new bmp image from the two given image
    // pic1 on top of pic2

    // check if the two bmp are compatible or not
    if (p1->bpp != p2->bpp){
        printf("Incompatible bpp");
        exit(1);
    }

    // allocating memory for the new bmp
    size_t total_size = p1->image_size + p2->image_size;
    byte *pic_arr = (byte*)malloc(total_size);

    bmp_info new_bmp;
    // width
    if (p1->width > p2->width){
        new_bmp.width = p1->width;
    }
    //height
    new_bmp.height = p1->height + p2->height;
    new_bmp.array_offset = 54;
    new_bmp.image_size = total_size;
    new_bmp.bpp = p1->bpp;

    // assigning 0 to the array
    for (int i = 0; i < total_size; i++){
        pic_arr[i] = 0;
    }

    // bitmap structure

    // bitmap signature
    pic_arr[0] = 'B';
    pic_arr[1] = 'M';

    // file size
    pic_arr[2] = 0;
    pic_arr[3] = 0;
    pic_arr[4] = 0;
    pic_arr[5] = 0;

    // pixel array offset starts
    pic_arr[10] = new_bmp.array_offset;

    // DIB header
    // dib header size
    pic_arr[14] = 28;
    // width
    pic_arr[18] = new_bmp.width;
    //height
    pic_arr[22] = new_bmp.height;
    //bpp
    pic_arr[28] = new_bmp.bpp;

    // assigning value to the pixel array

    // bottom pic width is smaller than top pic width so white pixels will substitute the remaining pixels
    if (p1->width > p2->width){
        for (size_t i = 0; i < new_bmp.height; i++){
            for (size_t j = 0; j < new_bmp.width; j++){
                if (j <= new_bmp.width){
                    pic_arr[new_bmp.array_offset + j] = *(p1->pixel_array + j);
                }
            }
        }
    }

    // writing the bmp array into a new bmp file
    FILE *write;
    write = fopen("../merged.bmp", "wb");
    for (int i = 0; i < new_bmp.image_size; i++){
        fputc(pic_arr[i], write);
    }
    fclose(write);
}
