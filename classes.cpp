#include <fstream>
#include "classes.h"

#define BULLET_SPEED 2000
#define PLAYER_SPEED 500

static SDL_Point center={906,540};

void game::save(){
    std::ofstream file("saveFile.rktd");
    file<<timeSurvived<<"\n";
    file<<zombieKilled;

    file.close();
}

void game::load(){
    std::ifstream file("saveFile.rktd");
    file>>timeSurvived;
    file>>zombieKilled;

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

void game::draw(bool right){

    SDL_SetRenderDrawColor(renderer,255,0,0,255);
    SDL_RenderDrawRect(renderer,&player.hitbox);
    SDL_RenderCopyEx(renderer, player.texture, NULL, &player.hitbox,NULL, NULL, SDL_FLIP_NONE);

    for(Bullets bullet:player.gun.bullets){
        SDL_RenderFillRect(renderer,&bullet.hitbox);
    }
    
    if(right) SDL_RenderCopyEx(renderer, player.gun.texture, NULL, &player.gun.textureTarget, player.gun.angle, NULL, SDL_FLIP_NONE);
    else SDL_RenderCopyEx(renderer, player.gun.texture, NULL, &player.gun.textureTarget, player.gun.angle, NULL, SDL_FLIP_VERTICAL);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);

    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
}

void game::Player::Gun::shoot(){
    Bullets bullet={-cos(angle*M_PI/180),-sin(angle*M_PI/180),{955,535,10,10}};
    bullets.push_back(bullet);   
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
    player.texture = IMG_LoadTexture(renderer, "player.png");
    if (!player.texture) std::cerr <<"player texture not loaded: "<< SDL_GetError();
    player.gun.texture = IMG_LoadTexture(renderer, "ak47.png");
    if (!player.gun.texture) std::cerr <<"gun texture not loaded: "<< SDL_GetError();

    player.gun.textureTarget={900,517,120,46};
    player.health=3;
    player.gun.angle=0;
    player.hitbox={940,490,40,100};
}

void Mouse::update(){
    Uint32 buttons = SDL_GetMouseState(&x, &y);
    leftButton = (buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0;
}