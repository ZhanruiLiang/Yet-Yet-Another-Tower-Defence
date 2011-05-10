#ifndef CLIPPER_H
#define CLIPPER_H

#include "preinclude.h"
#include "sbox.h"
#include <vector>
using std::vector;

//usage:
// step 1. init using the static method 'initFrom', e.g. Clipper::initFrom("resource/cp1") see cp1 for details
// step 2. now the class is ready, just use as usual
// step 3. when the class is no longer needed, use static method Clipper::clean() to clean
//
// You may want to derive this class to make more then one type of sprites. To do this:
// class TowerClipper: public Clipper{
//		private:
//          ...
//		public:
//			...
// };
// you don't need to overload any methods
class Clipper
{
	public:
		Clipper();
		~Clipper();
		
		//set,get x, y
		void setX(int x);
		void setY(int y);
		int getX();
		int getY();

		// width and height
		void setWidth(int width);
		int getWidth();
		void setHeight(double height);
		int getHeight();

		//depth
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
		static void clean();
	protected:
		// the frame struct, to store a frame's information
		struct Frame
		{
			SDL_Surface * surface;
			string label;
			Frame(){}
			Frame(SDL_Surface * surface0, string label0):surface(surface0)
														 ,label(label0){}
		};

		SDL_Rect _rect;
		double _scale;
		int _depth;
		bool _visible;
		int _frame;
		bool _stop;

	private:
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
