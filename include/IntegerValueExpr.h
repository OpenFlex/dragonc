#ifndef INTEGERVALUEEXPR_H
#define INTEGERVALUEEXPR_H
#include "DragonBaseExpression.h"

namespace Dragonc
{

class IntegerValueExpr : public BaseExpression
{
public:
	IntegerValueExpr(int value) : BaseExpression(), mValue(value) {} ;
	
    virtual Value *emitCode(IRBuilder<>& builder, Module &module);
	
private:
	int mValue;	
};

}

#endif // INTEGERVALUEEXPR_H
