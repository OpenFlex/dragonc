#ifndef DRAGON_TYPES_H
#define DRAGON_TYPES_H

#include <llvm/DerivedTypes.h>
#include <llvm/IRBuilder.h>
#include <llvm/Module.h>
#include <llvm/Instruction.h>
#include <string>
#include <list>

namespace Dragonc
{
	
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

class VariableList
{
public:
    void push_back(DragonVariable& var)
    {
        mStdList.push_back(var);
    }

    inline int num_args()
    {
        return mStdList.size();
    }

private:
    std::list<DragonVariable> mStdList;
};


} // namespace Dragonc

#endif
