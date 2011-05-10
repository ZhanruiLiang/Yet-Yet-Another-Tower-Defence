#include "tower_factory.h"
#include "tower_config.h"
#include "tower.h"

#include <cassert>
#include <cstddef>
#include <ciso646>

TowerFactory::TowerFactory() {
}

TowerFactory::~TowerFactory() {
}

Tower *TowerFactory::getTower(tower::TowerType type) {
#ifdef DEBUG
    assert(type >= 0 and type < (int)tower::TOWER_TYPES);
#endif
    Tower *new_tower = new Tower();
    new_tower->setType(type);
    new_tower->setDamage(tower::DAMAGE[type][0]);
    new_tower->setRange(tower::RANGE[type][0]);
    new_tower->setCooldown(tower::COOLDOWN[type][0]);
    return new_tower;
}
