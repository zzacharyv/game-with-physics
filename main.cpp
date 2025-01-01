#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "ltimer.h"

#include "player.h"
#include "level.h"
#include "map.cpp"
#include "level.h"

// vector<vector<int>> map = {{0, 0, 0, 0, 0, 0, 0, 0},
// 						   {0, 0, 0, 0, 0, 0, 0, 0},
// 						   {0, 0, 0, 0, 0, 0, 0, 0},
// 						   {0, 0, 0, 0, 0, 0, 0, 0},
// 						   {0, 0, 0, 0, 0, 0, 0, 0},
// 						   {0, 0, 0, 0, 0, 0, 0, 0},
// 						   {0, 0, 0, 0, 0, 0, 0, 0},
// 						   {0, 0, 0, 0, 0, 0, 0, 0},
// 						   {0, 0, 0, 0, 0, 0, 0, 0},
// 						   {0, 0, 0, 0, 0, 0, 0, 0},
// 						   {0, 0, 0, 0, 0, 0, 0, 0},
// 						   {1, 1, 1, 1, 1, 1, 1, 1},
// 						   {0, 0, 0, 0, 0, 0, 0, 0},
// 						   {0, 0, 0, 0, 0, 0, 0, 0},
// 						   {0, 0, 0, 0, 0, 0, 0, 0},
// 						   {0, 0, 0, 0, 0, 0, 0, 0},
// 						   {0, 0, 0, 0, 0, 0, 0, 0},
// 						   {0, 0, 0, 0, 0, 0, 0, 0},
// 						   {0, 0, 0, 0, 0, 0, 0, 0},
// 						   {0, 0, 0, 0, 0, 0, 0, 0},
// 						   {0, 0, 0, 0, 0, 0, 0, 0},
// 						   {0, 0, 0, 0, 0, 0, 0, 0},
// 						   {0, 0, 0, 0, 0, 0, 0, 0},
// 						   {1, 1, 1, 1, 1, 1, 1, 1}};
// // 24x23
// vector<vector<int>> level_select = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
// 									{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
// 									{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
// 									{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
// 									{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
// 									{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
// 									{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
// 									{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
// 									{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
// 									{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
// 									{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
// 									{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
// 									{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
// 									{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
// 									{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
// 									{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
// 									{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
// 									{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
// 									{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
// 									{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
// 									{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
// 									{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
// 									{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
// 									{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
// // 12x11

// Screen dimension constants
const int SCREEN_WIDTH = 1216;
const int SCREEN_HEIGHT = 519;
const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

extern vector<vector<int>> map;
extern vector<vector<int>> level_select;
extern vector<vector<int>> home;
extern vector<vector<int>> one;

// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void close();

// The window we'll be rendering to
SDL_Window *gWindow = NULL;

// The window renderer
SDL_Renderer *gRenderer = NULL;

