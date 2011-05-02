#ifndef CREEP_H
#define CREEP_H

// Forward declarations
class GridMap;

// Creep Class
// *Note*: All the position and velocity methods returns double
class Creep {

    public:

        typedef int CreepType;

        Creep();
        virtual ~Creep();

        // Let the creep know the gridmap so that it may move
        // according to the directions marked on the map
        void setGridMap(GridMap *grid_map);

        // Update the creep (performs move)
        // This method should be called in each iteration of the
        // game loop
        void update();

        // Set the specific type of creep
        void setType(CreepType type);

        // Set coordinate
        void setX(double x);  
        void setY(double y);

        void setSpeed(double speed);

        void setHealth(int health);

        void decreaseHealth(int damage);
    

        CreepType getType() const;

        double getX() const;
        double getY() const;

        double getSpeed() const;

        int getHealth() const;


        bool isDead() const;

    private:

        GridMap *_grid_map;

        double _x;
        double _y;

        double _speed;

        int _health;

        CreepType _type;
};

#endif
