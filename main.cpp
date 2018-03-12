#include "SDL/include/SDL.h"
#include "SDL_Image/include/SDL_image.h"
#include "SDL_Mixer/include/SDL_mixer.h"

#pragma comment(lib,"SDL/libx86/SDL2.lib")
#pragma comment(lib,"SDL/libx86/SDL2main.lib")
#pragma comment(lib,"SDL_Image/libx86/SDL2_image.lib")
#pragma comment(lib,"SDL_Mixer/libx86/SDL2_mixer.lib")

int main(int argc, char* argv[])
{
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Event checkEvents;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Init(SDL_INIT_AUDIO);
	IMG_Init(IMG_INIT_PNG);
	Mix_Init(MIX_INIT_OGG);
	//Declare the Red Rectangle Dimensions and Position
	SDL_Rect redRect;
	redRect.x = 1280 / 4;
	redRect.y = 720 / 4;
	redRect.w = 250;
	redRect.h = 150;

	SDL_Rect greenRect;
	greenRect.x = 0;
	greenRect.y = 620;
	greenRect.w = 1280;
	greenRect.h = 100;

	//Set the Window
	window = SDL_CreateWindow(
		"Best Game EVER!",                   // window title
		SDL_WINDOWPOS_CENTERED,             // initial x position
		SDL_WINDOWPOS_CENTERED,            // initial y position
		1280,                             // width, in pixels
		720,                             // height, in pixels
		0								// flags 
	);
	//Set the Renderer
	renderer = SDL_CreateRenderer(window, -1, 0);

	int xspeed = 0, yspeed = 1, bulletSpeed = 2;
	int bulletArrPos = 0;
	bool exitLoop = false;
	bool renderShot = false;
	bool leftPressed = false, rightPressed = false, upPressed = false, downPressed = false, spacePressed = false, grounded = false;

	//Set the PNG Background
	SDL_Texture *back= nullptr;
	SDL_Texture *ShipTexture = nullptr;
	SDL_Texture *laserTexture = nullptr;
	SDL_Surface *Background = IMG_Load("background.png");
	SDL_Surface *Ship = IMG_Load("ae86.png");
	SDL_Surface *Laser = IMG_Load("laser.png");
	back = SDL_CreateTextureFromSurface(renderer,Background);
	ShipTexture = SDL_CreateTextureFromSurface(renderer,Ship);
	laserTexture = SDL_CreateTextureFromSurface(renderer, Laser);

	//Initialize music sounds
	Mix_Music *bgm=nullptr;
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	bgm = Mix_LoadMUS("bgmusic.ogg");
	Mix_VolumeMusic(100);
	//Mix_PlayMusic(bgm,-1);

	//Initialize wav sounds
	Mix_Chunk *shot = nullptr;
	shot = Mix_LoadWAV("spshot.wav");

	if (back==nullptr || ShipTexture==nullptr|| Laser==nullptr)
	{
		return -1;
	}
	else
	{
		while (exitLoop != true)
		{

			//Set the inputs into the KeyPressed variables
			while (SDL_PollEvent(&checkEvents) != 0)
			{
				if (checkEvents.type == SDL_KEYUP)
				{
					switch (checkEvents.key.keysym.sym)
					{
					case SDLK_LEFT:
						leftPressed = false;
						break;
					case SDLK_RIGHT:
						rightPressed = false;
						break;
					case SDLK_DOWN:
						downPressed = false;
						break;
					case SDLK_UP:
						upPressed = false;
						break;
					}
				}
				if (checkEvents.type == SDL_KEYDOWN)
				{
					switch (checkEvents.key.keysym.sym)
					{
					case SDLK_ESCAPE:
						exitLoop = true;
						break;
					case SDLK_LEFT:
						leftPressed = true;
						break;
					case SDLK_RIGHT:
						rightPressed = true;
						break;
					case SDLK_DOWN:
						downPressed = true;
						break;
					case SDLK_UP:
						upPressed = true;
						break;
						//Shoot a green laser
					case SDLK_SPACE:
						spacePressed = true;
						break;

					}
				}
			}

			// Using the KeyPressed variables to change speed, thus position
			if (leftPressed == true)
			{
				xspeed=-1;
			}
			if (rightPressed == true)
			{
				xspeed=1;
			}
			if (upPressed == true)
			{
				redRect.y += xspeed;
			}
			if (rightPressed == false && leftPressed == false)
			{
				xspeed = 0;
			}
			if (rightPressed == true && leftPressed == true)
			{
				xspeed = 0;
			}



			//Logic GRAVITY

			if (redRect.y + 150 >= greenRect.y && grounded == false)
			{
				grounded = true;
			}
			
			if (grounded == true)
			{
				yspeed = 0;
			}



			//Move the player
			redRect.y += yspeed;
			redRect.x += xspeed;



			//SDL_SetRenderDrawColor(renderer, 65, 105, 255, 255);
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, back, NULL, NULL);



			//SET the Draw color for the rectangle
			//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderCopy(renderer,ShipTexture, NULL, &redRect);
		    //SDL_RenderFillRect(renderer, &redRect);


			//Place the ground Man
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			SDL_RenderFillRect(renderer, &greenRect);
			//Update the Render
			SDL_RenderPresent(renderer);
			//Delay 5 milliseconds
			//SDL_Delay(5);
		}

		SDL_DestroyTexture(back);
		SDL_DestroyTexture(ShipTexture);
		SDL_DestroyTexture(laserTexture);

		SDL_FreeSurface(Background);
		SDL_FreeSurface(Ship);
		SDL_FreeSurface(Laser);

		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);

		Mix_FreeMusic(bgm);

		renderer = nullptr;
		window = nullptr;
		back = nullptr;
		ShipTexture = nullptr;
		laserTexture = nullptr;
		 
	
		IMG_Quit();
		Mix_Quit();
		
		return 0;
	}
}




