#include <SDL2/SDL.h>
#include <array>
#include <iostream>
#include <stdexcept>
#include "world.cpp"
using namespace std;

class Player
{
private:
    int posx;
    int posy;
    double physics_posx;
    double physics_posy;
    double x_velocity;
    double y_velocity;
public:
    double gravity = 3.0;
    int color[3];
    int getPosx();
    int getPosy();
    double getVelocityX();
    double getVelocityY();
    void setPosx(int);
    void setPosy(int);
    void setVelocityX(double);
    void setVelocityY(double);
    Player();
    void update(SDL_Renderer *, int, World *, int, int, int);
    void updateVelocityX(double);
    void render(SDL_Renderer *gRenderer, int, int, int);

};

int Player::getPosx()
{
    return posx;
}

int Player::getPosy()
{
    return posy;
}

double Player::getVelocityX() {
    return x_velocity;
}

double Player::getVelocityY() {
    return y_velocity;
}

void Player::setPosx(int posx)
{
    this->posx = posx;
    physics_posx = posx;
}

void Player::setPosy(int posy)
{
    this->posy = posy;
}

void Player::setVelocityX(double x) {
    x_velocity = x;
}

void Player::setVelocityY(double y) {
    y_velocity = y;
}

Player::Player()
{
    posx = 250;
    posy = 0;
    physics_posx = 250;
    physics_posy = 0;
    x_velocity = 0.0;
    y_velocity = 0.0;
    color[0] = 0;
    color[1] = 255;
    color[2] = 255;
}

