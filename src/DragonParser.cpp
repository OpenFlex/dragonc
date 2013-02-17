#include "DragonParser.h"
#include "Function.h"
#include <iostream>
using namespace std;
namespace Dragonc
{

Parser::Parser(Lexer *dragonLexer)
{
	mLexer = dragonLexer;
}

BaseExpression *Parser::parse()
{
	switch (mLexer->getToken()) {
		case TYPE:
			return handleTypeDecl();
			break;
		default:
			return NULL;
			
	}
	return NULL;
}

BaseExpression *Parser::handleTypeDecl()
{
	BaseExpression *expr = NULL;
	
	string value = mLexer->getCurrentTokenValue();
	cout << value << endl;
	
	string identifierName;
	bool valid = true;
	while (valid) {
		switch (mLexer->getToken()) {
			case IDENTIFIER:
				identifierName = mLexer->getCurrentTokenValue();
				cout << identifierName << endl;
				break;
			case FUNCTION_DECL:
				identifierName = mLexer->getCurrentTokenValue();
				cout << identifierName << endl;
				return parseFunctionPrototype(value, identifierName);
				break;
		}
	}
	return expr;
}

BaseExpression *Parser::parseFunctionPrototype(string returnValue, string name)
{
	map<string, string> arguments;
	bool finishedParsing = false;
	bool error = false;
	string typeName;
	BaseExpression *functionBody;
	while(!finishedParsing) {
		switch (mLexer->getToken()) {
			case TYPE:
				typeName = mLexer->getCurrentTokenValue();
				break;
			case IDENTIFIER:
				arguments[typeName] = mLexer->getCurrentTokenValue();
				break;
			case SPECIAL_SYMBOL:
				string symbol = mLexer->getCurrentTokenValue();
				if(symbol == ",") {
					continue;
				} else if(symbol == ")") {
					continue;
				} else if(symbol == "{") {
					functionBody = NULL;	
				} else if(symbol == "}") {
					finishedParsing = true;
				} else {
					finishedParsing = true;
					error = true;
				}
				break;				
			
		}
	}
	
	
	return new Dragonc::Function(name, returnValue, arguments); 
}




}
