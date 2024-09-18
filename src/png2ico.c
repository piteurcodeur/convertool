#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <png2ico/png2ico.h>
#include <utils.h>


#pragma pack(push)

int c_png2ico(char *input, char* output)
{

    int width, height, channels;
    unsigned char *img = stbi_load(input, &width, &height, &channels, 4);
    if (!img) {
        printf("Error loading image %s\n", input);
        return -1;
    }

    FILE *out = fopen(output, "wb");
    if (!out) {
        printf("Error creating output file %s\n", output);
        stbi_image_free(img);
        return -1;
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

int c_jpg2png(char *input, char* output)
{
    
    int width, height, channels;

    unsigned char *img = stbi_load(input, &width, &height, &channels, 0);

    if (img == NULL) {
        SDL_ExitWithError("Erreur lors du chargement de l'image\n");
        return -1;
    }

    // Check that the image data is in the expected format
    if (channels != 3) {
        fprintf(stderr, "Error: image data is not in RGB format\n");
        stbi_image_free(img);
        return -1;
    }

    printf("Image chargee: largeur=%d, hauteur=%d, canaux=%d\n", width, height, channels);

    if (stbi_write_png(output, width, height, channels, img, width * channels)) {
        printf("Image sauvegardee sous '%s'\n", output);
    } else {
        printf("Erreur lors de la sauvegarde de l'image\n");
        return -1;
    }

    stbi_image_free(img);
    return 0;
}

int c_png2jpg(char* input, char* output)
{
    int width, height, channels;
    unsigned char *img = stbi_load(input, &width, &height, &channels, 0);
    
    if(img == NULL) {
        printf("Erreur lors du chargement de l'image\n");
        return -1;
    }
    
    // Convertir en RGB si l'image est en RGBA
    if(channels == 4) {
        unsigned char *rgb_img = malloc(width * height * 3);
        for(int i = 0; i < width * height; i++) {
            rgb_img[i*3] = img[i*4];
            rgb_img[i*3+1] = img[i*4+1];
            rgb_img[i*3+2] = img[i*4+2];
        }
        stbi_image_free(img);
        img = rgb_img;
        channels = 3;
    }
    
    int success = stbi_write_jpg(output, width, height, channels, img, 90);
    
    if(!success) {
        printf("Erreur lors de l'écriture de l'image JPG\n");
        return -1;
    }
    
    stbi_image_free(img);
    return 0;
}

int c_jpg2bmp(char* input, char* output)
{
    int width, height, channels;
    unsigned char *img = stbi_load(input, &width, &height, &channels, 0);
   
    if (img == NULL) {
        fprintf(stderr, "Erreur lors du chargement de l'image '%s'\n", input);
        return -1;
    }

    printf("Image chargee : %dx%d avec %d canaux\n", width, height, channels);

    //3 (RGB) ou 4 (RGBA) canaux
    int output_channels = (channels == 4) ? 4 : 3;
    
    int success = stbi_write_bmp(output, width, height, output_channels, img);
    if (!success) {
        fprintf(stderr, "Erreur lors de l'écriture de l'image BMP '%s'\n", output);
        stbi_image_free(img);
        return -1;
    }

    printf("Image BMP ecrite avec succès : '%s'\n", output);
    
    stbi_image_free(img);
    return 0;
}


int c_png2bmp(char* input, char* output)
{
    int width, height, channels;
    unsigned char *img = stbi_load(input, &width, &height, &channels, 0);
   
    if (img == NULL) {
        fprintf(stderr, "Erreur lors du chargement de l'image PNG '%s'\n", input);
        return -1;
    }

    printf("Image PNG chargee : %dx%d avec %d canaux\n", width, height, channels);

    //nombre de canaux pour la sortie
    int output_channels = (channels == 4) ? 4 : 3;
    
    int success = stbi_write_bmp(output, width, height, output_channels, img);
    if (!success) {
        fprintf(stderr, "Erreur lors de l'écriture de l'image BMP '%s'\n", output);
        stbi_image_free(img);
        return -1;
    }

    printf("Image BMP ecrite avec succes : '%s'\n", output);
    
    stbi_image_free(img);
    return 0;
}



unsigned char* load_ico(char* filename, int* width, int* height, int* channels) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Impossible d'ouvrir le fichier ICO '%s'\n", filename);
        return NULL;
    }

    ICONDIR dir;
    if (fread(&dir, sizeof(ICONDIR), 1, file) != 1) {
        fclose(file);
        return NULL;
    }

    if (dir.type != 1 || dir.count == 0) {
        fclose(file);
        return NULL;
    }

    ICONDIRENTRY entry;
    if (fread(&entry, sizeof(ICONDIRENTRY), 1, file) != 1) {
        fclose(file);
        return NULL;
    }

    fseek(file, entry.image_offset, SEEK_SET);

    BITMAPINFOHEADER bih;
    if (fread(&bih, sizeof(BITMAPINFOHEADER), 1, file) != 1) {
        fclose(file);
        return NULL;
    }

    if (bih.compression != 0) {
        fclose(file);
        return NULL;
    }

    *width = bih.width;
    *height = bih.height / 2;  // Diviser par 2 car la hauteur inclut le masque alpha
    *channels = bih.bit_count / 8;

    if (*channels != 3 && *channels != 4) {
        fclose(file);
        return NULL;
    }

    int rowSize = ((bih.bit_count * bih.width + 31) / 32) * 4;
    int imageSize = rowSize * (*height);

    unsigned char* data = malloc(imageSize);
    if (!data) {
        fclose(file);
        return NULL;
    }

    if (fread(data, 1, imageSize, file) != imageSize) {
        free(data);
        fclose(file);
        return NULL;
    }

    fclose(file);

    // Inverser les lignes de l'image
    unsigned char* flipped_data = malloc(imageSize);
    for (int y = 0; y < *height; ++y) {
        memcpy(flipped_data + y * rowSize, 
               data + (*height - 1 - y) * rowSize, 
               rowSize);
    }
    free(data);

    return flipped_data;
}

