#ifndef GRIDMAP_H
#define GRIDMAP_H

// GridMap class
// Holds a two-dimensional array of grids and calculates
// the routes of the creeps.
//
// *Note*: All the public methods involving the coodinates
// uses the world coordinates instead of grid coordinates.
//
// *Note*: In each iteration of the game loop:
// The calling sequence should be like this:
//
// loop: 
//      gm->clearCreepsInfo();
//      for each creep in creeps:
//          int x = creep.getX(), y = creep.getY();
//          gm->addCreepsAt(x, y);
//
//      if gm->canBuildAt(tower_x, tower_y):
//          int x = gm->toGridCenterX(tower_x);
//          int y = gm->toGridCenterY(tower_y);
//          // ...
//          // build tower stuff here
//          gm->setWalkableAt(x, y, false);
class GridMap {
    
    public:

        // enum the directions
        enum Direction {
            NONE        = 0x0,  // 0000
            LEFT        = 0x1,  // 0001
            RIGHT       = 0x2,  // 0010
            UP          = 0x4,  // 0100
            DOWN        = 0x8,  // 1000 
            TOPLEFT     = 0x5,  // 0101
            TOPRIGHT    = 0x6,  // 0110
            BOTTOMLEFT  = 0x9,  // 1001
            BOTTOMRIGHT = 0xA   // 1010
        };

        // GridMap constructor, takes two params namely the 
        // width and height of the map
        GridMap(int width, int height, int grid_size);

        // destructor
        ~GridMap();

        // Set the source coordinate of this grid map
        // The source is where the creeps spawn
        void setSource(int x, int y);

        // Set the target coordinate of the this grid map
        // The target coordinate is where the creeps exit
        // note that x grows from left to right and
        // y grows from top to bottom.
        void setTarget(int x, int y);

        // Set whether the grid at the given coordinate is walkable
        // *Note*: When a tower is built, this method should be
        // called to set the correponding coordinate to be 
        // not walkable, and when a tower is destroyed, this method
        // should also be called to set the grid to be walkable
        void setWalkableAt(int x, int y, bool walkable);

        // Set all grids to have no creeps on them
        // *Note*: This is will not affect any *REAL* creeps
        // it only clears the has_creep flag in the grid struct
        // This method should be called in each iteration of 
        // the game loop before setHasCreepsAt();
        void clearCreepsInfo();

        // Set whether the grid at the given coordinate has a creep
        // *Note*: This method should be called at each iteration
        // of the game loop after clearCreepsInfo()
        void addCreepsAt(int x, int y);

        // Check whether a tower can be built at the given coordinate
        bool canBuildAt(int x, int y);

        // Update the routes, this method is called each time
        // a new tower is built or a present tower is destroyed.
        void updateRoute();

        // Get the width(number of horizontal grids) of the map 
        int getWidth() const;

        // Get the height(number of vertical grids) of the map
        int getHeight() const;

        // Get the direction the creeps should head for
        // at the given coordinate
        Direction getDirectionAt(int x, int y) const;

        // Adjust the given coordinate to be the nearest center
        // of a grid
        // Used when building a tower(A tower should be build at
        // the center a grid)
        int toGridCenterX(int x) const;
        int toGridCenterY(int y) const;


#ifdef DEBUG
        void printRoute() const;
        void printWalkable() const;
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
            bool has_creeps;     // 
        };


    // Helper functions
        
        // Convert from world coordinate to grid coordinate
        int toGridX(int x) const;
        int toGridY(int y) const;

        // Clear all grids' directions and mark them as unvisited.
        // used in updateRoute()
        void _clearGridsFlags(Grid **grids);

        // Determine whether the given coordinate is valid
        bool _isValidCoord(int x, int y) const; 

        // Helper function to update the specified grids
        void _updateRouteHelper(Grid **grids);
                                

    // Data memebers

        // Two dimensional array to hold the grids
        Grid **_grids;      

        // Grids for testing whether after certain given commands
        // the routes will be blocked
        // used in canBuildAt(int x, int y)
        Grid **_test_grids;

        // Width and Height of each grid
        int _grid_size;

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
