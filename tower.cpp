#include "tower.h"
#include "creep.h"

#include <cmath>    // For: hypot
#include <ciso646>  // For: and or not
#include <cassert>

Tower::Tower()
    :_level(0) {
}

Tower::~Tower() {
}

// Try to attack a creep
// Return true if the cooldown count has reached 0,
// and the creep is within the tower's range
bool Tower::attack(Creep *creep) {
    if (_cooldown_count <= 0 and
        hypot(_x - creep->getX(), _y - creep->getY()) <= _range) {
        _cooldown_count = _cooldown;
        return true;
    }
    return false;
}

void Tower::update() {
    --_cooldown_count;
}

void Tower::setType(TowerType type) {
    _type = type;
}

void Tower::setCoord(int x, int y) {
    _x = x;
    _y = y;
}

void Tower::setRange(double range) {
    _range = range;
}

void Tower::setDamage(int damage) {
    _damage = damage;
}

void Tower::setCooldown(int cooldown) {
    _cooldown = cooldown;
}

void Tower::upgrade() {
#ifdef DEBUG
    assert(_level < 4);
#endif
    ++_level;
}

Tower::TowerType Tower::getType() const {
    return _type;
}

double Tower::getRange() const {
    return _range;
}

int Tower::getDamage() const {
    return _damage;
}

int Tower::getX() const {
    return _x;
}

int Tower::getY() const {
    return _y;
}

int Tower::getLevel() const {
    return _level;
}
