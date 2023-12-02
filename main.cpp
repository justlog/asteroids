#include <SDL.h>
#include <stdio.h>
#include "common.h"
#include "game.h"
#define EXIT(s) printf("SDL could not " s ", SDL_Error %s\n", SDL_GetError()); exit(1);

#define RENDER_HEIGHT 720
#define RENDER_WIDTH 720

#define SHIP_TEXTURE_WIDTH 50
#define SHIP_TEXTURE_HEIGHT 50



struct AnimatedSprite {
	SDL_Texture** frames;
	u32 count;
	u32 index;
	bool active;
};

//static SDL_Texture *shipTexture;
static SDL_Texture *asteroidTexture;
static AnimatedSprite shipSprite;

SDL_Texture* LoadTexture(SDL_Renderer* renderer, const char* path)
{
	SDL_Surface* s = SDL_LoadBMP(path);
	if(s == NULL){
		EXIT("load bmp");
	}
	SDL_Texture* t = SDL_CreateTextureFromSurface(renderer, s);
	if(t == NULL){
		EXIT("create texture from surface");
	}
	SDL_FreeSurface(s);
	return t;
}
AnimatedSprite LoadAnimatedSprite(SDL_Renderer* renderer, const char** paths, u32 count)
{
	AnimatedSprite sprite = {0, count, 0, false};
	sprite.frames = (SDL_Texture**)malloc(sizeof(SDL_Texture*)*count);
	SDL_Texture** frames = sprite.frames;
	while(count > 0){
		*frames = LoadTexture(renderer, *paths++);
		frames++;
		count -= 1;
	}
	return sprite;
}
void RenderGame(SDL_Renderer* renderer)
{
	//TODO: Not working properly. check numbers in debugger.
	const u32 HALF_SHIP_WIDTH = SHIP_TEXTURE_WIDTH/2;
	SDL_Rect r = {(i32)(RENDER_WIDTH*globalShip.pos.x - HALF_SHIP_WIDTH), (i32)(RENDER_HEIGHT - RENDER_HEIGHT*globalShip.pos.y)-25, 50, 50};
	f64 angle = (f64)globalShip.angle;


	SDL_Texture* shipTexture = shipSprite.frames[0];
	if(shipSprite.active || shipSprite.index != 0){
		if(shipSprite.index == shipSprite.count){
			shipSprite.index = 0;
		}
		else{
			shipTexture = shipSprite.frames[shipSprite.index++];
		}
	}
	SDL_RenderCopyEx(renderer, shipTexture, NULL, &r, 90.0+angle, NULL, SDL_RendererFlip::SDL_FLIP_NONE);
}
int main(int, char**)
{
	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		EXIT("init SDL");
	}

	window = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, RENDER_WIDTH, RENDER_HEIGHT, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
	//No resize for now... need to figure out how to keep aspect ratio.
	//window = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, RENDER_WIDTH, RENDER_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		EXIT("create window");
	}
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == NULL){
		EXIT("create renderer");
	}

	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PixelFormatEnum::SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, RENDER_WIDTH, RENDER_HEIGHT);
	if(texture == NULL){
		EXIT("create texture");
	}

	void* pixels = calloc(1, RENDER_HEIGHT*RENDER_WIDTH*4);
	if(pixels == NULL){
		EXIT("allocate pixels");
	}
	RenderingContext renderCtx = {0};
	renderCtx.pixels = pixels;
	renderCtx.bpp = 4;
	renderCtx.height = RENDER_HEIGHT;
	renderCtx.width = RENDER_WIDTH;
	renderCtx.pitch = renderCtx.bpp * renderCtx.width;

	asteroidTexture = LoadTexture(renderer, "assets/asteroid.bmp");
	const char* shipSpritePaths[] = {
		"assets/ship_frames/ship_f1.bmp",
		"assets/ship_frames/ship_f2.bmp",
		"assets/ship_frames/ship_f3.bmp",
		"assets/ship_frames/ship_f4.bmp",
		"assets/ship_frames/ship_f5.bmp",
		"assets/ship_frames/ship_f6.bmp",
		"assets/ship_frames/ship_f7.bmp",
	};
	shipSprite = LoadAnimatedSprite(renderer, shipSpritePaths, 7);


	bool quit = false;
	Controls controls = {0};
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	u32 startTime = SDL_GetTicks();
	u32 endTime = SDL_GetTicks();
	while(!quit)
	{
		u32 dt = endTime - startTime;
		SDL_Event e;
		while (SDL_PollEvent(&e) != NULL){
			switch(e.type){
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:
					if(e.key.keysym.sym == SDLK_RIGHT){
						controls.rightPressed = true;
					}
					else if(e.key.keysym.sym == SDLK_LEFT){
						controls.leftPressed = true;
					}
					else if(e.key.keysym.sym == SDLK_UP){
						controls.upPressed = true;
						shipSprite.active = true;
					}
					break;
				case SDL_KEYUP:
					if(e.key.keysym.sym == SDLK_RIGHT){
						controls.rightPressed = false;
					}
					else if(e.key.keysym.sym == SDLK_LEFT){
						controls.leftPressed = false;
					}
					else if(e.key.keysym.sym == SDLK_UP){
						controls.upPressed = false;
						shipSprite.active = false;
					}
					break;
				default:
					break;
			}
		}
		if(dt > 1000.0/60.0){
			startTime = endTime;
			SDL_RenderClear(renderer);
			SDL_Rect r = {RENDER_WIDTH/2-25, RENDER_HEIGHT/2-25, 50, 50};
			GameLoop(controls, dt);
			//TODO: Set a boundary of game logic vs rendering. does the game logic return state for the rendering to look at?
			RenderGame(renderer);
			SDL_RenderPresent(renderer);
		}
		endTime = SDL_GetTicks();
	}
	return 0;
}
