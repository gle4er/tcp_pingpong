#include <iostream>
#include <SDL2/SDL.h> 

#include "../headers/gfx.h"
#include "../headers/ball.h"

int main()
{
    initGfx(800, 600);
	SDL_Event e;
    bool quit = false;

    Ball *ball = new Ball();

	while(!quit) {
		while(SDL_PollEvent( &e ) != 0) {
			if(e.type == SDL_QUIT) 
				quit = true;
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_q)
                    quit = true;
            }
        }
        ball->move();
        draw(ball);
    }
    clear();
    return 0;
}
