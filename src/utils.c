#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <utils.h>
#include "background.h"
#include <string.h>
#include <png2ico/png2ico.h>

//DropArea droparea = {0, 0, WINDOW_WIDTH/2, WINDOW_HEIGHT};
DropArea droparea = {0, 0, WINDOW_WIDTH/2, WINDOW_HEIGHT};


void SDL_ExitWithError(const char *message)
{
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

SDL_bool isDropOnArea(PointerPos *_p, SDL_Rect _rect)
{
    SDL_GetMouseState(&(_p->x), &(_p->y));

    if(_p->x < (_rect.x+_rect.w)&& _p->x > _rect.x && _p->y < (_rect.y+_rect.h) && _p->y > _rect.y)
    {
        return SDL_TRUE;
    }

    return SDL_FALSE;
    
}


SDL_bool isImageFile(char *filename) {
    if (filename == NULL) {
        return SDL_FALSE;
    }

    char *ext = strrchr(filename, '.');

    if (ext != NULL && 
        (strcmp(ext, ".png") == 0 || strcmp(ext, ".jpg") == 0 ||
         strcmp(ext, ".jpeg") == 0 || strcmp(ext, ".ico") == 0 || strcmp(ext, ".bmp") == 0)) {
        return SDL_TRUE;
    }
    /*
    strcmp(ext, ".bmp") == 0 ||
         strcmp(ext, ".tga") == 0 || strcmp(ext, ".tiff") == 0 ||
         strcmp(ext, ".tif") == 0 || 
    1*/

    return SDL_FALSE;
}

void changeTypeName(char *filename, char* type) {
    unsigned len = strlen(filename);
    char *ext = strrchr(filename, '.');

    if (ext != NULL) {
        // Replace existing extension with ".ico"
        strcpy(ext, type);
    } else {
        // Append ".ico" to the end of the filename
        snprintf(filename + len, 4, type);
    }
}



int convertFile(char *input, char* output, char* newType, char* actualType)
{
    /*
    Done:

    png -> ico
    png -> jpg
    png -> bmp

    jpg -> ico
    jpg -> png
    jpg -> bmp

    ico -> png
    ico -> jpg
    ico -> bmp

    bmp -> ico
    bmp -> png
    bmp -> jpg
    


    */
    printf("convert %s to %s\n", actualType, newType);
    if (strcmp(actualType, newType)==0)
    {
        return -2;
    }

    int verif = 0;
    changeTypeName(output, newType);
    
    if (strcmp(actualType, ".png")==0 && strcmp(newType, ".ico")==0)
    {
        verif = c_png2ico(input, output);
    }
    else if ((strcmp(actualType, ".jpg")==0 || strcmp(actualType, ".jpeg")==0) && strcmp(newType, ".ico")==0)
    {
        verif = c_jpg2ico(input, output);
    }
    else if ((strcmp(actualType, ".jpg")==0 || strcmp(actualType, ".jpeg")==0) && strcmp(newType, ".png")==0)
    {
        verif = c_jpg2png(input, output);
    }
    else if (strcmp(actualType, ".png")==0 && (strcmp(newType, ".jpg")==0 || strcmp(newType, ".jpeg")==0))
    {
        verif = c_png2jpg(input, output);
    }
    else if ((strcmp(actualType, ".jpg")==0 || strcmp(actualType, ".jpeg")==0) && strcmp(newType, ".bmp")==0)
    {
        verif = c_jpg2bmp(input, output);
    }
    else if (strcmp(actualType, ".png")==0 && strcmp(newType, ".bmp")==0)
    {
        verif = c_png2bmp(input, output);
    }
    else if (strcmp(actualType, ".ico")==0 && strcmp(newType, ".bmp")==0)
    {
        verif = c_ico2bmp(input, output);
    }
    else if (strcmp(actualType, ".ico")==0 && strcmp(newType, ".png")==0)
    {
        verif = c_ico2png(input, output);
    }
    else if (strcmp(actualType, ".ico")==0 && strcmp(newType, ".jpg")==0)
    {
        verif = c_ico2jpg(input, output, 90);
    }
    else if (strcmp(actualType, ".bmp")==0 && strcmp(newType, ".ico")==0)
    {
        verif = c_bmp2ico(input, output);
    }
    else if (strcmp(actualType, ".bmp")==0 && strcmp(newType, ".png")==0)
    {
        verif = c_bmp2png(input, output);
    }
    else if (strcmp(actualType, ".bmp")==0 && strcmp(newType, ".jpg")==0)
    {
        verif = c_bmp2jpg(input, output, 90);
    }
    else{
        return -2;
    }
    


    if (verif != 0)
    {
        printf("\033[1;32mErreur lors de la conversion\033[0m\n");
        return -1;
    }
    else
    {
        return 0;
    }
}

int c_jpg2ico(char* input, char* output)
{
    return c_png2ico(input, output);
}

