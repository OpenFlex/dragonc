#include "DragonLexer.h"
#include <llvm/ADT/StringSwitch.h>

#include <stdio.h>
#include <fstream>

using namespace llvm;
using namespace std;
namespace Dragonc 
{


Lexer::Lexer(string sourceFile)
{
	mSourceStream = new ifstream(sourceFile.c_str());
}

Lexer::~Lexer()
{
	delete mSourceStream;
}

LexerToken Lexer::getToken()
{
	LexerToken lexerToken;
	static char c = mSourceStream->get();

	while(isspace(c)) {
		c =  mSourceStream->get();
	}
	
	if(!mSourceStream->good() || c == EOF) {
		lexerToken.type = TOKEN_EOF;
		return lexerToken;
	}

	/* Values and types*/
	if(isalpha(c)) {		
		lexerToken.value += c;
		while(isalnum(c = mSourceStream->get()) || c == '_') {
			lexerToken.value += c;
		}

		TokenType type = StringSwitch<TokenType>(StringRef(lexerToken.value))
		.Cases("return", "printf", KEYWORD)
		.Cases("int", "double", TYPE)
		.Default(INVALID);

		if(type == TYPE) {
			lexerToken.type = type;
		} else if (type == KEYWORD) {
			lexerToken.type = type;
		}else {
			lexerToken.type = IDENTIFIER;
		}
	}
	/* Numbers */
	else if(isdigit(c)) {
		lexerToken.value += c;
		lexerToken.type = CONST_NUMBER;
		while(isdigit(c = mSourceStream->get())) {
			lexerToken.value += c;
		}
	}
	/* Special symbols */
	else {
		/* Braces */
		if(c == '{' || c == '}' || c == '(' || c == ')') {
			lexerToken.value= c;
			while(isspace(c = mSourceStream->get()));
			lexerToken.type = BRACE;
		}
		/* End expression symbols */
		else if(c == ';') {
			lexerToken.value= c;
			while(isspace(c = mSourceStream->get()));
			lexerToken.type = EXPRESSION_END;
		}
		/* End expression symbols */
		else if(c == '+' || c == '-' || c == '*' || c == '/' || c == '=') {

			// Single line comments
			if(c == '/') 
			{
				c = mSourceStream->get();
				if(c == '/')
				{
					while(c != '\n' && c != '\r'){
						c = mSourceStream->get();
					}
				}
				else
				{
					mSourceStream->putback(c);
					c = '/';
				}
			
			} else if(c == '+' || c == '-') { // Increment/Decrement unary operation
				char next = mSourceStream->get();
				if(c == '+' && next == '+') {
					lexerToken.value = "++";
					lexerToken.type = INCREMENT;
					// Eat next +
					c = mSourceStream->get();
					return lexerToken;
				} else if( c == '-' && next == '-') {
					lexerToken.value = "--";
					lexerToken.type = DECREMENT;
					// Eat next -
					c = mSourceStream->get();
					return lexerToken;
				} else {
					mSourceStream->putback(next);
				}
				
			}
			lexerToken.value = c;
			while(isspace(c = mSourceStream->get()));
			lexerToken.type = BINARY_OP;
		}
// 		/* Assignment */
// 		else if(c == '=') {
// 			lexerToken.value= c;
// 			while(isspace(c = mSourceStream->get()));
// 			lexerToken.type = ASSIGNMENT_OP;
// 		}
		/* Everything else */
		else {
			lexerToken.value += c;
			while(isspace(c = mSourceStream->get()));
			lexerToken.type = SPECIAL_SYMBOL;
		}
		
	}

	
	return lexerToken;
}

// string Lexer::getCurrentTokenValue()
// {
// 	return mCurrentTokenValue;
// }

}
