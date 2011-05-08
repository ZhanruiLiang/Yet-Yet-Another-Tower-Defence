#ifndef CLIPPER_H
#define CLIPPER_H

#include "preinclude.h"
#include "sbox.h"
#include <vector>
#include "res_manager.h"
using std::vector;

class Clipper
{
	public:
		Clipper();
		~Clipper();
		static void setResManager(ResManager * ptr_rm);

		
		//set,get x, y
		void setX(int x);
		void setY(int y);
		int getX();
		int getY();

		//XXX: hide some features first
		/*
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
		*/

		void setDepth(int depth);
		int getDepth();

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
		int totalFrame();

		void play();

		void stop();

		void loop();

		//init the static members, from a floder "$filename"
		static bool initFrom(const string & filename);
	protected:
		typedef ResManager::ID_t ID_t;
		// the frame struct, to store a frame's information
		struct Frame
		{
			ID_t id;
			string label;
			Frame(){}
			Frame(ID_t id0, string label0):id(id0),label(label0){}
		};

		int _x, _y;
		int _width, _height;
		double _scale;
		int _depth;
		bool _visible;
		int _frame;
		bool _stop;

		static ResManager * _res_manager;
		static vector< Frame >  _frames;

		// methods
		bool _changeFrame(int num);

		// static methods
		// add some frames from a file(*.png), the format is defined between
		//    between begin and end
		bool static _addFramesFromFile(string filename, string::iterator begin, string::iterator end);
		// add a frame from a specific rect of the source surface
		void static _addFrame(SDL_Surface * surface, SDL_Rect rect, string label);
};

#endif
