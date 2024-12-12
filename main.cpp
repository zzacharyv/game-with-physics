/*This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.*/

// Using SDL, SDL_image, SDL_ttf, standard IO, strings, and string streams
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "player.cpp"
// #include "ltexture.cpp"
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

// //Walking animation
// const int WALKING_ANIMATION_FRAMES = 4;
// SDL_Rect gSpriteClips[ WALKING_ANIMATION_FRAMES ];
// LTexture gSpriteSheetTexture;

// Globally used font
TTF_Font *gFont = NULL;

// Scene textures
// LTexture gFPSTextTexture;

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

				// Initialize SDL_ttf
				// if (TTF_Init() == -1)
				// {
				// 	printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
				// 	success = false;
				// }
			}
		}
	}

	return success;
}

void close()
{
	// Free loaded images
	idlePlayerSpriteSheetTexture.free();
	walkingRightPlayerSpriteSheetTexture.free();
	walkingLeftPlayerSpriteSheetTexture.free();

	// Free loaded images
	// gFPSTextTexture.free();

	// Free global font
	TTF_CloseFont(gFont);
	gFont = NULL;

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

void reset()
{
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
		Grid grid = Grid(level, SCREEN_WIDTH, SCREEN_HEIGHT);

		// Player
		Player player = Player();
		int jumped_frame = 0;
		int jumped_y_pos;
		bool player_jump = true;

		// Mouse
		int xMouse, yMouse;
		float windowX, windowY;

		// Load media
		if (!(player.loadMedia(gRenderer) && Cell::loadMedia(gRenderer) && grid.loadMedia(gRenderer)))
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
							// can accelerate out of control
							// player.x_velocity += 0.5;
							player.x_velocity += 0.2;
						}
						if (e.key.keysym.sym == SDLK_LEFT)
						{
							// can accelerate out of control
							// player.x_velocity += -0.5;
							player.x_velocity += -0.2;
						}
						if (e.key.keysym.sym == SDLK_UP)
						{
							// can accelerate out of control
							// player.x_velocity += -0.5;
							if (player_jump)
							{
								if (player.y_velocity == 0.0) {
									player.y_velocity = -12.0;
								} else {
									player.y_velocity += .04;
								}
								
							}
							// if (player.y_velocity <= -4.0)
							// {
							// 	player_jump = false;
							// } else {
							// 	player_jump = true;
							// }
						} else {
							player.y_velocity == 0.0;
						}
					}
					if (e.type == SDL_KEYUP)
					{
						if (e.key.keysym.sym == SDLK_RIGHT)
						{
							player.x_velocity = 0.0;
						}
						if (e.key.keysym.sym == SDLK_RIGHT)
						{
							player.x_velocity = 0.0;
						}
						if (e.key.keysym.sym == SDLK_LEFT)
						{
							player.x_velocity = 0.0;
						}
						if (e.key.keysym.sym == SDLK_UP)
						{
							player.y_velocity = 0.0;
							jumped_frame = 0;
							
						}
					}
					SDL_GetMouseState(&xMouse, &yMouse);
					// jump right
					if (grid.buttons[2].inBounds(xMouse, yMouse))
					{
						// grid.buttons[2].setColor(255,0,0);
						if (e.type == SDL_MOUSEBUTTONUP)
						{

							if (player.getPosx() < 3 && player.isHighJumpingLeft() == false && player.isWalkingRight() == false && player.isWalkingLeft() == false && player.isHighJumpingRight() == false)
							{
								grid.buttons[2].setColor(0, 255, 255);
								frame = 0;
								jumpingframe = 0;
								player.setHighJumpingRight(true);
								player.setPosx(2 + player.getPosx());
							}
						}
					}
					if (grid.buttons[0].inBounds(xMouse, yMouse))
					{
						// grid.buttons[0].color[0] = 0;
						// grid.buttons[0].color[1] = 0;
						// grid.buttons[0].color[2] = 0;
						if (e.type == SDL_MOUSEBUTTONUP)
						{

							if (player.getPosx() > 0 && player.isHighJumpingLeft() == false && player.isWalkingRight() == false && player.isWalkingLeft() == false && player.isHighJumpingRight() == false)
							{
								// grid.buttons[0].color[0] = 255;
								// grid.buttons[0].color[1] = 0;
								// grid.buttons[0].color[2] = 0;
								frame = 0;
								jumpingframe = 0;
								player.setWalkingLeft(true);
								player.setPosx(-1 + player.getPosx());
							}
						}
					}
					if (grid.buttons[3].inBounds(xMouse, yMouse))
					{
						// grid.buttons[3].color[0] = 0;
						// grid.buttons[3].color[1] = 0;
						// grid.buttons[3].color[2] = 0;
						if (e.type == SDL_MOUSEBUTTONUP)
						{

							if (player.getPosx() < 4 && player.isHighJumpingLeft() == false && player.isWalkingRight() == false && player.isWalkingLeft() == false && player.isHighJumpingRight() == false)
							{
								// grid.buttons[3].color[0] = 255;
								// grid.buttons[3].color[1] = 0;
								// grid.buttons[3].color[2] = 0;
								frame = 0;
								jumpingframe = 0;
								player.setWalkingRight(true);
								player.setPosx(1 + player.getPosx());
							}
						}
					}
					if (grid.buttons[1].inBounds(xMouse, yMouse))
					{
						// grid.buttons[1].color[0] = 0;
						// grid.buttons[1].color[1] = 0;
						// grid.buttons[1].color[2] = 0;
						if (e.type == SDL_MOUSEBUTTONUP)
						{

							if (player.getPosx() > 1 && player.isHighJumpingLeft() == false && player.isWalkingRight() == false && player.isWalkingLeft() == false && player.isHighJumpingRight() == false)
							{
								// grid.buttons[1].color[0] = 255;
								// grid.buttons[1].color[1] = 0;
								// grid.buttons[1].color[2] = 0;
								frame = 0;
								jumpingframe = 0;
								player.setHighJumpingLeft(true);
								player.setPosx(-2 + player.getPosx());
							}
						}
					}
					// reset button
					if (grid.buttons[4].inBounds(xMouse, yMouse))
					{
						// grid.buttons[4].color[0] = 0;
						// grid.buttons[4].color[1] = 0;
						// grid.buttons[4].color[2] = 0;
						if (e.type == SDL_MOUSEBUTTONUP)
						{

							if (true)
							{
								cout << "reset" << endl;

								grid = Grid(level, SCREEN_WIDTH, SCREEN_HEIGHT);
								player = Player(0, 3);
								// grid.buttons[4].color[0] = 255;
								// grid.buttons[4].color[1] = 0;
								// grid.buttons[4].color[2] = 0;
								frame = 0;
								jumpingframe = 0;
							}
						}
					}
				}

				if (grid.getCell(1, 4)->equals(grid.getCell(2, 4)) && grid.getCell(2, 4)->equals(grid.getCell(3, 4)) && grid.getCell(1, 4)->equals(grid.getCell(3, 4)))
				{
					cout << "game won" << endl;
				}

				// Calculate and correct fps
				float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
				if (avgFPS > 2000000)
				{
					avgFPS = 0;
				}

				// // Update the player
				// player.update(grid.getLevel(), &grid);
				player.physics_update();

				// Set text to be rendered
				timeText.str("");
				timeText << "Average Frames Per Second (With Cap) " << avgFPS;

				// Render text
				// if (!gFPSTextTexture.loadFromRenderedText(timeText.str().c_str(), textColor, gRenderer, gFont))
				// {
				// 	printf("Unable to render FPS texture!\n");
				// }

				// Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				// Render the grid
				grid.renderGrid(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);

				// Render the player
				int meatDimensions[2] = {0, 0};
				grid.getMeatDimensions(meatDimensions);
				// player.renderPlayer(gRenderer, jumpingframe, meatDimensions, SCREEN_WIDTH, SCREEN_HEIGHT);
				player.physics_renderPlayer(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);

				// Update screen
				SDL_RenderPresent(gRenderer);
				++countedFrames;

				// Go to next frame
				++frame;
				++jumpingframe;
				++jumped_frame;

				// Cycle Animation
				if (jumpingframe / 4 >= HIGH_JUMPING_ANIMATION_FRAMES)
				{
					jumpingframe = 0;
					if (player.isHighJumpingRight() == true)
					{
						player.setHighJumpingRight(false);
						player.setColorFresh(true);
					}
					if (player.isHighJumpingLeft() == true)
					{
						player.setHighJumpingLeft(false);
						player.setColorFresh(true);
					}
				}
				if (frame / 4 >= IDLE_ANIMATION_FRAMES)
				{
					frame = 0;
					if (player.isWalkingRight() == true)
					{
						player.setWalkingRight(false);

						player.setColorFresh(true);
					}
					if (player.isWalkingLeft() == true)
					{
						player.setWalkingLeft(false);
						player.setColorFresh(true);
					}
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

// void keyDown() {
// 	if (e.key.keysym.sym == SDLK_RIGHT && player.getPosx() < 4 && player.isWalkingRight() == false && player.isWalkingLeft() == false && player.isHighJumpingRight() == false)
// 						{
// 							frame = 0;
// 							jumpingframe = 0;
// 							player.setWalkingRight(true);
// 							player.setPosx(1 + player.getPosx());
// 						}
// 						else if (e.key.keysym.sym == SDLK_LEFT && player.getPosx() > 0 && player.isWalkingRight() == false && player.isWalkingLeft() == false && player.isHighJumpingRight() == false)
// 						{
// 							frame = 0;
// 							jumpingframe = 0;
// 							player.setWalkingLeft(true);
// 							player.setPosx(-1 + player.getPosx());
// 						}
// 						else if (e.key.keysym.sym == SDLK_UP && player.getPosx() < 3 && player.isWalkingRight() == false && player.isWalkingLeft() == false && player.isHighJumpingRight() == false)
// 						{
// 							frame = 0;
// 							jumpingframe = 0;
// 							player.setHighJumpingRight(true);
// 							player.setPosx(2 + player.getPosx());
// 						}
// }