#include "roller.h"

Roller::Roller()
{
    posx = 800;
    posy = 100;
    angle = 0.0;
    speed = 1.0;
    radius = 20;
}


void Roller::render(SDL_Renderer *gRenderer, SDL_Rect player)
{
    if (roller_texture.getTexture() == NULL)
    {
        loadMedia(gRenderer);
    }

    SDL_SetRenderDrawColor(gRenderer,255,0,0,255);
    SDL_RenderFillCircle(gRenderer, posx, posy, radius);

    // SDL_RenderDrawLine(gRenderer, posx,posy,player.x+20,player.y);
    // SDL_Point center = {0, 20};
        // shooter_texture.render(posx, posy, gRenderer, &la);
    SDL_Rect la = {100, 100, radius*2, radius*2};
    roller_texture.render(posx, posy, gRenderer, &la, -angle);

}

// void Roller::update(SDL_Rect player, int SCREEN_WIDTH, int SCREEN_HEIGHT)
// {

// }

bool Roller::loadMedia(SDL_Renderer *gRenderer)
{
    // Loading success flag
    bool success = true;

    // Load sprite sheet textures
    // Ground Collision
    if (!roller_texture.loadFromFile("media/roller/poop.jpg", gRenderer))
    {
        printf("Failed to load shooter texture!\n");
        success = false;
    }
    return success;
}

void Roller::update(int frame, int SCREEN_HEIGHT, int SCREEN_WIDTH, std::vector<std::vector<int>> current_map, std::vector<std::vector<int>> map) {
    angle -= speed;
    if (angle <  -360) {
        angle = static_cast<int>(angle)%-360;
    }


    posx+=speed;
    posy = (SCREEN_HEIGHT / map.size())*(current_map.size()-1)-2*radius;
        // int w_unit = SCREEN_WIDTH / (map[0].size());
        // int h_unit = SCREEN_HEIGHT / map.size();
        // int width = current_map[0].size();
        // int height = current_map.size();

        double n_posx = 4*speed;

    if(posx > SCREEN_WIDTH) {
        posx = SCREEN_WIDTH-radius*2;
        speed = -speed;
    }
    if(posx < 0) {
        posx = 0;
        speed = -speed;
    }
    if(posy > SCREEN_HEIGHT) {
        posy = SCREEN_HEIGHT-radius*2;
    }
    if(posy < 0) {
        posy = 0;
    }
   
}
