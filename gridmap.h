#ifndef GRIDMAP_H
#define GRIDMAP_H

// GridMap class
// Holds a two-dimensional array of grids and calculates
// the routes of the creeps.
class GridMap {
    
    public:

        // enum the directions
        enum Direction {NONE, LEFT, RIGHT, UP, DOWN, 
                        TOPLEFT, TOPRIGHT, BOTTOMLEFT, BOTTOMRIGHT};

        // GridMap constructor, takes two params namely the 
        // width and height of the map
        GridMap(int width, int height);

        // destructor
        ~GridMap();

        // Set the source coordinate of this grid map
        // The source is where the creeps spawn
        //void setSource(int x, int y);

        // Set the target coordinate of the this grid map
        // The target coordinate is where the creeps exit
        // note that x grows from left to right and
        // y grows from top to bottom.
        void setTarget(int x, int y);

        // Update the routes, this method is called each time
        // a new tower is built or a present tower is destroyed.
        void updateRoute();

        // Check to see whether the path from source to target
        // is being blocked
        bool isBlocked();

        // Check whether a tower can be built at the given coordinate
        bool canBuildAt(int x, int y);

        // Get the width of the map
        int getWidth() const;

        // Get the height of the map
        int getHeight() const;

        // Get the direction the creeps should head for
        // at the given coordinate
        Direction getDirectionAtCoord(int x, int y) const;


#ifdef DEBUG
        void debugPrint() const;
#endif

    private:

        // Grid struct, stores the information of the creeps or 
        // tower on this grid
        struct Grid {
            Grid();
            ~Grid();
            Direction direction; // 
            bool is_walkable;    //
            bool visited;        // 
        };


    // Helper functions

        // Clear all grids' directions and mark them as unvisited.
        // used in updateRoute()
        void _clearGridsFlags(); 

        // Determine whether the given coordinate is valid
        bool _isValidCoord(int x, int y) const; 
                                

    // Data memebers

        // Two dimensional array to hold the grids
        Grid **_grids;      

        // Grids for testing whether after certain given commands
        // the routes will be blocked
        Grid **_test_grids;

        // Width and height of the grid map
        int _width;    
        int _height;

        // Coordinate of source grid
        int _source_x;
        int _source_y;

        // Coordinate of target grid
        int _target_x; 
        int _target_y;

};

#endif 
