
#ifndef MANTICORE_RULE_H
#define MANTICORE_RULE_H

#include <iostream>
#include <vector>

namespace Manticore
{
	class Rule
	{
	public:
		Rule ();
		
		
		std::string name;
		std::vector<std::string> parts;
	};
	std::vector<Rule> parseRule (std::string name, std::string rule);
}

#endif
