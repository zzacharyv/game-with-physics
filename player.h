
#ifndef PLAYER_H_
#define PLAYER_H_

#include <SDL2/SDL.h>
#include <array>
#include <iostream>
#include <stdexcept>
#include "world.h"

class Player
{
private:
    int posx;
    int posy;
    double physics_posx;
    double physics_posy;
    double x_velocity;
    double y_velocity;
    double gravity = 1.0;
    bool on_ground = true;

public:
    int getPosx();
    int getPosy();
    double getVelocityX();
    double getVelocityY();
    bool isOnGround();
    void setPosx(int);
    void setPosy(int);
    void setVelocityX(double);
    void setVelocityY(double);
    Player();
    void update(SDL_Renderer *, int, World *, int, int, int,std::vector<std::vector<int>>,std::vector<std::vector<int>>, bool *);
    void render(SDL_Renderer *gRenderer, int, int, int);
    void ground_collision();
    void in_air();
    int pre_jump_pos = 200;
    bool falling = false;

};

#endif
