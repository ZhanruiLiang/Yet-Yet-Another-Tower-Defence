#include "grid_map.h"
#include "creep.h"

#include <cassert>  // For: assert
#include <cstddef>  // For: NULL

inline int _sign(double n) {
    return n > 0 ? 1 : -1;
}

Creep::Creep()
    :_grid_map(NULL),
     _x(.0),
     _y(.0),
     _speed(.0),
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
/*
#ifdef DEBUG
    assert(dir != GridMap::NONE);
#endif
*/
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

void Creep::setSpeed(double speed) {
    _speed = speed;
}

void Creep::setHealth(int health) {
    _health = health;
}

void Creep::decreaseHealth(int damage) {
    _health -= damage;
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

double Creep::getSpeed() const {
    return _speed;
}

int Creep::getHealth() const {
    return _health;
}

bool Creep::isDead() const {
    return _health <= 0;
}
