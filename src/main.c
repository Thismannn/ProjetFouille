#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <string.h>




int main(int argc, char** argv)
{
    int quit = 0;
    SDL_Event event;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window * window = SDL_CreateWindow("L'algorithme PAM",100, 100, 400, 400, 0);


	int n=50;//points
	int k=6;//groupes
	if(k>n)exit(0);

    pam(n,k,window);

    while (!quit)
    {
        SDL_WaitEvent(&event);

        switch (event.type)
        {
        case SDL_QUIT:
            quit = 1;
            break;
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}