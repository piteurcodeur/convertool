#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <png2ico/png2ico.h>

#pragma pack(pop)

int c_png2ico(char *input, char* output)
{

    int width, height, channels;
    unsigned char *img = stbi_load(input, &width, &height, &channels, 4);
    if (!img) {
        printf("Error loading image %s\n", input);
        return 1;
    }

    FILE *out = fopen(output, "wb");
    if (!out) {
        printf("Error creating output file %s\n", output);
        stbi_image_free(img);
        return 1;
    }

    ICONDIR icondir = {0, 1, 1};
    ICONDIRENTRY entry = {width, height, 0, 0, 1, 32, width * height * 4 + 40, sizeof(ICONDIR) + sizeof(ICONDIRENTRY)};
    BITMAPINFOHEADER bmi = {40, width, height * 2, 1, 32, 0, width * height * 4, 0, 0, 0, 0};

    fwrite(&icondir, sizeof(ICONDIR), 1, out);
    fwrite(&entry, sizeof(ICONDIRENTRY), 1, out);
    fwrite(&bmi, sizeof(BITMAPINFOHEADER), 1, out);

    // Write pixel data (BGRA)
    for (int y = height - 1; y >= 0; y--) {
        for (int x = 0; x < width; x++) {
            int idx = (y * width + x) * 4;
            uint8_t temp = img[idx];
            img[idx] = img[idx + 2];
            img[idx + 2] = temp;
            fwrite(&img[idx], 4, 1, out);
        }
    }

    fclose(out);
    stbi_image_free(img);
    printf("ICO file created successfully: %s\n", output);
    return 0;
}
