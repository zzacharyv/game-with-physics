#include "world.h"


World::World()
{
    ground_collisions = {};
}

void World::render(SDL_Renderer *gRenderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, int offset, std::vector<std::vector<int>> current_map, std::vector<std::vector<int>> map, std::string *level)
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
    int y_offset=0;
    int i = map[0][0];
    int w_unit = SCREEN_WIDTH / (map[0].size());

    int h_unit = SCREEN_HEIGHT / (map.size());
    for (int col = 0; col < current_map[0].size(); ++col)
    {
        for (int row = 0; row < current_map.size(); ++row)
        {
            if (current_map[row][col] == 1)
            {
                SDL_Rect ground = {col * w_unit - offset + 2, row * h_unit-y_offset, w_unit - 4, h_unit};
                // SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
                // SDL_RenderFillRect(gRenderer, &ground);
                SDL_SetRenderDrawColor(gRenderer, 55, 54, 50, 255);
                SDL_Rect border = {col * w_unit - offset, row * h_unit - 3-y_offset, w_unit, h_unit + 3};
                SDL_RenderFillRect(gRenderer, &border);

                block.render(0, 0, ground, gRenderer);
            }
        }
    }

    if (*level == "home")
    {
        // eyes
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
        double p = 15.0 / static_cast<double>(SCREEN_WIDTH);
        double x = p * static_cast<double>(player.x);

        SDL_RenderFillCircle(gRenderer, 606 + x, 237, 4);
        SDL_RenderFillCircle(gRenderer, 647 + x, 237, 4);

        SDL_Rect play_button = {836, 234, 120, 120};
        SDL_SetRenderDrawColor(gRenderer, 13, 146, 81, 255);

        SDL_RenderFillRect(gRenderer, &play_button);

        if (box_collision(play_button, player))
        {
            *level = "level select";
        }
    }
    else if (*level == "level select")
    {
        // eyes
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
        double p = 15.0 / static_cast<double>(SCREEN_WIDTH);
        double x = p * static_cast<double>(player.x);

        SDL_RenderFillCircle(gRenderer, 606 + x, 237, 4);
        SDL_RenderFillCircle(gRenderer, 647 + x, 237, 4);

        for (int i = 0; i < 7; ++i)
        {
            levels[i].area = {((i) * 304 + 250 * (1 + i)) - offset, SCREEN_HEIGHT / 3, 304, 130};

            SDL_Rect outline = levels[i].area;
            outline.x -= 10;
            outline.w += 20;
            outline.y -= 10;
            outline.h += 20;
            SDL_SetRenderDrawColor(gRenderer, 13, 146, 81, 255);
            if(!levels[i].unlocked) {
                SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
            }

            SDL_RenderFillRect(gRenderer, &outline);
            (*levels[i].icon).render(0, 0, levels[i].area, gRenderer);

            if (box_collision(levels[i].area, player) && levels[i].unlocked == true)
            {
                *level = levels[i].title;
            }
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
        printf("Failed to load two dollar front small texture!\n");
        success = false;
    }
    if (!five_dollar_small.loadFromFile("media/five dollar/front_small.jpeg", gRenderer))
    {
        printf("Failed to load five dollar front small texture!\n");
        success = false;
    }
    if (!ten_dollar_small.loadFromFile("media/ten dollar/front_small.jpeg", gRenderer))
    {
        printf("Failed to load ten dollar front small texture!\n");
        success = false;
    }
    if (!twenty_dollar_small.loadFromFile("media/twenty dollar/front_small.jpeg", gRenderer))
    {
        printf("Failed to load twenty dollar front small texture!\n");
        success = false;
    }
    if (!fifty_dollar_small.loadFromFile("media/fifty dollar/front_small.jpeg", gRenderer))
    {
        printf("Failed to load fifty dollar front small texture!\n");
        success = false;
    }
    if (!one_hundred_dollar_small.loadFromFile("media/one hundred dollar/front_small.jpeg", gRenderer))
    {
        printf("Failed to load one hundred dollar front small texture!\n");
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
                std::vector<Unit *>::iterator nth = ground_collisions.begin() + j;
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
