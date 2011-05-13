#ifndef PEN_H
#define PEN_H
#include "preinclude.h"

// Usage: 
//		1. construct a pen
//		2. set the pen using 
//			a. setColor.   b. setWidth   c. setSurface
//		3. use it using:
//			a. moveTo.     b. lineTo
class Pen
{
	public:
		Pen();
		Pen(SDL_Surface * surface);

		virtual void moveTo(int x, int y);
		virtual void lineTo(int x, int y);

		void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0xff);
		void setColor(Uint32 color);
		void setWidth(int width);

		//set the target surface
		void setSurface(SDL_Surface * surface);
	protected:

		SDL_Surface * _surface;
		Uint32 _color;
		int _width;
		//the current position
		int _cur_x;
		int _cur_y;

};

class AAPen:public Pen
{
	public:
		AAPen(SDL_Surface * surface);
		void lineTo(int x, int y);
	private:
		void setWidth(int){};
};
#endif
