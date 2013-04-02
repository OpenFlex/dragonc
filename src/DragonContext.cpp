#include "DragonContext.h"

#include <vector>

namespace Dragonc{
namespace DragonContext{

static std::vector<DragonContextType> global_context;

void push(DragonContextType context)
{
    global_context.push_back(context);
}

void pop()
{
    global_context.pop_back();
}

void clear()
{
    global_context.clear();
    global_context.push_back(GLOBAL);
}

DragonContextType get()
{
    if(!global_context.size())
    {
        DragonContext::clear();
    }

    return global_context.back();
}

}} // namespace Dragonc::DragonContext

