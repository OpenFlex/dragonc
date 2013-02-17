#ifndef DRAGONPARSER_H
#define DRAGONPARSER_H

#include "DragonLexer.h"
#include "DragonBaseExpression.h"
#include <map>
using namespace std;
namespace Dragonc 
{

class Parser
{
public:
	Parser(Lexer *dragonLexer);
	BaseExpression *parse();
	

private:
	BaseExpression *handleTypeDecl();
	
	BaseExpression *parseFunctionPrototype(string returnValue, string name);
	
	
	
private:
	Lexer *mLexer;
	
};

}

#endif // DRAGONPARSER_H
