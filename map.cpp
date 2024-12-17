int map[6][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                 {0, 0, 0, 0, 1, 0, 0, 0},
                 {0, 0, 1, 0, 0, 0, 0, 0},
                 {0, 0, 1, 0, 0, 0, 0, 0},
                 {1, 0, 1, 0, 0, 0, 0, 0},
                 {1, 1, 1, 1, 1, 1, 1, 1}};

int on_deck[6][2] = {{0, 0},
                     {0, 0},
                     {0, 0},
                     {0, 0},
                     {0, 0},
                     {1, 1}};

int combined[6][10];

bool first = true;
static int countt = 0;

void combine() 
{
    for(int i=0; i<6; i++) {
        std::copy(map[i],map[i]+8,combined[i]);
        std::copy(on_deck[i],on_deck[i]+2,combined[i]+8);
    }
    // std::copy(map, map+8, combined);
    // std::copy(on_deck, on_deck+2, combined+8);
}

void shift()
{
    for (auto &row : map)
    {
        std::rotate(row, row + 1, row + 8);
    }
}
