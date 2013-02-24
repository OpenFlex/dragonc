#ifndef INITIALIZEEXPR_H
#define INITIALIZEEXPR_H
#include "DragonBaseExpression.h"
#include <string>

using namespace std;

namespace Dragonc {

class IdentifierDeclaration : public Dragonc::BaseExpression
{
public:
	IdentifierDeclaration(string& name)
	:BaseExpression(), mName(name) {};
	
    virtual Value *emitCode(IRBuilder<> &builder, Module &module);
    virtual Value *getValue() { return mValue; };
private:
	string mName;
	Value *mValue;
};

}

#endif // INITIALIZEEXPR_H
