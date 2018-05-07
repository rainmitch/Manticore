
#ifndef IR_TO_BYTE_CODE_H
#define IR_TO_BYTE_CODE_H

#include <iostream>
#include <vector>

#include <IR/IR.h>



namespace Manticore
{
	std::vector<IR> translateIRToByteCode (std::string input);
}

#endif
