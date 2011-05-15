#ifndef GRAPHIC_ENGINE_H
#define GRAPHIC_ENGINE_H
#include "preinclude.h"
#include "clipper.h"
#include "sbox.h"
#include <vector>
using std::vector;


// Name convention in this class : cp means clipper
/*

usage:

GraphicEngine gEngine;
gEngine.init();

Clipper cp1;
DeriveClipper cp2;
// init the clippers
...
//

gEngine.addClipper(&cp1);
gEngine.addClipper(&cp2);


   */
class GraphicEngine
{
	public:
		GraphicEngine();
		~GraphicEngine();

		void init();

		struct Node
		{
			Clipper * cp;
			Node(){}
			Node(Clipper * cp0):cp(cp0){}
			bool operator<(const Node & rhs)const
			{
				return cp->getDepth() < rhs.cp->getDepth();
			}
		};


		typedef vector<Node>::iterator iterator;
		typedef Uint32 Time_t;

		//clipper operating
		iterator addClipper(Clipper * ptr_cp);
		bool deleteClipper(iterator it_cp);

		//call this to make the graphic run
		void loop();

		void setFPS(double fps);
		double getFPS();

		//this class is iteratable
		iterator begin();
		iterator end();
#ifdef DEBUG
		void addMark(int x, int y, string type = "normal")
		{
			static int cnt = 0;
			cout << "cnt = " << cnt++ << '\n';
			if(type == "keep")
			{
				//marks.push_back(Mark(x,y,true));
			}
			else
			{
				cout << "(" << x << "," << y << '\n';
				cout << "size of makrs: " << (int)marks.size() << '\n';
				//marks.push_back(Mark(x,y));
			}
		}

#endif
	private:
#ifdef DEBUG
		struct Mark
		{
			int x, y;
			bool keep;
			Mark(){}
			Mark(int x, int y, bool keep = false):x(x),y(y),keep(keep){}
		};

		vector<Mark> marks;
		SDL_Surface * _surface_mark;
#endif

		double _FPS;
		vector<Node> _cps;

		Time_t _start_time;
		Time_t _current_time;
		//the next "should be" update time
		Time_t _next_time;

		//methods
		void _sortClipper();
};

#endif
