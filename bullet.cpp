#include "bullet.h"
#include "tower.h"
#include "creep.h"

#include <cstddef> // For: NULL
#include <ciso646> // For: and, or, not
#include <cmath>   // For: hypot
#include <cassert> // For: assert

Bullet::Bullet()
    :_tower(NULL),
     _creep(NULL),
     _x(.0),
     _y(.0),
     _speed(.0),
     _type(0),
     _collided(false) {
}

Bullet::~Bullet() {
}


void Bullet::setTower(Tower *tower) {
    _tower = tower;
}

void Bullet::setCreep(Creep *creep) {
    _creep = creep;
}

void Bullet::update() {
#ifdef DEBUG
    assert(_creep != NULL);
#endif
    // Get Creep position
    double cx = _creep->getX();
    double cy = _creep->getY();

    // Get distance
    double dx = cx - _x;
    double dy = cy - _y;

    double dist = hypot(dx, dy);

    // If can move to creep in one step
    if (dist <= _speed) {
        _x = cx;
        _y = cy;
        // decrease creeps health
        _creep->decreaseHealth(_damage);

        _collided = true; 
        return;
    }
    
    // Move
    _x += dx * _speed / dist;
    _y += dy * _speed / dist;
}

void Bullet::setType(Bullet::BulletType type) {
    _type = type; 
}

void Bullet::setX(double x) {
    _x = x;
} 

void Bullet::setY(double y) {
    _y = y;
}

void Bullet::setSpeed(double speed) {
    _speed = speed;
}

void Bullet::setDamage(int damage) {
    _damage = damage;
}

Bullet::BulletType Bullet::getType() const {
    return _type;
}

double Bullet::getX() const {
    return _x;
}

double Bullet::getY() const {
    return _y;
}

double Bullet::getSpeed() const {
    return _speed;
}

int Bullet::getDamage() const {
    return _damage;
}

bool Bullet::isDead() const {
    return _collided or _creep->isDead();
}
