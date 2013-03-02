#include "Expressions.h"

#include <iostream>

namespace Dragonc
{

Value * AddExpression::emitCode(IRBuilder< true >& builder, Module &module)
{
	return builder.CreateAdd(mRhs->emitCode(builder, module), mLhs->emitCode(builder, module));
}


Value * SubstractExpression::emitCode(IRBuilder< true >& builder, Module &module)
{
	return builder.CreateSub(mRhs->emitCode(builder, module), mLhs->emitCode(builder, module));
}


Value * MultiplyExpression::emitCode(IRBuilder< true >& builder, Module &module)
{
	return builder.CreateMul(mRhs->emitCode(builder, module), mLhs->emitCode(builder, module));
}


Value * DivideExpression::emitCode(IRBuilder< true >& builder, Module &module)
{
	Value* rexpr = builder.CreateCast(Instruction::UIToFP, mRhs->emitCode(builder, module), builder.getFloatTy());
	Value* lexpr = builder.CreateCast(Instruction::UIToFP, mLhs->emitCode(builder, module), builder.getFloatTy());
	return builder.CreateCast(Instruction::FPToUI, builder.CreateFDiv(rexpr, lexpr), builder.getInt32Ty());
}


Value * AssignmentExpression::emitCode(IRBuilder< true >& builder, Module &module)
{
	return builder.CreateStore(mRhs->emitCode(builder, module), mLhs->emitCode(builder, module));
}


Value* IdentifierDeclaration::emitCode(IRBuilder<> &builder, Module &module)
{
	if(!mValue)
		mValue = builder.CreateAlloca(Type::getInt32Ty(getGlobalContext()), 0, mName);
	return mValue;
}


Value *IntegerValueExpr::emitCode(IRBuilder<>& builder, Module &module)
{
	return ConstantInt::get(getGlobalContext(), APInt(32, mValue));
}


Value* VariableExpression::emitCode(IRBuilder< true >& builder, Module &module)
{
	return builder.CreateLoad(mIdent->getValue());
}


}