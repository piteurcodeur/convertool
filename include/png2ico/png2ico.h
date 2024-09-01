//#define STB_IMAGE_IMPLEMENTATION
//#include <../stb/stb_image.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#pragma pack(push, 1)

typedef struct {
    uint16_t reserved;
    uint16_t type;
    uint16_t count;
} ICONDIR;

typedef struct {
    uint8_t width;
    uint8_t height;
    uint8_t color_count;
    uint8_t reserved;
    uint16_t planes;
    uint16_t bit_count;
    uint32_t bytes_in_res;
    uint32_t image_offset;
} ICONDIRENTRY;

typedef struct {
    uint32_t size;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t bit_count;
    uint32_t compression;
    uint32_t image_size;
    uint32_t x_pixels_per_m;
    uint32_t y_pixels_per_m;
    uint32_t colors_used;
    uint32_t colors_important;
} BITMAPINFOHEADER;

int c_png2ico(char *input, char* output);
void jpg2png(char *input, char* output);