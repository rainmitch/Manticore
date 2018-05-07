
#ifndef MANTICORE_AST_H
#define MANTICORE_AST_H

#include <iostream>

namespace Manticore
{
	class AST
	{
	public:
		AST (std::string value, uint32_t line, uint32_t col);
		
		
		
		std::string value;
		uint32_t line;
		uint32_t col;
		std::vector<AST> children;
	};
}

#endif
