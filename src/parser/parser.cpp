
#include <parser/parser.h>

#include <parser/lexer.h>
#include <parser/rule.h>
#include <parser/ast.h>

typedef struct
{
	uint32_t pos = 0; // the parser's position in it's loop
} ParserHelper;

std::string strip (std::string input)
{
	return input.substr (1, input.size () - 2);
}


namespace Manticore
{
	AST parseFunction (Lexer lex, std::vector<Rule> rules, ParserHelper helper)
	{
		AST out = AST ("ROOT");
		
		
		int n = lex.size ();
		int r = rules.size ();
		
		auto P = std::vector<std::vector<std::vector<bool>>> ();
		
		for (int i = 0; i < n; i++)
		{
			P.push_back (std::vector<std::vector<bool>> ());
			for (int j = 0; j < n-i; j++)
			{
				P[i].push_back (std::vector<bool> (n-i));
				for (int k = 0; k < r; k++)
				{
					P[i][j].push_back (false);
				}
			}
		}
		
		for (int sliceLength = 1; sliceLength < n+1; sliceLength++)
		{
			std::cout << "length of slice: " << sliceLength << ":" << std::endl;
			for (int posOfSlice = 0; posOfSlice < n-sliceLength+1; posOfSlice++)
			{
				std::cout << "   pos: " << posOfSlice << std::endl;
				Lexer tokens = lex.slice (posOfSlice, sliceLength);
				
			}
		}
		
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n-i; j++)
			{
				std::cout << "[";
				for (int k = 0; k < r; k++)
				{
					std::cout << ((P[i][j][k] == true) ? "X" : "-");
					if (k != r - 1)
						std::cout << ", ";
				}
				std::cout << "]";
				if (j != n-i - 1)
					std::cout << ", ";
			}
			std::cout << std::endl;
		}
		
		return out;
	}
	
	AST Parser::parse (std::string input)
	{
		Lexer lex;
		lex.whitespace = {" ", "\t", "\n"};
		lex.feed (input);
		return parse (lex);
	}
	
	AST Parser::parse (Lexer lex)
	{
		ParserHelper helper = {0};
		return parseFunction (lex, rules, helper);
	}
	
	void Parser::add (std::string name, std::string rule)
	{
		std::vector<Rule> rs = parseRule (name, rule);
		
		for (Rule &r : rs)
			rules.push_back (r);
	}
}
