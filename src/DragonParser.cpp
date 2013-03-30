#include "DragonParser.h"
#include "DragonContext.h"
#include "Expressions.h"

#include <llvm/ADT/StringSwitch.h>

#include <iostream>
#include <map>
#include <cstdlib>
#include <list>


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
	return new UseVariableExpression(name);
}

void Parser::emitCode(IRBuilder<> &builder, Module &module)
{
    DragonContext::clear();
	int size = mExprList.size();
	
	for (int i = 0; i < size; i++) {
		BaseExpression* e = mExprList[i];
		if(e != NULL)
			mExprList[i]->emitCode(builder, module);
	}
}


void Parser::parse()
{
	LexerToken currentToken;
	
	do {
		currentToken = mLexer->getToken();

		BaseExpression* expr = 0;
		switch (currentToken.type) {
			case TYPE:
				expr = handleType(currentToken.value);
				break;
			case IDENTIFIER:
				expr = handleIdentifier(currentToken);
				break;
			case EXPRESSION_END:
				
				break;
			case ASSIGNMENT_OP:
// 				handleAssignment();
				break;
			case CONST_NUMBER:

				break;
			case BRACE:
// 				handleBrace(currentToken.value.c_str()[0]);
				break;
			case KEYWORD:
				expr = handleKeyword(currentToken.value);
				break;
			default:
				break;
		}

		if(expr) {
			mExprList.push_back(expr);
		};
	} while (currentToken.type != TOKEN_EOF);
}

BaseExpression* Parser::handleType(string type_name)
{
	DragonType type = toDragonType(type_name);
	
	LexerToken identifier = mLexer->getToken();
	BaseExpression* expr = 0;
	
	switch (identifier.type) {
		case IDENTIFIER:
			expr = handleDeclaration(type, identifier.value);
			break;
		default:
			printf("Expected identifier after type %s", type_name.c_str());exit(0);
			break;
	}

	return expr;
}

BaseExpression* Parser::handleDeclaration(DragonType type, string name)
{
	LexerToken nextToken = mLexer->getToken();
	BaseExpression* expr = 0;

	switch (nextToken.type) {
		case EXPRESSION_END:
			expr = new IdentifierDeclaration(name);
			expr = new AssignmentExpression(expr, new IntegerValueExpression(0));
			break;
		case BINARY_OP:
			expr = new IdentifierDeclaration(name);
			expr = handleBinaryOp(expr, nextToken.value);
			break;
		case BRACE:
			if(nextToken.value[0] == '('){
				expr = handleFunctionDeclaration(type, name);
			} else {
				printf("Unexpected '%s' after '%s', expected '('", nextToken.value.c_str(), name.c_str());exit(0);
			}
			break;
		default:
			printf("Unexpected '%s' after '%s', expected ';', '=' or '('", nextToken.value.c_str(), name.c_str());exit(0);
			break;
	}

	return expr;
}

BaseExpression* Parser::handleFunctionDeclaration(DragonType type, string name)
{
	VariableList args;
	LexerToken nextToken;
	DragonVariable argument = {TYPE_NONE, ""};

	while(nextToken.value[0] != ')') {
		nextToken = mLexer->getToken();

		switch (nextToken.type) {
		case TYPE:
			argument.type = toDragonType(nextToken.value);
			break;
		case IDENTIFIER:
			if(argument.type != TYPE_NONE) {
				argument.name = nextToken.value;
				args.push_back(argument);
				argument.type = TYPE_NONE;
			} else {
				printf("No type specified '%s' in argument list for function '%s'", argument.name.c_str(), name.c_str());exit(0);
			}
			break;
		case BRACE:
		case SPECIAL_SYMBOL:
			break;
		default:
			printf("Unexpected '%s' in argument list for function '%s',"
				 " expected ','", nextToken.value.c_str(), name.c_str());exit(0);
			break;
		}
	}

	return new FunctionDeclExpr(type, name, args);
}

BaseExpression* Parser::handleKeyword(string keyword)
{
	int type = StringSwitch<int>(StringRef(keyword))
	.Case("printf", 0)
	.Case("scanf", 1)
	.Case("return", 10);
	BaseExpression *expr;
	LexerToken token;
	switch(type) {
		case 0:
			token = mLexer->getToken();
			if(token.value == "(") {
				expr = new PrintfInvocation(handleIdentifier(mLexer->getToken()));
			}
			token = mLexer->getToken();

			if(token.value != ";") {
				throw "Expected )";
			}
			break;
		default:
			break;
	}
	return expr;
}

