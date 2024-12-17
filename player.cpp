#include <SDL2/SDL.h>
#include <array>
#include <iostream>
#include <stdexcept>
#include "world.cpp"
#include "colors/spectral.cpp"
#include "colors/color_conversion.cpp"
using namespace std;

// Idle animation
const int IDLE_ANIMATION_FRAMES = 4;
SDL_Rect idlePlayerSpriteClips[IDLE_ANIMATION_FRAMES];
LTexture idlePlayerSpriteSheetTexture;

// SDL_Rect ground_collision_sprite_clips[4];
// LTexture ground_collision_sprite_sheet;

// LTexture cellTexture;

const int POO_ANIMATION_FRAMES = 8;
SDL_Rect pooPlayerSpriteClips[POO_ANIMATION_FRAMES];
LTexture pooPlayerSpriteSheetTexture;

// Walking animation
const int WALKING_ANIMATION_FRAMES = 4;
SDL_Rect walkingRightPlayerSpriteClips[WALKING_ANIMATION_FRAMES];
LTexture walkingRightPlayerSpriteSheetTexture;

SDL_Rect walkingLeftPlayerSpriteClips[WALKING_ANIMATION_FRAMES];
LTexture walkingLeftPlayerSpriteSheetTexture;

const int HIGH_JUMPING_ANIMATION_FRAMES = 16;
SDL_Rect highJumpRightPlayerSpriteClips[HIGH_JUMPING_ANIMATION_FRAMES];
LTexture highJumpRightPlayerSpriteSheetTexture;

SDL_Rect highJumpLeftPlayerSpriteClips[HIGH_JUMPING_ANIMATION_FRAMES];
LTexture highJumpLeftPlayerSpriteSheetTexture;

class Player
{
public:
    int posx;
    int posy;
    double physics_posx;
    double physics_posy;
    double x_velocity;
    double y_velocity;
    double gravity = 3.0;
    int color[3];
    bool walkingLeft;
    bool walkingRight;
    bool highJumpingRight;
    bool highJumpingLeft;
    bool colorFresh;
    int getPosx();
    int getPosy();
    bool isWalkingLeft();
    bool isWalkingRight();
    bool isHighJumpingRight();
    bool isHighJumpingLeft();
    bool isColorFresh();
    void setPosx(int posx);
    void setPosy(int posy);
    void setColor(int r, int g, int b);
    // int getColorR();
    // int getColorG();
    // int getColorB();
    Player(int posx, int posy);
    Player();
    // void update(array<array<Cell, 5>, 5> level, Grid *grid);
    void physics_update(SDL_Renderer *, int, World *, int, int);
    void updateVelocityX(double delta);
    void setWalkingLeft(bool isWalkingLeft);
    void setWalkingRight(bool isWalkingRight);
    void setHighJumpingRight(bool isHighJumpingRight);
    void setHighJumpingLeft(bool isHighJumpingLeft);
    void setColorFresh(bool isColorFresh);

    void render(SDL_Renderer *gRenderer, int meatDimensions[2], int SCREEN_WIDTH, int SCREEN_HEIGHT);
    void renderPlayer(SDL_Renderer *gRenderer, int frame, int meatDimensions[2], int SCREEN_WIDTH, int SCREEN_HEIGHT);
    void physics_renderPlayer(SDL_Renderer *gRenderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, int offset);
    bool loadMedia(SDL_Renderer *gRenderer);

    bool detect_ground_collision(int, int);
    void render_ground_collision(SDL_Renderer *, int);

    void doIT(int n_posx, int n_posy, int SCREEN_WIDTH, int SCREEN_HEIGHT);
};

