// #include "cell.cpp"
#include <iostream>
#include <array>
#include <SDL2/SDL.h>
#include "levels/level.cpp"
#include "cell.cpp"
using namespace std;

LTexture bgOneTexture;
LTexture bgTwoTexture;
LTexture bgThreeTexture;

int lev[5][5] = {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {1, 1, 1, 1, 1}};
// LTexture cellTexture;

class Grid
{
private:
    array<array<Cell, 5>, 5> meat;
    Level level;

public:
    Grid();
    Grid(int level, int SCREEN_WIDTH, int SCREEN_HEIGHT);
    Button buttons[5] = {
        Button("media/arrow-left-1.png", 0, 0), 
        Button("media/arrow-up-left.png", 0, 0),
        Button("media/arrow-up-right.png", 0, 0),
        Button("media/arrow-right-1.png", 0, 0),
        Button("media/reset.png",0,0,150,150,150)};
    // buttons[0] = Button("media/foo.png",0,0);
    // buttons[1] = Button("media/foo.png",50,0);
    // buttons[2] = Button("media/foo.png",100,0);
    // buttons[3] = Button("media/foo.png",150,0);
    void getMeatDimensions(int *arr)
    {
        arr[0] = 5;
        arr[1] = 5;
    }
    array<array<Cell, 5>, 5> getLevel()
    {
        return meat;
    }
    void renderGrid(SDL_Renderer *gRenderer, int SCREEN_WIDTH, int SCREEN_HEIGHT);
    void renderBG(SDL_Renderer *gRenderer, int SCREEN_WIDTH, int SCREEN_HEIGHT);
    Cell *getCell(int xpos, int ypos);
    void setCellColor(Cell *cell, int r, int g, int b);
    bool loadMedia(SDL_Renderer *gRenderer);
};

Grid::Grid(int level, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    this->level = Level(level);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            int cellType = this->level.filled[i][j];
            if (cellType == 0)
            {
                meat[i][j] = Cell();
            }
            else if (cellType == -1 || cellType == -2)
            {
                meat[i][j] = Cell(cellType);
            }
            else
            {
                meat[i][j] = Cell(cellType, this->level.color[i][j][0], this->level.color[i][j][1], this->level.color[i][j][2]);
            }
        }
    }
    SDL_Rect renderQuad = {0, 0, SCREEN_WIDTH / 6,SCREEN_WIDTH / 6};
    buttons[0].setRenderQuad(renderQuad);
    renderQuad.x = SCREEN_WIDTH / 6;
    buttons[1].setRenderQuad(renderQuad);
    renderQuad.x = SCREEN_WIDTH - (2 * SCREEN_WIDTH) / 6;
    buttons[2].setRenderQuad(renderQuad);
    renderQuad.x = SCREEN_WIDTH - SCREEN_WIDTH / 6;
    buttons[3].setRenderQuad(renderQuad);
    renderQuad = {0, 7*SCREEN_HEIGHT/9, SCREEN_WIDTH / 9,SCREEN_WIDTH / 9};
    // renderQuad.x = SCREEN_WIDTH - (3.5 * SCREEN_WIDTH) / 6;
    buttons[4].setRenderQuad(renderQuad);
}

void Grid::renderGrid(SDL_Renderer *gRenderer, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    int width = sizeof(meat) / sizeof(meat[0]);
    int height = sizeof(meat[0]) / sizeof(meat[0][0]);
    int width_unit = SCREEN_WIDTH / width;
    int height_unit = SCREEN_HEIGHT / height;

    this->renderBG(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            Cell cell = meat[i][j];
            if (cell.getType() != 0)
            {
                SDL_Rect fillRect = {width_unit * j - 15, height_unit * i, width_unit + 30, height_unit};
                cell.render(gRenderer, &fillRect);
                // SDL_Rect renderQuad = {width_unit * getPosx(), height_unit * getPosy(), width_unit, height_unit};
                // SDL_Rect currentClip = {100, 100, 286, 256};
                // cellTexture.setColor(color[0], color[1], color[2]);
                // cellTexture.render(0, 0, gRenderer, &fillRect);

                // SDL_Rect poop;
                // poop.x = 256;
                // poop.y = 0;
                // poop.w = 256;
                // poop.h = 256;

                // // SDL_Rect *currentClip = &poop;
                // SDL_Rect renderQuad = {1, 1, 200, 200};
                // cellTexture.setColor(0, 0, 0);
                // cellTexture.render(0, 0, renderQuad, gRenderer, &poop);
            }
        }
    }

      for (int i = 0; i < 5; ++i)
    {
        buttons[i].render(gRenderer);
    }
}

Cell *Grid::getCell(int xpos, int ypos)
{
    return &this->meat[ypos][xpos];
}

void Grid::setCellColor(Cell *cell, int r, int g, int b)
{
    (*cell).setColor(r, g, b);
}
bool Grid::loadMedia(SDL_Renderer *gRenderer)
{
    // Loading success flag
    bool success = true;

    // Load sprite sheet textures
    // Idle
    if (!bgOneTexture.loadFromFile("media/bg-1.png", gRenderer))
    {
        printf("Failed to load cell texture!\n");
        success = false;
    }
    if (!bgTwoTexture.loadFromFile("media/bg-2.png", gRenderer))
    {
        printf("Failed to load cell texture!\n");
        success = false;
    }
    if (!bgThreeTexture.loadFromFile("media/bg-3.png", gRenderer))
    {
        printf("Failed to load cell texture!\n");
        success = false;
    }
    // cout << "poop" << endl;
    return success;
}

void Grid::renderBG(SDL_Renderer *gRenderer, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    // SDL_Rect renderQuad = {width_unit * getPosx(), height_unit * getPosy(), width_unit, height_unit};
    //             SDL_Rect currentClip = {100, 100, 286, 256};
    //             cellTexture.setColor(color[0], color[1], color[2]);
    //             cellTexture.render(0, 0, gRenderer, &fillRect);

    SDL_Rect poop;
    poop.x = 0;
    poop.y = 0;
    poop.w = SCREEN_WIDTH;
    poop.h = SCREEN_HEIGHT;

    // SDL_Rect *currentClip = &poop;
    SDL_Rect renderQuad = {1, 1, 200, 200};
    bgOneTexture.setColor(255, 200, 200);
    bgOneTexture.render(0, 0, gRenderer, &poop);
    bgTwoTexture.setColor(255, 255, 200);
    bgTwoTexture.render(0, 0, gRenderer, &poop);
    bgThreeTexture.setColor(200, 200, 255);
    bgThreeTexture.render(0, 0, gRenderer, &poop);
    // bgOneTexture.setColor(255,0,0);
    // bgOneTexture.render(0, 0, gRenderer);
    // bgOneTexture.setColor(255,0,0);
    // bgOneTexture.render(0, 0, gRenderer);
}

// bool Grid::loadMedia(SDL_Renderer *gRenderer)
// {
//     // Loading success flag
//     bool success = true;

//     // Load sprite sheet textures
//     // Idle
//     if (!cellTexture.loadFromFile("media/cell.png", gRenderer))
//     {
//         printf("Failed to load cell texture!\n");
//         success = false;
//     }
//     cout << "poop" << endl;
//     return success;
// }
