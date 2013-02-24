#include "DragonLexer.h"
#include <llvm/ADT/StringSwitch.h>

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

TokenType Lexer::getToken()
{
	string value;
	static char c = ' ';
	
	if(!mSourceStream->good() || c == EOF)
		return TOKEN_EOF;
	
	while(isspace(c)) {
		c =  mSourceStream->get();
	}
		
	
	if(isalpha(c)) {
		value += c;
		while(isalnum(c = mSourceStream->get())) {
			value += c;
		}
		
		
		TokenType type = StringSwitch<TokenType>(StringRef(value)).Cases("int", "double", TYPE).Default(INVALID);
		
		if(type == TYPE) {
			mCurrentTokenValue = value;		
			return type;
		} else {
			mCurrentTokenValue = value;
			if(c == '(')
				return FUNCTION_DECL;
			return IDENTIFIER;
		}
		
	} else if(isdigit(c)) {
		value += c;
		while(isdigit(c = mSourceStream->get())) {
			value += c;
		}
		mCurrentTokenValue = value;
		if(c != '.') {
			return INTEGER;
		}
		return INTEGER;
	} else {
		value += c;
		while(isspace(c = mSourceStream->get()));
		mCurrentTokenValue = value;
		return SPECIAL_SYMBOL;
	}
	return TOKEN_EOF;
}

string Lexer::getCurrentTokenValue()
{
	return mCurrentTokenValue;
}

}
