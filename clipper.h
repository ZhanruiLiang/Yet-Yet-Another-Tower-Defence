#ifndef CLIPPER_H
#define CLIPPER_H

#include "preinclude.h"
#include "sbox.h"
#include <vector>
using std::vector;

class Clipper
{
	public:
		Clipper();
		~Clipper();
		bool initFrom(const char * filename);
		//set,get x, y
		void setX(int x);
		void setY(int y);
		int getX();
		int getY();

		//set,get the scale, width, height
		//attention, these three ones with keep sync automatically.
		//e.g. if you set the scale, the other two will change, too

		// scale in [0,1]
		void setScale(double scale);
		double getScale();
		// width and height
		void setWidth(int width);
		double getWidth();
		void setHeight(double height);
		double getHeight();

		// visible
		void setVisible(bool val);
		bool getVisible();

		// get the surface of this clipper, usually use this surface to blit
		SDL_Surface * getSurface();

		//some methods use to control the frame playing, if success, return true
		bool gotoAndPlay(int num);
		//bool gotoAndPlay(const string & label);
		bool gotoAndStop(int num);
		//bool gotoAndStop(const string & lable);

		int currentFrame();

		void play();

		void stop();

	private:
		int _x, _y;
		int _width, _height;
		double _scale;
		bool _visible;
		int _frame;
		int _frame_cnt;
		bool _stop;
		vector< SDL_Surface* >  _surfaces;

		// methods
		bool _changeFrame(int num);
};

#endif
