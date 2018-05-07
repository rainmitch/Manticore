
#include <parser/ast.h>

#include <parser/lexer.h>

namespace Manticore
{
	AST::AST (std::string value, uint32_t line, uint32_t col)
	{
		this->value = value;
		this->line = line;
		this->col = col;
	}
	
	void AST::add (std::string value)
	{
		children.push_back (AST (value, 0, 0));
	}
	
	void AST::add (AST value)
	{
		children.push_back (value);
	}
	
	void AST::add (Token t)
	{
		children.push_back (AST (std::string (1, t.token), t.line, t.col));
	}
	
	int AST::size ()
	{
		return children.size ();
	}
	
	AST &AST::operator [](int place)
	{
		return children[place];
	}
	
	void AST::print (int depth)
	{
		for (int i = 0; i < depth; i++)
		{
			std::cout << "   ";
		}
		std::cout << value;
		if (size () > 0)
			std::cout << ":";
		std::cout << std::endl;
		
		
	}
}
