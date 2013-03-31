#ifndef DRAGONPARSER_H
#define DRAGONPARSER_H

#include "DragonLexer.h"
#include "Expressions.h"
#include "DragonTypes.h"
#include "DragonSymbolTable.h"

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
	BaseExpression* handleBrace(char value);
	BaseExpression* handleType(string value);
	BaseExpression* handleKeyword(string keyword);
	BaseExpression* handleDeclaration(DragonType type, string value);
	BaseExpression* handleIdentifier(const LexerToken& currentToken);
	BaseExpression* handleAssignment();
	BaseExpression* handleBinaryOp(BaseExpression *lhs, int precedence = 0);
	BaseExpression* handleFunctionDeclaration(DragonType type, string name);
	BaseExpression* handleOperand();

private:
	Lexer *mLexer;
	vector<BaseExpression*> mExprList;
	map<std::string, int> mOperatorPrecedence;
	LexerToken mCurrentToken;

	


};

}

#endif // DRAGONPARSER_H
