#include "../include/IdentifierDeclaration.h"
#include <llvm/Module.h>
#include <iostream>
namespace Dragonc 
{

Value* IdentifierDeclaration::emitCode(IRBuilder<> &builder, Module &module)
{
	if(!mValue)
		mValue = builder.CreateAlloca(Type::getInt32Ty(getGlobalContext()), 0, mName);
	return mValue;
}

}