BaseExpression* Parser::handleAssignment()
{
// 	LexerToken nextToken = mLexer->getToken();
// 	BaseExpression* expr = 0;
// 
// 	switch (nextToken.type) {
// 		case IDENTIFIER:
// 			expr = new AssignmentExpression(new IdentifierDeclaration(value), new IntegerValueExpr(0));
// 			break;
// 		case ASSIGNMENT_OP:
// 			expr = new AssignmentExpression(new IdentifierDeclaration(value), handleAssignment());
// 			break;
// 		case BRACE:
// 			function
// 		default:
// 			printf("Unexpected %s, expected ';', '=' or '('", value.c_str());exit(0);
// 			break;
// 	}
// 
// 	return expr;
}

BaseExpression* Parser::handleIdentifier(const LexerToken& identifier)
{
	LexerToken nextToken = mLexer->getToken();
	BaseExpression* expr = 0;

	switch (nextToken.type) {
		case EXPRESSION_END:
			expr = new UseVariableExpression(identifier.value);
			break;
		case BINARY_OP:
			expr = handleBinaryOp(new UseVariableExpression(identifier.value), nextToken.value);
			break;
		case BRACE:
			if(nextToken.value == ")") {
				expr = new UseVariableExpression(identifier.value);
			}
			break;
		default:
			printf("Unexpected '%s' after '%s', expected ';', '=' or '('", nextToken.value.c_str(), identifier.value.c_str());exit(0);
			break;
	}

	return expr;
}

BaseExpression* Parser::handleBrace(char brace)
{
// 	switch((char)brace)
// 	{
// 		case '(':
// 			switch(mCurrentContext){
// 				case DECLARATION:
// 					mCurrentContext = FUNCTION_PARAMETERS_BLOCK;
// 				case EXPRESSION:
// 					mCurrentContext = FUNCTION_PARAMETERS_BLOCK;
// 			}
// 			break;
// 		case ')':
// 			mCurrentContext = GLOBAL;
// 			break;
// 		case '{':
// 			mCurrentContext = FUNCTION_BODY;
// 			break;
// 		case '}':
// 			mCurrentContext = GLOBAL;
// 			break;
// 	};
}


void Parser::handleIdentifierDeclaration()
{
// 	LexerToken currentToken = mLexer->getToken();
// 	
// 	if(mSymbolTable.find(currentToken.value) == mSymbolTable.end())
// 	{
// 		IdentifierDeclaration *decl = new IdentifierDeclaration(currentToken.value);
// 		mExprList.push_back(decl);
// 		mSymbolTable[currentToken.value] = decl;
// 
// 	}
// 	
// 	while (currentToken.value != ";") {
// 		switch ((currentToken = mLexer->getToken()).type) {
// 			case SPECIAL_SYMBOL:
// 				string symbol = currentToken.value;
// 				if (symbol == "=") {
// 					mExprList.push_back(handleBinaryOp(mSymbolTable[currentToken.value], symbol));
// 				}
// 				break;
// 		}
// 	}
}

BaseExpression* Parser::handleBinaryOp(BaseExpression *lhs, string symbol)
{
	LexerToken currentToken = mLexer->getToken();
	BaseExpression *expr = NULL;

	switch(currentToken.type) {
		case CONST_NUMBER:
			expr = new IntegerValueExpression(atoi(currentToken.value.c_str()));
			break;
		case IDENTIFIER:
			expr = new UseVariableExpression(currentToken.value);
			break;
	}

	currentToken = mLexer->getToken();
	if (currentToken.type == BINARY_OP) {
		expr = handleBinaryOp(expr, currentToken.value);
	}
	
	if(symbol == "=") {
		return new AssignmentExpression(lhs, expr);
	}
	else if (symbol == "+") {
		return new AddExpression(lhs, expr);
	}
	else if (symbol == "-") {
		return new SubstractExpression(lhs, expr);
	}
	else if (symbol == "*") {
		return new MultiplyExpression(lhs, expr);
	}
	else if (symbol == "/") {
		return new DivideExpression(lhs, expr);
	}
	else {
		throw "unhandled sitation";
	}
}


}

