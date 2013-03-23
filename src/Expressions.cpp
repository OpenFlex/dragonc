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

Value *FuctionDeclExpr::emitCode(IRBuilder<>& builder, Module &module)
{
	llvm::FunctionType *funcType = llvm::FunctionType::get(builder.getInt32Ty(), false);
	llvm::Function *mainFunc = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, mName, &module);
	llvm::BasicBlock *entry = llvm::BasicBlock::Create(module.getContext(), "entrypoint", mainFunc);
	builder.SetInsertPoint(entry);
	
	return entry;
}

Value *PrintfInvocation::emitCode(IRBuilder< true >& builder, Module &module)
{
	Function* printf_proto = module.getFunction("printf");

	llvm::Constant *format_const = llvm::ConstantDataArray::getString(builder.getContext(), "%d\n");
	llvm::GlobalVariable *var = new llvm::GlobalVariable(module, llvm::ArrayType::get(llvm::IntegerType::get(builder.getContext(), 8), 4),
					 true, llvm::GlobalValue::PrivateLinkage, format_const, ".str");
	llvm::Constant *zero = llvm::Constant::getNullValue(llvm::IntegerType::getInt32Ty(builder.getContext()));

	std::vector<llvm::Constant*> indices;
	indices.push_back(zero);
	indices.push_back(zero);
	llvm::Constant *var_ref = llvm::ConstantExpr::getGetElementPtr(var, indices);

	llvm::CallInst *call = builder.CreateCall2(printf_proto, var_ref, mParams->emitCode(builder, module));
	call->setTailCall(false);
	
	return call;
}


}