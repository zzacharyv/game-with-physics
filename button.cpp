#include <iostream>
#include <array>
#include <SDL2/SDL.h>
#include "ltexture.cpp"

using namespace std;


class Button { 
    public:
        // int xpos,ypos,width,height;
        // bool clicked, released;
        int color[3];
        int saved_color[3];
        int hover_color[3] = {0};
        SDL_Rect renderQuad;
        LTexture texture;
        // SDL_Rect renderQuad = {1, 1, 200, 200};
        string filepath;
        int xpos, ypos;
        void render(SDL_Renderer *gRenderer);
        bool inBounds(int xMouse, int yMouse);
        Button(string filepath, int xpos, int ypos);
        Button(string filepath, int xpos, int ypos, int r, int g, int b);
        void setColor(int r, int g, int b);
        bool loadMedia(SDL_Renderer *gRenderer);
        void setRenderQuad(SDL_Rect renderQuad);
};

Button::Button(string filepath, int xpos, int ypos) {
    color[0], saved_color[0] = 255;
    color[1], saved_color[1]  = 255;
    color[2], saved_color[2]  = 255;

    this->filepath = filepath;
    this->xpos = xpos;
    this->ypos = ypos;
    renderQuad = {xpos,ypos,80,80};
}

Button::Button(string filepath, int xpos, int ypos, int r, int g, int b) {
    color[0], saved_color[0]  = r;
    color[1], saved_color[1]  = g;
    color[2], saved_color[2]  = b;
    this->filepath = filepath;
    this->xpos = xpos;
    this->ypos = ypos;
    renderQuad = {xpos,ypos,80,80};
}

bool Button::loadMedia(SDL_Renderer *gRenderer)
{
    // Loading success flag
    bool success = true;

    // Load sprite sheet textures
    // Idle
    if (!texture.loadFromFile(filepath, gRenderer))
    {
        printf("Failed to load cell texture!\n");
        success = false;
    }
    return success;
}

void Button::render(SDL_Renderer *gRenderer)
{
    // if (this->texture.)
    // SDL_Rect renderQuad = {width_unit * getPosx(), height_unit * getPosy(), width_unit, height_unit};
    //             SDL_Rect currentClip = {100, 100, 286, 256};
    //             cellTexture.setColor(color[0], color[1], color[2]);
    //             cellTexture.render(0, 0, gRenderer, &fillRect);

    // cout << (*fillRect).x << (*fillRect).y << (*fillRect).w << (*fillRect).h << endl;

    // SDL_Rect *currentClip = &poop;
    if(texture.getTexture() == NULL) {
        loadMedia(gRenderer);
    }
    this->texture.setColor(color[0],color[1],color[2]);
    this->texture.render(xpos, ypos, renderQuad, gRenderer);
    // SDL_SetRenderDrawColor(gRenderer, color[0],color[1],color[2],255);
    // SDL_RenderFillRect(gRenderer,&renderQuad);
    // texture.setColor(this->getR(), this->getG(), this->getB());
    // texture.render(0,0, gRenderer, &poop);
}

bool Button::inBounds(int xMouse, int yMouse) {
   
   if(xMouse >= renderQuad.x && xMouse <= renderQuad.x + renderQuad.w) {
        if(yMouse >= renderQuad.y && yMouse <= renderQuad.y + renderQuad.h ) {
            this->setColor(hover_color[0],hover_color[1],hover_color[2]);
            return true;
        }
    } 
    this->setColor(saved_color[0],saved_color[1],saved_color[2]);

    return false;
    
}

void Button::setRenderQuad(SDL_Rect renderQuad) {
    this->renderQuad = renderQuad;
}

void Button::setColor(int r, int g, int b) {
    color[0] = r;
    color[1] = g;
    color[2] = b;
}
