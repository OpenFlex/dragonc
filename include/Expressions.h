#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include <llvm/DerivedTypes.h>
#include <llvm/IRBuilder.h>
#include <llvm/Module.h>
#include <llvm/Instruction.h>

#include <string>

#include "DragonTypes.h"

using namespace llvm;
using namespace std;

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



class SubstractExpression : public BaseExpression
{
public:
	SubstractExpression(BaseExpression *lhs, BaseExpression *rhs)
	:BaseExpression(), mLhs(lhs), mRhs(rhs) {};
	virtual ~SubstractExpression() { delete mLhs;delete mRhs;}

	virtual Value *emitCode(IRBuilder< true >& builder, Module &module);

private:
	BaseExpression *mLhs, *mRhs;

};



class MultiplyExpression : public BaseExpression
{
public:
	MultiplyExpression(BaseExpression *lhs, BaseExpression *rhs)
	:BaseExpression(), mLhs(lhs), mRhs(rhs) {};
	virtual ~MultiplyExpression() { delete mLhs;delete mRhs;}

	virtual Value *emitCode(IRBuilder< true >& builder, Module &module);

private:
	BaseExpression *mLhs, *mRhs;

};



class DivideExpression : public BaseExpression
{
public:
	DivideExpression(BaseExpression *lhs, BaseExpression *rhs)
	:BaseExpression(), mLhs(lhs), mRhs(rhs) {};
	virtual ~DivideExpression() { delete mLhs;delete mRhs;}

	virtual Value *emitCode(IRBuilder< true >& builder, Module &module);

private:
	BaseExpression *mLhs, *mRhs;

};



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



class IdentifierDeclaration : public BaseExpression
{
public:
	IdentifierDeclaration(string& name)
	:BaseExpression(), mName(name) {};

	virtual Value *emitCode(IRBuilder<> &builder, Module &module);
	virtual Value *getValue() { return mValue; };
private:
	string mName;
	Value *mValue;
};



class IntegerValueExpr : public BaseExpression
{
public:
	IntegerValueExpr(int value) : BaseExpression(), mValue(value) {} ;

	virtual Value *emitCode(IRBuilder<>& builder, Module &module);

private:
	int mValue;
};



class FuctionDeclExpr : public BaseExpression
{
public:
	FuctionDeclExpr(DragonType returnType, string name) : BaseExpression(), mName(name), mReturnType(returnType){} ;

	virtual Value *emitCode(IRBuilder<>& builder, Module &module);

private:
	
	string mName;
	DragonType mReturnType;
};



class VariableExpression : public BaseExpression
{
public:
	VariableExpression(BaseExpression *identifier):BaseExpression(), mIdent(identifier) {};
	virtual Value *emitCode(IRBuilder< true >& builder, Module &module);

private:
	BaseExpression *mIdent;
};

class PrintfInvocation : public BaseExpression
{
public:
	PrintfInvocation(BaseExpression *identifier):BaseExpression(), mParams(identifier) {};
	virtual Value *emitCode(IRBuilder< true >& builder, Module &module);

private:
	// Only single param for now
	BaseExpression *mParams;
};




}

#endif // EXPRESSIONS_H
