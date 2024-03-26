#include <fstream>
#include "classes.h"
#include <SDL.h>

#include "sdl_functions.hpp"

static const SDL_Point center={960,540};

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

float game::getDetaTime(){
    currentTime = SDL_GetTicks(); 
    float deltaTime = (currentTime - previousTime) / 1000.0f; 
    previousTime = currentTime; 
    return deltaTime;
}

void game::events(){
    switch(event.type){  
        case SDL_QUIT:
            quit=1;
            break;
    }
    
}

void game::move(){
    const Uint8* key = SDL_GetKeyboardState(NULL);
    
    if(key[SDL_SCANCODE_W]){
        player.hitbox.y -= PLAYER_SPEED * deltaTime;
        player.gun.textureTarget.y -= PLAYER_SPEED * deltaTime;
    } 
    if(key[SDL_SCANCODE_A]){
        player.hitbox.x -= PLAYER_SPEED * deltaTime;
        player.gun.textureTarget.x -= PLAYER_SPEED * deltaTime;
    } 
    if(key[SDL_SCANCODE_S]){
        player.hitbox.y += PLAYER_SPEED * deltaTime;
        player.gun.textureTarget.y += PLAYER_SPEED * deltaTime;
    } 
    if(key[SDL_SCANCODE_D]){
        player.hitbox.x += PLAYER_SPEED * deltaTime;
        player.gun.textureTarget.x += PLAYER_SPEED * deltaTime;
    } 

    
    for(auto it = player.gun.bulletsAlive.begin(); it != player.gun.bulletsAlive.end();++it) {
        Bullets &bullet = *it;
        if(!it->isAlive) continue;
        bullet.hitbox.x += bullet.xSpeed * BULLET_SPEED * deltaTime;
        bullet.hitbox.y += bullet.ySpeed * BULLET_SPEED * deltaTime;
        
        for(auto current=zombieAlive.begin();current!=zombieAlive.end();++current){
            Zombies &zombie = *current;

            if(!current->isAlive) continue;
            if(SDL_HasIntersectionF(&zombie.hitbox, &bullet.hitbox) && it->isAlive){
                it->isAlive = 0;
                --zombie.health;
                if(zombie.health == 0 ) {
                    it->isAlive = 0;
                    current->isAlive = 0;
                    continue; 
                }
            }

        }
        if((bullet.hitbox.x < -10 || bullet.hitbox.x > 1920 || bullet.hitbox.y < -10 || bullet.hitbox.y > 1080)) {
            it->isAlive = 0;
        } 
    }
    std::erase_if(player.gun.bulletsAlive, [](const Bullets& bullet) { return !bullet.isAlive; });
    std::erase_if(zombieAlive, [](const Zombies& zombie) { return !zombie.isAlive; });
}

void game::draw(bool right, TTF_Font* font){

    SDL_SetRenderDrawColor(renderer,255,255,255,255);

    sdl::v_quick_text("", zombieAlive.size(), 255, 255, 255, 20, renderer, font);

    for(Bullets bullet:player.gun.bulletsAlive){
        SDL_RenderFillRectF(renderer,&bullet.hitbox);
    }
    for(Zombies zombie:zombieAlive){
        SDL_RenderFillRectF(renderer,&zombie.hitbox);
    }

    SDL_RenderDrawRectF(renderer,&player.hitbox);
    SDL_RenderCopyExF(renderer, player.texture, NULL, &player.hitbox,NULL, NULL, SDL_FLIP_NONE);
    if(right) SDL_RenderCopyExF(renderer, player.gun.texture, NULL, &player.gun.textureTarget, player.gun.angle, NULL, SDL_FLIP_NONE);
    else SDL_RenderCopyExF(renderer, player.gun.texture, NULL, &player.gun.textureTarget, player.gun.angle, NULL, SDL_FLIP_VERTICAL);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);

    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
}

void game::spawn(){
    Zombies zombie;
    zombie.health=3;
    zombie.hitbox.x=rand()%2320-200;
    zombie.hitbox.y=rand()%1480-200;
    zombie.hitbox.w=40;
    zombie.hitbox.h=100;
    zombie.isAlive=1;
    zombieAlive.push_back(zombie);
}

void game::Player::shoot(){
    Bullets bullet={cos(gun.angle*M_PI/180),sin(gun.angle*M_PI/180),{hitbox.x+20.0,hitbox.y+45.0,10,10},1};
    gun.bulletsAlive.push_back(bullet);
}


void game::initialize(){
    player.texture = IMG_LoadTexture(renderer, "player.png");
    if (!player.texture) std::cout <<"player texture not loaded: "<< SDL_GetError();
    player.gun.texture = IMG_LoadTexture(renderer, "ak47.png");
    if (!player.gun.texture) std::cout <<"gun texture not loaded: "<< SDL_GetError();

    player.gun.textureTarget={900,527,120,46};
    player.health=3;
    player.gun.angle=0;
    player.hitbox={940,490,40,100};
}

void Mouse::update(){
    Uint32 buttons = SDL_GetMouseState(&x, &y);
    leftButton = (buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0;
}
