#include "DragonParser.h"
#include "AssignmentExpression.h"
#include "IntegerValueExpr.h"
#include "AddExpression.h"
#include "VariableExpression.h"
#include <iostream>
#include <map>
#include <cstdlib>
using namespace std;
namespace Dragonc
{

Parser::Parser(Lexer *dragonLexer)
{
	mLexer = dragonLexer;
}

Parser::~Parser()
{
	int size = mExprList.size();
	for(int i = 0; i < size; i++) {
		delete mExprList[i];
	}
}


BaseExpression* Parser::getIdent(string name)
{
	return new VariableExpression(mSymbolTable[name]);
}

void Parser::emitCode(IRBuilder<> &builder, Module &module)
{
	int size = mExprList.size();
    for (int i = 0; i < size; i++) {
		if(mExprList[i] != NULL)
        mExprList[i]->emitCode(builder, module);
    }
}

void Parser::parse()
{
	TokenType token;
    do {
		token = mLexer->getToken();
        switch (token) {
        case IDENTIFIER:
            handleIdentifierDeclaration();
            break;
        default:
            break;
        }
    } while (token != TOKEN_EOF);
}


void Parser::handleIdentifierDeclaration()
{
	string name = mLexer->getCurrentTokenValue();
	string initValue;
	if(mSymbolTable.find(name) == mSymbolTable.end()) 
	{
			IdentifierDeclaration *decl = new IdentifierDeclaration(name);
			mExprList.push_back(decl);
			mSymbolTable[name] = decl;
			
	}
    while (mLexer->getCurrentTokenValue() != ";") {
        switch (mLexer->getToken()) {
        case SPECIAL_SYMBOL:
            string symbol = mLexer->getCurrentTokenValue();
            if (symbol == "=") {
				mExprList.push_back(handleBinaryOp(mSymbolTable[name], symbol));
            }
            break;
        }
    }
}

BaseExpression* Parser::handleBinaryOp(BaseExpression *lhs, string symbol)
{
	BaseExpression *expr = NULL;
	switch(mLexer->getToken()) {
		case INTEGER:
			expr = new IntegerValueExpr(atoi(mLexer->getCurrentTokenValue().c_str()));
			break;
		case IDENTIFIER:
			expr = new VariableExpression(mSymbolTable[mLexer->getCurrentTokenValue()]);
			break;
	}
	
 	mLexer->getToken();
     if (mLexer->getCurrentTokenValue() == "+") {
         expr = handleBinaryOp(expr, mLexer->getCurrentTokenValue());
     }
	
 	if(symbol == "=") {
 		return new AssignmentExpression(lhs, expr);
 	}
  	else if (symbol == "+") {
 		return new AddExpression(lhs, expr);
 	}
}


}
