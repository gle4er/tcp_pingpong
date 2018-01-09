#include <vector>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../headers/gfx.h"
#include "../headers/client.h"
#include "../headers/settings.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

TTF_Font* font = NULL;
SDL_Color white = {255, 255, 255, 255};

void initGfx()
{
	SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	gWindow = SDL_CreateWindow("kurs", SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 
            SDL_WINDOW_SHOWN );
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
    font = TTF_OpenFont("/usr/share/fonts/TTF/Ubuntu-R.ttf", 90);
}

void draw(std::vector<Object *> *objects, int *score)
{
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gRenderer);
    circleRGBA(gRenderer, objects->at(BALL)->getX(), objects->at(BALL)->getY(), 
            SIZE_BALL, 0xFF, 0xFF, 0xFF, 0xFF);
    for (int i = 0; i < 2; i++) {
        static int mult = -1;
        int x1 = objects->at(i)->getX() - SIZE_PANE_X * mult;
        int x2 = objects->at(i)->getX();
        int y1 = objects->at(i)->getY() - SIZE_PANE_Y;
        int y2 = objects->at(i)->getY() + SIZE_PANE_Y;
        rectangleRGBA(gRenderer, x1, y1, x2, y2, 0xFF, 0xFF, 0xFF, 0xFF);
        mult *= -1;
    }

    char *msg = (char *) malloc(sizeof(*msg) * 20);
    sprintf(msg, "%d - %d", score[0], score[1]);
    SDL_Surface* msgSurf = TTF_RenderText_Blended(font, msg, white);
    SDL_Texture* msgTexture = SDL_CreateTextureFromSurface(gRenderer, msgSurf);
    SDL_Rect msgRect = { SCREEN_WIDTH / 2 - 50, 0, 100, 75 };
    SDL_RenderCopy(gRenderer, msgTexture, NULL, &msgRect);

	SDL_RenderPresent(gRenderer);

    SDL_DestroyTexture(msgTexture);
    SDL_FreeSurface(msgSurf);
    free(msg);

    SDL_Delay(32);
}

void clear()
{
    TTF_CloseFont(font);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}
