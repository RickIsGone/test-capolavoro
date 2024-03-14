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
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    game g;
    Mouse mouse;
    
    g.load();
    g.initialize();

    do{
        g.deltaTime=g.getDetaTime();

        mouse.update();
        if(mouse.leftButton) g.player.gun.shoot();

        while (SDL_PollEvent(&g.event)){
            g.events();
            g.player.gun.angle=atan2(540-mouse.y,960-mouse.x)*180/M_PI;
        }

        g.move();

        g.draw(mouse.x>960);  

    }while(!g.quit);
    g.save();

    SDL_Quit();
    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    return EXIT_SUCCESS;
}