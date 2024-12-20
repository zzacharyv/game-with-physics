#include <iostream>
#include <vector>
#include <set>
#include <SDL2/SDL.h>
#include <algorithm>
#include "ltexture.cpp"
#include "draw.cpp"
using namespace std;

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

class Level_Select
{
public:
    int levels[7] = {1, 2, 5, 10, 20, 50, 100};
    LTexture *level_icons[7] = {&one_dollar_small, &two_dollar_small, &five_dollar_small, &ten_dollar_small, &twenty_dollar_small, &fifty_dollar_small, &one_hundred_dollar_small};
    Level_Select() {};
};

class World
{
private:
    vector<Unit *> ground_collisions;
    SDL_Rect player;

public:
    World();
    void update(SDL_Rect);
    void render(SDL_Renderer *, int, int, int, vector<vector<int>>, vector<vector<int>>, string);
    void render_ground_collision(SDL_Renderer *, int, int, int, int);
    bool loadMedia(SDL_Renderer *);
    void add_ground_collision(int, int);
    bool box_collision(SDL_Rect, SDL_Rect);
};

World::World()
{
    ground_collisions = {};
}

void World::render(SDL_Renderer *gRenderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, int offset, vector<vector<int>> current_map, vector<vector<int>> map, string level)
{
    // for(vector<int> r : *current_map) {
    //             for(int c : r) {
    //                 cout << c << " ";
    //             }
    //             cout << endl;
    //         }
    // background
    SDL_Rect bg = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    one_dollar.render(0, 0, bg, gRenderer);

   

    // tilemap
    int i = map[0][0];
    int w_unit = SCREEN_WIDTH / (map[0].size());

    int h_unit = SCREEN_HEIGHT / (map.size());
    for (int col = 0; col < current_map[0].size(); ++col)
    {
        for (int row = 0; row < current_map.size(); ++row)
        {
            if (current_map[row][col] == 1)
            {
                SDL_Rect ground = {col * w_unit - offset + 2, row * h_unit, w_unit - 4, h_unit};
                // SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
                // SDL_RenderFillRect(gRenderer, &ground);
                SDL_SetRenderDrawColor(gRenderer, 55, 54, 50, 255);
                SDL_Rect border = {col * w_unit - offset, row * h_unit - 3, w_unit, h_unit + 3};
                SDL_RenderFillRect(gRenderer, &border);

                block.render(0, 0, ground, gRenderer);
            }
        }
    }

    if ( level == "home") {
        // eyes
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
        double p = 15.0 / static_cast<double>(SCREEN_WIDTH);
        double x = p * static_cast<double>(player.x);

        SDL_RenderFillCircle(gRenderer, 606 + x, 237, 4);
        SDL_RenderFillCircle(gRenderer, 647 + x, 237, 4);

        SDL_Rect choose_level = {836,234,120,120};
        SDL_SetRenderDrawColor(gRenderer, 13, 146, 81, 255);

        SDL_RenderFillRect(gRenderer, &choose_level);


    }
     else if (level == "level select")
    {
         // eyes
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
        double p = 15.0 / static_cast<double>(SCREEN_WIDTH);
        double x = p * static_cast<double>(player.x);

        SDL_RenderFillCircle(gRenderer, 606 + x, 237, 4);
        SDL_RenderFillCircle(gRenderer, 647 + x, 237, 4);
        
        for (int i = 0; i < 7; ++i)
        {
            SDL_Rect one = {((i) * 304 + 150 * (1 + i)) - offset, SCREEN_HEIGHT / 3, 304, 130};
            SDL_Rect one_outline = one;
            one_outline.x -= 10;
            one_outline.w += 20;
            one_outline.y -= 10;
            one_outline.h += 20;
            SDL_SetRenderDrawColor(gRenderer, 13, 146, 81, 255);

            SDL_RenderFillRect(gRenderer, &one_outline);
            Level_Select l = Level_Select();
            LTexture *poo = l.level_icons[0];
            (*(l.level_icons[1])).render(0, 0, one, gRenderer);
        }
    }
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
    if (!one_dollar.loadFromFile("media/one dollar/front.jpeg", gRenderer))
    {
        printf("Failed to load dollar front texture!\n");
        success = false;
    }
    if (!one_dollar_small.loadFromFile("media/one dollar/front_small.jpeg", gRenderer))
    {
        printf("Failed to load dollar front small texture!\n");
        success = false;
    }
    if (!two_dollar_small.loadFromFile("media/two dollar/front_small.jpg", gRenderer))
    {
        printf("Failed to load two dollar front texture!\n");
        success = false;
    }
    if (!block.loadFromFile("media/level/block_1.jpeg", gRenderer))
    {
        printf("Failed to load block texture!\n");
        success = false;
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

void World::render_ground_collision(SDL_Renderer *gRenderer, int frame, int xpos, int ypos, int offset)
{
    for (int j = 0; j < ground_collisions.size(); j++)
    {
        Unit *i = ground_collisions[j];
        SDL_Rect *currentClip = &ground_collision_sprite_clips[(*i).getFrame()];
        SDL_Rect renderQuad = {(*i).getX() - offset, (*i).getY(), 40, 40};
        ground_collision_sprite_sheet.render(0, 0, renderQuad, gRenderer, currentClip);
        if ((*i).getFrame() != 3)
        {
            if (frame % 15 == 0)
            {
                (*i).setFrame((*i).getFrame() + 1);
            }
        }
        else
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

void World::update(SDL_Rect player)
{
    this->player = player;
}

bool World::box_collision(SDL_Rect rect1, SDL_Rect rect2)
{
    if (
        rect1.x < rect2.x + rect2.w &&
        rect1.x + rect1.w > rect2.x &&
        rect1.y < rect2.y + rect2.h &&
        rect1.y + rect1.h > rect2.y)
    {
        return true;
    }
    else
    {
        return false;
    }
}
