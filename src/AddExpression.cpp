#include "AddExpression.h"
#include <iostream>
namespace Dragonc
{
	
Value * AddExpression::emitCode(IRBuilder< true >& builder, Module &module) 
{
	return builder.CreateAdd(mRhs->emitCode(builder, module), mLhs->emitCode(builder, module));
}
	
}
