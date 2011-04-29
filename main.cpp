#include <cstdio>
#include <cstdlib>

#include "gridmap.h"


#ifdef DEBUG
void canBuildAt(GridMap *gm, int x, int y) {
    printf("can build at (%d, %d) ? %s\n",
           x, y,
           gm->canBuildAt(x, y) ? "True" : "False");
}
#endif


int main(int argc, char *argv[]) {
   
#ifdef DEBUG
    enum {GRID_SIZE = 20};
    GridMap *gm = new GridMap(30, 30, GRID_SIZE);
    gm->setTarget(5 * GRID_SIZE, 5 * GRID_SIZE);
    for (int i = 0; i < 20; ++i) {
        gm->setWalkableAt(10 * GRID_SIZE, i * GRID_SIZE, false);
    }
    for (int i = 10; i < 20; ++i) {
        gm->setWalkableAt(i * GRID_SIZE, 10 * GRID_SIZE, false);
    }
    gm->updateRoute();

    // test route
    gm->printRoute();

    gm->clearCreepsInfo();
    gm->addCreepsAt(1 * GRID_SIZE, 1 * GRID_SIZE);

    canBuildAt(gm, 1 * GRID_SIZE, 1 * GRID_SIZE);
    canBuildAt(gm, 10 * GRID_SIZE, 10 * GRID_SIZE);
    canBuildAt(gm, 20 * GRID_SIZE, 20 * GRID_SIZE);

    // clear grids again
    puts("Clear grids again");
    gm->clearCreepsInfo();
    canBuildAt(gm, 1 * GRID_SIZE, 1 * GRID_SIZE);
    printf("Center of (5, 15) : (%d, %d)\n", 
           gm->toGridCenterX(5), gm->toGridCenterY(15));

    delete gm;
#endif

    return EXIT_SUCCESS;
}
