#ifndef PARSER_H
#define PARSER_H

#include<string>
#include<iterator>
#include<algorithm>

using std::string;
typedef string::iterator strIter;

// a section has the format:
//    \section{sectionName}{sectionContent}
class Section
{
	public:
		Section();
		const strIter & begin();
		const strIter & end();

		const strIter & cont_beg();
		const strIter & cont_end();

		virtual string getName();
		//this method may be override, 
		// since the return type may be different
		string getContent();

		void markName(strIter begin, strIter end);
		void markContent(strIter begin, strIter end);
		void markAll(strIter begin, strIter end);
	protected:
		strIter _beg,
				_end,
				_name_beg,
				_name_end,
				_cont_beg,
				_cont_end;
};

typedef Section EqlSection;

// The parser class
class Parser
{
	public:
		// init, tell the parser where to begin and end
		void init(strIter begin, strIter end);
		// usage, use nextSection() first, then use currentSection() to 
		// get
		bool virtual nextSection();
		Section virtual currentSection();
		bool isEnd();
	protected:
		strIter _begin,
				_end,
				_current;
		Section _section;
};

class EqlParser: public Parser
{
	public:
		bool virtual nextSection();
	protected:
		//none 
};
bool decode(const strIter begin,
		const strIter end,
		string & result);

bool encode(const strIter begin,
		const strIter end,
		string & result);

#endif
