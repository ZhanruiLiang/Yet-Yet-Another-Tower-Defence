#include "clipper.h"
#include <fstream>
#include <sstream>
#include "parser.h"
using std::ifstream;
using std::stringstream;

typedef vector<SDL_Surface*>::iterator SurfaceIter;

Clipper::Clipper():_x(0),_y(0),
	_width(0),_height(0),
	_scale(1.0),
	_visible(true),
	_frame(0),
	_stop(false)
{

}

// initialize the clipper from files
// the filename is a floder, it must contians:
// 		1) index.tdidx: a plain ASCII file
//		2) *.png: the frames, one or more these files


// 1. read the whole index file to a string
// 2. decode the string
// 3. parse the string
bool Clipper::initFrom(const char * filename)
{
	//open file
	ifstream fin;
	fin.open(filename);
	if( fin.fail() )
	{
		fin.close();
		return false;
	}

	// open succeed, read into whole
	string whole = "";
	string temp;
	do
	{
		getline(fin, temp);
		if(!fin) break;
		whole += temp + "\n";
	}while(true)
	fin.close();

	// decoded whole, store in dw
	string dw;
	if(!decode(whole.begin(), whole.end(), dw))
	{
#ifdef DEBUG
		std::cout << "Decode failed!\n";
#endif
		return false;
	}

	// decode success, parse
	Parser par1;
	par1.init(dw.begin(), dw.end());

	while(par1.nextSection())
	{
		// in 1st level
		Section sec1 = par1.currentSection();
		if(sec1.getName() == "datafield")
		{
			// in 2nd level
			EqlParser par2;
			par2.init(sec1.cont_beg(), sec1.cont_end());
			while(par2.nextSection())
			{
				// in 3rd level
				Section sec2 = par2.currentSection();
				string name = sec2.getName();
				string value = sec2.getContent();
				stringstream ss;
				ss << value;
				if(name == "_x"){ ss >> _x;}
				else if(name == "_y"){ ss >> _y; }
				//TODO: add others
			}
		}
		else if(sec1.getName() == "frame")
		{
			// in 2nd level
			Parser par2;
			par2.init(sec1.cont_beg(), sec1.cont_end());
			while(par2.nextSection())
			{
				Section sec2 = par2.currentSection();
				string filename = sec2.getName();
				// add some frames from the file "$filename"
				_addFramesFromFile(filename, sec2.cont_beg(), sec2.cont_end());
			}
		}
	}
	//finish adding frames	
}

bool Clipper::_addFramesFromFile(string filename, strIter begin, strIter end)
{
	EqlParser par1;
	par1.init(begin, end);
	//XXX
}

Clipper::~Clipper()
{
}
void Clipper::setX(int x)
{
	_x = x;
}

void Clipper::setY(int y)
{
	_y = y;
}

int Clipper::getX()
{
	return _x;
}

int Clipper::getY()
{
	return _y;
}

/*
// if the scale is set, the height and width will be reset to new value
// 	scale * widht0 = width
//	width0 = width / scale
//  width1 / scale1 = width2 / scale2
//  width2 = width1 * scale2 / scale1
void Clipper::setScale(double scale)
{
	if(scale < 0.001)
		scale = 0.001;
	_width = _width * scale / _scale;
	_height = _height * scale / _scale;
	_scale = scale;
}

double Clipper::getScale()
{
	return _scale;
}

void setDepth(int depth)
{
	_depth = depth;
}

int getDepth()
{
	return _depth;
}
*/

void Clipper::setVisible(bool val)
{
	_visible = val;
}

bool Clipper::getVisible()
{
	return _visible;
}

SDL_Surface * Clipper::getSurface()
{
	if(_visible)
		return _res_manager->getSurface(_surfaces[currentFrame()]);
	else
		return NULL;
}

bool Clipper::_changeFrame(int num)
{
	if(num < _surfaces.size())
		_frame = num;
	else
	{
#ifdef DEBUG
		cout << "Error! " << "Frame " << num << " out of range.\n";
#endif
		return false;
	}
	return true;
}

bool Clipper::gotoAndPlay(int num)
{
	bool flag;
	flag = _changeFrame(num);
	if(!flag) return false;
	_stop = false;
	return true;
}

bool Clipper::gotoAndStop(int num)
{
	bool flag;
	flag = _changeFrame(num);
	if(!flag) return false;
	_stop = true;
	return true;
}

int Clipper::currentFrame()
{
	return _frame;
}

void Clipper::play()
{
	_stop = false;
}

void Clipper::stop()
{
	_stop = true;
}
