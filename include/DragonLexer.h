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
	IDENTIFIER,
	INTEGER,
	DOUBLE,
	BIN_OP,
	TOKEN_EOF,
	TYPE, 
	FUNCTION_DECL,
	SPECIAL_SYMBOL
};


class Lexer
{
public:
	Lexer(string sourceFile);
	virtual ~Lexer();
	
	TokenType getToken();
	
	string getCurrentTokenValue();
	
private:
	ifstream *mSourceStream;
	string mCurrentTokenValue;
	
};

}

#endif // DRAGONLEXER_H
