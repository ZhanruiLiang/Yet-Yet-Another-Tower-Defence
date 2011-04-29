#ifndef CREEP_H
#define CREEP_H

// Forward declarations
class GridMap;

// Base Creep class
//
// *Note*: All the position and velocity methods returns double
class Creep {

    public:
        Creep();
        virtual ~Creep();

        // Let the creep know the gridmap so that it may move
        // according to the directions marked on the map
        void setGridMap(GridMap *grid_map);

        // Update the creep (performs move)
        // This method should be called in each iteration of the
        // game loop
        void update();

        void setX(double x);  
        void setY(double y);

        void setVelocity(double velocity);

        double getX() const;
        double getY() const;

        double getVelocity() const;

    private:

        GridMap *_grid_map;

        double _x;
        double _y;

        double _velocity;
};

#endif
