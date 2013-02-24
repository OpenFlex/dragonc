#ifndef VARIABLEEXPRESSION_H
#define VARIABLEEXPRESSION_H
#include "DragonBaseExpression.h"

namespace Dragonc
{

class VariableExpression : public BaseExpression
{
public:
    VariableExpression(BaseExpression *identifier):BaseExpression(), mIdent(identifier) {};
    virtual Value *emitCode(IRBuilder< true >& builder, Module &module);
	
private:
	BaseExpression *mIdent;
};

}

#endif // VARIABLEEXPRESSION_H
