#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "levels/level.cpp"
#include "cell.cpp"
#include "animation_cubit.cpp"
using namespace std;

SDL_Rect ground_collision_sprite_clips[4];
LTexture ground_collision_sprite_sheet;

class World
{
public:
    World();
    void render(SDL_Renderer *, int, int);
    void render_ground_collision(SDL_Renderer *, int, int, int);
    bool loadMedia(SDL_Renderer *);
    void poo(SDL_Renderer *);
        vector<int> ground_collisions;


private:
};

World::World()
{

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

static int coount = 0;

void World::render_ground_collision(SDL_Renderer *gRenderer, int frame, int xpos, int ypos)
{

    this->ground_collisions.push_back(frame);


    cout << ground_collisions.size() << endl;
    cout << ++coount << endl;
    // SDL_Rect *currentClip = &ground_collision_sprite_clips[1];
    //     SDL_Rect renderQuad = {xpos,ypos+40, 40, 40};
    //     // walkingRightPlayerSpriteSheetTexture.setColor(color[0], color[1], color[2]);
    //     ground_collision_sprite_sheet.render(0, 0, renderQuad, gRenderer, currentClip);
        SDL_Rect player = {xpos,ypos+40,40,40};
        SDL_SetRenderDrawColor(gRenderer, 255,0,0,255);
        SDL_RenderDrawRect(gRenderer,&player);

}

void World :: poo(SDL_Renderer *gRenderer) {
    for (auto animation_cubit : this->ground_collisions) // access by reference to avoid copying
    {
        if(animation_cubit != NULL) {
            
        // }
        // int f = animation_cubit->getFrame();
        // SDL_Rect *currentClip = &ground_collision_sprite_clips[f];
        // SDL_Rect renderQuad = {animation_cubit->getX(), animation_cubit->getY(), 40, 40};
        // // walkingRightPlayerSpriteSheetTexture.setColor(color[0], color[1], color[2]);
        // ground_collision_sprite_sheet.render(0, 0, renderQuad, gRenderer, currentClip);

        // if ( f < 3 ) {
        //     cout << animation_cubit->getFrame() << endl;
        //     animation_cubit->setFrame(f+1);
        //                 cout << animation_cubit->getFrame() << endl;

        }
    }
}