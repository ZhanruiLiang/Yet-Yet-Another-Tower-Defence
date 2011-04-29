#include "gridmap.h"
#include "creep.h"

#include <cassert>  // For: assert
#include <cstddef>  // For: NULL

Creep::Creep()
    :_grid_map(NULL),
     _x(.0),
     _y(.0),
     _velocity(.0),
     _health(0),
     _type(0){     
}

Creep::~Creep() {
}

// Let the creep know the gridmap so that it may move
// according to the directions marked on the map
void Creep::setGridMap(GridMap *grid_map) {
    _grid_map = grid_map;
} 

// Update the creep (performs move)
// This method should be called in each iteration of the
// game loop
void Creep::update() {
#ifdef DEBUG
    assert(_grid_map != NULL);
#endif

    int x = (int)_x;
    int y = (int)_y;
    GridMap::Direction dir = _grid_map->getDirectionAt(x, y);

#ifdef DEBUG
    assert(dir != GridMap::NONE);
#endif
    
    if (dir & GridMap::RIGHT) {
        _x += _velocity;
    }
    if (dir & GridMap::LEFT) {
        _x -= _velocity; 
    }
    if (dir & GridMap::UP) {
        _y -= _velocity; 
    }
    if (dir & GridMap::DOWN) {
        _y += _velocity; 
    }
}

void Creep::setType(CreepType type) {
    _type = type;
}

void Creep::setX(double x) {
    _x = x;
}

void Creep::setY(double y) {
    _y = y;
}

void Creep::setVelocity(double velocity) {
    _velocity = velocity;
}

void Creep::setHealth(int health) {
    _health = health;
}

Creep::CreepType Creep::getType() const {
    return _type;
}

double Creep::getX() const {
    return _x;
}

double Creep::getY() const {
    return _y;
}

double Creep::getVelocity() const {
    return _velocity;
}

int Creep::getHealth() const {
    return _health;
}

bool Creep::isDead() const {
    return _health <= 0;
}
