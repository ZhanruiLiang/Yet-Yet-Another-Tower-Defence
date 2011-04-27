#ifndef SBOX_H
#define SBOX_H
#include "preinclude.h"
#include <vector>
using std::vector;

// a class to provide some often use function's
class Sbox
{
	public:
		Sbox();
		//
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

		//
		SDL_Color get_SDL_Color(Uint8 r, Uint8 g, Uint8 b);
		SDL_Rect getRect(int x, int y, int w = 0, int h = 0);
		Uint32 getColorByName(string colorName);
		void delay(int time = 0);

		// variables
		SDL_Surface* screen;

		static const int SCREEN_WIDTH = 640;
		static const int SCREEN_HEIGHT = 480;
		static const int SCREEN_BPP = 32;
		static const int MAX_FPS = 40;
	private:
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

		void initColorName();
		vector<ColorNamePair> _color_name;
};
#endif
