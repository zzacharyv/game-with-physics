#ifndef LEVEL_H_
#define LEVEL_H_

#include "shooter.h"
#include "roller.h"
#include "ltimer.h"
#include <string>
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

class Level
{
    Shooter shooter;
    Roller roller;
    Uint32 shooter_update_time = 0;

public:
    void render(SDL_Renderer *, SDL_Rect);
    Level(std::string);
    void update(int, LTimer *, SDL_Rect, int, int, std::vector<std::vector<int>>,std::vector<std::vector<int>>);
};

#endif
