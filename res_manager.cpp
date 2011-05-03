#include "res_manager.h"

ResManager::ResManager()
{
	_id_count = 0;
}

ResManager::~ResManager()
{

	for(vector<Node>::iterator it = _nodes.begin();
			it != _nodes.end();
			it ++)
	{
		SDL_FreeSurface(it->surface);
	}
}

SDL_Surface * ResManager::getSurface(ID_t sur_id)
{
	for(vector<Node>::iterator it = _nodes.begin();
			it != _nodes.end();
			it ++)
	{
		if(it->id == sur_id)
		{
			//find it!
			return it->surface;
		}
	}
	return NULL;
}

bool ResManager::deleteSurface(ID_t sur_id)
{
	for(vector<Node>::iterator it = _nodes.begin();
			it != _nodes.end();
			it ++)
	{
		if(it->id == sur_id)
		{
			// found it, delete it
			_nodes.erase(it);
			return true;
		}
	}
	return false;
}

ResManager::ID_t ResManager::addSurface(SDL_Surface * surface)
{
	_id_count++;
	_nodes.push_back(Node(_id_count, surface));
	return _id_count;
}

