#include <cstdio>
#include <cstdlib>

#include "grid_map.h"
#include "creep.h"
#include "creep_config.h"
#include "creep_factory.h"
#include "tower.h"
#include "tower_config.h"
#include "tower_factory.h"

#include "preinclude.h"
#include "clipper.h"
#include "graphic_engine.h"

#ifdef DEBUG

#include <unistd.h>

void canBuildAt(GridMap *gm, int x, int y) {
    printf("can build at (%d, %d) ? %s\n",
           x, y,
           gm->canBuildAt(x, y) ? "True" : "False");
}   


void test() {

    enum {GRID_SIZE = 20};

	//graphic engine
	GraphicEngine * graEngine;
	graEngine = new GraphicEngine;
    
	graEngine->init();

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

	//print
	Clipper cps[30][30];
	Clipper cpcp;

	int width = GRID_SIZE;

	for(int i = 0; i < 30; i++)
		for(int j = 0; j < 30; j++)
		{
			cps[i][j].initFrom("resource/cp2");
			cps[i][j].setY(width*i);
			cps[i][j].setX(width*j);
			cps[i][j].setDepth(0);
			graEngine->addClipper(&cps[i][j]);
		}

	cpcp.initFrom("resource/cp3");
	cpcp.setDepth(1);
	graEngine->addClipper(&cpcp);

	cpcp.debugPrint();
	bool quit = false;
	SDL_Event event;
	while(!quit){
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT)
				quit = true;
		}

        creep->update();
		cpcp.setX(creep->getX());
		cpcp.setY(creep->getY());

        for (int i = 0; i < 30; ++i) {
            for (int j = 0; j < 30; ++j) {
				Clipper & cp = cps[i][j];
                if (gm->getDirectionAt(j * width, i * width) 
                    == GridMap::NONE) {
					cp.gotoAndStop(0); // X
                } else {
					cp.gotoAndStop(2); // _
                }
            }
        }
		graEngine->loop();
		//use this delay function temporally
		SDL_Delay(6);
    }

	Clipper::clean();
    delete gm;
	delete graEngine;
}

#endif




int main(int argc, char *argv[]) {

#ifdef DEBUG
    test();
#endif

    return EXIT_SUCCESS;
}
