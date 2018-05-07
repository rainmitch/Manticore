
#ifndef MANTICORE_PARSER_H
#define MANTICORE_PARSER_H

#include <iostream>
#include <vector>
#include <map>

#include <parser/lexer.h>
#include <parser/rule.h>

namespace Manticore
{
	class Parser
	{
	public:
		virtual void parse (std::string input);
		void parse (Lexer lex);
		void add (std::string name, std::string rule);
		
		std::vector<Rule> rules;
	};
}

#endif
