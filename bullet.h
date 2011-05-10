#ifndef BULLET_H
#define BULLET_H

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

        // Set the specific type of bullet
        void setType(BulletType type);

        // Set coordinate
        void setX(double x);  
        void setY(double y);

        void setSpeed(double speed);

        BulletType getType() const;

        double getX() const;
        double getY() const;

        double getSpeed() const;

    private:

        double _x;
        double _y;

        double _speed;

        BulletType _type;
};

#endif
