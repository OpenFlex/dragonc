#include "DragonTypes.h"

#include <llvm/ADT/StringSwitch.h>

namespace Dragonc{

llvm::Type* toLlvmType(llvm::IRBuilder<>& builder, DragonType type)
{
	switch(type)
	{
		case TYPE_INTEGER:
			return builder.getInt32Ty();
			break;
		case TYPE_VOID:
			return builder.getVoidTy();
			break;
		case TYPE_FLOAT:
			return builder.getFloatTy();
			break;
		case TYPE_DOUBLE:
			return builder.getDoubleTy();
			break;
		case TYPE_CHAR:
			return builder.getInt8Ty();
			break;
		default:
			return 0;
	}
}

DragonType toDragonType(std::string typeName)
{
	DragonType type = llvm::StringSwitch<DragonType>(llvm::StringRef(typeName))
	.Case("int", TYPE_INTEGER)
	.Case("char", TYPE_CHAR)
	.Case("double", TYPE_DOUBLE)
	.Case("float", TYPE_FLOAT)
	.Case("void", TYPE_VOID)
	.Default(TYPE_NONE);

	return type;
}

} // namespace Dragonc

