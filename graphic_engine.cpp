#include "graphic_engine.h"
#include <algorithm>

GraphicEngine::GraphicEngine():
	_FPS(30)
{
}

GraphicEngine::~GraphicEngine()
{
	for(iterator it = _cps.begin(); it != _cps.end(); it++)
	{
		//XXX
	}
	sbox::cleanSDL();
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
	sbox::initSDL();
	sbox::MAX_FPS = _FPS;
	_start_time = SDL_GetTicks();
}

bool GraphicEngine::_clipperCompareLess(GraphicEngine::iterator a, GraphicEngine::iterator b)
{
	return a->cp->getDepth() < b->cp->getDepth();
}

void GraphicEngine::_sortClipper()
{
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
	SDL_FillRect(sbox::screen, &sbox::getRect(0,0,sbox::SCREEN_WIDTH,sbox::SCREEN_HEIGHT), sbox::getColorByName("white"));
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
