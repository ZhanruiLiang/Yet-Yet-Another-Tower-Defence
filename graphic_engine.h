#ifndef GRAPHIC_ENGINE_H
#define GRAPHIC_ENGINE_H
#include "preinclude.h"
#include "clipper.h"
#include "sbox.h"
#include <list>
using std::list;

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
		};


		typedef list<Node>::iterator iterator;
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
	private:
		double _FPS;
		list<Node> _cps;

		Time_t _start_time;
		Time_t _current_time;
		//the next "should be" update time
		Time_t _next_time;

		//methods
		bool _clipperCompareLess(GraphicEngine::iterator,GraphicEngine::iterator);
		void _sortClipper();
};

#endif
