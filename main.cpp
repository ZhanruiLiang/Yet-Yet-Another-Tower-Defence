#include <cstdlib>

#include "gridmap.h"


int main(int argc, char *argv[]) {
   
    GridMap *gm = new GridMap(30, 30);
    gm->setTarget(5, 5);
    for (int i = 0; i < 20; ++i) {
        gm->setWalkableAt(10, i, false);
    }
    for (int i = 10; i < 20; ++i) {
        gm->setWalkableAt(i, 10, false);
    }
    gm->updateRoute();

#ifdef DEBUG
    gm->debugPrint();
#endif

    delete gm;

    return EXIT_SUCCESS;
}
