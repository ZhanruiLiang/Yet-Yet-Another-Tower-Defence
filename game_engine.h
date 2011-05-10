#ifndef ENGINE_H
#define ENGINE_H

#include <list>

class Creep;
class Tower;
class GridMap;

class GameEngine {
    
    public:

        GameEngine();
        ~GameEngine();

        void loop();

    private:
        
        void _handleEvents();
        void _updateCreeps();
        void _updateTowers();
        void _updateBullets();

        std::list<Creep *> _creeps;
        std::list<Tower *> _towers;

        GridMap *_grid_map;
};

#endif
