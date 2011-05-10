#include <cstdio>
#include <cstdlib>

#include "grid_map.h"
#include "creep.h"
#include "creep_config.h"
#include "creep_factory.h"
#include "tower.h"
#include "tower_config.h"
#include "tower_factory.h"
#include "direction.h"

#ifdef DEBUG

#include <unistd.h>

void canBuildAt(GridMap *gm, int x, int y) {
    printf("can build at (%d, %d) ? %s\n",
           x, y,
           gm->canBuildAt(x, y) ? "True" : "False");
}   

void next_test() {
    enum {GRID_SIZE = 32};
    
    // build map
    GridMap *gm = new GridMap(30, 30, GRID_SIZE);
    gm->setTarget(5 * GRID_SIZE, 5 * GRID_SIZE);

    for (int i = 0; i < 20; ++i) {
        gm->setWalkableAt(10 * GRID_SIZE, i * GRID_SIZE, false);
    }

    for (int i = 10; i < 20; ++i) {
        gm->setWalkableAt(i * GRID_SIZE, 10 * GRID_SIZE, false);
    }

    gm->updateRoute();

    for (int i = 0; i < 30; ++i) {
        for (int j = 0; j < 30; ++j) {
            printf("%d,%d ", gm->getNextX(j * 32 + 16, i * 32 + 16), gm->getNextY(j * 32 + 16, i * 32 + 16));
        }
        puts("");
    }
}

void build_test() {

    enum {GRID_SIZE = 32};
    
    // build map
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

    CreepFactory *factory = new CreepFactory();

    Creep *creep = factory->getCreep(creep::NORMAL);
    creep->setX(500.0);
    creep->setY(500.0);
    creep->setGridMap(gm);

    printf("%d, %d\n", gm->getNextX(193, 193), gm->getNextY(193, 193));
}


void move_test() {
   
    enum {GRID_SIZE = 32};
    
    // build map
    GridMap *gm = new GridMap(30, 30, GRID_SIZE);
    gm->setTarget(5 * GRID_SIZE, 5 * GRID_SIZE);

    for (int i = 0; i < 20; ++i) {
        gm->setWalkableAt(10 * GRID_SIZE, i * GRID_SIZE, false);
    }

    for (int i = 10; i < 20; ++i) {
        gm->setWalkableAt(i * GRID_SIZE, 10 * GRID_SIZE, false);
    }

    gm->updateRoute();

    gm->printRoute();
   // return;


    CreepFactory *factory = new CreepFactory();

    Creep *creep = factory->getCreep(creep::NORMAL);

    creep->setGridMap(gm);
    creep->setX(500.0);
    creep->setY(500.0);

    for (int i = 0; i < 3000; ++i) {
        system("clear");    
        creep->update();
        for (int i = 0; i < 30; ++i) {
            for (int j = 0; j < 30; ++j) {
                if (gm->getDirectionAt(j * GRID_SIZE, i * GRID_SIZE) 
                    == D_NONE) {
                    printf("X ");
                } else if (i == (int)creep->getY() / GRID_SIZE and 
                           j == (int)creep->getX() / GRID_SIZE)  {
                    printf("o ");
                } else {
                    printf("  ");
                }
            }
            puts("");
        }
        printf("%d %d\n", (int)creep->getX(), (int)creep->getY());
        usleep(6000);
    }

    delete gm;
}

#endif




int main(int argc, char *argv[]) {

#ifdef DEBUG
    move_test();
#endif

    return EXIT_SUCCESS;
}
