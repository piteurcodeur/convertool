#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include <background.h>
#include <utils.h>

#include <png2ico/png2ico.h>


/**
 * @brief 
 * 
 * https://wiki.libsdl.org/SDL2/FrontPage
 * 
 * @param 
 */



void Create_Window(SDL_Window *win, SDL_Renderer *rend);
void initSDL();
void doInput();
void prepareScene();
void presentScene();
SDL_Surface* createMainSurface(SDL_Window *window);
void cleanup();
//void loadImage(char* filepath);

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
} App;

//Application principale
App app;
//nom du fichier drop dans la zone
char *drop_file_dir;
//position du pointeur de souris
PointerPos ptrP;



int main(int argc, char **argv)
{
    SDL_version nb;
    SDL_VERSION(&nb);
    printf("Bienvenue sur la SDL %d.%d.%d\n", nb.major, nb.minor, nb.patch);

    SDL_bool program_launched = SDL_TRUE;

    memset(&app, 0, sizeof(App));

    initSDL();
    atexit(cleanup);


    lineCoord lineCoord1 = {WINDOW_WIDTH/2, 0, WINDOW_WIDTH/2, WINDOW_HEIGHT};
    SDL_Rect rect = {WINDOW_WIDTH/2, 0, 10, WINDOW_HEIGHT};
    //SDL_Surface *MainSurface = createMainSurface(app.window);

    prepareScene();
    changeColor (BLACK, app.renderer);
    //drawline(app.renderer, lineCoord1);
    drawRect(app.renderer, &rect, SDL_TRUE);
    showText(app.renderer, BLACK, 80, 10, 20, "Drag & Drop image file");

    while (program_launched)
    {
        
        doInput();

        presentScene();

        SDL_Delay(16);
    }

    
    /*-------------------------------------------------------------------------*/

    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    SDL_Quit();

    return EXIT_SUCCESS;

}

/*  Compilation   */
//          gcc src/main.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2

/*  Execution   */
//          ./bin/prog




void Create_Window(SDL_Window *win, SDL_Renderer *rend)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_ExitWithError("init video");
    }

    if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &win, &rend) != 0)
    {
        SDL_ExitWithError("init window and render");
    }

}

void initSDL(void)
{
    int rendererFlags, windowFlags;

    rendererFlags = SDL_RENDERER_ACCELERATED;

    windowFlags = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_ExitWithError("Couldn't initialize SDL:");
    }

    app.window = SDL_CreateWindow("Convertool", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, windowFlags);

    if (!app.window)
    {
        SDL_ExitWithError("Failed to open window:");
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);

    if (!app.renderer)
    {
        SDL_ExitWithError("Failed to create renderer: %s");
    }
}

void doInput(void)
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                exit(0);
                break;

            case SDL_DROPFILE:
                if(isDropOnArea(&ptrP))
                {
                    
                    drop_file_dir = event.drop.file;
                    if (isImageFile(drop_file_dir))
                    {
                        printf("%s\n", drop_file_dir);
                        //loadImage(drop_file_dir);
                        showText(app.renderer, BLACK, 80, 150, 20, "image loaded");

                        //nom du fichier ico créé
                        char * newFile = malloc(strlen(drop_file_dir) * sizeof(char));

                        strcpy(newFile, drop_file_dir);
                        changeTypeName(newFile);
                        c_png2ico(drop_file_dir, newFile);
                        free(newFile);
                    }
                    else
                    {
                        printf("Not an image file\n");
                    }
                    
                    
                }
                else{
                    printf("Drop file outside of the area\n");
                }
                   
                break;

            default:
                break;

        }
    }
}

void prepareScene(void)
{
    SDL_SetRenderDrawColor(app.renderer, 128, 128, 128, 255);
    SDL_RenderClear(app.renderer);
}

void presentScene(void)
{
    SDL_RenderPresent(app.renderer);
}

void cleanup()
{
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    SDL_Quit();
}

SDL_Surface* createMainSurface(SDL_Window *window) {
    // Obtenir la surface principale de la fenêtre
    SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
    if (!screenSurface) {
        printf("Erreur lors de l'obtention de la surface de la fenêtre : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1); // Utilisez exit(1) pour quitter le programme en cas d'erreur
    }
    return screenSurface;
}

/*
void loadImage(char *filepath)
{
    int width, height, channels;

    unsigned char *img = stbi_load(filepath, &width, &height, &channels, 0);

    if (img == NULL) {
        SDL_ExitWithError("Erreur lors du chargement de l'image\n");
    }

    // Check that the image data is in the expected format
    if (channels != 3) {
        fprintf(stderr, "Error: image data is not in RGB format\n");
        stbi_image_free(img);
        
    }

    printf("Image chargée: largeur=%d, hauteur=%d, canaux=%d\n", width, height, channels);
/*
    if (stbi_write_png("output.png", width, height, channels, img, width * channels)) {
        printf("Image sauvegardée sous 'output.png'\n");
    } else {
        printf("Erreur lors de la sauvegarde de l'image\n");
    }
*/
/*
    if (save_as_ico("output.ico", width, height, img)) {
        printf("Image sauvegardée sous 'output.ico'\n");
    } else {
        printf("Erreur lors de la sauvegarde de l'image\n");
    }


    if (convert(img, width, height, channels) == 0) {
        printf("Image sauvegardée sous 'output.ico'\n");
    } else {
        printf("Erreur lors de la sauvegarde de l'image\n");
    }
    
    stbi_image_free(img);
}
*/