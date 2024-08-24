#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

//#include <stb/stb_image.h>

#pragma pack(push, 1)

typedef struct {
    uint8_t width;
    uint8_t height;
    uint8_t color_count;
    uint8_t reserved;
    uint16_t planes;
    uint16_t bit_count;
    uint32_t size_in_bytes;
    uint32_t image_offset;
} IcoDirEntry;

typedef struct {
    uint16_t reserved;
    uint16_t type;
    uint16_t count;
} IcoHeader;

typedef struct {
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bit_count;
    uint32_t compression;
    uint32_t image_size;
    int32_t x_pixels_per_meter;
    int32_t y_pixels_per_meter;
    uint32_t colors_used;
    uint32_t important_colors;
} BitmapInfoHeader;
#pragma pack(pop)

int save_as_ico(const char *filename, int width, int height, const unsigned char *data) {
    IcoHeader ico_header = {0, 1, 1};
    IcoDirEntry dir_entry = {0};
    BitmapInfoHeader bmp_info_header = {0};

    FILE *file = fopen(filename, "wb");
    if (!file) {
        return 0;
    }

    dir_entry.width = (width >= 256) ? 0 : width;
    dir_entry.height = (height >= 256) ? 0 : height;
    dir_entry.color_count = 0;
    dir_entry.reserved = 0;
    dir_entry.planes = 1;
    dir_entry.bit_count = 32;
    dir_entry.size_in_bytes = width * height * 4 + sizeof(BitmapInfoHeader);
    dir_entry.image_offset = sizeof(IcoHeader) + sizeof(IcoDirEntry);

    bmp_info_header.size = sizeof(BitmapInfoHeader);
    bmp_info_header.width = width;
    bmp_info_header.height = height * 2;  // La hauteur est doublée pour le masque
    bmp_info_header.planes = 1;
    bmp_info_header.bit_count = 32;
    bmp_info_header.compression = 0;
    bmp_info_header.image_size = width * height * 4;

    fwrite(&ico_header, sizeof(IcoHeader), 1, file);
    fwrite(&dir_entry, sizeof(IcoDirEntry), 1, file);
    fwrite(&bmp_info_header, sizeof(BitmapInfoHeader), 1, file);

    // Écrire les données de l'image (les lignes de bas en haut pour BMP)
    for (int y = height - 1; y >= 0; y--) {
        fwrite(data + y * width * 4, 4, width, file);
    }

    // Ajouter un masque vide (nécessaire pour les fichiers .ico)
    uint8_t zero_byte = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            uint8_t mask_byte = (x % 8 == 0) ? 0x80 : (mask_byte >> 1);
            fwrite(&mask_byte, 1, 1, file);
        }
        // Ajouter des octets nuls pour aligner la taille de la ligne sur un multiple de 4
        int padding = (width + 7) / 8 % 4;
        for (int i = 0; i < padding; i++) {
            fwrite(&zero_byte, 1, 1, file);
        }
    }

    fclose(file);
    return 1;
}
