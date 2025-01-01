#ifndef DRAW_H_
#define DRAW_H_

#include <SDL2/SDL.h>

void DrawCircle(SDL_Renderer * renderer, int32_t centreX, int32_t centreY, int32_t radius);
int SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius);

#endif

