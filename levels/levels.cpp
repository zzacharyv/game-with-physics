#include <array>
#include "../colors/colors.cpp"
using namespace std;

array<array<int, 5>, 5> level_0_filled = {{{0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0}}};

array<array<array<int, 3>, 5>, 5> level_0_color = {{{none, none, none, none, none},
                                                    {none, none, none, none, none},
                                                    {none, none, none, none, none},
                                                    {none, none, none, none, none},
                                                    {none, none, none, none, none}}};

array<array<int, 5>, 5> level_1_filled = {{{0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0},
                                           {-1, 1, 1, 1, -2}}};

array<array<array<int, 3>, 5>, 5> level_1_color = {{{{none, none, none, none, none}},
                                                    {{none, none, none, none, none}},
                                                    {{none, none, none, none, none}},
                                                    {{none, none, none, none, none}},
                                                    {{none, {255,0,255}, yell, {0,255,255}, none}}}};

array<array<int, 5>, 5> level_2_filled = {{{0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0},
                                           {-1, 1, 1, 1, -2}}};

array<array<array<int, 3>, 5>, 5> level_2_color = {{{{none, none, none, none, none}},
                                                    {{none, none, none, none, none}},
                                                    {{none, none, none, none, none}},
                                                    {{none, none, none, none, none}},
                                                    {{none, green, red, yell, none}}}};
