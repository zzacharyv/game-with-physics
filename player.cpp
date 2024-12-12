#include <SDL2/SDL.h>
#include <array>
#include <iostream>
#include "grid.cpp"
#include "colors/spectral.cpp"
#include "colors/color_conversion.cpp"
using namespace std;

// Idle animation
const int IDLE_ANIMATION_FRAMES = 4;
SDL_Rect idlePlayerSpriteClips[IDLE_ANIMATION_FRAMES];
LTexture idlePlayerSpriteSheetTexture;

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
    void update(array<array<Cell, 5>, 5> level, Grid *grid);
    void physics_update();
    void updateVelocityX(double delta);
    void setWalkingLeft(bool isWalkingLeft);
    void setWalkingRight(bool isWalkingRight);
    void setHighJumpingRight(bool isHighJumpingRight);
    void setHighJumpingLeft(bool isHighJumpingLeft);
    void setColorFresh(bool isColorFresh);

    void render(SDL_Renderer *gRenderer, int meatDimensions[2], int SCREEN_WIDTH, int SCREEN_HEIGHT);
    void renderPlayer(SDL_Renderer *gRenderer, int frame, int meatDimensions[2], int SCREEN_WIDTH, int SCREEN_HEIGHT);
    void physics_renderPlayer(SDL_Renderer *gRenderer, int SCREEN_WIDTH, int SCREEN_HEIGHT);
    bool loadMedia(SDL_Renderer *gRenderer);
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
bool Player::isHighJumpingLeft() {
    return highJumpingLeft;
}
bool Player::isColorFresh()
{
    return colorFresh;
}
void Player::setPosx(int posx)
{
    this->posx = posx;
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
void Player::setHighJumpingLeft(bool isHighJumpingLeft) {
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
    posx = 0;
    posy = 0;
    physics_posx = 0;
    physics_posy = 0;
    x_velocity = 0.1;
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
    else if (this->isHighJumpingLeft() == true) {
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

void Player::update(array<array<Cell, 5>, 5> level, Grid *grid)
{
    // check if there is a filled block beneath the player
    if (level[this->getPosy() + 1][this->getPosx()].getType() == false)
    {
        this->setPosy(this->getPosy() + 1);
    }
    int cellBelowType = (*grid).getCell(this->getPosx(), this->getPosy() + 1)->getType();
    if (cellBelowType < 0)
    {
        this->setColorFresh(false);
        if (cellBelowType == -2)
        {
            cout << "end block" << endl;
        }
        else
        {
        }
    }
    if (this->isColorFresh() == true)
    {
        
        Cell *cell = (*grid).getCell(this->getPosx(), this->getPosy() + 1);

        unsigned char cellr = (*cell).getR();
        unsigned char cellg = (*cell).getG();
        unsigned char cellb = (*cell).getB();

        unsigned char playerr = color[0];
        unsigned char playerg = color[1];
        unsigned char playerb = color[2];

        // If cell is white, treat it like transparent
        if (playerr == 255 && playerg == 255 && playerb == 255)
        {
            color[0] = cellr;
            color[1] = cellg;
            color[2] = cellb;
        }
        // Else mix the colors of the cell and player
        else
        {
            array<int, 3> mix = spectral_mix({cellr, cellg, cellb}, {playerr, playerg, playerb}, 0.5);
            HSL hsl = rgb2hsl(static_cast<float>(mix[0]),static_cast<float>(mix[1]),static_cast<float>(mix[2]));
            // if (hsl.s < 0.5) {
            //     hsl.s = 0.5;
            // }
            RGB rgb = hsl2rgb(hsl.h, hsl.s, hsl.l);
            (*cell).setColor(rgb.r, rgb.g, rgb.b);

            mix = spectral_mix({cellr, cellg, cellb}, {playerr, playerg, playerb}, 0.25);
            hsl = rgb2hsl(static_cast<float>(mix[0]),static_cast<float>(mix[1]),static_cast<float>(mix[2]));
            // if (hsl.s < 0.5) {
            //     hsl.s = 0.5;
            // }
            rgb = hsl2rgb(hsl.h, hsl.s, hsl.l);
            color[0] = rgb.r;
            color[1] = rgb.g;
            color[2] = rgb.b;
        }

        this->setColorFresh(false);
    }
}

bool Player::loadMedia(SDL_Renderer *gRenderer)
{
    // Loading success flag
    bool success = true;

    // Load sprite sheet textures
    // Idle
    if (!idlePlayerSpriteSheetTexture.loadFromFile("media/Untitled.png", gRenderer))
    {
        printf("Failed to load idle animation texture!\n");
        success = false;
    }
    else
    {
        // Set sprite clips
        idlePlayerSpriteClips[0].x = 0;
        idlePlayerSpriteClips[0].y = 0;
        idlePlayerSpriteClips[0].w = 64;
        idlePlayerSpriteClips[0].h = 64;

        idlePlayerSpriteClips[1].x = 64;
        idlePlayerSpriteClips[1].y = 0;
        idlePlayerSpriteClips[1].w = 64;
        idlePlayerSpriteClips[1].h = 64;

        idlePlayerSpriteClips[2].x = 128;
        idlePlayerSpriteClips[2].y = 0;
        idlePlayerSpriteClips[2].w = 64;
        idlePlayerSpriteClips[2].h = 64;

        idlePlayerSpriteClips[3].x = 192;
        idlePlayerSpriteClips[3].y = 0;
        idlePlayerSpriteClips[3].w = 64;
        idlePlayerSpriteClips[3].h = 64;
    }

    if (!pooPlayerSpriteSheetTexture.loadFromFile("media/player_idle.png", gRenderer))
    {
        printf("Failed to load idle animation texture!\n");
        success = false;
    }
    else
    {
        for (int i = 0; i < POO_ANIMATION_FRAMES; ++i)
        {
            pooPlayerSpriteClips[i].x = i * 256;
            pooPlayerSpriteClips[i].y = 0;
            pooPlayerSpriteClips[i].w = 256;
            pooPlayerSpriteClips[i].h = 256;
        }
    }
    // Walking Right
    if (!walkingRightPlayerSpriteSheetTexture.loadFromFile("media/walking_player.png", gRenderer))
    {
        printf("Failed to load walking animation texture!\n");
        success = false;
    }
    else
    {
        for (int i = 0; i < WALKING_ANIMATION_FRAMES; ++i)
        {
            walkingRightPlayerSpriteClips[i].x = i * 512;
            walkingRightPlayerSpriteClips[i].y = 0;
            walkingRightPlayerSpriteClips[i].w = 512;
            walkingRightPlayerSpriteClips[i].h = 256;
        }
    }
    // Walking Left
    if (!walkingLeftPlayerSpriteSheetTexture.loadFromFile("media/walking_player.png", gRenderer))
    {
        printf("Failed to load walking animation texture!\n");
        success = false;
    }
    else
    {
        for (int i = 0; i < WALKING_ANIMATION_FRAMES; ++i)
        {
            walkingLeftPlayerSpriteClips[i].x = walkingRightPlayerSpriteClips[WALKING_ANIMATION_FRAMES - 1 - i].x;
            walkingLeftPlayerSpriteClips[i].y = walkingRightPlayerSpriteClips[WALKING_ANIMATION_FRAMES - 1 - i].y;
            walkingLeftPlayerSpriteClips[i].w = walkingRightPlayerSpriteClips[WALKING_ANIMATION_FRAMES - 1 - i].w;
            walkingLeftPlayerSpriteClips[i].h = walkingRightPlayerSpriteClips[WALKING_ANIMATION_FRAMES - 1 - i].h;
        }
    }
    // High jumping right
    if (!highJumpRightPlayerSpriteSheetTexture.loadFromFile("media/jumping_player_1.png", gRenderer))
    {
        printf("Failed to load high-jumping animation texture!\n");
        success = false;
    }
    else
    {
        for (int i = 0; i < HIGH_JUMPING_ANIMATION_FRAMES; ++i)
        {
            highJumpRightPlayerSpriteClips[i].x = 768 * i;
            highJumpRightPlayerSpriteClips[i].y = 0;
            highJumpRightPlayerSpriteClips[i].w = 768;
            highJumpRightPlayerSpriteClips[i].h = 512;
        }
    }
     // High jumping left
    if (!highJumpLeftPlayerSpriteSheetTexture.loadFromFile("media/jumping_player_2.png", gRenderer))
    {
        printf("Failed to load high-jumping animation texture!\n");
        success = false;
    }
    else
    {
        for (int i = 0; i < HIGH_JUMPING_ANIMATION_FRAMES; ++i)
        {
            highJumpLeftPlayerSpriteClips[HIGH_JUMPING_ANIMATION_FRAMES-1-i].x = 768 * i;
            highJumpLeftPlayerSpriteClips[HIGH_JUMPING_ANIMATION_FRAMES-1-i].y = 0;
            highJumpLeftPlayerSpriteClips[HIGH_JUMPING_ANIMATION_FRAMES-1-i].w = 768;
            highJumpLeftPlayerSpriteClips[HIGH_JUMPING_ANIMATION_FRAMES-1-i].h = 512;
        }
    }

    // if (!cellTexture.loadFromFile("media/cell.png", gRenderer))
    // {
    //     printf("Failed to load cell texture!\n");
    //     success = false;
    // }
    return success;
}

void Player::physics_update() {
    this->physics_posx = physics_posx + x_velocity;
    this->posx = static_cast<int>(physics_posx);

    this->physics_posy = physics_posy + y_velocity + gravity;
    this->posy = static_cast<int>(physics_posy);

}

void Player::physics_renderPlayer(SDL_Renderer *gRenderer, int SCREEN_WIDTH, int SCREEN_HEIGHT) {
     // gSpriteSheetTexture.render( ( SCREEN_WIDTH - currentClip->w ) / 2, ( SCREEN_HEIGHT - currentClip->h ) / 2, currentClip );
    // idlePlayerSpriteSheetTexture.render(0, 0, gRenderer, currentClip);

    // int color[] = {255, 0, 255, 255};
   
    
        // SDL_Rect *currentClip = &pooPlayerSpriteClips[0];
        // pooPlayerSpriteSheetTexture.setColor(color[0], color[1], color[2]);
        // pooPlayerSpriteSheetTexture.render(this->posx, this->posy, gRenderer, currentClip);
        SDL_Rect player = {this->posx, this->posy,40,40};
        SDL_SetRenderDrawColor(gRenderer, 255,0,0,255);
        SDL_RenderFillRect(gRenderer,&player);
}

void Player::updateVelocityX(double delta) {
    double cap = 0.5;
    this->x_velocity += delta;
    if (abs(this->x_velocity) > 0.5) {
        if( this->x_velocity > 0) {
            this->x_velocity = 0.5;
        } else {
            this->x_velocity = -0.5;
        }
    }

}