#ifndef CLIPPER_H
#define CLIPPER_H

#include "preinclude.h"
#include "sbox.h"
#include <vector>
using std::vector;

//usage:
// step 1. init using the method 'initFrom', e.g. MyClipper.initFrom("resource/cp1") see the file "resource/cp1" for details
// step 2. now the class is ready, just use as usual
// step 3. when the class is no longer needed, use static method Clipper::clean() to clean
//
/* An Example

Clipper MyC1;
Clipper MyC2("resource/cp1");

MyC1.initFrom("resource/cp2");

MyC1.setX(200);
...

Clipper::clean();
return;

*/
class Clipper
{
	public:
		Clipper();
		Clipper(const string & filename);
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

		//init the frames, from a floder "$filename"
		bool initFrom(const string & filename);
		static void clean();

#ifdef DEBUG
		//debug
		void debugPrint();
#endif
	protected:
		// the frame struct, to store a frame's information
		struct Frame
		{
			SDL_Surface * surface;
			string label;
			//methods
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
		//the FrameRecord, is used to record loaded pictures.
		// if a record exist, then fetch it form a FrameRecord.
		struct FrameRecord
		{
			string filename;
			SDL_Rect rect;
			SDL_Surface * surface;

			FrameRecord(){}
			FrameRecord(string fn, 
					SDL_Rect rt, 
					SDL_Surface * surface0 = NULL):
				filename(fn),
				rect(rt),
				surface(surface0){}

			bool operator==(const FrameRecord & fmRec)const
			{
				return (filename == fmRec.filename)&&
					(rect.x == fmRec.rect.x)&&
					(rect.y == fmRec.rect.y)&&
					(rect.w == fmRec.rect.w)&&
					(rect.h == fmRec.rect.h);
			}
		};
		static vector<FrameRecord> _fm_records;

		vector< Frame >  _frames;

		// methods
		bool _changeFrame(int num);

		// add some frames from a file(*.png), the format is defined 
		//    between begin and end
		bool _addFramesFromFile(string filename, string::iterator begin, string::iterator end);
};

#endif
