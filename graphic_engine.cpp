#include "graphic_engine.h"
#include "preinclude.h"
#include <algorithm>

GraphicEngine::GraphicEngine()
{
	_FPS = 24;
}

GraphicEngine::~GraphicEngine()
{
	for(iterator it = _cps.begin(); it != _cps.end(); it++)
	{
		//XXX
	}
}

GraphicEngine::iterator GraphicEngine::addClipper(Clipper *ptr_cp)
{
	_cps.push_back(Node(ptr_cp));
	return _cps.end() - 1;
}

bool GraphicEngine::deleteClipper(GraphicEngine::iterator it_cp)
{
	_cps.erase(it_cp);
	return true;
}

void GraphicEngine::setFPS(double fps)
{
	_FPS = fps;
	sbox::MAX_FPS = fps;
}

double GraphicEngine::getFPS()
{
	return _FPS;
}

GraphicEngine::iterator GraphicEngine::begin()
{
	return _cps.begin();
}

GraphicEngine::iterator GraphicEngine::end()
{
	return _cps.end();
}

void GraphicEngine::init()
{
	_next_time = _start_time = SDL_GetTicks();
#ifdef DEBUG
	marks.clear();
	cout << "first size: " << marks.size() << '\n';
	_surface_mark = sbox::loadImage("resource/debug/mark.png");
#endif
}


void GraphicEngine::_sortClipper()
{
	//std::sort(_cps.begin(), _cps.end());
	/*
	   //slow implementation
	Node temp;
	iterator begin,end,it,it1;
	begin = _cps.begin();
	end = _cps.end();
	
	while(begin != end)
	{
		end--;
		
		it = begin;
		it1 = it;
		it1++;
		while(it != end)
		{
			if(!_clipperCompareLess(it,it1))
			{
				//swap
				temp = *it; *it = *(it1); *(it1) = temp;
			}
			it++;
			it1++;
		}
	}
	*/
}

void GraphicEngine::loop()
{
	_current_time = SDL_GetTicks();
	if(_current_time >= _next_time)
	{
		for(iterator it = _cps.begin(); it != _cps.end(); it++)
			it->cp->loop();
	}
	else
		return;

	_sortClipper();
	//refresh
	SDL_FillRect(sbox::screen, 
			&sbox::screen->clip_rect, 
			sbox::getColorByName("white"));
	//blit all
	for(iterator it = _cps.begin(); it != _cps.end(); it++)
	{
		Clipper * cp = it->cp;
		//blit
		SDL_Rect rect = sbox::getRect(cp->getX(), cp->getY()); 
		SDL_BlitSurface(cp->getSurface(),
				NULL,
				sbox::screen,
				&rect);
	}
	//debug blit
#ifdef DEBUG
	for(vector<Mark>::iterator it = marks.begin();
			it != marks.end(); it++)
	{
		SDL_Rect rect = sbox::getRect(it->x, it->y);
		SDL_BlitSurface(_surface_mark, NULL, sbox::screen, &rect);
	}
	vector<Mark>::iterator it1,it2;
	for(it1 = marks.begin(); it1 != marks.end(); it1 = it2)
	{
		it2 = it1 + 1;
		if(it1->keep == false)
			marks.erase(it1);
	}
#endif

	SDL_Flip(sbox::screen);

	//update 
	_current_time = SDL_GetTicks();
	while(_next_time <= _current_time)
	{
		//update _next_time
		_next_time += 1000/_FPS;
	}
}
