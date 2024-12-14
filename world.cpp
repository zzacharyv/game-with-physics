#include <iostream>
#include <vector>
#include <set>
#include <SDL2/SDL.h>
#include "levels/level.cpp"
#include "cell.cpp"
#include "animation_cubit.cpp"
#include <algorithm>
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
    int getX()
    {
        return x;
    }
    int getY()
    {
        return y;
    }
    int getFrame()
    {
        return frame;
    }
    void setFrame(int frame) {
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
    void add_ground_collision(Unit);

private:
    vector<Unit *> ground_collisions;
};

World::World()
{
    ground_collisions = {};
}

void World::render(SDL_Renderer *gRenderer, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    SDL_Rect ground = {0, 288, SCREEN_WIDTH, SCREEN_HEIGHT - 288};
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderFillRect(gRenderer, &ground);
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

// struct Foo
// {
//   int i;
// };

// bool operator==(const Foo& lhs, const Foo& rhs) { return lhs.i == rhs.i; }

// std::vector<Foo*> v = ....;

// Foo f{42};

// std::find_if(v.begin(), v.end(), [&f](const Foo* p) { return *p == f; });


void World::add_ground_collision(Unit unit)
{
    // if (ground_collisions.count(unit) == 0)
    // {
        // int cnt = count(ground_collisions.begin(), ground_collisions.end(), unit);
        // vector<Unit *> poop;

        auto result = std::find_if(ground_collisions.begin(), ground_collisions.end(), [unit](const Unit* p) { return *p == unit; });
        if (result != ground_collisions.end()) {
                        cout << "in vector" << endl;


        } else {
            cout << "not in vector" << endl;
ground_collisions.push_back(&unit);
        }
        // Unit* instance = std::find_if(ground_collisions.begin(), ground_collisions.end(), [unit](const Unit* p) { return *p == *unit; });
        // if(cnt == 0) {
        //                 cout << ground_collisions.size() << endl;

        //     ground_collisions.push_back(unit);

        // }
                            cout << ground_collisions.size() << endl;// found it!


        // ground_collisions.insert(unit);
    // }

}

void World::render_ground_collision(SDL_Renderer *gRenderer, int frame, int xpos, int ypos)
{
    Unit l = Unit(xpos, ypos + 40, 0);
    add_ground_collision(l);
    for (Unit * unit : ground_collisions)
    {
        SDL_Rect player = {(*unit).getX(), (*unit).getY(), 40, 40};
        SDL_Rect *currentClip = &ground_collision_sprite_clips[(*unit).getFrame()];
        ground_collision_sprite_sheet.render(0, 0, player, gRenderer, currentClip);


        currentClip = &ground_collision_sprite_clips[1];
        SDL_Rect renderQuad = {xpos,ypos+40, 40, 40};
    //     // walkingRightPlayerSpriteSheetTexture.setColor(color[0], color[1], color[2]);
        ground_collision_sprite_sheet.render(0, 0, renderQuad, gRenderer, currentClip);

        if((*unit).getFrame() != 3) {
            (*unit).setFrame((*unit).getFrame()+1);

        }
    }
    // cout << ++coount << endl;
    // SDL_Rect *currentClip = &ground_collision_sprite_clips[1];
    //     SDL_Rect renderQuad = {xpos,ypos+40, 40, 40};
    //     // walkingRightPlayerSpriteSheetTexture.setColor(color[0], color[1], color[2]);
    //     ground_collision_sprite_sheet.render(0, 0, renderQuad, gRenderer, currentClip);
}

void World ::poo(SDL_Renderer *gRenderer)
{
    for (auto animation_cubit : this->ground_collisions) // access by reference to avoid copying
    {
    }
}