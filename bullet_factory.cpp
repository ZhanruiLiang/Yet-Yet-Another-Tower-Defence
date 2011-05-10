#include "bullet_factory.h"
#include "bullet_config.h"
#include "bullet.h"
#include "tower.h"

#include <cassert>
#include <cstddef>
#include <ciso646>

BulletFactory::BulletFactory() {
}

BulletFactory::~BulletFactory() {
}

Bullet *BulletFactory::getBullet(bullet::BulletType type,
                                 Tower *tower,
                                 Creep *creep) {
    Bullet *new_bullet = new Bullet();
    new_bullet->setType(type);
    new_bullet->setTower(tower);
    new_bullet->setCreep(creep);
    new_bullet->setDamage(tower->getDamage());
    new_bullet->setSpeed(bullet::SPEED[type]);
    new_bullet->setX(tower->getX());
    new_bullet->setY(tower->getY());
    return new_bullet;
}
