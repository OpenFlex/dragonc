#ifndef DRAGON_SYMBOL_TABLE_H
#define DRAGON_SYMBOL_TABLE_H

#include "DragonContext.h"
#include "Expressions.h"
#include <string>
#include <map>
#include <stdio.h>

namespace Dragonc {


class SymbolTable
{
public:
	BaseExpression* const& operator [](const std::string& name);
	void addSymbol(string name, BaseExpression* e);

private:
	map<std::string, BaseExpression*> mGlobalTable;
	map<std::string, BaseExpression*> mLocalTable;
};

} // namespace Dragonc

#endif
