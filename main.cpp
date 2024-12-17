#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "player.cpp"
#include "ltimer.cpp"

// Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 360;
const int SCREEN_FPS = 84;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

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
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
	ground_collision_sprite_sheet.free();

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

int main(int argc, char *args[])
{
	// Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		// Grid
		int level = 2;
		World world = World();

		// Player
		Player player = Player();
		int jumped_frame = 0;
		int jumped_y_pos;
		bool player_jump = true;

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
					if (e.type == SDL_KEYDOWN)
					{
						if (e.key.keysym.sym == SDLK_RIGHT)
						{
							if (player.getVelocityX() == 0.0)
							{
								player.setVelocityX(1);
							}
							player.setVelocityX(player.getVelocityX()+0.4);
						}
						if (e.key.keysym.sym == SDLK_LEFT)
						{
							if (player.getVelocityX() == 0.0)
							{
								player.setVelocityX(-1);
							}
							player.setVelocityX(player.getVelocityX()-0.4);
						}
						if (e.key.keysym.sym == SDLK_UP)
						{
							if (player_jump)
							{
								if (player.getVelocityY() == 0.0)
								{
									player.setVelocityY(-12);
								}
								else
								{
									player.setVelocityY(player.getVelocityY() + .04);
								}
							}
						}
						else
						{
							player.setVelocityY(0);
						}
						if (e.key.keysym.sym == SDLK_DOWN)
						{
							if (player.getVelocityY() == 0.0)
							{
								player.setVelocityY(1);
							}
							player.setVelocityY(player.getVelocityY() + .04);

						}
					}
					if (e.type == SDL_KEYUP)
					{
						if (e.key.keysym.sym == SDLK_RIGHT)
						{
							player.setVelocityX(0);
						}
						if (e.key.keysym.sym == SDLK_LEFT)
						{
							player.setVelocityX(0);
						}
						if (e.key.keysym.sym == SDLK_UP)
						{
							player.setVelocityY(0);
							jumped_frame = 0;
						}
						if (e.key.keysym.sym == SDLK_DOWN)
						{
							player.setVelocityY(0);
							jumped_frame = 0;
						}
					}
				}
				cout << player.getVelocityX() << endl;

				// Calculate and correct fps
				float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
				if (avgFPS > 2000000)
				{
					avgFPS = 0;
				}
				
				// Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);
		
				int offset = player.getPosx()-50;
				if(offset < 0) offset = 0;
				if(offset > 200) offset = 200;
	
				// Render the world
				world.render(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT, offset);

				// // Update the player
				player.update(gRenderer, frame, &world, SCREEN_HEIGHT, SCREEN_WIDTH, offset);

				// Render the player
				player.render(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT, offset);

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
