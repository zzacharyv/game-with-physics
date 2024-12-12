#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct rgb
{
    float r, g, b;
} RGB;

typedef struct hsl
{
    float h, s, l;
} HSL;

/*
 * Converts an RGB color value to HSL. Conversion formula
 * adapted from http://en.wikipedia.org/wiki/HSL_color_space.
 * Assumes r, g, and b are contained in the set [0, 255] and
 * returns HSL in the set [0, 1].
 */
HSL rgb2hsl(float r, float g, float b)
{

    HSL result;

    r /= 255;
    g /= 255;
    b /= 255;

    float max = MAX(MAX(r, g), b);
    float min = MIN(MIN(r, g), b);

    result.h = result.s = result.l = (max + min) / 2;

    if (max == min)
    {
        result.h = result.s = 0; // achromatic
    }
    else
    {
        float d = max - min;
        result.s = (result.l > 0.5) ? d / (2 - max - min) : d / (max + min);

        if (max == r)
        {
            result.h = (g - b) / d + (g < b ? 6 : 0);
        }
        else if (max == g)
        {
            result.h = (b - r) / d + 2;
        }
        else if (max == b)
        {
            result.h = (r - g) / d + 4;
        }

        result.h /= 6;
    }

    return result;
}

////////////////////////////////////////////////////////////////////////

/*
 * Converts an HUE to r, g or b.
 * returns float in the set [0, 1].
 */
float hue2rgb(float p, float q, float t)
{

    if (t < 0)
        t += 1;
    if (t > 1)
        t -= 1;
    if (t < 1. / 6)
        return p + (q - p) * 6 * t;
    if (t < 1. / 2)
        return q;
    if (t < 2. / 3)
        return p + (q - p) * (2. / 3 - t) * 6;

    return p;
}

////////////////////////////////////////////////////////////////////////

/*
 * Converts an HSL color value to RGB. Conversion formula
 * adapted from http://en.wikipedia.org/wiki/HSL_color_space.
 * Assumes h, s, and l are contained in the set [0, 1] and
 * returns RGB in the set [0, 255].
 */
RGB hsl2rgb(float h, float s, float l)
{

    RGB result;

    if (0 == s)
    {
        result.r = result.g = result.b = l; // achromatic
    }
    else
    {
        float q = l < 0.5 ? l * (1 + s) : l + s - l * s;
        float p = 2 * l - q;
        result.r = hue2rgb(p, q, h + 1. / 3) * 255;
        result.g = hue2rgb(p, q, h) * 255;
        result.b = hue2rgb(p, q, h - 1. / 3) * 255;
    }

    return result;
}
