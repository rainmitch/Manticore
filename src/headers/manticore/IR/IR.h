
#ifndef MANTICORE_IR_H
#define MANTICORE_IR_H

#include <iostream>
#include <vector>

#include <IR/IRToByteCode.h>

namespace Manticore
{
	class IR
	{
	public:
		uint16_t opcode;
		std::vector<std::string> operands;
	};
}

inline std::ostream &operator <<(std::ostream &os, const Manticore::IR &ir)
{
	os << "0x" << std::hex << std::uppercase << ir.opcode << std::endl;
	os << "   Operands: ";
	
	for (unsigned int i = 0; i < ir.operands.size (); i++)
	{
		os << ir.operands[i];
		if (i < ir.operands.size () - 1)
			os << " ";
	}
	
	return os;
}

#endif
