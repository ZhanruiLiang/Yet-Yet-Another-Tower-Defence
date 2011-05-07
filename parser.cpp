#include "parser.h"
#include "parser.h"
#include <algorithm>
#include <iterator>
using std::search;
//Section class

Section::Section(){

}
const strIter & Section::begin()
{
	return _beg;
}
const strIter & Section::end()
{
	return _end;
}
const strIter & Section::cont_beg()
{
	return _cont_beg;
}
const strIter & Section::cont_end()
{
	return _cont_end;
}
string Section::getName()
{
	string ans;
	for(strIter it = _name_beg; it != _name_end; it++)
		ans.push_back(*it);
	return ans;
}

string Section::getContent()
{
	string ans;
	for(strIter it = _cont_beg; it != _cont_end; it++)
		ans.push_back(*it);
	return ans;
}

void Section::markName(strIter begin, strIter end)
{
	_name_beg = begin;
	_name_end = end;
}
void Section::markContent(strIter begin, strIter end)
{
	_cont_beg= begin;
	_cont_end= end;
}
void Section::markAll(strIter begin, strIter end)
{
	_beg = begin;
	_end = end;
}

// Parser class
void Parser::init(strIter begin, strIter end)
{
	_begin = begin;
	_current = begin;
	_end = end;
}

bool Parser::nextSection()
{
	static const string KEY_SECTION = "\\section";
	strIter secPos,secEndPos;
	strIter nameBegin, nameEnd, contBegin, contEnd;

	secPos = search( _current, _end,
			KEY_SECTION.begin(), KEY_SECTION.end());
	if(secPos == _end) return false;

	while(_current != _end && *_current != '{') _current++;
	if(_current == _end) return false;
	//now, \section{...}{.......}
	//             ^
	nameBegin = _current + 1;
	// the {} counter, cnt
	int cnt = 1;
	while(cnt != 0)
	{
		_current++;
		if(_current == _end) return false;
		if(*_current == '{') cnt++;
		else if(*_current == '}') cnt--;
	}

	//now, \section{...}{.......}
	//                 ^
	nameEnd = _current;
	_section.markName(nameBegin, nameEnd);

	_current++;
	while(_current != _end && *_current != '{') _current++;
	if(_current == _end) return false;
	//now, \section{...}  {.......}
	//                    ^
	contBegin = _current + 1;
	cnt = 1;
	while(cnt != 0)
	{
		_current++;
		if(_current == _end) return false;
		if(*_current == '{') cnt++;
		else if(*_current == '}') cnt--;
	}

	//now, \section{...}  {.......}
	//                            ^
	contEnd = _current;
	_section.markContent(contBegin, contEnd);

	_current++;
	_section.markAll(secPos, _current);
	return true;
}

Section Parser::currentSection()
{
	return _section;
}

bool Parser::isEnd()
{
	return _current == _end;
}


bool EqlParser::nextSection()
{
	// find '='
	strIter eqlPos = std::find(_current, _end, '=');
	if(eqlPos == _end)
		return false;
	// mark
	strIter p1,p2;
	p1 = _current;
	// todo, __lskdj__=_lksldj__\n
	//         ^p1 ^p2  
	while(*p1 == ' ' || *p1 == '\t' || *p1 == '\n')
		p1++;
	p2 = eqlPos - 1;
	while(*p2 == ' ' || *p2 == '\t' || *p2 == '\n')
		p2--;
	// 		mark name
	_section.markName(p1,p2+1);

	// todo, __lskdj__=_lksldj__\n
	//                  ^p1  ^p2  
	p1 = eqlPos + 1;
	while(p1 != _end && 
			(*p1 == ' ' || *p1 == '\t' || *p1 == '\n'))
		p1++;
	p2 = p1;
	while(p2 != _end && *p2 != '\n')
		p2++;
	//		mark content
	_section.markContent(p1,p2);

	_section.markAll(_current, p2);
	//		continue
	_current = p2 + 1;

	return true;
}


bool decode(const strIter begin,
		const strIter end,
		string & result)
{
	result = "";
	copy(begin, end, std::back_insert_iterator<string>(result));
	return true;
}

bool encode(const strIter begin,
		const strIter end,
		string & result)
{
	result = "";
	copy(begin, end, std::back_insert_iterator<string>(result));
	return true;
}
