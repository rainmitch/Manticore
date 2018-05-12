
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
	l.feed ("void a = 5;");
	
	Parser p;
	
	p.add ("test",  "!(<word> <word>) ('=') !'5' ';'");
	
	p.rootRule = "test";
	
	AST tree = p.parse (l);
	
	tree.print ();
}
