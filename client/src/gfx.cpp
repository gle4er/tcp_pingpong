#include <vector>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL.h>

#include "../headers/gfx.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

void initGfx(int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	gWindow = SDL_CreateWindow("kurs", SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 
            SDL_WINDOW_SHOWN );
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
}

void draw(Ball *ball)
{
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gRenderer);
    circleRGBA(gRenderer, ball->getX(), ball->getY(), 5, 
            0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderPresent( gRenderer );
    SDL_Delay(32);
}

void clear()
{
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}
