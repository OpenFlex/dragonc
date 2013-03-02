#ifndef DRAGONLEXER_H
#define DRAGONLEXER_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;
namespace Dragonc 
{


enum TokenType
{
	INVALID = -1,
	KEYWORD = 'k',
	EXPRESSION_END = 'x',
	TYPE = 't',
	IDENTIFIER = 'i',
	CONST_NUMBER = 'n',
	ASSIGNMENT_OP = 'a',
	BINARY_OP = 'b',
	BRACE = 'r',
	TOKEN_EOF = 'e',
	FUNCTION_DECL = 'f',
	SPECIAL_SYMBOL = 's',
};


struct LexerToken
{
	TokenType type;
	string value;
};

class Lexer
{
public:
	Lexer(string sourceFile);
	virtual ~Lexer();
	
	LexerToken getToken();
	
// 	string getCurrentTokenValue();
	
private:
	ifstream *mSourceStream;
	string mCurrentTokenValue;
	
};

}

#endif // DRAGONLEXER_H
