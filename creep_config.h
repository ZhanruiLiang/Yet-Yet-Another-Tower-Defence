#ifndef CREEP_CONFIG_H
#define CREEP_CONFIG_H

namespace creep {

    enum {CREEP_TYPES = 3};

    enum CreepType {
        NORMAL = 0,
        STRONG = 1,
        FAST   = 2
    };

    const double UPGRADE_RATIO = 1.2;

    const int HEALTH[CREEP_TYPES] = {
        5,         // NORMAL
        10,        // STRONG
        7          // FAST
    };

    const double SPEED[CREEP_TYPES] = {
        1.0,       // NORMAL
        1.0,       // STRONG
        2.0        // FAST
    };

}
#endif
