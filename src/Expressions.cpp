#include "Expressions.h"

#include <iostream>

namespace Dragonc
{

Value * AddExpression::emitCode(IRBuilder< true >& builder, Module &module)
{
	return builder.CreateAdd(mLhs->emitCode(builder, module), mRhs->emitCode(builder, module));
}


Value * SubstractExpression::emitCode(IRBuilder< true >& builder, Module &module)
{
	return builder.CreateSub(mLhs->emitCode(builder, module), mRhs->emitCode(builder, module));
}


Value * MultiplyExpression::emitCode(IRBuilder< true >& builder, Module &module)
{
	return builder.CreateMul(mLhs->emitCode(builder, module), mRhs->emitCode(builder, module));
}


Value * DivideExpression::emitCode(IRBuilder< true >& builder, Module &module)
{
	Value* rexpr = builder.CreateCast(Instruction::UIToFP, mRhs->emitCode(builder, module), builder.getFloatTy());
	Value* lexpr = builder.CreateCast(Instruction::UIToFP, mLhs->emitCode(builder, module), builder.getFloatTy());
	return builder.CreateCast(Instruction::FPToUI, builder.CreateFDiv(lexpr, rexpr), builder.getInt32Ty());
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


FunctionDeclExpr::FunctionDeclExpr(DragonType returnType, string name, VariableList &variableList):BaseExpression()
{
    mName = name;
    mReturnType = returnType;
//    mVariableList = variableList;
}

Value *FunctionDeclExpr::emitCode(IRBuilder<>& builder, Module &module)
{
	bool isMain = (mName == "main");
	Type* returnType = toLlvmType(builder, mReturnType);

	if(!returnType)
	{
		throw "Invalid return type for function " + mName;
	}
	
	llvm::FunctionType *funcType = 0;
	funcType = llvm::FunctionType::get(returnType, false);
	
	llvm::Function *funcPtr = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, mName, &module);
	llvm::BasicBlock *entry = llvm::BasicBlock::Create(module.getContext(), "entrypoint", funcPtr);
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
