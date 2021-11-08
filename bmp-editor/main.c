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

unsigned int row_size();
void read_bmp();

int main() {
    read_bmp();
    return 0;
}

void read_bmp(){
    FILE *fp = fopen("../sample.bmp", "rb");
    if (fp == NULL){
        printf("Error opening file");
        fclose(fp);
        exit(1);
    }
    int32 data, height, width, bits_per_pixel, header_size, image_size, pixel_array_offset, temp;
    char compression_method[BUFFER_SIZE];
    fseek(fp, PIXEL_ARRAY_OFFSET, SEEK_SET);
    fread(&data, 4, 1, fp);
    fseek(fp, WIDTH_OFFSET, SEEK_SET);
    fread(&width, 4, 1, fp);
    fseek(fp, HEIGHT_OFFSET, SEEK_SET);
    fread(&height, 4, 1, fp);
    fseek(fp, BITS_PER_PIXEL_OFFSET, SEEK_SET);
    fread(&bits_per_pixel, 2, 1, fp);
    fseek(fp, HEADER_SIZE_OFFSET, SEEK_SET);
    fread(&header_size, 4, 1, fp);
    fseek(fp, IMAGE_SIZE_OFFSET, SEEK_SET);
    fread(&image_size, 4, 1, fp);
    fseek(fp, PIXEL_ARRAY_OFFSET, SEEK_SET);
    fread(&pixel_array_offset, 4, 1, fp);
    fseek(fp, 0xCA, SEEK_SET);
    fread(&temp, 4, 1, fp);
    printf("height: %d\n", height);
    printf("width: %d\n", width);
    printf("bits per pixel: %d\n", bits_per_pixel);
    printf("header size: %d bytes\n", header_size);
    printf("image size: %d bytes\n", image_size);
    printf("pixel arrays starts at: %X\n", pixel_array_offset);
    printf("%d", temp);
}



