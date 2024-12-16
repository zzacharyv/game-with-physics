#include <iostream>
#include <vector>
#include <set>
#include <SDL2/SDL.h>
#include "levels/level.cpp"
#include "cell.cpp"
#include <algorithm>
#include "map.cpp"
using namespace std;

SDL_Rect ground_collision_sprite_clips[4];
LTexture ground_collision_sprite_sheet;

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

class World
{
public:
    World();
    int coount = 0;
    void render(SDL_Renderer *, int, int);
    void render_ground_collision(SDL_Renderer *, int, int, int);
    bool loadMedia(SDL_Renderer *);
    void poo(SDL_Renderer *);
    void add_ground_collision(int, int);

private:
    vector<Unit *> ground_collisions;
};

World::World()
{
    ground_collisions = {};
}

void World::render(SDL_Renderer *gRenderer, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    int i = map[0][0];
    int w_unit = SCREEN_WIDTH/(sizeof(map[0])/sizeof(int));
    int h_unit = SCREEN_HEIGHT/(sizeof(map)/sizeof(map[0]));
    for(int col=0; col<sizeof(map[0])/sizeof(int); ++col) {
        for(int row=0; row<sizeof(map)/sizeof(map[0]); ++row) {
            if (map[row][col] == 1) {
                SDL_Rect ground = {col*w_unit, row*h_unit, w_unit, h_unit};
                // ground = {50,50,50,50};
                SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
                SDL_RenderFillRect(gRenderer, &ground);
                SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 255);
                SDL_RenderDrawRect(gRenderer, &ground);
            }
        }
    }
    // SDL_Rect ground = {0, 288, SCREEN_WIDTH, SCREEN_HEIGHT - 288};
    // SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    // SDL_RenderFillRect(gRenderer, &ground);
}

bool World::loadMedia(SDL_Renderer *gRenderer)
{
    // Loading success flag
    bool success = true;

    // Load sprite sheet textures
    // Ground Collision
    if (!ground_collision_sprite_sheet.loadFromFile("media/ground collision/ground_collision_v1.png", gRenderer))
    {
        printf("Failed to load idle animation texture!\n");
        success = false;
    }
    else
    {
        for (int i = 0; i < 4; ++i)
        {
            ground_collision_sprite_clips[i].x = i * 40;
            ground_collision_sprite_clips[i].y = 0;
            ground_collision_sprite_clips[i].w = 40;
            ground_collision_sprite_clips[i].h = 40;
        }
    }

    return success;
}

void World::add_ground_collision(int xpos, int ypos)
{
    Unit *unit_pointer = new Unit(xpos, ypos + 40, 0);
    auto result = std::find_if(ground_collisions.begin(), ground_collisions.end(), [unit_pointer](Unit *item)
                               { 
    if (item == nullptr) return false;
    return *item == *unit_pointer; });

    if (result != ground_collisions.end())
    {
        // Do nothing
    }
    else
    {
        ground_collisions.push_back(unit_pointer);
    }
}

void World::render_ground_collision(SDL_Renderer *gRenderer, int frame, int xpos, int ypos)
{
    for (int j = 0; j < ground_collisions.size(); j++)
    {
        Unit * i = ground_collisions[j];
        SDL_Rect *currentClip = &ground_collision_sprite_clips[(*i).getFrame()];
        SDL_Rect renderQuad = {(*i).getX(), (*i).getY(), 40, 40};
        ground_collision_sprite_sheet.render(0, 0, renderQuad, gRenderer, currentClip);
        if ((*i).getFrame() != 3)
        {
            if (frame % 15 == 0)
            {
                (*i).setFrame((*i).getFrame() + 1);
            }
        } else
            {
                if (frame == 15)
                {
                    vector<Unit *>::iterator nth = ground_collisions.begin() + j;
                    delete ground_collisions[j];
                    ground_collisions.erase(nth);
                }
            }
    }
}


void World ::poo(SDL_Renderer *gRenderer)
{
    for (auto animation_cubit : this->ground_collisions) // access by reference to avoid copying
    {
    }
}