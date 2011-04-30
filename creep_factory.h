#ifndef CREEP_FACTORY_H
#define CREEP_FACTORY_H

#include "creep_config.h"

class Creep;

// Factory Class for creating creeps
class CreepFactory {
    
    public:

        CreepFactory();
        ~CreepFactory();

        Creep *getCreep(creep::CreepType type);
};

#endif
