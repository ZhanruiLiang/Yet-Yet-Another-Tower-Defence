#ifndef BULLET_FACTORY_H
#define BULLET_FACTORY_H

#include "bullet_config.h"

class Bullet;
class Tower;
class Creep;

// Factory Class for creating bullets
class BulletFactory {
    
    public:

        BulletFactory();
        ~BulletFactory();

        Bullet *getBullet(Tower *tower, Creep *creep);
};

#endif
