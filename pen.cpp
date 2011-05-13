#include "pen.h"
#include "sbox.h"


Pen::Pen():_surface(NULL),
	_color(Uint32(0x000000ff)),
	_width(1),
	_cur_x(0),
	_cur_y(0)
{

}
Pen::Pen(SDL_Surface * surface):_surface(surface),
	_color(Uint32(0x000000ff)),
	_width(1),
	_cur_x(0),
	_cur_y(0)
{

}

void Pen::moveTo(int x, int y)
{
	_cur_x = x;
	_cur_y = y;
}

void Pen::lineTo(int x, int y)
{
	lineColor(_surface, _cur_x, _cur_y, x, y, _color);
	//thickLineColor(_surface, _cur_x, _cur_y, x, y, _width, _color);
	_cur_x = x;
	_cur_y = y;
}

void Pen::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	_color = (r<<24) + (g<<16) + (b<<8) + a;
}

void Pen::setColor(Uint32 color)
{
	_color = color;
}

void Pen::setWidth(int width)
{
	_width = width;
}

void Pen::setSurface(SDL_Surface * surface)
{
	_surface = surface;
}

// AAPen
AAPen::AAPen(SDL_Surface * surface):Pen(surface)
{
}
void AAPen::lineTo(int x, int y)
{
	aalineColor(_surface, _cur_x, _cur_y, x, y, _color);
	_cur_x = x;
	_cur_y = y;
}
