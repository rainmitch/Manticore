
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
		Token (std::string token, uint32_t line, uint32_t col);
		std::string token;
		uint32_t line;
		uint32_t col;
	};

	class Lexer
	{
	public:
		Lexer ();
		
		Token &operator[] (int place);
		uint32_t size ();
		
		void feed (std::string data);
		
		void push (Token t);
		
		Token next ();
		Token peek ();
		bool eos (); // end of stream
		bool empty ();
		void reset ();
		void rewind (int steps);
		void skip (int steps);
		void stepBack ();
		
		
		std::vector<Token> tokens;
		
		std::vector<std::string> whitespace;
		std::string newline = "\n"; // presume most languages use \n
		
		uint32_t internalPointer;
	};
}

inline std::ostream &operator << (std::ostream &os, const Manticore::Token &tok)
{
	return os << "'" << tok.token << "' line: " << tok.line << ", col: " << tok.col;
}

inline bool operator ==(const Manticore::Token &token, const std::string &val)
{
	return token.token == val;
}

inline bool operator ==(const std::string &val, const Manticore::Token &token)
{
	return token == val;
}

inline bool operator !=(const Manticore::Token &token, const std::string &val)
{
	return !(token == val); // not whatever the function above returns
}

#endif
