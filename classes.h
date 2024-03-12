#pragma once
#include <SDL.h>
#include <iostream>
#include <unordered_map>
#include <vector>


class game{
    SDL_Window *window=SDL_CreateWindow("capolavoro",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,1920,1080,SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Event event;
    SDL_Event WindowEvent;

public:

    void save();
};