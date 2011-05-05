#ifndef PARSER_H
#define PARSER_H

#include<string>
#include<iterater>
#include<algorithm>

using std::string;
typedef string::iterator strIter;

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
	protected:
		//TODO:finish it
};

class EqlSection: public Section
{
	public:
		EqlSection();
		string getContent();
	private:
		//TODO
};

// The parser class
class Parser
{
	public:
		Parser();
		// init, tell the parser where to begin and end
		void init(strIter begin, strIter end);
		bool virtual nextSection();
		Section virtual currentSection();
		bool isEnd();
	protected:
		// TODO
};

class EqlParser: public Parser
{
	public:
		EqlParser();
		bool virtual nextSection();
		Section virtual currentSection();
	private:
		// TODO
};
bool decode(const strIter begin,
		const strIter end,
		string & result);

bool encode(const strIter begin,
		const strIter end,
		string & result);

#endif