int c_ico2jpg(char* input, char* output, int quality) {
    int width, height, channels;
    unsigned char* img = load_ico(input, &width, &height, &channels);
    if (!img) {
        fprintf(stderr, "Erreur lors du chargement de l'image ICO '%s'\n", input);
        return -1;
    }

    printf("Image ICO chargee : %dx%d avec %d canaux\n", width, height, channels);

    unsigned char* rgb_img = malloc(width * height * 3);
    if (!rgb_img) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        free(img);
        return -1;
    }

    // Convertir BGR(A) en RGB
    for (int i = 0; i < width * height; i++) {
        rgb_img[i*3] = img[i*channels + 2];
        rgb_img[i*3 + 1] = img[i*channels + 1];
        rgb_img[i*3 + 2] = img[i*channels];
    }

    int success = stbi_write_jpg(output, width, height, 3, rgb_img, quality);
    if (!success) {
        fprintf(stderr, "Erreur lors de l'ecriture de l'image JPG '%s'\n", output);
        free(rgb_img);
        free(img);
        return -1;
    }

    printf("Image JPG ecrite avec succes : '%s'\n", output);
    
    free(rgb_img);
    free(img);
    return 0;
}

int c_ico2png(char* input, char* output) {
    int width, height, channels;
    unsigned char* img = load_ico(input, &width, &height, &channels);
    if (!img) {
        fprintf(stderr, "Erreur lors du chargement de l'image ICO '%s'\n", input);
        return -1;
    }

    printf("Image ICO chargee : %dx%d avec %d canaux\n", width, height, channels);

    unsigned char* rgb_img = malloc(width * height * channels);
    if (!rgb_img) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        free(img);
        return -1;
    }

    // Convertir BGR(A) en RGB(A)
    for (int i = 0; i < width * height; i++) {
        rgb_img[i*channels] = img[i*channels + 2];
        rgb_img[i*channels + 1] = img[i*channels + 1];
        rgb_img[i*channels + 2] = img[i*channels];
        if (channels == 4) {
            rgb_img[i*channels + 3] = img[i*channels + 3];
        }
    }

    int success = stbi_write_png(output, width, height, channels, rgb_img, width * channels);
    if (!success) {
        fprintf(stderr, "Erreur lors de l'écriture de l'image PNG '%s'\n", output);
        free(rgb_img);
        free(img);
        return -1;
    }

    printf("Image PNG écrite avec succès : '%s'\n", output);
    
    free(rgb_img);
    free(img);
    return 0;
}

int c_ico2bmp(char* input, char* output) {
    int width, height, channels;
    unsigned char* img = load_ico(input, &width, &height, &channels);
    if (!img) {
        fprintf(stderr, "Erreur lors du chargement de l'image ICO '%s'\n", input);
        return -1;
    }

    printf("Image ICO chargée : %dx%d avec %d canaux\n", width, height, channels);

    unsigned char* rgb_img = malloc(width * height * 3);
    if (!rgb_img) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        free(img);
        return -1;
    }

    // Convertir BGR(A) en RGB
    for (int i = 0; i < width * height; i++) {
        rgb_img[i*3] = img[i*channels + 2];
        rgb_img[i*3 + 1] = img[i*channels + 1];
        rgb_img[i*3 + 2] = img[i*channels];
    }

    int success = stbi_write_bmp(output, width, height, 3, rgb_img);
    if (!success) {
        fprintf(stderr, "Erreur lors de l'écriture de l'image BMP '%s'\n", output);
        free(rgb_img);
        free(img);
        return -1;
    }

    printf("Image BMP écrite avec succès : '%s'\n", output);
    
    free(rgb_img);
    free(img);
    return 0;
}

#pragma pack(pop)