#include "IntegerValueExpr.h"

namespace Dragonc 
{
	
Value *IntegerValueExpr::emitCode(IRBuilder<>& builder, Module &module) 
{
	return ConstantInt::get(getGlobalContext(), APInt(32, mValue));
}

}