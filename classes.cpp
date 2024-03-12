#include <fstream>
#include "classes.h"

#define BULLET_SPEED 2000
#define PLAYER_SPEED 500

void game::save(){
    std::ofstream file("saveFile.rktd");
    file<<timeSurvived<<"\n";
    file<<zombieKilled;

    file.close();
}

void game::events(){
    switch(event.type){  
        case SDL_QUIT:
            quit=1;
            break;
    }
    player.move();
}

void game::draw(){

    SDL_SetRenderDrawColor(renderer,255,0,0,255);
    SDL_RenderDrawRect(renderer,&player.hitbox);
    SDL_RenderCopyEx(renderer, player.texture, NULL, &player.hitbox, player.angle, NULL, SDL_FLIP_NONE);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);

    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
}

void game::Player::shoot(){
    // sin(angle);
    // cos(angle);   per stabilire le proporzioni della velocita del proiettile in e y 
}

void game::Player::move(){
    const Uint8* key = SDL_GetKeyboardState(NULL);
    
    if(key[SDL_SCANCODE_W]);
    if(key[SDL_SCANCODE_A]);
    if(key[SDL_SCANCODE_S]);
    if(key[SDL_SCANCODE_D]);
    if(key[SDL_SCANCODE_R]);
}

void game::initialize(){
    player.texture = IMG_LoadTexture(renderer, "ak47.png");
    if (!player.texture) std::cerr <<"player texture not loaded: "<< SDL_GetError();
    
    player.health=3;
    player.angle=0;
    player.hitbox={920,500,80,80};
}

void Mouse::update(){
    Uint32 buttons = SDL_GetMouseState(&x, &y);
    leftButton = (buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0;
    
}