
#ifndef MANTICORE_AST_H
#define MANTICORE_AST_H

#include <iostream>
#include <vector>

namespace Manticore
{
class Token;

	class AST
	{
	public:
		AST (std::string value, uint32_t line=0, uint32_t col=0);
		
		void add (std::string value);
		void add (AST value);
		void add (Token t);
		
		int size ();
		AST &operator [](int place);
		
		void print (int depth=0);
		
		std::string value;
		uint32_t line;
		uint32_t col;
		std::vector<AST> children;
	};
}

#endif
