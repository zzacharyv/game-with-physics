#include <cmath>
#include <SDL2/SDL.h>

bool box_collision(SDL_Rect rect1, SDL_Rect rect2)
{
    if (
        rect1.x < rect2.x + rect2.w &&
        rect1.x + rect1.w > rect2.x &&
        rect1.y < rect2.y + rect2.h &&
        rect1.y + rect1.h > rect2.y)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool circle_box_collision(float cx, float cy, float radius, SDL_Rect rect) {

  // temporary variables to set edges for testing
  float testX = cx;
  float testY = cy;

  // which edge is closest?
  if (cx < rect.x)         testX = rect.x;      // test left edge
  else if (cx > rect.x+rect.w) testX = rect.x+rect.w;   // right edge
  if (cy < rect.y)         testY = rect.y;      // top edge
  else if (cy > rect.y+rect.h) testY = rect.y+rect.h;   // bottom edge

  // get distance from closest edges
  float distX = cx-testX;
  float distY = cy-testY;
  float distance = sqrt( (distX*distX) + (distY*distY) );

  // if the distance is less than the radius, collision!
  if (distance <= radius) {
    return true;
  }
  return false;
}