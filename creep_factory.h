#ifndef CREEP_FACTORY_H
#define CREEP_FACTORY_H

class Creep;

// Factory Class for creating creeps
class CreepFactory {
    
    public:

        Creep

        CreepFactory();
        ~CreepFactory();

        Creep *getCreep(CreepType);
};

#endif
