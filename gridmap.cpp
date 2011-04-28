#include "gridmap.h"

#include <cassert>
#include <ciso646> // For "and" "or" "not"
#include <cstddef> // For "NULL"
#include <queue>   // For "priority_queue"

#ifdef DEBUG
#define VALID_COORD \
    assert(x >= 0 and x < _width and y >= 0 and y < _height);
#endif


// struct GreedyNode
// Data fields:
//     Coord coord: coordinate of this node
//     int dist: distance from the source node to this node
//
// Node with smaller dist will have higher priority
// while being stored in the priority_queue
//
// Used in GridMap::updateRoute()
struct GreedyNode {
    GreedyNode(int x, int y, int dist)
        :x(x),
         y(y),
         dist(dist) {}
    bool operator<(const GreedyNode &rhs) const {
        return dist > rhs.dist;
    }
    int x, y;
    int dist;
};


GridMap::Grid::Grid() 
    :direction(GridMap::NONE),
     is_walkable(true),
     visited(false),
     has_creeps(false) {
}

GridMap::Grid::~Grid() {
}


// GridMap constructor 
GridMap::GridMap(int width, int height)
    :_grids(NULL),
     _width(width),
     _height(height),
     _source_x(0),
     _source_y(0),
     _target_x(0),
     _target_y(0) {
#ifdef DEBUG
    assert(width > 0 and height > 0);
#endif
    // construct a two dimensional array of grids
    _grids = new Grid*[height];
    _test_grids = new Grid*[height];
    for (int i = 0; i < height; ++i) {
        _grids[i] = new Grid[width];
        _test_grids[i] = new Grid[width];
    }
}

// Destructor
GridMap::~GridMap() {
    for (int i = 0; i < _height; ++i) {
        delete [] _grids[i];
        delete [] _test_grids[i];
    }
    delete [] _grids;
    delete [] _test_grids;
}


// Set the source coordinate of the map
void GridMap::setSource(int x, int y) {
    _source_x = x;
    _source_y = y;
}


// Set the target coordinate of the map
void GridMap::setTarget(int x, int y) {
#ifdef DEBUG
    VALID_COORD
#endif
    _target_x = x;
    _target_y = y;
}


// Set whether the grid at the given coordinate is walkable
void GridMap::setWalkableAt(int x, int y, bool walkable) {
#ifdef DEBUG
    VALID_COORD
#endif
    _grids[y][x].is_walkable = walkable;
}


// Set all grids to have no creeps on them
void GridMap::clearCreepsInfo() {
    for (int i = 0; i < _height; ++i) {
        for (int j = 0; j < _width; ++j) {
            _grids[i][j].has_creeps = false;
        }
    }
}

// Set the given grid to be have creeps on it
void GridMap::addCreepsAt(int x, int y) {
#ifdef DEBUG
    VALID_COORD
#endif
    _grids[y][x].has_creeps = true;
}


// Check whether a tower can be built at the given coordinate
bool GridMap::canBuildAt(int x, int y) {

    // Reset _test_grids info
    for (int i = 0; i < _height; ++i) {
        for (int j = 0; j < _width; ++j) {
            _test_grids[y][x] = _grids[y][x];
        }
    }

    // Check whether the coordinate already has creeps on it
    // or it's not walkable(has built a tower on it)
    if (_test_grids[y][x].has_creeps or 
        not _test_grids[y][x].is_walkable) {
        return false;
    }

    // Update route on _test_grids
    _updateRouteHelper(_test_grids);

    // Check whether the routes from source to target is blocked
    if (_test_grids[_source_y][_source_x].direction == NONE) {
        return false;
    }

    // Check whether the grids that still has creeps on them is blocked
    for (int i = 0; i < _height; ++i) {
        for (int j = 0; j < _width; ++j) {
            if (_test_grids[i][j].has_creeps and 
                _test_grids[i][j].direction == NONE) {
                return false;
            }
        }
    }
    return true;
}


// Update the routes, this method is called each time
// a new tower is built or a present tower is destroyed.
//
// see _updateRouteHelper() for more details
void GridMap::updateRoute() {
    _updateRouteHelper(_grids);
}

