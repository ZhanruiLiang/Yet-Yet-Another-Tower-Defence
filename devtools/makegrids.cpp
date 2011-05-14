#include "../sbox.h"
#include "../pen.h"
typedef SDL_Surface Surface;

bool save(Surface * picture, string filename)
{
	return SDL_SaveBMP(picture, filename.c_str())==0;
}

int main()
{
	int n, m;
	int width;
	SDL_Event event;

	cout << "Input n,m(n row, m column): ";
	cin >> n >> m;
	cout << "Width(32?): ";
	cin >> width;
	
	sbox::SCREEN_WIDTH = m*width;
	sbox::SCREEN_HEIGHT = n*width;
	sbox::initSDL();
	//pre bliting

	Surface* backgd = sbox::newSurface(m*width, n*width);

	//draw white
	SDL_FillRect(backgd, &backgd->clip_rect, sbox::getColorByName("white"));

	//draw lines
	Pen pen(backgd);
	pen.setColor(0,0,0);

	for(int i = 1; i <= n; i++)
	{
		pen.moveTo(0, width*i-1);
		pen.lineTo(m*width-1, width*i-1);
	}
	for(int i = 1; i <= m; i++)
	{
		pen.moveTo(width*i-1, 0);
		pen.lineTo(i*width-1, width*n-1);
	}


	// blit
	SDL_BlitSurface(backgd, &backgd->clip_rect, sbox::screen, NULL);

	// save the picture
	string picture_file_name = "xx.bmp";
	if(save(backgd, picture_file_name)) cout << "Saved in "<<picture_file_name<<" .\n";
	else cout << "Save failed.\n";

	// wait for quit
	bool quit = false;
	while(!quit)
	{
		while(SDL_PollEvent( &event))
		{
			if(event.type == SDL_QUIT)
				quit = true;
		}
		//draw

		//flip
		if( SDL_Flip(sbox::screen) == -1 )
			return 1;
		sbox::delay();
	}
	SDL_FreeSurface(backgd);
	sbox::cleanSDL();
	return 0;
}
