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
SDL_bool isButtonClicked(Button *button, int x, int y);
void fileDropped(char * drop_file_dir);


typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
} App;

//Application principale
App app;
//nom du fichier drop dans la zone
char *drop_file_dir;
//nom du nouveau fichier
char *newFile;
//extension du fichier drop
char *extension;
//position du pointeur de souris
PointerPos ptrP;

Button btnPNG;
Button btnICO;
Button btnJPG;

SDL_bool isfileDrop = SDL_FALSE;



int main(int argc, char **argv)
{
    SDL_version nb;
    SDL_VERSION(&nb);
    printf("Bienvenue sur la SDL %d.%d.%d\n", nb.major, nb.minor, nb.patch);

    SDL_bool program_launched = SDL_TRUE;

    memset(&app, 0, sizeof(App));

    initSDL();
    atexit(cleanup);


    //lineCoord lineCoord1 = {WINDOW_WIDTH/2, 0, WINDOW_WIDTH/2, WINDOW_HEIGHT};
    SDL_Rect rect = {WINDOW_WIDTH/2, 0, 10, WINDOW_HEIGHT};
    //SDL_Surface *MainSurface = createMainSurface(app.window);


    /*---------------------Préparation de la fenetre----------------------------*/

    prepareScene();
    changeColor (BLACK, app.renderer);
    
    drawRect(app.renderer, &rect, SDL_TRUE);
    showText(app.renderer, BLACK, 60, 10, 30, "Drag & Drop image file");
    showText(app.renderer, BLACK, 500, 10, 30, "Select Format");
    changeColor (WHITE, app.renderer);
    SDL_Color black = {BLACK.r, BLACK.g, BLACK.b, BLACK.a};

    //création des boutons de l'interface
    btnPNG = createButton(app.renderer, 120, "> PNG", 600, 100, 80, 40, black);
    drawButton(app.renderer, &btnPNG);
    btnICO = createButton(app.renderer, 120, "> ICO", 600, 200, 80, 40, black);
    drawButton(app.renderer, &btnICO);
    btnJPG = createButton(app.renderer, 120, "> JPG", 600, 300, 80, 40, black);
    drawButton(app.renderer, &btnJPG);

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

    if (TTF_Init() < 0) {
        fprintf(stderr, "Erreur lors de l'initialisation de TTF: %s\n", TTF_GetError());
        SDL_Quit();
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
                TTF_Quit();
                SDL_Quit();
                exit(0);
                break;

            case SDL_DROPFILE:
                if(isDropOnArea(&ptrP))
                {
                    
                    drop_file_dir = event.drop.file;
                    isfileDrop = SDL_TRUE;
                    fileDropped(drop_file_dir);
                    
                }
                else{
                    printf("Drop file outside of the area\n");
                }
                   
                break;
            
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    
                    if (isfileDrop == SDL_TRUE)
                    {
                        if (isButtonClicked(&btnICO,  x, y))
                        {
                            printf("Conversion en ico...\n");
                            convertFile(drop_file_dir, newFile, ".ico", extension);
                        }
                        else if (isButtonClicked(&btnJPG, x, y))
                        {
                            printf("Conversion en jpg...\n");
                            convertFile(drop_file_dir, newFile, ".jpg", extension);
                        }
                        else if (isButtonClicked(&btnPNG, x, y))
                        {
                            printf("Conversion en png...\n");
                            convertFile(drop_file_dir, newFile, ".png", extension);
                        }   
                    }                        
                }
            default:
                break;
        }
    }
}

SDL_bool isButtonClicked(Button *button, int x, int y)
{
    if (x >= button->rect.x && x <= button->rect.x + button->rect.w && y >= button->rect.y && y <= button->rect.y + button->rect.h)
    {
        return SDL_TRUE;
    }
    return SDL_FALSE;
}

//allocation mémoire nouveau fichier
void fileDropped(char * drop_file_dir)
{
    if (isImageFile(drop_file_dir))
    {
        printf("Dropfile : %s\n", drop_file_dir);
        
        extension = strrchr(drop_file_dir, '.');

        showText(app.renderer, RED, 80, 150, 20, "image loaded");
        showText(app.renderer, BLACK, 80, 250, 20, extension);
        //nom du fichier ico créé
        newFile = malloc(strlen(drop_file_dir) * sizeof(char));
        strcpy(newFile, drop_file_dir);
        
        //free(newFile);
    }
    else
    {
        printf("Not an image file\n");
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
