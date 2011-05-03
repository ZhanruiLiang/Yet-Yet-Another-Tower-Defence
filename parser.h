#ifndef PARSER_H
#define PARSER_H

#include<string>
#include<iterater>
#include<algorithm>

using std::string;
typedef string::iterator strIter;

struct Section
{
	strIter name_beg, name_end;
	strIter cont_beg, cont_end;
	string getName()
	{
		string ans;
		copy(
				name_beg,
				name_end,
				std::back_insert_iterator< string >(ans)
			);
		return ans;
	}
};

struct Eql
{
	string name;
	string value;
	Eql(string name0, string value0):name(name0),value(value0){}
	Eql();
}

bool nextSection(const strIter begin,
		const strIter end,
		strIter & current, // will be modified
		Section & section); // the result will be store here, if succeed

bool nextEql(const strIter begin,
		const strIter end,
		strIter & current,
		Eql & eql);

bool decode(const strIter begin,
		const strIter end,
		string & result);

bool encode(const strIter begin,
		const strIter end,
		string & result);

#endif
