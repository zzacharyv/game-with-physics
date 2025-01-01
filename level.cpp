#include "level.h"

Level::Level(std::string level)
{
    shooter = Shooter();
    // roller = Roller();
}

void Level::render(SDL_Renderer *gRenderer, SDL_Rect player)
{
    shooter.render(gRenderer, player);
    // roller.render(gRenderer, player);
}

void Level::update(int frame, LTimer *shooterTimer,  SDL_Rect player, int SCREEN_WIDTH, int SCREEN_HEIGHT,std::vector<std::vector<int>>current_map,std::vector<std::vector<int>>map)
{
    Uint32 ticks = (*shooterTimer).getTicks() / 1000;
    if (shooter_update_time + 0.25 < (*shooterTimer).getTicks() / 1000)
    {
        shooter_update_time = ticks;

            shooter.add_projectile(player);
    }
    shooter.update(player, SCREEN_WIDTH, SCREEN_HEIGHT);
        // roller.update(frame, SCREEN_HEIGHT, SCREEN_WIDTH, current_map,  map);
    
}
