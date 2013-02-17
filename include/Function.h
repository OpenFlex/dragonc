#ifndef FUNCTION_H
#define FUNCTION_H
#include "DragonBaseExpression.h"
#include <string>
#include <map>
#include <iostream>
using namespace std;

namespace Dragonc
{

class Function : public BaseExpression
{
public:
	Function(string name, string returnType, map<string, string> arguments);
	virtual ~Function() {}
	virtual Value *emitCode() {return NULL;} 
	virtual void print();

private:
	BaseExpression *mBody;
	map<string, string> mArguments;
	string mReturnType;	
	string mName;
	
};


}
#endif // FUNCTION_H
