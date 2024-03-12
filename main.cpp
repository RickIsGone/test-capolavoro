#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h> 
#include <SDL_main.h>
#include <SDL_mixer.h>

#include "classes.h"

int main(int argc,char* argv[]){
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    game g;

    g.save();
    
    SDL_Quit();
    TTF_Quit();
    Mix_Quit();
    return EXIT_SUCCESS;
}