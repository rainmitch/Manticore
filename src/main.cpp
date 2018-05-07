
#include <iostream>

#include <core/internal.h>
#include <core/version.h>

#include <IR/IRToByteCode.h>

#include <parser/parser.h>

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
	
	Parser p;
	
	p.add ("test", "!('int' 'a') '=' '5' ';'");
}
