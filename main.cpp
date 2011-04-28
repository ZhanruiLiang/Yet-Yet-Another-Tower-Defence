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
    GridMap *gm = new GridMap(30, 30);
    gm->setTarget(5, 5);
    for (int i = 0; i < 20; ++i) {
        gm->setWalkableAt(10, i, false);
    }
    for (int i = 10; i < 20; ++i) {
        gm->setWalkableAt(i, 10, false);
    }
    gm->updateRoute();

    // test route
    gm->debugPrint();


    gm->clearCreepsInfo();
    gm->addCreepsAt(1, 1);

    canBuildAt(gm, 0, 0);
    canBuildAt(gm, 1, 1);
    canBuildAt(gm, 10, 10);

    // clear grids again
    puts("Clear grids again");
    gm->clearCreepsInfo();
    canBuildAt(gm, 1, 1);

    delete gm;
#endif

    return EXIT_SUCCESS;
}
