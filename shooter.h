#ifndef SHOOTER_H_
#define SHOOTER_H_

#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include "collision.h"
#include "draw.h"
#include "ltexture.h"

struct Line {
    // f(t) = A + t*N
    std::tuple<double, double> A, N;
};

struct Projectile {
    int posx,posy;
    int radius;
    double speed;
    Line line = {};
    bool operator==(const Projectile& rhs)
    {
        return posx == rhs.posx && posy == rhs.posy;
    }
};

class Shooter {
    private:
    int posx, posy, exitx,exity,width;
    double angle;
    std::vector<Projectile> projectiles;
    LTexture shooter_texture;
    
    void shoot();
    public:
        Shooter();
        void render(SDL_Renderer *, SDL_Rect);
        void add_projectile(SDL_Rect);
        void update(SDL_Rect, int, int);
        void remove_projectile(Projectile *);
        std::vector<Projectile *> get_projectiles();
        bool loadMedia(SDL_Renderer *);
};

#endif