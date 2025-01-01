#include "shooter.h"

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

Shooter::Shooter()
{
    posx = 800;
    posy = 100;
    width= 100;
    angle = 0.0;
    projectiles = {};
}

struct Linear {
    double m,b;
};
// std::vector<Projectile *> Shooter::get_projectiles() {
//     return this->projectiles;
// }


static void plot_line(SDL_Renderer * gRenderer, Linear line) {
        SDL_SetRenderDrawColor(gRenderer,255,255,0,255);

   
    for(int i=50; i<519; ++i) {
        SDL_RenderFillCircle(gRenderer, i, i*line.m + line.b, 1);
    }
}

static void plot_line_vector(SDL_Renderer * gRenderer, Line line) {
     double dx,dy;
     SDL_SetRenderDrawColor(gRenderer,0,0,255,255);

   
    for(double i=0; i<519; i=i+0.1) {
        dx = i*std::get<0>(line.N) + std::get<0>(line.A);
        dy = i*std::get<1>(line.N) + std::get<1>(line.A);
        SDL_RenderFillCircle(gRenderer, dx, dy, 2);
    }
}

void Shooter::render(SDL_Renderer *gRenderer, SDL_Rect player)
{
    if (shooter_texture.getTexture() == NULL)
    {
        loadMedia(gRenderer);
    }

    //     std::cout << x << std::endl;

    // SDL_RenderFillCircle(gRenderer, x,y, 20);
    SDL_Rect la = {100, 100, 100, 40};

    SDL_SetRenderDrawColor(gRenderer,255,0,0,255);
    SDL_RenderFillCircle(gRenderer, posx, posy, 4);

    // SDL_RenderDrawLine(gRenderer, posx,posy,player.x+20,player.y);
    SDL_Point center = {0, 20};
        // shooter_texture.render(posx, posy, gRenderer, &la);

    shooter_texture.render(posx, posy-center.y, gRenderer, &la, -angle,&center);

    double run = (posx-(player.x+20));
    double rise = (posy-player.y);
    double m;
    if(run == 0) {
        m =10000;
    } else if (rise == 0) {
        m = 0;
    } else {
        m = rise/run;
    }
    double b;
    if(posx*m != posy) {
        b = posy - posx*m;
    }
    // std::cout << "y=" << m << "x+" << b << std::endl;
    Linear l = {m,b};
    // std::cout << " " << atan(m)* (180.0 / M_PI ) << std::endl;
    // plot_line(gRenderer,{m,b});

    // if(player.x < posx) {
    //     m = -m;
    // }
    double magnitude = sqrt(1*1 + m*m);
    std::tuple<double,double> N = {1/magnitude,m/magnitude};
    std::tuple<double,double> A = {posx,posy};
    if(player.x + 20 < posx) {
       
            N = {-1/magnitude,-m/magnitude};
    }
    Line ll = {A,N};

    // plot_line_vector(gRenderer,ll);

    if (!projectiles.empty())
    {
        // std::cout << (projectiles[0]).posx << " " << (projectiles[0]).posy << std::endl;
        for (int i = 0; i < projectiles.size(); ++i)
        {
            SDL_SetRenderDrawColor(gRenderer, 55, 54, 50, 255);
            SDL_RenderFillCircle(gRenderer, (projectiles[i]).posx, (projectiles[i]).posy, (projectiles[i]).radius);
        }
    }
}

void Shooter::add_projectile(SDL_Rect player)
{
    // Projectile p = {posx, posy, 5, 1.0};
    int x = static_cast<int>(100 * cos(angle)) + posx;
    int y = static_cast<int>(sin(angle)) + posy;
    // std::cout << x << std::endl;
    double radians_angle = angle * (M_PI / 180.0);
   
    double speedx = cos(radians_angle);
    double speedy = -sin(radians_angle);
    //  std::cout << speedx << " " << speedy << std::endl;

     double run = (posx-(player.x+20));
    double rise = (posy-player.y);
    double m;
    if(run == 0) {
        m =10000;
    } else if (rise == 0) {
        m = 0;
    } else {
        m = rise/run;
    }
    double b;
    if(posx*m != posy) {
        b = posy - posx*m;
    }
    // direction vector = < 1, m > 
    // magnitude = sqrt(1^2 + m^2)
    // N = direction vector / magnitude = < 1 / magnitude, m / magnitude >
    //  f(t) = A + t*N
    double magnitude = sqrt(1*1 + m*m);
    std::tuple<double,double> N = {1/magnitude,m/magnitude};
    std::tuple<double,double> A = {posx,posy};
    if(player.x + 20 < posx) {
        N = {-1/magnitude,-m/magnitude};
    }
    projectiles.insert(projectiles.end(), {exitx, exity, 10, 2,{A,N}});
}

// void Shooter::remove_projectile(Projectile * p) {
//         // projectiles.erase(projectiles.begin() +index);
//         projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), p), projectiles.end());

// }

void Shooter::update(SDL_Rect player, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    double x, y;

    x = posx - player.x - 20;
    y = posy - player.y;

    // if (y == 0.0)
    // {
    //     y == 1.0;
    // }
    // if (x == 0.0)
    // {
    //     x = 1.0;
    // }
    angle = atan2(x,y) * (180.0 / M_PI) + 90;
    // if (player.x >= posy && player.y >= posy)
    // {
    //     angle = 360 - angle;
    // }
    // if (player.x >= posy && player.y < posy)
    // {
    //     angle = -angle;
    // }
    // if (player.x < posy && player.y < posy)
    // {
    //     angle = 90 - angle + 90;
    // }
    // if (player.x < posy && player.y >= posy)
    // {
    //     angle = 180 + abs(angle);
    // }
    // std::cout << angle << std::endl;
    double radians_angle = angle * (M_PI / 180.0);
    exitx = posx + (posx + width - posx) * cos(radians_angle) + sin(radians_angle) * (posy-posy);
    exity = posy - (posx + width - posx) * sin(radians_angle) + cos(radians_angle) * (posy-posy);

    // if(angle < 0.0) {
    //     angle = angle+180;
    // }
    if (!projectiles.empty())
    {
        for (int i = 0; i < projectiles.size(); ++i)
        {
            double dx = std::get<0>(projectiles[i].line.N)*projectiles[i].speed + std::get<0>(projectiles[i].line.A);
            double dy = std::get<1>(projectiles[i].line.N)*projectiles[i].speed + std::get<1>(projectiles[i].line.A);
            projectiles[i].line.A = {dx,dy};

            (projectiles[i]).posx = dx;
            (projectiles[i]).posy = dy;
            if (circle_box_collision(projectiles[i].posx, projectiles[i].posy, projectiles[i].radius, player))
            {
                // delete &projectiles[i];
                projectiles.erase(projectiles.begin() + i);
            }
            if (projectiles[i].posx - projectiles[i].radius > SCREEN_WIDTH || projectiles[i].posx + projectiles[i].radius < 0
            || projectiles[i].posy - projectiles[i].radius > SCREEN_HEIGHT || projectiles[i].posy + projectiles[i].radius < 0) {
                projectiles.erase(projectiles.begin() + i);

            }
        }
    }
    // std::cout << projectiles.size() << std::endl;  
}

bool Shooter::loadMedia(SDL_Renderer *gRenderer)
{
    // Loading success flag
    bool success = true;

    // Load sprite sheet textures
    // Ground Collision
    if (!shooter_texture.loadFromFile("media/shooter/shooter.png", gRenderer))
    {
        printf("Failed to load shooter texture!\n");
        success = false;
    }
    return success;
}
