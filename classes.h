#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <unordered_map>
#include <vector>


class game{
    SDL_Window *window=SDL_CreateWindow("capolavoro",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,1920,1080,SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Event WindowEvent;

public:

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    bool quit=0;
    SDL_Event event;
    void save();
    void events();
    void draw();
    
    struct Player{
        int health;
        double angle;
        SDL_Rect hitbox;
        SDL_Texture* texture; 
        void shoot();
        void move();
    }player;

    void initialize();
}extern g;