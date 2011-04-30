#include "creep_factory.h"
#include "creep_config.h"
#include "creep.h"

#include <cassert>
#include <cstddef>
#include <ciso646>

CreepFactory::CreepFactory() {
}

CreepFactory::~CreepFactory() {
}

Creep *CreepFactory::getCreep(creep::CreepType type) {
#ifdef DEBUG
    assert(type >= 0 and type < (int)creep::CREEP_TYPES);
#endif
    Creep *new_creep = new Creep();
    new_creep->setType(type);
    new_creep->setHealth(creep::HEALTH[type]);
    new_creep->setSpeed(creep::SPEED[type]);
    return new_creep;
}