int Player::getPosx()
{
    return posx;
}
int Player::getPosy()
{
    return posy;
}
bool Player::isWalkingLeft()
{
    return walkingLeft;
}
bool Player::isWalkingRight()
{
    return walkingRight;
}
bool Player::isHighJumpingRight()
{
    return highJumpingRight;
}
bool Player::isHighJumpingLeft()
{
    return highJumpingLeft;
}
bool Player::isColorFresh()
{
    return colorFresh;
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
void Player::setWalkingRight(bool isWalkingRight)
{
    this->walkingRight = isWalkingRight;
}
void Player::setWalkingLeft(bool isWalkingLeft)
{
    this->walkingLeft = isWalkingLeft;
}
void Player::setHighJumpingRight(bool isHighJumpingRight)
{
    this->highJumpingRight = isHighJumpingRight;
}
void Player::setHighJumpingLeft(bool isHighJumpingLeft)
{
    this->highJumpingLeft = isHighJumpingLeft;
}
void Player::setColorFresh(bool isColorFresh)
{
    this->colorFresh = isColorFresh;
}
void Player::setColor(int r, int g, int b)
{
    color[0] = r;
    color[1] = g;
    color[2] = b;
}

Player::Player()
{
    posx = 250;
    posy = 0;
    physics_posx = 250;
    physics_posy = 0;
    x_velocity = 0.0;
    y_velocity = 0.0;
    walkingLeft = false;
    walkingRight = false;
    highJumpingLeft = false;
    highJumpingRight = false;
    colorFresh = true;
    color[0] = 0;
    color[1] = 255;
    color[2] = 255;
};
Player::Player(int posx, int posy)
{
    this->posx = posx;
    this->posy = posy;
    walkingLeft = false;
    walkingRight = false;
    highJumpingLeft = false;
    highJumpingRight = false;
    colorFresh = true;
    // 0, 33, 133
    // 35 G:35, B:255
    color[0] = 255;
    color[1] = 255;
    color[2] = 255;
}

void Player::render(SDL_Renderer *gRenderer, int meatDimensions[2], int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    int color[] = {255, 0, 255, 255};
    int width = meatDimensions[0];
    int height = meatDimensions[1];
    int width_unit = SCREEN_WIDTH / width;
    int height_unit = SCREEN_HEIGHT / height;
}

void Player::renderPlayer(SDL_Renderer *gRenderer, int frame, int meatDimensions[2], int SCREEN_WIDTH, int SCREEN_HEIGHT)
{

    // gSpriteSheetTexture.render( ( SCREEN_WIDTH - currentClip->w ) / 2, ( SCREEN_HEIGHT - currentClip->h ) / 2, currentClip );
    // idlePlayerSpriteSheetTexture.render(0, 0, gRenderer, currentClip);

    // int color[] = {255, 0, 255, 255};
    int width = meatDimensions[0];
    int height = meatDimensions[1];
    int width_unit = SCREEN_WIDTH / width;
    int height_unit = SCREEN_HEIGHT / height;

    // Set rendering space and render to screen
    if (this->isWalkingRight() == true)
    {
        SDL_Rect *currentClip = &walkingRightPlayerSpriteClips[frame / 4];
        SDL_Rect renderQuad = {width_unit * (getPosx() - 1), height_unit * getPosy(), width_unit * 2, height_unit};
        walkingRightPlayerSpriteSheetTexture.setColor(color[0], color[1], color[2]);
        walkingRightPlayerSpriteSheetTexture.render(0, 0, renderQuad, gRenderer, currentClip);
    }
    else if (this->isWalkingLeft() == true)
    {
        SDL_Rect *currentClip = &walkingLeftPlayerSpriteClips[frame / 4];

        SDL_Rect renderQuad = {width_unit * getPosx(), height_unit * getPosy(), width_unit * 2, height_unit};
        walkingLeftPlayerSpriteSheetTexture.setColor(color[0], color[1], color[2]);
        walkingLeftPlayerSpriteSheetTexture.render(0, 0, renderQuad, gRenderer, currentClip);
    }
    else if (this->isHighJumpingRight() == true)
    {
        SDL_Rect *currentClip = &highJumpRightPlayerSpriteClips[frame / 4];
        SDL_Rect renderQuad = {width_unit * (getPosx() - 2), height_unit * (getPosy() - 1), width_unit * 3, height_unit * 2};
        highJumpRightPlayerSpriteSheetTexture.setColor(color[0], color[1], color[2]);
        highJumpRightPlayerSpriteSheetTexture.render(0, 0, renderQuad, gRenderer, currentClip);
    }
    else if (this->isHighJumpingLeft() == true)
    {
        SDL_Rect *currentClip = &highJumpLeftPlayerSpriteClips[frame / 4];
        SDL_Rect renderQuad = {width_unit * getPosx(), height_unit * (getPosy() - 1), width_unit * 3, height_unit * 2};
        highJumpLeftPlayerSpriteSheetTexture.setColor(color[0], color[1], color[2]);
        highJumpLeftPlayerSpriteSheetTexture.render(0, 0, renderQuad, gRenderer, currentClip);
    }
    else
    {
        SDL_Rect *currentClip = &pooPlayerSpriteClips[frame / 8];
        SDL_Rect renderQuad = {width_unit * getPosx(), height_unit * getPosy(), width_unit, height_unit};
        pooPlayerSpriteSheetTexture.setColor(color[0], color[1], color[2]);
        pooPlayerSpriteSheetTexture.render(0, 0, renderQuad, gRenderer, currentClip);
    }
    // SDL_Rect *currentClip = &pooPlayerSpriteClips[frame / 8];
    //     SDL_Rect renderQuad = {width_unit * getPosx(), height_unit * getPosy(), width_unit, height_unit};
    //     cellTexture.setColor(color[0], color[1], color[2]);
    //     cellTexture.render(0, 0, renderQuad, gRenderer, currentClip);
}

bool Player::loadMedia(SDL_Renderer *gRenderer)
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

    return success;
}

