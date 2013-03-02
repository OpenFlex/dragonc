#ifndef DRAGONPARSER_H
#define DRAGONPARSER_H

#include "DragonLexer.h"
#include "Expressions.h"

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

enum DragonType
{
	TYPE_NONE,
	TYPE_VOID,
	TYPE_INTEGER,
	TYPE_DOUBLE,
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
	BaseExpression* handleDeclaration(DragonType type, string value);
	BaseExpression* handleIdentifier(const LexerToken& currentToken);
	BaseExpression* handleAssignment();
	BaseExpression* handleBinaryOp(BaseExpression *lhs, string symbol);

private:
	Lexer *mLexer;
	vector<BaseExpression*> mExprList;
	map<std::string, BaseExpression*> mSymbolTable;

	/* State */
	ParserContext mCurrentContext;
	DragonType mCurrentType;
	LexerToken mCurrentIdentifier;
	
	void clearState()
	{
		mCurrentContext = GLOBAL;
		mCurrentType = TYPE_NONE;
		mCurrentIdentifier.type = INVALID;
		mCurrentIdentifier.value = "";
	}
};

}

#endif // DRAGONPARSER_H
