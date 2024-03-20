#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>

#define BULLET_SPEED 6500.0
#define PLAYER_SPEED 2000.0


struct Bullets{
    double xSpeed;
    double ySpeed;
    SDL_FRect hitbox;
};

class game{
    SDL_Window *window=SDL_CreateWindow("capolavoro",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,1920,1080,SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Event WindowEvent;

public:

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    bool quit=0;
    SDL_Event event;
    void save();
    void load();
    void events();
    void move();
    void draw(bool right, TTF_Font* font);
    int zombieKilled=0,timeSurvived=0;
    
    Uint32 currentTime = 0;
    Uint32 previousTime = 0;
    float deltaTime=0;
    float getDetaTime();

    struct Player{
        int health;
        SDL_Rect hitbox;
        SDL_Texture* texture; 
        
        struct Gun{
            SDL_Texture* texture;
            SDL_Rect textureTarget;
            double angle;
            std::vector<Bullets>bulletsAlive;
            void shoot();
        }gun;
    }player;

    void initialize();
}extern g;

struct Mouse{
    int x, y; 
    bool leftButton=0;
    void update();
}extern mouse;