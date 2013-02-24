#ifndef ASSIGNMENTEXPRESSION_H
#define ASSIGNMENTEXPRESSION_H
#include "DragonBaseExpression.h"
namespace Dragonc {

class AssignmentExpression : public BaseExpression
{
public:
	AssignmentExpression(BaseExpression *lhs, BaseExpression *rhs)
	:BaseExpression(),mLhs(lhs), mRhs(rhs) {}	
    
    virtual ~AssignmentExpression() 
	{ 
		delete mRhs; 
	};
    virtual Value *emitCode(IRBuilder< true >& builder, Module &module);
	
private:
	BaseExpression *mLhs;
	BaseExpression *mRhs;
};

}

#endif // ASSIGNMENTEXPRESSION_H
