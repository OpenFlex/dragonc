#ifndef DRAGONPARSER_H
#define DRAGONPARSER_H

#include "DragonLexer.h"
#include "DragonBaseExpression.h"
#include "IdentifierDeclaration.h"
#include <map>
#include <vector>

using namespace std;
namespace Dragonc 
{

class Parser
{
public:
	Parser(Lexer *dragonLexer);
	void parse();
	void emitCode(IRBuilder<> &builder, Module &module);
	virtual ~Parser();
	BaseExpression* getIdent(string name);
	

private:
	void handleIdentifierDeclaration();
    BaseExpression* handleBinaryOp(BaseExpression *lhs, string symbol);
	
	
	
private:
	Lexer *mLexer;
	vector<BaseExpression*> mExprList;
	map<std::string, BaseExpression*> mSymbolTable; 
   
	
};

}

#endif // DRAGONPARSER_H
