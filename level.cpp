#include "shooter.cpp"
#include "ltimer.cpp"
#include <string>
#include <iostream>

using namespace std;

class Level
{
    vector<Shooter> shooters;
    Uint32 shooter_update_time = 0;

public:
    void render(SDL_Renderer *);
    Level(string);
    void update(int, LTimer *);
};

Level::Level(string level)
{
    if (level == "one")
    {
        shooters.push_back(Shooter());
        // for(Shooter s: shooters) {
        //     s.add_projectile();
        // }
    }
}

void Level::render(SDL_Renderer *gRenderer)
{
    for (Shooter s : shooters)
    {
        s.render(gRenderer);
    }
}

void Level::update(int frame, LTimer *shooterTimer)
{
    Uint32 ticks = (*shooterTimer).getTicks() / 1000;
    if (shooter_update_time + 0.25 < (*shooterTimer).getTicks() / 1000)
    {
        shooter_update_time = ticks;

        for (int i = 0; i < shooters.size(); ++i)
        {

            shooters[i].add_projectile();
        }
    }

    for (int i = 0; i < shooters.size(); ++i)
    {
        shooters[i].update();
    }
}
