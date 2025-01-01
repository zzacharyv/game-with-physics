#include "player.h"

int Player::getPosx()
{
    return posx;
}

int Player::getPosy()
{
    return posy;
}

double Player::getVelocityX()
{
    return x_velocity;
}

double Player::getVelocityY()
{
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
    physics_posy = posy;
}

void Player::setVelocityX(double x)
{
    x_velocity = x;
}

void Player::setVelocityY(double y)
{
    y_velocity = y;
}

Player::Player()
{
    posx = 100;
    posy = 200;
    physics_posx = 100;
    physics_posy = 200;
    x_velocity = 0.0;
    y_velocity = 0.0;
}

void Player::ground_collision()
{
    on_ground = true;
    y_velocity = 0;
}

bool Player::isOnGround()
{
    return on_ground;
}

void Player::in_air()
{
    on_ground = false;
}

void Player::update(SDL_Renderer *gRenderer, int frame, World *world, int SCREEN_HEIGHT, int SCREEN_WIDTH, int offset, std::vector<std::vector<int>> current_map, std::vector<std::vector<int>> map, bool *descending)
{

    // if(isOnGround() && getVelocityY() == 0) {
    // 					*descending = false;
    // 				}
    //                 if(getVelocityY() > 0) {
    //                     setVelocityY(0);
    //                     physics_posy -= getVelocityY();
    //                     // SDL_FlushEvent(Uint32 type);
    //                 }
    //                 if(*descending == true) {
    // 					setVelocityY(getVelocityY()+2);
    // 					// std::cout <<"descent" << std::endl;
    // 				}
    // COLLISION v v v v v
    // if(getPosy() < pre_jump_pos - 100) {
    //     falling = true;
    //     setVelocityY(0);
    // }
    // if(isOnGround()) {
    //     falling = false;
    // }
    bool ground_collision = false;

    int w_unit = SCREEN_WIDTH / (map[0].size());
    int h_unit = SCREEN_HEIGHT / map.size();
    int width = current_map[0].size();
    int height = current_map.size();

    double n_posx = physics_posx;
    double n_posy = physics_posy;
    double delta = 0;
    if (!isOnGround())
    {
        setVelocityY(getVelocityY() + gravity);
        // delta = physics_posy + y_velocity;
    }
    double step_speed = y_velocity / 3;
    for (int i = 1; i <= 3; ++i)
    {
        n_posy += step_speed;
        int left = n_posx / w_unit;
        int right = (n_posx + 40) / w_unit;
        int top = n_posy / h_unit;
        int bottom = (n_posy + 40) / h_unit;

        int x = (n_posx + (40 / 2)) / w_unit;
        int y = (n_posy + (40 / 2)) / h_unit;

        // vertical collision ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // upper left tile
        if (x - 1 >= 0 && x - 1 < width && y - 1 < height && y - 1 >= 0)
        {
            if (current_map[y - 1][x - 1] == 1)
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
            if (current_map[y - 1][x] == 1)
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
            if (current_map[y - 1][x + 1] == 1)
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
            if (current_map[y + 1][x - 1] == 1)
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
            if (current_map[y + 1][x] == 1)
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
            if (current_map[y + 1][x + 1] == 1)
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
    }

    // horizontal collision ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     int left = n_posx / w_unit;
        int right = (n_posx + 40) / w_unit;
        int top = n_posy / h_unit;
        int bottom = (n_posy + 40) / h_unit;

        int x = (n_posx + (40 / 2)) / w_unit;
        int y = (n_posy + (40 / 2)) / h_unit;

n_posx += x_velocity;
    // left upper tile
    if (x - 1 >= 0 && x - 1 < width && y - 1 < height && y - 1 >= 0)
    {
        if (current_map[y - 1][x - 1] == 1)
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
        if (current_map[y][x - 1] == 1)
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
        if (current_map[y + 1][x - 1] == 1)
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
        if (current_map[y - 1][x + 1] == 1)
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
        if (current_map[y][x + 1] == 1)
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
        if (current_map[y + 1][x + 1] == 1)
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

    // window permimeter
    if (n_posx < 0)
    {
        n_posx = 0;
    }
    int bounds = current_map[0].size() * w_unit;
    if (n_posx + 40 > bounds)
    {
        n_posx = bounds - 40;
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
        this->ground_collision();
        // (*world).add_ground_collision(posx, posy);
    }
    else
    {
        in_air();
    }

    // VELOCITY
    // if(isOnGround() && *descending == true) {
    // 						setVelocityY(0);
    // 						*descending == false;
    // }

    // (*world).render_ground_collision(gRenderer, frame, getPosx(), getPosy(), offset);
}

void Player::render(SDL_Renderer *gRenderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, int offset)
{
    SDL_Rect player = {this->posx - offset, this->posy, 40, 40};
    SDL_SetRenderDrawColor(gRenderer, 247, 62, 152, 255);
    SDL_RenderFillRect(gRenderer, &player);
}
