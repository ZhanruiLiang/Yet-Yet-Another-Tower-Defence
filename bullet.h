#ifndef BULLET_H
#define BULLET_H

class Tower;
class Creep;

// Bullet Class
//
// *Note*: All the position and velocity methods returns double
class Bullet {

    public:

        typedef int BulletType;

        Bullet();
        virtual ~Bullet();

        // Update the bullet (performs move)
        // This method should be called in each iteration of the
        // game loop
        void update();

        // Set the tower from which the bullet is fired
        void setTower(Tower *tower);

        // Set the creep at which the bullet is targeting
        void setCreep(Creep *creep);

        // Set the specific type of bullet
        void setType(BulletType type);

        // Set coordinate
        void setX(double x);  
        void setY(double y);

        void setSpeed(double speed);

        void setDamage(int damage);

        BulletType getType() const;

        double getX() const;
        double getY() const;

        double getSpeed() const;

        int getDamage() const;

        // Check whether this bullet is dead.
        // A dead bullet refers to a bullet which has collided
        // with a creep or a bullet which is targeting at
        // an already dead creep.
        bool isDead() const;

    private:

        Tower *_tower;
        Creep *_creep;

        double _x;
        double _y;

        double _speed;

        int _damage;

        BulletType _type;

        bool _collided;
};

#endif
