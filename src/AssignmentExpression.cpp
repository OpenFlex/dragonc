#include "AssignmentExpression.h"

namespace Dragonc
{

Value * AssignmentExpression::emitCode(IRBuilder< true >& builder, Module &module) 
{
	return builder.CreateStore(mRhs->emitCode(builder, module), mLhs->emitCode(builder, module));
}

}