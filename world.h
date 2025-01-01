#ifndef WORLD_H_
#define WORLD_H_

#include <iostream>
#include <vector>
#include <set>
#include <SDL2/SDL.h>
#include <algorithm>
#include "ltexture.h"
#include "level.h"


class Unit
{
    int x;
    int y;
    int frame;

public:
    Unit(int x, int y, int frame)
    {
        this->x = x;
        this->y = y;
        this->frame = frame;
    }
    bool operator==(const Unit &right) const
    {
        return (x == right.x) && (y == right.y);
    }
    bool operator>(const Unit &right) const
    {
        return false;
    }
    bool operator<(const Unit &right) const
    {

        return true;
    }
    int getX() const
    {
        return x;
    }
    int getY() const
    {
        return y;
    }
    int getFrame() const
    {
        return frame;
    }
    void setFrame(int frame)
    {
        this->frame = frame;
    }
};

struct LevelSelect
{
    std::string title;
    bool unlocked;
    SDL_Rect area;
    LTexture *icon;
};

class World
{
private:
SDL_Rect ground_collision_sprite_clips[4];
LTexture ground_collision_sprite_sheet;

LTexture one_dollar;
LTexture one_dollar_small;
LTexture two_dollar_small;
LTexture five_dollar_small;
LTexture ten_dollar_small;
LTexture twenty_dollar_small;
LTexture fifty_dollar_small;
LTexture one_hundred_dollar_small;

LTexture block;

    std::vector<Unit *> ground_collisions;
    SDL_Rect player;
    LevelSelect levels[7] = {{"one", true, {}, &one_dollar_small},
                             {"two", false, {}, &two_dollar_small},
                             {"five", false, {}, &five_dollar_small},
                             {"ten", false, {}, &ten_dollar_small},
                             {"twenty", false, {}, &twenty_dollar_small},
                             {"fifty", false, {}, &fifty_dollar_small},
                             {"one hundred", false, {}, &one_hundred_dollar_small}};

public:
    World();
    void update(SDL_Rect);
    void render(SDL_Renderer *, int, int, int, std::vector<std::vector<int>>, std::vector<std::vector<int>>, std::string *);
    void render_ground_collision(SDL_Renderer *, int, int, int, int);
    bool loadMedia(SDL_Renderer *);
    void add_ground_collision(int, int);
};

#endif