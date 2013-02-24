#ifndef DRAGONBASEEXPRESSION_H
#define DRAGONBASEEXPRESSION_H
#include <llvm/DerivedTypes.h>
#include <llvm/IRBuilder.h>
#include <llvm/Module.h>
using namespace llvm;

namespace Dragonc
{

class BaseExpression
{
public:
	BaseExpression() {};
	virtual Value *emitCode(IRBuilder<> &builder, Module &module) = 0;
	virtual ~BaseExpression() {}
	virtual Value *getValue() { return NULL; }
};

}

#endif // DRAGONBASEEXPRESSION_H
