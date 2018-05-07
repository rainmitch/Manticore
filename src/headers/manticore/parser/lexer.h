
#ifndef MANTICORE_LEXER_H
#define MANTICORE_LEXER_H

#include <iostream>
#include <vector>

namespace Manticore
{
	
	class Token // keeping input data like this will make error generating easier in the future
	{
	public:
		Token ();
		Token (char token, uint32_t line, uint32_t col);
		char token;
		uint32_t line;
		uint32_t col;
	};

	class Lexer
	{
	public:
		Lexer ();
		
		Token &operator[] (int place);
		int size ();
		
		void feed (std::string data);
		
		std::vector<Token> tokens;
		
		std::vector<std::string> whitespace;
		std::string newline = "\n"; // presume most languages use \n
	};
}

inline std::ostream &operator << (std::ostream &os, const Manticore::Token &tok)
{
	return os << "'" << tok.token << "' line: " << tok.line << ", " << tok.col;
}

#endif