void Player::physics_update(SDL_Renderer *gRenderer, int frame, World *world, int SCREEN_HEIGHT, int SCREEN_WIDTH)
{

    combine();

    int w_unit = SCREEN_WIDTH / (sizeof(map[0]) / sizeof(int));
    int h_unit = SCREEN_HEIGHT / (sizeof(map) / sizeof(map[0]));
    int width = ((sizeof(map[0]) + sizeof(on_deck[0])) / sizeof(int));
    int height = ((sizeof(map)) / sizeof(map[0]));

    double n_posx = (physics_posx + x_velocity);
    double n_posy = physics_posy;

    int left = n_posx / w_unit;
    int right = (n_posx + 40) / w_unit;
    int top = n_posy / h_unit;
    int bottom = (n_posy + 40) / h_unit;

    int x = (n_posx + (40 / 2)) / w_unit;
    int y = (n_posy + (40 / 2)) / h_unit;

    // horizontal collision ~~~~~~~~~~~~~~~~~~~~~~~~
    // left upper tile
    if (x - 1 >= 0 && x - 1 < 10 && y - 1 < 6 && y - 1 >= 0)
    {
        if (combined[y - 1][x - 1] == 1)
        {
            if (n_posy < (y)*h_unit)
            {
                if (n_posx < (x) * w_unit)
                {
                    n_posx = (x) * w_unit;
                }
            }
        }
    }

    // left center tile
    if (x - 1 >= 0 && x - 1 < 10 && y < 6 && y >= 0)
    {
        if (combined[y][x - 1] == 1)
        {
                if (n_posx < (x) * w_unit)
                {
                    n_posx = (x) * w_unit;
                }
        }
    }

    // left lower tile
    if (x - 1 >= 0 && x - 1 < 10 && y + 1 < 6 && y + 1 >= 0)
    {
        if (combined[y + 1][x - 1] == 1)
        {
            if (n_posy +40 > (y+1)*h_unit)
            {
                if (n_posx < (x) * w_unit)
                {
                    n_posx = (x) * w_unit;
                }
            }
        }
    }

    // right upper tile
    if (x + 1 >= 0 && x + 1 < 10 && y - 1 < 6 && y - 1 >= 0)
    {
        if (combined[y - 1][x + 1] == 1)
        {
            if (n_posy < (y)*h_unit)
            {
                if (n_posx +40 > (x+1) * w_unit)
                {
                    n_posx = (x+1) * w_unit - 40;
                }
            }
        }
    }

    // right center tile
    if (x + 1 >= 0 && x + 1 < 10 && y < 6 && y >= 0)
    {
        if (combined[y][x + 1] == 1)
        {
                if (n_posx+40 > (x+1) * w_unit)
                {
                    n_posx = (x+1) * w_unit-40;
                }
        }
    }

    // right lower tile
    if (x + 1 >= 0 && x + 1 < 10 && y + 1 < 6 && y + 1 >= 0)
    {
        if (combined[y + 1][x + 1] == 1)
        {
            if (n_posy+40 > (y+1)*h_unit)
            {
                if (n_posx +40 > (x+1) * w_unit)
                {
                    n_posx = (x+1) * w_unit - 40;
                }
            }
        }
    }

    // vertical collision ~~~~~~~~~~~~~~~~~~~~~~~~
    n_posy = (physics_posy + y_velocity + gravity);
    x = (n_posx + (40 / 2)) / w_unit;

    // upper left tile
    if (x - 1 >= 0 && x - 1 < 10 && y - 1 < 6 && y - 1 >= 0)
    {
        if (combined[y - 1][x - 1] == 1)
        {
            if (n_posx < (x)*w_unit)
            {
                if (n_posy < (y) * h_unit)
                {
                    n_posy = (y) * h_unit;
                }
            }
        }
    }

    // upper center tile
    if (x >= 0 && x < 10 && y - 1 < 6 && y - 1 >= 0)
    {
        if (combined[y - 1][x] == 1)
        {
            if (n_posy < (y)*h_unit)
            {
                n_posy = (y)*h_unit;
            }
        }
    }

    // upper right tile
    if (x + 1 >= 0 && x + 1 < 10 && y - 1 < 6 && y - 1 >= 0)
    {
        if (combined[y - 1][x + 1] == 1)
        {
            if (n_posx + 40 > (x+1)*w_unit)
            {
                if (n_posy < (y) * h_unit)
                {
                    n_posy = (y) * h_unit;
                }
            }
        }
    }

    // bottom left tile
    if (x - 1 >= 0 && x - 1 < 10 && y + 1 < 6 && y + 1 >= 0)
    {
        if (combined[y + 1][x - 1] == 1)
        {
            if (n_posx < (x)*w_unit)
            {
                if (n_posy + 40 > (y + 1) * h_unit)
                {
                    n_posy = (y + 1) * h_unit - 40;
                }
            }
        }
    }

    // bottom center tile
     if (x >= 0 && x < 10 && y + 1 < 6 && y + 1 >= 0)
    {
        if (combined[y + 1][x] == 1)
        {
                if (n_posy + 40 > (y + 1) * h_unit)
                {
                    n_posy = (y + 1) * h_unit - 40;
                }
        }
    }

    // bottom right tile
    if (x + 1 >= 0 && x + 1 < 10 && y + 1 < 6 && y + 1 >= 0)
    {
        if (combined[y + 1][x + 1] == 1)
        {
            if (n_posx+40 > (x+1)*w_unit)
            {
                if (n_posy + 40 > (y + 1) * h_unit)
                {
                    n_posy = (y + 1) * h_unit - 40;
                }
            }
        }
    }

    // for (int i = x - 1; i < x + 2; i++)
    // {
    //     if (i >= 0 && i < 10)
    //     {
    //         if (y - 1 >= 0 && y - 1 < 6)
    //         {
    //             if (combined[y - 1][i] == 1)
    //             {
    //                 if ((y)*h_unit > n_posy)
    //                 {
    //                     n_posy = physics_posy;
    //                     n_posx = physics_posx;
    //                     cout << "collided!" << endl;
    //                 }
    //             }
    //         }
    //     }
    // }
    // for (int i = x - 1; i < x + 2; i++)
    // {
    //     if (i >= 0 && i < 10)
    //     {

    //         if (y + 1 >= 0 && y + 1 < 6)
    //         {
    //             if (combined[y + 1][i] == 1)
    //             {
    //                 if ((y + 1) * h_unit < (n_posy + 40))
    //                 {
    //                     n_posy = physics_posy;
    //                     n_posx = physics_posx;
    //                     cout << "collided!" << endl;
    //                 }
    //             }
    //         }
    //     }
    // }

    // for (int j = y - 1; j < y + 2; j++)
    // {
    //     for (int i = x - 1; i < x + 2; i++)
    //     {
    //         if (j >= 0 && j < 6 && i >= 0 && i < 10) {
    //             if(combined[j][i] == 1) {
    //                 if((i+1)*w_unit > n_posx) {
    //                     if(j*h_unit > n_posy+40) {
    //                         cout << "collided" << endl;
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }

    // cout << endl;

    // doIT(n_posx, physics_posy,SCREEN_WIDTH, SCREEN_HEIGHT);

    // doIT(n_posx, n_posy,SCREEN_WIDTH, SCREEN_HEIGHT);

    // if (n_posx < 0)
    // {
    //     n_posx = 0;
    // }
    // if (n_posx > SCREEN_WIDTH - 40)
    // {
    //     n_posx = SCREEN_WIDTH - 40;
    // }
    // if (n_posy < 0)
    // {
    //     n_posy = 0;
    // }
    // if (n_posy > SCREEN_HEIGHT - 40)
    // {
    //     n_posy = SCREEN_HEIGHT - 40;
    // }

    bool ground_collision = false;

    this->physics_posx = n_posx;
    this->posx = static_cast<int>(physics_posx);

    this->physics_posy = n_posy;
    this->posy = static_cast<int>(physics_posy);

    if (ground_collision)
    {
        (*world).add_ground_collision(posx, posy);
    }
    // (*world).render_ground_collision(gRenderer, frame, getPosx(), getPosy());
}

