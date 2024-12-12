#include "button.cpp"
using namespace std;

LTexture cellTexture;

class Cell
{
private:
    int type;
    unsigned char color[3];

public:
    Cell()
    {
        type = 0;
        color[0] = 0;
        color[1] = 0;
        color[2] = 0;
    }
    Cell(int type)
    {
        this->type = type;
        if (type == -1)
        {
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
        }
        else if (type == -2)
        {
            color[0] = 0;
            color[1] = 0;
            color[2] = 0;
        }
        else
        {
            color[0] = 100;
            color[1] = 100;
            color[2] = 100;
        }
    }
    Cell(int type, int r, int g, int b)
    {
        this->type = type;
        color[0] = r;
        color[1] = g;
        color[2] = b;
    }
    int getType()
    {
        return this->type;
    }
    int getR()
    {
        return color[0];
    }
    int getG()
    {
        return color[1];
    }
    int getB()
    {
        return color[2];
    }
    void setColor(int r, int g, int b)
    {
        this->color[0] = r;
        this->color[1] = g;
        this->color[2] = b;
    }
    void printColor()
    {
        std::cout << static_cast<int>(color[0]) << ", " << static_cast<int>(color[1]) << ", " << static_cast<int>(color[2]) << std::endl;
    }
    void render(SDL_Renderer *gRenderer, SDL_Rect *fillRect);
    static bool loadMedia(SDL_Renderer *gRenderer);
    string getColor();
    bool equals(Cell * cell);
};

bool Cell::loadMedia(SDL_Renderer *gRenderer)
{
    // Loading success flag
    bool success = true;

    // Load sprite sheet textures
    // Idle
    if (!cellTexture.loadFromFile("media/cell.png", gRenderer))
    {
        printf("Failed to load cell texture!\n");
        success = false;
    }
    return success;
}

void Cell::render(SDL_Renderer *gRenderer, SDL_Rect *fillRect)
{
    // SDL_Rect renderQuad = {width_unit * getPosx(), height_unit * getPosy(), width_unit, height_unit};
    //             SDL_Rect currentClip = {100, 100, 286, 256};
    //             cellTexture.setColor(color[0], color[1], color[2]);
    //             cellTexture.render(0, 0, gRenderer, &fillRect);

    SDL_Rect poop;
    poop.x = 256;
    poop.y = 0;
    poop.w = 256;
    poop.h = 256;

   

    // SDL_Rect *currentClip = &poop;
    SDL_Rect renderQuad = {1, 1, 200, 200};
    cellTexture.setColor(this->getR(), this->getG(), this->getB());
    cellTexture.render((*fillRect).x, (*fillRect).y, gRenderer);
}

string Cell::getColor() {
    string ret = to_string(color[0]) + to_string(color[1]) + to_string(color[2]);
    // cout << to_string(255) << endl;
    return ret;
}

bool Cell::equals(Cell * cell) {
    if(abs(cell->getR()-this->getR()) <= 10 && (abs(cell->getG()-this->getG()) <= 10 && (abs(cell->getB()-this->getB()) <= 10))) {
        return true;
    }
    return false;
}