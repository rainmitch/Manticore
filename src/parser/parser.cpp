
#include <parser/parser.h>

#include <parser/lexer.h>
#include <parser/rule.h>
#include <parser/ast.h>

namespace Manticore
{
	AST Parser::parse (std::string input)
	{
		Lexer lex;
		lex.whitespace = {" ", "\t", "\n"};
		lex.feed (input);
		return parse (lex);
	}
	
	AST Parser::parse (Lexer lex)
	{
		AST out = AST ("ROOT");
		
		return out;
	}
	
	void Parser::add (std::string name, std::string rule)
	{
		std::vector<Rule> rs = parseRule (name, rule);
		
		for (Rule &r : rs)
			rules.push_back (r);
	}
}
