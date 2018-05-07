
#ifndef MANTICORE_PARSER_H
#define MANTICORE_PARSER_H

#include <iostream>
#include <vector>
#include <map>


namespace Manticore
{
	class Lexer;
	class Rule;
	class AST;
	
	class Parser
	{
	public:
		virtual AST parse (std::string input);
		AST parse (Lexer lex);
		void add (std::string name, std::string rule);
		
		std::vector<Rule> rules;
	};
}

#endif
