#ifndef DRAGONPARSER_H
#define DRAGONPARSER_H

#include "DragonLexer.h"
#include "Expressions.h"
#include "DragonTypes.h"

#include <map>
#include <vector>

using namespace std;
namespace Dragonc 
{

enum ParserContext
{
	GLOBAL,
	DECLARATION,
	EXPRESSION,
	R_EXPRESSION,
	FUNCTION_PARAMETERS_BLOCK,
	FUNCTION_BODY,
};

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
	map<std::string, BaseExpression*> mSymbolTable;
	map<std::string, int> mOperatorPrecedence;

	/* State */
	ParserContext mCurrentContext;
	DragonType mCurrentType;
	LexerToken mCurrentToken;

	void clearState()
	{
		mCurrentContext = GLOBAL;
		mCurrentType = TYPE_NONE;
		mCurrentToken.type = INVALID;
		mCurrentToken.value = "";
	}

};

}

#endif // DRAGONPARSER_H
