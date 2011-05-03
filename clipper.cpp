#include "clipper.h"

typedef vector<SDL_Surface*>::iterator SurfaceIter;

Clipper::Clipper():_x(0),_y(0),
	_width(0),_height(0),
	_scale(1.0),
	_visible(false),
	_frame(0),
	_stop(false)
{

}

// initialize the clipper from files
// the filename is a floder, it must contians:
// 		1) index.tdidx: a plain ASCII file
//		2) *.png: the frames, one or more these files

bool Clipper::initFrom(const char * filename)
{
	//TODO: think about the stucture of the tdidx file
}

Clipper::~Clipper()
{
	for(SurfaceIter it = _surfaces.begin();
			it != _surfaces.end();
			it ++)
	{
		SDL_FreeSurface(*it);
	}
}
void Clipper::setX(int x)
{
	_x = x;
}

void Clipper::setY(int y)
{
	_y = y;
}

int Clipper::getX()
{
	return _x;
}

int Clipper::getY()
{
	return _y;
}


// if the scale is set, the height and width will be reset to new value
// 	scale * widht0 = width
//	width0 = width / scale
//  width1 / scale1 = width2 / scale2
//  width2 = width1 * scale2 / scale1
void Clipper::setScale(double scale)
{
	if(scale < 0.001)
		scale = 0.001;
	_width = _width * scale / _scale;
	_height = _height * scale / _scale;
	_scale = scale;
}

double Clipper::getScale()
{
	return _scale;
}

void Clipper::setVisible(bool val)
{
	_visible = val;
}

bool Clipper::getVisible()
{
	return _visible;
}

SDL_Surface * Clipper::getSurface()
{
	return _surfaces[_frame];
}

bool Clipper::_changeFrame(int num)
{
	if(num < _surfaces.size())
		_frame = num;
	else
	{
#ifdef DEBUG
		cout << "Error! " << "Frame " << num << " out of range.\n";
#endif
		return false;
	}
	return true;
}

bool Clipper::gotoAndPlay(int num)
{
	bool flag;
	flag = _changeFrame(num);
	if(!flag) return false;
	_stop = false;
	return true;
}

bool Clipper::gotoAndStop(int num)
{
	bool flag;
	flag = _changeFrame(num);
	if(!flag) return false;
	_stop = true;
	return true;
}

int Clipper::currentFrame()
{
	return _frame;
}

void Clipper::play()
{
	_stop = false;
}

void Clipper::stop()
{
	_stop = true;
}
