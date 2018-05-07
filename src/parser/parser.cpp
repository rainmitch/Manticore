
#include <parser/parser.h>

namespace Manticore
{
	void Parser::parse (std::string input)
	{
		Lexer lex;
		lex.whitespace = {" ", "\t", "\n"};
		lex.feed (input);
		return parse (lex);
	}
	
	void Parser::parse (Lexer lex)
	{
		
	}
	
	void Parser::add (std::string name, std::string rule)
	{
		std::vector<Rule> rs = parseRule (name, rule);
		
		for (Rule &r : rs)
			rules.push_back (r);
	}
}
