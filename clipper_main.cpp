#include "clipper.h"
#include "sbox.h"
#include "preinclude.h"
#include "pen.h"
int main()
{
	sbox::initSDL();

	Clipper ccc;
	ResManager rm;

	ccc.setResManager(&rm);
	Clipper::initFrom("resource/cp1");
	ccc.setX(100);
	ccc.setY(100);
	ccc.setDepth(0);
	ccc.gotoAndPlay(0);

	bool quit = false;
	SDL_Event event;
	int cnt = 0;
	while(!quit)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
				quit = true;
		}
		//blit

		SDL_BlitSurface(ccc.getSurface(), 
				NULL,
				sbox::screen, 
				&sbox::getRect(ccc.getX(), ccc.getY()));

//		ccc.gotoAndPlay(cnt % ccc.totalFrame());
		cnt++;
		SDL_Flip(sbox::screen);
		sbox::delay();
	}

	sbox::cleanSDL();
	return 0;
}
