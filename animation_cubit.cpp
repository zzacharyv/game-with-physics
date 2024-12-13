class Animation_Cubit
{
private:
    int x, y, frame;

public:
    Animation_Cubit(int, int, int);
    void setFrame(int);
    int getFrame();
    int getX();
    int getY();
};

Animation_Cubit ::Animation_Cubit(int xpos, int ypos, int frame)
{
    x = xpos;
    y = ypos;
    this->frame = frame;
}

void Animation_Cubit ::setFrame(int frame)
{
    this->frame = frame;
}

int Animation_Cubit ::getFrame()
{
    return this->frame;
}

int Animation_Cubit ::getX() {
    return this->x;
}

int Animation_Cubit ::getY() {
    return this->y;
}