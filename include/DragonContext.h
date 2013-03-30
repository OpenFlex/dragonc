#ifndef DRAGON_CONTEXT_H
#define DRAGON_CONTEXT_H

#include <llvm/DerivedTypes.h>
#include <llvm/IRBuilder.h>
#include <llvm/Module.h>
#include <llvm/Instruction.h>
#include <string>
#include <vector>

namespace Dragonc{

enum DragonContextType
{
    GLOBAL,
    FUNCTION_BODY,
};

namespace DragonContext{

void push(DragonContextType context);
void pop();
void clear();
DragonContextType get();

}} // namespace Dragonc::DragonContext

#endif