// Helper function for updating the routes
// This method uses a Greedy algorithm to calculate the routes.
//
// To begin with, the target node is pushed into the priority
// queue with distance 0. While the priorit queue is not
// empty, at each iteration, the node with minimal distance will 
// be popped from the queue. Then its adjacent nodes will
// be inspected. For each adjacent node, if it has not been
// visited before, it will be pushed into the queue with the
// new distance and its direction and visited flag will be set.
//
// The Creeps can go horizontally, vertically or diagonally.
// A diagonal direction is valid only when the the diagonal
// grid can be accessed from both the two ways:
// e.g.
//    A | B       A -> D is valid only when both
//    --+--       A -> B -> D is valid and
//    C | D       A -> C -> D is valid
//
// Creeps can can directly go from A to D if Both B and C
// is not occupied by towers.
//
// By introducing the diagonal shortcuts, the routes will
// be more natural.
void GridMap::_updateRouteHelper(Grid **grids) {

    // horizontal and vertical offsets
    static const int offset_x[] = {-1, 0, 1, 0};
    static const int offset_y[] = {0, 1, 0, -1};
    
    // diagonal offsets
    static const int d_offset_x[] = {-1, -1, 1, 1}; 
    static const int d_offset_y[] = {-1, 1, 1, -1};

    // Correspondencies between index and position
    // 
    //     offset              d_offset:      
    //  +---+---+---+        +---+---+---+
    //  |   | 3 |   |        | 0 |   | 3 | 
    //  +---+---+---+        +---+---+---+
    //  | 0 |   | 2 |        |   |   |   |
    //  +---+---+---+        +---+---+---+
    //  |   | 1 |   |        | 1 |   | 2 |
    //  +---+---+---+        +---+---+---+
    // 
    // if offset[i] is invalid, then
    // d_offset[i] and 
    // d_offset[(i + 1) % 4] is invalid.

    // horizontal and vertical directions
    static const Direction dirs[] = {
        RIGHT, UP, LEFT, DOWN
    };

    // diagonal directions
    static const Direction ddirs[] = {
        BOTTOMRIGHT, TOPRIGHT, TOPLEFT, BOTTOMLEFT
    };


    // Step1: Clear all grids' direction to be Grid::NONE
    //        and mark all grids as un-visited
    _clearGridsFlags(grids);

    // Step2: Begin Greedy Search
    std::priority_queue<GreedyNode> pq;
    pq.push(GreedyNode(_target_x, _target_y, 0));
    grids[_target_y][_target_x].visited = true;

    while (not pq.empty()) {

        // indicate whether the diagonal direction is available
        bool diagonal_valid[] = {true, true, true, true};

        // take one node from the queue
        GreedyNode node = pq.top();
        pq.pop();

        int x = node.x, y = node.y;
        int dist = node.dist;

        // Inspect the adjacent nodes
        for (int i = 0; i < 4; ++i) {

            // Next node's coordinate
            int next_x = x + offset_x[i];
            int next_y = y + offset_y[i];

            if (_isValidCoord(next_x, next_y)) {

                if (not grids[next_y][next_x].visited) {
                    // Update the grid's direction
                    grids[next_y][next_x].direction = dirs[i];
                    
                    // Push the node into the queue
                    pq.push(GreedyNode(next_x, next_y, dist + 10));
                    
                    // Mark the grid as visited
                    grids[next_y][next_x].visited = true;
                }

            } else {
                // The coordinate is invalid 
                // Thus the corresponding diagonal coordinate is invalid
                diagonal_valid[i] = false;
                diagonal_valid[(i + 1) % 4] = false;
            }
        }

        // Further inspect the diagonally adjacent nodes
        for (int i = 0; i < 4; ++i) {

            if (diagonal_valid[i]) {

                int next_x = x + d_offset_x[i];
                int next_y = y + d_offset_y[i];

                if (_isValidCoord(next_x, next_y) and 
                    not grids[next_y][next_x].visited) {
                    // Update the grid's direction
                    grids[next_y][next_x].direction = ddirs[i];

                    // Push the node into the queue
                    pq.push(GreedyNode(next_x, next_y, dist + 14));

                    // Mark the grid as visited
                    grids[next_y][next_x].visited = true;
                }
            } 
        }
    }
}



int GridMap::getWidth() const {
    return _width;
}

int GridMap::getHeight() const {
    return _height;
}

GridMap::Direction GridMap::getDirectionAt(int x, int y) const {
#ifdef DEBUG
    VALID_COORD
#endif
    return _grids[y][x].direction;
}


// Clear all grids' directions and mark them as unvisited.
void GridMap::_clearGridsFlags(Grid **grids) {
    for (int i = 0; i < _height; ++i) {
        for (int j = 0; j < _width; ++j) {
            grids[i][j].visited = false;
            grids[i][j].direction = NONE;
        }
    }
}

// Determine if the given coordinate is inside the map
// and is walkable
bool GridMap::_isValidCoord(int x, int y) const {
    return x >= 0 and x < _width and
           y >= 0 and y < _height and
           _grids[y][x].is_walkable;
}


#ifdef DEBUG

#include <cstdio>

void GridMap::debugPrint() const {
    printf("  ");
    for (int i = 0; i < _width; ++i) {
        printf("%2d", i);
    }
    puts("");
    for (int i = 0; i < _height; ++i) {
        printf("%2d ", i);
        for (int j = 0; j < _width; ++j) {
            switch (_grids[i][j].direction) {
                case NONE:
                    putchar(' '); break;
                case LEFT:
                    putchar('<'); break;
                case RIGHT:
                    putchar('>'); break;
                case UP:
                    putchar('^'); break;
                case DOWN:
                    putchar('v'); break;
                case TOPLEFT:
                case BOTTOMRIGHT:
                    putchar('\\'); break;
                default:
                    putchar('/'); break;
            }
            printf(" ");
        }
        puts("");
    }
}


#endif
