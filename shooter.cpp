#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include "draw.cpp"

using namespace std;

struct Projectile {
    int posx,posy;
    int radius;
    double speed;
};

class Shooter {
    int posx, posy;
    vector<Projectile> projectiles = {};
    
    void shoot();
    public:
        Shooter();
        void render(SDL_Renderer *);
        void add_projectile();
        void update();
};

Shooter::Shooter() {
    posx = 100;
    posy = 100;
    projectiles = {{200,200,5,2.0}};
}

void Shooter::render(SDL_Renderer * gRenderer) {
    SDL_RenderFillCircle(gRenderer, posx, posy, 20);
               
    for(Projectile p: projectiles) {
         
            SDL_RenderFillCircle(gRenderer, p.posx, p.posy, p.radius);

    }
}

void Shooter::add_projectile() {
    projectiles.insert(projectiles.end(),{posx,posy,5,2.0});
}

void Shooter::update() {
    for(int i=0; i<projectiles.size(); ++i) {
       projectiles[i].posx += projectiles[i].speed;
        projectiles[i].posy += projectiles[i].speed;
    }
}