bool init()
{
	// Initialization flag
	bool success = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		// Create window
		gWindow = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				// Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				// Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

void close()
{
	// Free loaded images
	// ground_collision_sprite_sheet.free();

	// Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	// Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void change_level(string *new_level, string *level, vector<vector<int>> *current_map, Player *player)
{

	if (*new_level == "home")
	{
		*current_map = home;
		*level = *new_level;
	}
	else if (*new_level == "level select")
	{
		*current_map = level_select;
		*level = *new_level;
	}
	else if (*new_level == "one")
	{
		*current_map = one;
		*level = *new_level;
	}
	else
	{
		*current_map = home;
		*level = "home";
		*new_level = *level;
	}
	(*player).setPosx(100);
	(*player).setPosy(200);
}

int main(int argc, char *args[])
{
	// Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		const Uint8 *keystates = SDL_GetKeyboardState(NULL);

		// World
		Level l = Level("one");
		string level = "one";
		string saved_level = level;
		World world = World();
		vector<vector<int>> current_map = one;

		// Player
		Player player = Player();
		int jumped_frame = 0;
		int jumped_y_pos;
		bool descent = false;
		// int pre_jump_pos = player.getPosy();
		// bool falling = false;

		// Mouse
		int xMouse, yMouse;
		float windowX, windowY;

		// Load media
		if (!(world.loadMedia(gRenderer)))
		{
			printf("Failed to load media!\n");
		}
		else
		{
			// Main loop flag
			bool quit = false;

			// Event handler
			SDL_Event e;

			// Set text color as black
			SDL_Color textColor = {0, 0, 0, 255};

			// The frames per second timer
			LTimer fpsTimer;

			// The projectiles timer
			LTimer shooterTimer;
			shooterTimer.start();

			// The jumping timer
			LTimer jumpingTimer;
			int jumpingTime;

			// The frames per second cap timer
			LTimer capTimer;

			// In memory text stream
			std::stringstream timeText;

			// Start counting frames per second
			int countedFrames = 0;
			fpsTimer.start();

			// Current animation frame
			int frame = 0;
			int jumpingframe = 0;

			// While application is running
			while (!quit)
			{
				// Start cap timer
				capTimer.start();

				

				// Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					// User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					// if (e.type = SDL_MOUSEBUTTONDOWN) {
					// 	int x, y;
					// 	SDL_GetMouseState(&x, &y);
					// 	cout << x << " " << y << endl;
					// }
					if (e.type == SDL_KEYDOWN)
					{
						// if (e.key.keysym.sym == SDLK_RIGHT)
						// {
						// 	if (player.getVelocityX() == 0.0)
						// 	{
						// 		player.setVelocityX(1);
						// 	}
						// 	player.setVelocityX(player.getVelocityX() + 0.4);
						// }
						// if (e.key.keysym.sym == SDLK_LEFT)
						// {
						// 	if (player.getVelocityX() == 0.0)
						// 	{
						// 		player.setVelocityX(-1);
						// 	}
						// 	player.setVelocityX(player.getVelocityX() - 0.4);
						// }
						if (e.key.keysym.sym == SDLK_UP)
						{
							// if (player.isOnGround())
							// {
							// 	player.setPosy(player.getPosy() - 35);
							// 	player.pre_jump_pos = player.getPosy();
							// 	player.falling = false;
							// }

							// std::cout << "poop" << std::endl;
							// if(descent == false && player.getVelocityY() >= 0 ) {
							// 	player.setVelocityY(player.getVelocityY()-10);
							// }
							// else if(player.getVelocityY() < 0) {
							// 	// std::cout <<"sdfghjk" << std::endl;
							// 	descent = true;
							// }

							// if(player.isOnGround() && player.getVelocityY() == 0) {
							// 	descent = false;
							// }

							// else if(player.getVelocityY() < 0)
							// {
							// 	player.setVelocityY(0);
							// } else {
							// 	player.setVelocityY(player.getVelocityY() + 2);
							// }
						}
						// else
						// {
						// 	player.setVelocityY(0);
						// }
						if (e.key.keysym.sym == SDLK_DOWN)
						{
							if (player.getVelocityY() == 0.0)
							{
								player.setVelocityY(1);
							}
							player.setVelocityY(player.getVelocityY() + .04);
						}
						if (e.key.keysym.sym == SDLK_r)
						{
							string l = "level_select";
							change_level(&l, &level, &current_map, &player);
						}
					}
					if (e.type == SDL_KEYUP)
					{
						// if (e.key.keysym.sym == SDLK_RIGHT)
						// {
						// 	player.setVelocityX(0);
						// }
						// if (e.key.keysym.sym == SDLK_LEFT)
						// {
						// 	player.setVelocityX(0);
						// }
						// if (e.key.keysym.sym == SDLK_UP)
						// {
						// 	player.setVelocityY(0);
						// 	jumped_frame = 0;
						// }
						// if (e.key.keysym.sym == SDLK_DOWN)
						// {
						// 	player.setVelocityY(0);
						// 	jumped_frame = 0;
						// }
					}
				}
				keystates = SDL_GetKeyboardState(NULL);
				if (keystates[SDL_SCANCODE_UP])
				{
					// if (!player.falling)
					// {
					// 	std::cout << "gfbsk" << std::endl;
					if(player.isOnGround()) {
						player.setVelocityY(-15);
					// }
					}
					
				}
				if (keystates[SDL_SCANCODE_RIGHT])
				{
					if (player.getVelocityX() < 10)
					{
						player.setVelocityX(player.getVelocityX() + 0.25);
					}
				}
				else if (keystates[SDL_SCANCODE_LEFT])
				{
					if (player.getVelocityX() > -10)
					{
						player.setVelocityX(player.getVelocityX() - 0.25);
					}
				}
				else if (player.getVelocityX() != 0)
				{
					if (player.getVelocityX() > 0)
					{
						player.setVelocityX(player.getVelocityX() - 0.75);
					}
					else if (player.getVelocityX() < 0)
					{
						player.setVelocityX(player.getVelocityX() + 0.75);
					}

					if(abs(player.getVelocityX()) < 1){
						player.setVelocityX(0);
					}
				}
				if (player.getPosy() > 443)
				{
					std::cout << player.getPosy() << " " << std::endl;
				}
				if (saved_level != level)
				{
					change_level(&level, &saved_level, &current_map, &player);
				}

				// Calculate and correct fps
				float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
				if (avgFPS > 2000000)
				{
					avgFPS = 0;
				}

				jumpingTime = jumpingTimer.getTicks();

				// Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				int offset = player.getPosx() - 400;
				if (offset < 0)
					offset = 0;
				int w_unit = (SCREEN_WIDTH / (map[0].size()));
				int off = w_unit * (current_map[0].size() - map[0].size());

				if (offset > off)
					offset = off;

				world.update({player.getPosx() - offset, player.getPosy(), 40, 40});

				// Render the world
				world.render(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT, offset, current_map, map, &level);

				// // Update the player
				player.update(gRenderer, frame, &world, SCREEN_HEIGHT, SCREEN_WIDTH, offset, current_map, map, &descent);
				// std::cout << player.getVelocityY() << std::endl;

				// Render the player
				player.render(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT, offset);

				if (level == "one")
				{
					SDL_Rect r = {player.getPosx(), player.getPosy(), 40, 40};

					l.update(frame, &shooterTimer, r, SCREEN_WIDTH, SCREEN_HEIGHT, current_map, map);
					l.render(gRenderer, r);
				}
				// Update screen
				SDL_RenderPresent(gRenderer);
				++countedFrames;

				// Go to next frame
				++frame;

				// Cycle Animation
				if (frame / 4 >= 4)
				{
					frame = 0;
				}

				// If frame finished early
				int frameTicks = capTimer.getTicks();
				if (frameTicks < SCREEN_TICK_PER_FRAME)
				{
					// Wait remaining time
					SDL_Delay(SCREEN_TICK_PER_FRAME - frameTicks);
				}
			}
		}
	}

	// Free resources and close SDL
	close();

	return 0;
}
