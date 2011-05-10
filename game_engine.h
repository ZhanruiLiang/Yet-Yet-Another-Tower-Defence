#ifndef ENGINE_H
#define ENGINE_H

#include <list>

class Creep;
class CreepFactory;
class Tower;
class TowerFactory;
class Bullet;
class BulletFactory;
class GridMap;



class GameEngine {
    
    public:

        GameEngine();
        ~GameEngine();

        void run();

    private:
        
        void _handleEvents();
        void _updateCreeps();
        void _updateTowers();
        void _updateBullets();

        std::list<Creep *> _creeps;
        std::list<Tower *> _towers;
        std::list<Bullet *> _bullets;

        GridMap *_grid_map;

        CreepFactory *_creep_factory;
        TowerFactory *_tower_factory;
        BulletFactory *_bullet_factory;
};

#endif
