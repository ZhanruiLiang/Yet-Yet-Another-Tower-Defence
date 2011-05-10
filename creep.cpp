#include "grid_map.h"
#include "creep.h"
#include "direction.h"

#include <cassert>  // For: assert
#include <cstddef>  // For: NULL
#include <cmath>    // For: hypot

inline int _sign(double n) {
    return n > 0 ? 1 : n == 0 ? 0 : -1;
}

Creep::Creep()
    :_grid_map(NULL),
     _x(.0),
     _y(.0),
     _next_x(.0),
     _next_y(.0),
     _direction(D_NONE),
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
    
    // Check whether the creep can get to the next position
    // in one move
    if (hypot(_x - _next_x, _y - _next_y) <= _speed) {
        // update position
        _x = _next_x;
        _y = _next_y;

        // get next target
        _next_x = _grid_map->getNextX((int)_x, (int)_y);
        _next_y = _grid_map->getNextY((int)_x, (int)_y);
        _direction = _grid_map->getDirectionAt((int)_x, (int)_y);

        return;
    }

    static const double DIA_RATIO = 1.4142;

    double dx = _next_x - _x;
    double dy = _next_y - _y;

    switch (_direction) {
        case D_LEFT:       
        case D_RIGHT:      
        case D_UP:         
        case D_DOWN:       
            _x += _sign(dx) * _speed;
            _y += _sign(dy) * _speed;
            break;
        case D_TOPLEFT:     
        case D_TOPRIGHT:    
        case D_BOTTOMLEFT:  
        case D_BOTTOMRIGHT: 
            _x += _sign(dx) * _speed / DIA_RATIO;
            _y += _sign(dy) * _speed / DIA_RATIO;
            break;
        default:
            break;
    }
}

void Creep::setType(CreepType type) {
    _type = type;
}

void Creep::setX(double x) {
    _x = (double)_grid_map->toGridCenterX(x);
    _next_x = _x;
}

void Creep::setY(double y) {
    _y = (double)_grid_map->toGridCenterY(y);
    _next_y = _y;
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
