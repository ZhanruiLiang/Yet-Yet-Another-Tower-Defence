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
	return _cps.end();
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
	std::cout << "start: " << _start_time << '\n';
}


void GraphicEngine::_sortClipper()
{
	std::sort(_cps.begin(), _cps.end());
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
	SDL_FillRect(sbox::screen, &sbox::screen->clip_rect, sbox::getColorByName("white"));
	//blit all
	for(iterator it = _cps.begin(); it != _cps.end(); it++)
	{
		Clipper * cp = it->cp;
		//blit
		SDL_BlitSurface(cp->getSurface(),
				NULL,
				sbox::screen,
				&sbox::getRect(cp->getX(), cp->getY()));
	}
	SDL_Flip(sbox::screen);

	//update 
	_current_time = SDL_GetTicks();
	while(_next_time <= _current_time)
	{
		//update _next_time
		_next_time += 1000/_FPS;
	}
}
