#ifndef TOWER_CONFIG_H
#define TOWER_CONFIG_H

namespace tower {

    enum {TOWER_TYPES = 3};
    enum {TOWER_LEVELS = 5};

    enum TowerType {
        NORMAL = 0,
        RAPID  = 1,
        LASER  = 2,
    };

    // 2D array to hold the damages of each tower at each level
    const int DAMAGE[TOWER_TYPES][TOWER_LEVELS] = {
        {10, 20, 50, 150, 400},       // NORMAL
        {5, 10, 25, 50, 200},         // RAPID
        {100, 200, 300, 500, 1000},   // LASER
    };

   
    const double RANGE[TOWER_TYPES][TOWER_LEVELS] = {
        {100.0, 120.0, 140.0, 160.0, 180.0},       // NORMAL
        {150.0, 170.0, 190.0, 210.0, 230.0},       // RAPID
        {150.0, 170.0, 190.0, 210.0, 230.0},       // LASER
    };

    const int COOLDOWN[TOWER_TYPES][TOWER_LEVELS] = {
        {30, 30, 30, 30, 30},       // NORMAL
        {10, 10, 9, 9, 9},          // RAPID
        {60, 60, 60, 60, 60},       // LASER
    };

}
#endif
