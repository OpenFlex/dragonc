#include "VariableExpression.h"

namespace Dragonc
{
	
Value* VariableExpression::emitCode(IRBuilder< true >& builder, Module &module)
{
	return builder.CreateLoad(mIdent->getValue());
}
	
	
}
