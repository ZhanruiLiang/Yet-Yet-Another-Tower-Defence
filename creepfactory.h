#ifndef CREEPFACTORY_H
#define CREEPFACTORY_H

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