void Player::update(SDL_Renderer *gRenderer, int frame, World *world, int SCREEN_HEIGHT, int SCREEN_WIDTH, int offset)
{

    bool ground_collision = false;

    int w_unit = SCREEN_WIDTH / (sizeof(map[0]) / sizeof(int));
    int h_unit = SCREEN_HEIGHT / (sizeof(map) / sizeof(map[0]));
    int width = (sizeof(full_map[0]) / sizeof(int));
    int height = ((sizeof(map)) / sizeof(map[0]));

    double n_posx = physics_posx + x_velocity;
    double n_posy = physics_posy;

    int left = n_posx / w_unit;
    int right = (n_posx + 40) / w_unit;
    int top = n_posy / h_unit;
    int bottom = (n_posy + 40) / h_unit;

    int x = (n_posx + (40 / 2)) / w_unit;
    int y = (n_posy + (40 / 2)) / h_unit;

    // horizontal collision ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // left upper tile
    if (x - 1 >= 0 && x - 1 < width && y - 1 < height && y - 1 >= 0)
    {
        if (full_map[y - 1][x - 1] == 1)
        {
            if (n_posy < (y)*h_unit)
            {
                if (n_posx < (x)*w_unit)
                {
                    n_posx = (x)*w_unit;
                }
            }
        }
    }

    // left center tile
    if (x - 1 >= 0 && x - 1 < width && y < height && y >= 0)
    {
        if (full_map[y][x - 1] == 1)
        {
            if (n_posx < (x)*w_unit)
            {
                n_posx = (x)*w_unit;
            }
        }
    }

    // left lower tile
    if (x - 1 >= 0 && x - 1 < width && y + 1 < height && y + 1 >= 0)
    {
        if (full_map[y + 1][x - 1] == 1)
        {
            if (n_posy + 40 > (y + 1) * h_unit)
            {
                if (n_posx < (x)*w_unit)
                {
                    n_posx = (x)*w_unit;
                }
            }
        }
    }

    // right upper tile
    if (x + 1 >= 0 && x + 1 < width && y - 1 < height && y - 1 >= 0)
    {
        if (full_map[y - 1][x + 1] == 1)
        {
            if (n_posy < (y)*h_unit)
            {
                if (n_posx + 40 > (x + 1) * w_unit)
                {
                    n_posx = (x + 1) * w_unit - 40;
                }
            }
        }
    }

    // right center tile
    if (x + 1 >= 0 && x + 1 < width && y < height && y >= 0)
    {
        if (full_map[y][x + 1] == 1)
        {
            if (n_posx + 40 > (x + 1) * w_unit)
            {
                n_posx = (x + 1) * w_unit - 40;
            }
        }
    }

    // right lower tile
    if (x + 1 >= 0 && x + 1 < width && y + 1 < height && y + 1 >= 0)
    {
        if (full_map[y + 1][x + 1] == 1)
        {
            if (n_posy + 40 > (y + 1) * h_unit)
            {
                if (n_posx + 40 > (x + 1) * w_unit)
                {
                    n_posx = (x + 1) * w_unit - 40;
                }
            }
        }
    }

    // vertical collision ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    n_posy = physics_posy + y_velocity + gravity;
    x = (n_posx + (40 / 2)) / w_unit;

    // upper left tile
    if (x - 1 >= 0 && x - 1 < width && y - 1 < height && y - 1 >= 0)
    {
        if (full_map[y - 1][x - 1] == 1)
        {
            if (n_posx < (x)*w_unit)
            {
                if (n_posy < (y)*h_unit)
                {
                    n_posy = (y)*h_unit;
                }
            }
        }
    }

    // upper center tile
    if (x >= 0 && x < width && y - 1 < height && y - 1 >= 0)
    {
        if (full_map[y - 1][x] == 1)
        {
            if (n_posy < (y)*h_unit)
            {
                n_posy = (y)*h_unit;
            }
        }
    }

    // upper right tile
    if (x + 1 >= 0 && x + 1 < width && y - 1 < height && y - 1 >= 0)
    {
        if (full_map[y - 1][x + 1] == 1)
        {
            if (n_posx + 40 > (x + 1) * w_unit)
            {
                if (n_posy < (y)*h_unit)
                {
                    n_posy = (y)*h_unit;
                }
            }
        }
    }

    // bottom left tile
    if (x - 1 >= 0 && x - 1 < width && y + 1 < height && y + 1 >= 0)
    {
        if (full_map[y + 1][x - 1] == 1)
        {
            if (n_posx < (x)*w_unit)
            {
                if (n_posy + 40 > (y + 1) * h_unit)
                {
                    n_posy = (y + 1) * h_unit - 40;
                    ground_collision = true;
                }
            }
        }
    }

    // bottom center tile
    if (x >= 0 && x < width && y + 1 < height && y + 1 >= 0)
    {
        if (full_map[y + 1][x] == 1)
        {
            if (n_posy + 40 > (y + 1) * h_unit)
            {
                n_posy = (y + 1) * h_unit - 40;
                ground_collision = true;
            }
        }
    }

    // bottom right tile
    if (x + 1 >= 0 && x + 1 < width && y + 1 < height && y + 1 >= 0)
    {
        if (full_map[y + 1][x + 1] == 1)
        {
            if (n_posx + 40 > (x + 1) * w_unit)
            {
                if (n_posy + 40 > (y + 1) * h_unit)
                {
                    n_posy = (y + 1) * h_unit - 40;
                    ground_collision = true;
                }
            }
        }
    }

    // window permimeter
    if (n_posx < 0)
    {
        n_posx = 0;
    }
    int bounds = ((sizeof(full_map[0])-sizeof(map[0]))/sizeof(int)) * SCREEN_WIDTH/(sizeof(map[0])/sizeof(int)); 
    if (n_posx + 40 > SCREEN_WIDTH + bounds)
    {
        n_posx = SCREEN_WIDTH + bounds - 40;
    }
    if (n_posy < 0)
    {
        n_posy = 0;
    }
    if (n_posy + 40 > SCREEN_HEIGHT)
    {
        n_posy = SCREEN_HEIGHT - 40;
    }

    // update final position
    physics_posx = n_posx;
    this->posx = static_cast<int>(physics_posx);

    physics_posy = n_posy;
    this->posy = static_cast<int>(physics_posy);

    // ground collision
    if (ground_collision)
    {
        (*world).add_ground_collision(posx, posy);
    }
    (*world).render_ground_collision(gRenderer, frame, getPosx(), getPosy(), offset);
}

void Player::render(SDL_Renderer *gRenderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, int offset)
{
    SDL_Rect player = {this->posx - offset, this->posy, 40, 40};
    SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
    SDL_RenderFillRect(gRenderer, &player);
}
