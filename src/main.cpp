
#include <iostream>

#include <core/internal.h>
#include <core/version.h>

#include <IR/IRToByteCode.h>

#include <parser/parser.h>
#include <parser/lexer.h>
#include <parser/rule.h>
#include <parser/ast.h>

using namespace Manticore;

void help ()
{
	std::cout << "Version: " << VERSION_STRING << std::endl;
}

int main (int argc, char **args)
{
	std::string test =
		".specification = 0;";
	
	Lexer l = Lexer ();
	l.whitespace = {" ", "\t", "\n"};
	l.feed ("int a = 5;");
	
	for (unsigned int i = 0; i < l.size (); i++)
	{
		std::cout << l[i] << std::endl;
	}
	
	Parser p;
	
	p.add ("test",  "'int' 'a' '=' '5' ';'");
	//p.add ("test2", "'int' 'a'");
	
	p.rootRule = "test";
	
	AST tree = p.parse (l);
	
	tree.print ();
}
