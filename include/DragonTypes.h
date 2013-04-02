#ifndef DRAGON_TYPES_H
#define DRAGON_TYPES_H

#include <llvm/DerivedTypes.h>
#include <llvm/IRBuilder.h>
#include <llvm/Module.h>
#include <llvm/Instruction.h>
#include <string>
#include <vector>

namespace Dragonc {
	
enum DragonType
{
	TYPE_NONE,
	TYPE_VOID,
	TYPE_INTEGER,
	TYPE_FLOAT,
	TYPE_CHAR,
	TYPE_DOUBLE,
};

llvm::Type* toLlvmType(llvm::IRBuilder<>& builder, DragonType type);
DragonType toDragonType(std::string typeName);

struct DragonVariable
{
    DragonType type;
    std::string name;
};

typedef std::vector<DragonVariable> VariableList;
typedef std::vector<DragonVariable>::iterator VariableIterator;

} // namespace Dragonc

#endif
