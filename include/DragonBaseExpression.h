#ifndef DRAGONBASEEXPRESSION_H
#define DRAGONBASEEXPRESSION_H
#include <llvm/DerivedTypes.h>

using namespace llvm;

namespace Dragonc
{

class BaseExpression
{
public:
	virtual Value *emitCode() = 0;
	virtual ~BaseExpression() {}
	virtual void print() {}
	
};

}

#endif // DRAGONBASEEXPRESSION_H
