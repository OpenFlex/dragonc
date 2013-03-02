#include "DragonParser.h"
#include "Expressions.h"

#include <llvm/ADT/StringSwitch.h>

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
	LexerToken currentToken;
	
	do {
		currentToken = mLexer->getToken();

		std::cout << (char)currentToken.type << " " << currentToken.value << '\n';
		
		switch (currentToken.type) {
			case TYPE:
				if(BaseExpression* expr = handleType(currentToken.value)) {
					mExprList.push_back(expr);
				}
				break;
			case IDENTIFIER:
				handleIdentifier(currentToken);
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
				
				break;
			default:
				break;
		}
	} while (currentToken.type != TOKEN_EOF);
}

BaseExpression* Parser::handleType(string type_name)
{
	DragonType type = StringSwitch<DragonType>(StringRef(type_name))
	.Case("int", TYPE_INTEGER)
	.Case("double", TYPE_DOUBLE);
	
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
			mSymbolTable[name] = expr;
			expr = new AssignmentExpression(expr, new IntegerValueExpr(0));
			break;
		case BINARY_OP:
			expr = new IdentifierDeclaration(name);
			mSymbolTable[name] = expr;
			expr = handleBinaryOp(expr, nextToken.value);
			break;
		case BRACE:
			// function
		default:
			printf("Unexpected %s, expected ';', '=' or '('", name.c_str());exit(0);
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
			expr = new VariableExpression(mSymbolTable[identifier.value]);
			break;
		case BINARY_OP:
			expr = handleBinaryOp(new VariableExpression(mSymbolTable[identifier.value]), nextToken.value);
			break;
		case BRACE:
			break;
		default:
			printf("Unexpected %s, expected ';', '=' or '('", identifier.value.c_str());exit(0);
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
			expr = new IntegerValueExpr(atoi(currentToken.value.c_str()));
			break;
		case IDENTIFIER:
			expr = new VariableExpression(mSymbolTable[currentToken.value]);
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

