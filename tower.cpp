#include "tower.h"
#include "creep.h"

#include <cmath>    // For: hypot
#include <ciso646>  // For: and or not

Tower::Tower() {
}

Tower::~Tower() {
}

// Try to attack a creep
// Return true if the cooldown count has reached 0,
// and the creep is within the tower's range
bool Tower::attack(Creep *creep) {
    if (_cooldown_count == 0 and
        hypot(_x - creep->getX(), _y - creep->getY()) <= _range) {
        _cooldown_count = _cooldown;
        return true;
    }
    return false;
}

void Tower::setCoord(int x, int y) {
    _x = x;
    _y = y;
}

void Tower::setCooldown(int cooldown) {
    _cooldown = cooldown;
}


int Tower::getX() {
    return _x;
}

int Tower::getY() {
    return _y;
}
