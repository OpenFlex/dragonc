#ifndef ADDEXPRESSION_H
#define ADDEXPRESSION_H

#include "DragonBaseExpression.h"

namespace Dragonc
{

class AddExpression : public BaseExpression
{
public:
    AddExpression(BaseExpression *lhs, BaseExpression *rhs)
	:BaseExpression(), mLhs(lhs), mRhs(rhs) {};
    virtual ~AddExpression() { delete mLhs;delete mRhs;}
	
    virtual Value *emitCode(IRBuilder< true >& builder, Module &module);
	
private:
	BaseExpression *mLhs, *mRhs;
	
};

}

#endif // ADDEXPRESSION_H
