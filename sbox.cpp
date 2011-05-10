#include "preinclude.h"
#include "sbox.h"

namespace sbox
{
	//vars
	int SCREEN_WIDTH = 640;
	int SCREEN_HEIGHT = 480;
	int SCREEN_BPP = 32;
	int MAX_FPS = 24;
	SDL_Surface * screen = NULL;

	vector<ColorNamePair> _color_name;

	//funcs
	bool initSDL()
	{
		if( SDL_Init( SDL_INIT_EVERYTHING ) == -1)
			return false;

		screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, 
				SCREEN_BPP, SDL_HWSURFACE|SDL_DOUBLEBUF);

		if( screen == NULL )
			return false;

		if( TTF_Init() == -1)
			return false;

		SDL_WM_SetCaption( "SDL window", NULL );

		//init color names
		initColorName();
		return true;
	}

	void cleanSDL()
	{
		SDL_Quit();
	}


	SDL_Surface* loadImage( string filename )
	{
		SDL_Surface* loadedImage = NULL;

		SDL_Surface* optimizedImage = NULL;

		//Load the image
		loadedImage = IMG_Load( filename.c_str() );

		//If the image loaded
		if( loadedImage != NULL )
		{
			optimizedImage = SDL_DisplayFormat( loadedImage );
			SDL_FreeSurface( loadedImage );
		}
		//Return the optimized surface
		return optimizedImage;
	}

	void applySurface( 
			int x,
			int y,
			SDL_Surface* source,
			SDL_Surface* destination,
			SDL_Rect* clip )
	{
		SDL_Rect offset;

		offset.x = x;
		offset.y = y;

		SDL_BlitSurface( source, clip, destination, &offset );
	}

	/*
	 * Return the pixel value at (x, y)
	 * NOTE: The surface must be locked before calling this!
	 */
	Uint32 getPixel(SDL_Surface *surface, int x, int y)
	{
		int bpp = surface->format->BytesPerPixel;
		/* Here p is the address to the pixel we want to retrieve */
		Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

		switch(bpp) {
			case 1:
				return *p;

			case 2:
				return *(Uint16 *)p;

			case 3:
				if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
					return p[0] << 16 | p[1] << 8 | p[2];
				else
					return p[0] | p[1] << 8 | p[2] << 16;

			case 4:
				return *(Uint32 *)p;

			default:
				return 0;       /* shouldn't happen, but avoids warnings */
		}
	}

	SDL_Color get_SDL_Color(Uint8 r, Uint8 g, Uint8 b)
	{
		SDL_Color color;
		color.r = r;
		color.g = g;
		color.b = b;
		return color;
	}

	SDL_Rect getRect(int x, int y, int w, int h)
	{
		SDL_Rect rect;
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;
		return rect;
	}

	SDL_Surface* newSurface(int w, int h)
	{
		SDL_Surface * surface = NULL;
		SDL_Surface * surface1 = NULL;
		//surface = SDL_CreateRGBSurface(0,w,h,32,0,0,0,0);
		surface = SDL_CreateRGBSurface(0,w,h,32,
				0xff000000,
				0x00ff0000,
				0x0000ff00,
				0x000000ff);
		
		surface1 = SDL_DisplayFormat(surface);
		SDL_FreeSurface(surface);
		return surface1;
	}

	void initColorName()
	{
		_color_name.push_back(ColorNamePair("white", SDL_MapRGBA(screen->format, 0xff, 0xff, 0xff, 0xff)));
		_color_name.push_back(ColorNamePair("black", SDL_MapRGBA(screen->format, 0x00, 0x00, 0x00, 0xff)));

		_color_name.push_back(ColorNamePair("red", SDL_MapRGBA(screen->format, 0xff, 0, 0, 0xff)));
		_color_name.push_back(ColorNamePair("green", SDL_MapRGBA(screen->format, 0, 0xff, 0, 0xff)));
		_color_name.push_back(ColorNamePair("blue", SDL_MapRGBA(screen->format, 0, 0, 0xff, 0xff)));

	}

	Uint32 getColorByName(string colorName)
	{
		vector<ColorNamePair>::iterator i;
		for(i = _color_name.begin(); i != _color_name.end(); i++)
			if(i->name == colorName)
				return i->color;
		cout << "Warning: No color " << colorName << " found!\n";
		return _color_name[0].color;
	}

	void delay(int time)
	{
		if(time == 0)
			time = 1000/MAX_FPS;
		SDL_Delay(time);
	}
}
