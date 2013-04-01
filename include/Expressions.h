#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include <llvm/DerivedTypes.h>
#include <llvm/IRBuilder.h>
#include <llvm/Module.h>
#include <llvm/Instruction.h>

#include <string>

#include "DragonTypes.h"
#include "DragonLexer.h"

using namespace llvm;
using namespace std;

namespace Dragonc
{

enum ExecutionOrder
{
	PRE,
	POST
};
	
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
		:BaseExpression(), mName(name), mValue(0), mBuilder(0) {}

	virtual Value *emitCode(IRBuilder<> &builder, Module &module);
	virtual Value *getValue() { return mBuilder->CreateLoad(mValue); }
private:
	string mName;
	Value *mValue;
	IRBuilder<> *mBuilder;
};




class UseVariableExpression : public BaseExpression
{
public:
	UseVariableExpression(string name):BaseExpression(), mName(name) {}
	virtual Value *emitCode(IRBuilder< true >& builder, Module &module);
	virtual Value* getValue();
private:
	string mName;
	Value* mValue;
};


class IncrementExpression : public BaseExpression
{
public:
	IncrementExpression(string identifierName, ExecutionOrder order)
	:BaseExpression(), mIdentifier(identifierName), mOrder(order) {}
	
	virtual Value *emitCode(IRBuilder<> &builder, Module &module);
private:
	string mIdentifier;
	string mName;
	ExecutionOrder mOrder;
};



class IntegerValueExpression : public BaseExpression
{
public:
	IntegerValueExpression(int value) : BaseExpression(), mValue(value) {} ;

	virtual Value *emitCode(IRBuilder<>& builder, Module &module);

private:
	int mValue;
};



class FunctionDeclExpr : public BaseExpression
{
public:
	FunctionDeclExpr(DragonType returnType, string name, VariableList& argList):BaseExpression()
	{
		mName = name;
		mReturnType = returnType;
		mArgList = argList;
	}

	virtual Value *emitCode(IRBuilder<>& builder, Module &module);

private:
	string mName;
	DragonType mReturnType;
	VariableList mArgList;
};



class FuncArgumentExpression : public BaseExpression
{
public:
	FuncArgumentExpression(Argument* arg):BaseExpression(), mArg(arg) {}
	virtual Value *emitCode(IRBuilder< true >& builder, Module &module);
	virtual Value* getValue(){return mArg;}
private:
	Argument* mArg;
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
