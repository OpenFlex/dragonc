#include "DragonSymbolTable.h"

#include <llvm/ADT/StringSwitch.h>

namespace Dragonc{

BaseExpression * const &SymbolTable::operator [](const string &name)
{
	BaseExpression* e;
	if((e = mLocalTable[name])) {
		return e;
	} else if((e = mGlobalTable[name])) {
		return e;
	} else {
		printf("variable %s not declared within this context", name.c_str());exit(0);
	}
}

void SymbolTable::addSymbol(string name, BaseExpression *e)
{
	switch (DragonContext::get())
	{
	case GLOBAL:
		mGlobalTable[name] = e;
		break;
	case FUNCTION_BODY:
		mLocalTable[name] = e;
		break;
	}
}



} // namespace Dragonc

