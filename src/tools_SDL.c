#include "chess.h"

void			LoadPic_SDL(const char *path, const unsigned int x, const unsigned int y)
{
	SDL_Surface		*surface;
	SDL_Texture		*texture;
	SDL_Rect		rect;

	surface = NULL;
	texture = NULL;
	if (!(surface = IMG_Load(path)))
		ExitWithError_SDL("IMG_Load");
	texture = SDL_CreateTextureFromSurface(RENDERER, surface);
	SDL_FreeSurface(surface);
	if (!texture)
		ExitWithError_SDL("SDL_CreateTextureFromSurface");
	if (SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h) != 0)
		ExitWithError_SDL("SDL_QueryTexture");
	rect.x = x;
	rect.y = y;
	if (SDL_RenderCopy(RENDERER, texture, NULL, &rect) != 0)
		ExitWithError_SDL("SDL_RenderCopy");
	SDL_DestroyTexture(texture);
}

 void			Exit_SDL(void)
{
	if (RENDERER)
		SDL_DestroyRenderer(RENDERER);
	if (WINDOW)
		SDL_DestroyWindow(WINDOW);
	SDL_Quit();
}

void			ExitWithError_SDL(const char *str)
{
	SDL_Log("ERROR %s : %s\n", str, SDL_GetError());
	Exit_SDL();
	exit(EXIT_FAILURE);
}

void			OpenWindow_SDL(const char *str, const unsigned int x, const unsigned int y)
{
	// Create window
	if (!(WINDOW = SDL_CreateWindow(str, SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, x, y, SDL_WINDOW_SHOWN)))
		ExitWithError_SDL("SDL_CreateWindow");
	// Create renderer
	if (!(RENDERER = SDL_CreateRenderer(WINDOW, -1, SDL_RENDERER_PRESENTVSYNC)))
		ExitWithError_SDL("SDL_CreateRenderer");
	// Set blend mode (superposition des couleurs en fonction de a dans rgba)
	if (SDL_SetRenderDrawBlendMode(RENDERER, SDL_BLENDMODE_MOD) != 0)
		ExitWithError_SDL("SDL_SetRenderDrawBlendMode");
}

void			Init_SDL(void)
{
	// Init SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		ExitWithError_SDL("SDL_Init");
	// start Exit_SDL at exit
	atexit(Exit_SDL);
}
