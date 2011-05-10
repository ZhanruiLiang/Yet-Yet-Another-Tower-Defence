#ifndef BULLET_CONFIG_H
#define BULLET_CONFIG_H


namespace bullet {

    // The bullet types should be in accordance with the tower's
    enum {BULLET_TYPES = 3};

    enum BulletType {
        NORMAL = 0,
        RAPID  = 1,
        LASER  = 2
    };


    const double SPEED[BULLET_TYPES] = {
        1.0,       // NORMAL
        1.0,       // STRONG
        2.0        // FAST
    };

}
#endif
