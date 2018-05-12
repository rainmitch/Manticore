
#ifndef MANTICORE_PARSER_H
#define MANTICORE_PARSER_H

#include <iostream>
#include <vector>
#include <map>

typedef struct
{
	uint32_t pos = 0; // the parser's position in it's loop
} ParserHelper;

namespace Manticore
{
	class Lexer;
	class Rule;
	class AST;
	
	class Parser
	{
	public:
		int scanAhead (Rule r, int tokensLeft);
		virtual AST parse (std::string input);
		AST parse (Lexer lex);
		void add (std::string name, std::string rule);
		std::vector<Rule> getRuleByName (std::string name);
		
		std::vector<Rule> rules;
		std::string rootRule;
	private:
		AST parseFunction (Lexer tokens, std::vector<Rule> internalRules, ParserHelper &helper);
	};
}

#endif
