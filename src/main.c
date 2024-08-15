#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stb/stb_image.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

/**
 * @brief 
 * 
 * https://wiki.libsdl.org/SDL2/FrontPage
 * 
 * @param 
 */


void SDL_ExitWithError(const char *message);
void Create_Window(SDL_Window *win, SDL_Renderer *rend);
void initSDL();
void doInput();
void prepareScene();
void presentScene();
void cleanup();

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
} App;

App app;

int main(int argc, char **argv)
{
    SDL_version nb;
    SDL_VERSION(&nb);
    printf("Bienvenue sur la SDL %d.%d.%d\n", nb.major, nb.minor, nb.patch);

    SDL_bool program_launched = SDL_TRUE;

    memset(&app, 0, sizeof(App));

    initSDL();
    atexit(cleanup);



    while (program_launched)
    {
        prepareScene();

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


void SDL_ExitWithError(const char *message)
{
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

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