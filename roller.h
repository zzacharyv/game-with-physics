#ifndef ROLLER_H_
#define ROLLER_H_

#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include "collision.h"
#include "draw.h"
#include "ltexture.h"

class Roller {
    private:
    int posx, posy, radius;
    double angle, speed;
    LTexture roller_texture;
    
    public:
        Roller();
        void render(SDL_Renderer *, SDL_Rect);
        void update(int frame, int SCREEN_HEIGHT, int SCREEN_WIDTH, std::vector<std::vector<int>> current_map, std::vector<std::vector<int>> map);
        bool loadMedia(SDL_Renderer *);
};

#endif