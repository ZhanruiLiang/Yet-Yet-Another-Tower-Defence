#ifndef TOWER_FACTORY_H
#define TOWER_FACTORY_H

#include "tower_config.h"

class Tower;

// Factory Class for creating towers
class TowerFactory {
    
    public:

        TowerFactory();
        ~TowerFactory();

        Tower *getTower(tower::TowerType type);
};

#endif
