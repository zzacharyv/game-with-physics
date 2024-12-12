#include <algorithm>
#include <iostream>
#include <array>
#include "levels.cpp";
using namespace std;

extern array<array<int, 5>, 5> level_0_filled;
extern array<array<array<int, 3>, 5>, 5> level_0_color;
extern array<array<int, 5>, 5> level_1_filled;
extern array<array<array<int, 3>, 5>, 5> level_1_color;
extern array<array<int, 5>, 5> level_2_filled;
extern array<array<array<int, 3>, 5>, 5> level_2_color;

class Level
{
public:
    array<array<int, 5>, 5> filled;
    array<array<array<int, 3>, 5>, 5> color;
    Level(int l);
    Level();
    void printLevel();
};

Level::Level()
{
    filled = level_0_filled;
    color = level_0_color;
}

Level::Level(int level)
{
    if (level == 1)
    {
        filled = level_1_filled;
        color = level_1_color;
    }
    else if (level == 2)
    {
        filled = level_2_filled;
        color = level_2_color;
    }
    else
    {
        filled = level_0_filled;
        color = level_0_color;
    }
}

void Level::printLevel()
{
    for (int a = 0; a < 5; ++a)
    {
        for (int b = 0; b < 5; ++b)
        {
            cout << filled[a][b] << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << endl;
    for (int a = 0; a < color.size(); ++a)
    {
        for (int b = 0; b < color[a].size(); ++b)
        {
            for (int c = 0; c < color[a][b].size(); ++c)
            {
                cout << color[a][b][c] << ",";
            }
            cout << " ";
        }
        cout << endl;
    }
}