void Player::doIT(int n_posx, int n_posy, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{

    int w_unit = SCREEN_WIDTH / (sizeof(map[0]) / sizeof(int));
    int h_unit = SCREEN_HEIGHT / (sizeof(map) / sizeof(map[0]));
    int width = ((sizeof(map[0]) + sizeof(on_deck[0])) / sizeof(int));
    int height = ((sizeof(map)) / sizeof(map[0]));

    int left = n_posx / w_unit;
    int right = (n_posx + 40) / w_unit;
    int top = n_posy / h_unit;
    int bottom = (n_posy + 40) / h_unit;

    if (left >= 0)
    {
        // bottom left
        if (bottom < height && combined[bottom][left] == 1)
        {
            int overlap_y = abs((n_posy + 40) - (h_unit * bottom));
            // int overlap_x = abs(n_posx - (w_unit * left + w_unit));
            int overlap_x = abs(n_posx - (w_unit * (n_posx / w_unit) + w_unit));

            if (overlap_y < overlap_x && (overlap_y != 0 || overlap_x != 0))
            {
                n_posy = bottom * h_unit - 40;
                // ground_collision = true;
            }
            else
            {
                n_posx = left * w_unit + w_unit;
                // n_posx = left * w_unit;
            }
        }
        // top left
        if (top >= 0 && combined[top][left] == 1)
        {
            int overlap_y = abs((n_posy) - (h_unit * top + h_unit));
            int overlap_x = abs(n_posx - (w_unit * left + w_unit));
            if (overlap_y < overlap_x && (overlap_y != 0 || overlap_x != 0))
            {
                n_posy = top * h_unit + h_unit;
            }
            else
            {
                n_posx = left * w_unit + w_unit;
            }
        }
    }
    if (right < width)
    {
        // bottom right
        if (bottom < height && combined[bottom][right] == 1)
        {
            int overlap_y = abs((n_posy + 40) - (h_unit * bottom));
            int overlap_x = abs((n_posx + 40) - (w_unit * right));
            if (overlap_y < overlap_x && (overlap_y != 0 || overlap_x != 0))
            {
                n_posy = bottom * h_unit - 40;
                // ground_collision = true;
            }
            else
            {
                n_posx = right * w_unit - 40;
            }
        }
        // top right
        if (top >= 0 && combined[top][right] == 1)
        {
            int overlap_y = abs((n_posy) - (h_unit * top + h_unit));
            int overlap_x = abs((n_posx + 40) - (w_unit * right));
            if (overlap_y < overlap_x && (overlap_y != 0 || overlap_x != 0))
            {
                n_posy = top * h_unit + h_unit;
            }
            else
            {
                n_posx = right * w_unit - 40;
            }
        }
    }
}

void Player::physics_renderPlayer(SDL_Renderer *gRenderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, int offset)
{
    // gSpriteSheetTexture.render( ( SCREEN_WIDTH - currentClip->w ) / 2, ( SCREEN_HEIGHT - currentClip->h ) / 2, currentClip );
    // idlePlayerSpriteSheetTexture.render(0, 0, gRenderer, currentClip);

    // int color[] = {255, 0, 255, 255};

    // SDL_Rect *currentClip = &pooPlayerSpriteClips[0];
    // pooPlayerSpriteSheetTexture.setColor(color[0], color[1], color[2]);
    // pooPlayerSpriteSheetTexture.render(this->posx, this->posy, gRenderer, currentClip);
    SDL_Rect player = {this->posx - offset, this->posy, 40, 40};
    SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
    SDL_RenderFillRect(gRenderer, &player);
}

void Player::updateVelocityX(double delta)
{
    double cap = 3.0;
    this->x_velocity += delta;
    if (abs(this->x_velocity) > cap)
    {
        if (this->x_velocity > 0)
        {
            this->x_velocity = cap;
        }
        else
        {
            this->x_velocity = -1.0 * cap;
        }
    }
}

bool Player::detect_ground_collision(int SCREEN_HEIGHT, int SCREEN_WIDTH)
{
    int p = map[0][0];
    int w_unit = SCREEN_WIDTH / (sizeof(map[0]) / sizeof(int));
    int h_unit = SCREEN_HEIGHT / (sizeof(map) / sizeof(map[0]));

    int row = (posy + 40) / h_unit;
    int col = posx / w_unit;

    if (row > 5 || col > 7)
    {
        throw std::invalid_argument("player out of bounds");
    }

    if (map[row][col] == 1)
    {
        posy = (row - 1) * h_unit + h_unit - 40;
        physics_posy = (row - 1) * h_unit + h_unit - 40;
        return true;
    }
    // if(row < SCREEN_HEIGHT/(sizeof(map)/sizeof(map[0]))-1 && map[col+1][row] == 1) {
    //     if(posy >= (col+1)*h_unit) {
    //         posy = col*h_unit;
    //         physics_posy = col*h_unit;
    //         return true;
    //     }
    // }
    return false;
}
