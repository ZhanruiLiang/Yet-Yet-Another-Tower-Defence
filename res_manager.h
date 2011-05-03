#ifndef RES_MANAGER_H
#define RES_MANAGER_H

#include "preinclude.h"
#include <vector>
using std::vector;
#include <map>
using std::map;

class ResManager
{
	public:
		ResManager();
		~ResManager();

		typedef int ID_t;

		SDL_Surface * getSurface(ID_t sur_id);
		bool deleteSurface(ID_t sur_id);
		ID_t addSurface(SDL_Surface * surface);
	private:

		struct Node
		{
			ID_t id;
			SDL_Surface * surface;

			Node(ID_t id0, SDL_Surface * surface0):id(id0),surface(suface0){}
		};

		vector<Node> _nodes;
		ID_t _id_count;
};

#endif
