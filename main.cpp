#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h> 
#include <SDL_main.h>
#include <SDL_mixer.h>
#include <ctime>

#include "classes.h"

int main(int argc,char* argv[]){
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    srand(time(0));
    
    game g;
    Mouse mouse;
    TTF_Font* font = TTF_OpenFont("calibri.ttf", 30);

    g.load();
    g.initialize();

    do{
        g.deltaTime=g.getDetaTime();

        mouse.update();
        if(mouse.leftButton) g.player.shoot();

        while (SDL_PollEvent(&g.event)){
            g.events();
           
        }
        g.player.gun.angle=atan2(mouse.y - g.player.hitbox.y-50, mouse.x - g.player.hitbox.x - 20)*180/M_PI;
        
        if(g.currentTime-g.timeSinceLastSpawn>1500){
            g.timeSinceLastSpawn=g.currentTime;
            g.spawn();
        }

        g.move();

        g.draw(mouse.x>g.player.hitbox.x + 20,font);
        
    }while(!g.quit);
    g.save();
    
    SDL_Quit();
    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    return EXIT_SUCCESS;
}