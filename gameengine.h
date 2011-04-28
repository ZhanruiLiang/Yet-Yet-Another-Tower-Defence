#ifndef ENGINE_H
#define ENGINE_H

#include <list>

class Creep;
class Tower;
class GridMap;

class Engine {
    
    public:

        Engine();
        ~Engine();

    private:

        std::list<Creep *> _creeps;
        std::list<Tower *> _towers;
};

#endif
