
#include <parser/ast.h>

namespace Manticore
{
	AST::AST (std::string value, uint32_t line, uint32_t col)
	{
		this->value = value;
		this->line = line;
		this->col = col;
	}
}
