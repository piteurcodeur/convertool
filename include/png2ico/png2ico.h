/**
 * @file png2ico.h
 * @author piteurcodeur
 * @brief little lib to convert image files in different types
 * 
 * 
 * @version 0.1
 * @date 2024-09-03
 * 
 * =======================================================================
 * |                                                                     |
 * |                            PNG to ICO                               |
 * |                                                                     |
 * =======================================================================
 * 
 */

#ifndef PNG2ICO_H
#define PNG2ICO_H

/**
 * @struct ICONDIR
 * @brief Structure representing the icon directory
 */
typedef struct {
    uint16_t reserved;  ///< Reserved field, must be 0
    uint16_t type;      ///< Type of the icon (1 for icon, 2 for cursor)
    uint16_t count;     ///< Number of images in the icon
} ICONDIR;

/**
 * @struct ICONDIRENTRY
 * @brief Structure representing an icon directory entry
 */
typedef struct {
    uint8_t width;          ///< Width of the image
    uint8_t height;         ///< Height of the image
    uint8_t color_count;    ///< Number of colors in the image
    uint8_t reserved;       ///< Reserved field, must be 0
    uint16_t planes;        ///< Number of planes in the image
    uint16_t bit_count;     ///< Number of bits per pixel
    uint32_t bytes_in_res;  ///< Size of the image data in bytes
    uint32_t image_offset;  ///< Offset of the image data in the file
} ICONDIRENTRY;

/**
 * @struct BITMAPINFOHEADER
 * @brief Structure representing a bitmap information header
 */
typedef struct {
    uint32_t size;               ///< Size of the header in bytes
    uint32_t width;              ///< Width of the image
    uint32_t height;             ///< Height of the image
    uint16_t planes;             ///< Number of planes in the image
    uint16_t bit_count;          ///< Number of bits per pixel
    uint32_t compression;        ///< Compression type (0 for uncompressed, 1 for RLE-8, 2 for RLE-4)
    uint32_t image_size;         ///< Size of the image data in bytes
    uint32_t x_pixels_per_m;     ///< Horizontal resolution in pixels per meter
    uint32_t y_pixels_per_m;     ///< Vertical resolution in pixels per meter
    uint32_t colors_used;        ///< Number of colors used in the image
    uint32_t colors_important;   ///< Number of important colors in the image
} BITMAPINFOHEADER;


/**
 * @fn int c_png2ico(char *input, char* output)
 * @brief Convert a PNG image to an ICO image
 * 
 * @param input Path to the input PNG image file
 * @param output Path to the output ICO image file
 * @return 0 on success, -1 on failure
 * 
 */
int c_png2ico(char *input, char* output);

/**
 * @fn void c_jpg2png(char *input, char* output)
 * @brief Convert a JPG image to a PNG image
 * 
 * @param input Path to the input JPG image file
 * @param output Path to the output PNG image file
 * 
 */
int c_jpg2png(char *input, char* output);

/**
 * @fn void c_png2jpg(char* input, char* output)
 * @brief Convert a PNG image to a JPG image
 * 
 * @param input Path to the input PNG image file
 * @param output Path to the output PNG image file
 * 
 */ 
int c_png2jpg(char* input, char* output);

/**
 * @brief 
 * 
 * @param input 
 * @param output 
 * @return int 
 */
int c_jpg2bmp(char *input, char *output);

/**
 * @brief 
 * 
 * @param input 
 * @param output 
 * @return int 
 */
int c_png2bmp(char *input, char *output);

/**
 * @brief 
 * 
 * @param input 
 * @param output 
 * @return int 
 */
int c_ico2bmp(char *input, char *output);

/**
 * @brief 
 * 
 * @param input 
 * @param output 
 * @param quality 
 * @return int 
 */
int c_ico2jpg(char *input, char *output, int quality);

/**
 * @brief 
 * 
 * @param input 
 * @param output 
 * @return int 
 */
int c_ico2png(char *input, char *output);

#endif //PNG2ICO_H