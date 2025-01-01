
#ifndef COLLISION_H_
#define COLLISION_H_

#include <SDL2/SDL.h>
#include <cmath>

    bool box_collision(SDL_Rect rect1, SDL_Rect rect2);
    bool circle_box_collision(int,int,int, SDL_Rect rect);

#endif

