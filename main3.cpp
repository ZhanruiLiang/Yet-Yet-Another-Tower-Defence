#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>

#include "grid_map.h"
#include "creep.h"
#include "creep_config.h"
#include "creep_factory.h"
#include "tower.h"
#include "tower_config.h"
#include "tower_factory.h"
#include "direction.h"
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

int calcuDirection(GridMap * gm, int x, int y)
{
	//  1 2 3
	//  8 0 4
	//  7 6 5
	const int DIRS[8][2] = { {-1,-1},{0,-1},{1,-1},{1,0},
		{1,1},{0,1},{-1,1},{-1,0}};

	int dx,dy;
	dx = gm->getNextX(x,y) - x;
	dy = gm->getNextY(x,y) - y;

	if(gm->getDirectionAt(x, y) == D_NONE)
		return 0;
	int ans = 0;
	double max= -2.0;
	for(int i = 0; i < 8; i++)
	{
		double cosT = (double)DIRS[i][0] * dx + DIRS[i][1] * dy / 
			(sqrt(DIRS[i][0] * DIRS[i][0] + DIRS[i][1] * DIRS[i][1]) * sqrt(dx * dx + dy * dy));
		//		double cosT = (double)DIRS[i][0] * dx + DIRS[i][1] * dy ;
		if(cosT > max)
		{
			ans = i;
			max = cosT;
		}
	}
	return ans+1;
}

void move_test() {

	enum {GRID_SIZE = 32};

	const int mapGridX = 30;
	const int mapGridY = 30;
	int mapLenX = mapGridX * GRID_SIZE;
	int mapLenY = mapGridY * GRID_SIZE;
	sbox::SCREEN_WIDTH = mapLenX;
	sbox::SCREEN_HEIGHT = mapLenY;
	sbox::initSDL();

	// build map
	GridMap *gm = new GridMap(mapGridX, mapGridY, GRID_SIZE);
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

	GraphicEngine * ge = new GraphicEngine;
	ge->init();

	const int DETAIL = 2;
	Clipper cp_dirs[DETAIL * mapGridY][DETAIL * mapGridX];
	Clipper cp_creep;

	for(int i = 0; i < DETAIL * mapGridY; i++)
		for(int j = 0; j < DETAIL * mapGridX; j++){
			int x,y;
			y = i*GRID_SIZE/DETAIL;
			x = j*GRID_SIZE/DETAIL;
			Clipper & cp = cp_dirs[i][j];
			cp.initFrom("resource/cp4");
			cp.setY(y);
			cp.setX(x);
			cp.setDepth(0);

			cp.gotoAndStop(calcuDirection(
						gm,
						(x + x + GRID_SIZE - 1)/2,
						(y + y + GRID_SIZE - 1)/2
						));
			ge->addClipper(&cp);
		}
	cp_creep.initFrom("resource/cp3");
	cp_creep.setX(creep->getX());
	cp_creep.setY(creep->getY());
	cp_creep.setDepth(1);
	ge->addClipper(&cp_creep);


	bool quit = false;
	SDL_Event event;
	while(!quit){
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT)
				quit = true;
		}

		creep->update();
		cp_creep.setX(creep->getX());
		cp_creep.setY(creep->getY());

		ge->loop();
		std::cout << cp_creep.getX() << ' ' << cp_creep.getX()<< '\n';

		//use this delay function temporally
		SDL_Delay(6);
	}

	Clipper::clean();
	delete ge;
	delete gm;
	sbox::cleanSDL();
}

#endif




int main(int argc, char *argv[]) {

#ifdef DEBUG
	move_test();
#endif

	return EXIT_SUCCESS;
}

