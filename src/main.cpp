
#include <iostream>

#include <core/internal.h>
#include <core/version.h>

#include <IR/IRToByteCode.h>

using namespace Manticore;

void help ()
{
	std::cout << "Version: " << VERSION_STRING << std::endl;
}

int main (int argc, char **args)
{
	std::string test =
		".specification = 0;";
	
	std::vector<IR> irCode = translateIRToByteCode (test);
	
	for (IR &ir : irCode)
	{
		std::cout << ir << std::endl;
	}
}
