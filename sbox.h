#ifndef SBOX_H
#define SBOX_H
#include "preinclude.h"
#include <vector>
using std::vector;

// a namespace provide some often use function's

namespace sbox
{
	struct ColorNamePair
	{
		string name;
		Uint32 color;
		ColorNamePair(string name_, Uint32 color_)
		{
			name = name_;

			color = color_;
		}
	};

	// constants and variables

	extern int SCREEN_WIDTH;
	extern int SCREEN_HEIGHT;
	extern int SCREEN_BPP;
	extern int MAX_FPS;

	extern vector<ColorNamePair> _color_name;

	extern SDL_Surface* screen;

	// functions
	void initColorName();
	bool initSDL();
	void cleanSDL();
	//
	SDL_Surface* loadImage(string filename);
	SDL_Surface* newSurface(int w, int h);
	void applySurface(
			int x,
			int y,
			SDL_Surface* source,
			SDL_Surface* destination,
			SDL_Rect* clip = NULL );
	Uint32 getPixel(SDL_Surface *, int x, int y);

	//
	SDL_Color get_SDL_Color(Uint8 r, Uint8 g, Uint8 b);
	SDL_Rect getRect(int x, int y, int w = 0, int h = 0);
	Uint32 getColorByName(string colorName);
	//
	void delay(int time = 0);
}
#endif
