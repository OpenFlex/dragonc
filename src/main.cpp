#include <stdlib.h>
#include "DragonLexer.h"
#include "DragonParser.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/LLVMContext.h"
#include "llvm/Module.h"
#include "llvm/Function.h"
#include "llvm/BasicBlock.h"
#include "llvm/IRBuilder.h"
#include "llvm/PassManager.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Support/TargetSelect.h>
#include "llvm/ExecutionEngine/JIT.h"
#include <vector>
#include <string>
using namespace llvm;
using namespace Dragonc;
using namespace std;

void print_usage(char *executable)
{
	std::cout << "Usage: " << executable << " <source file> " << std::endl;
}

static llvm::Function*
printf_prototype(llvm::LLVMContext& ctx, llvm::Module *mod)
{
	std::vector<llvm::Type*> printf_arg_types;
	printf_arg_types.push_back(llvm::Type::getInt8PtrTy(ctx));

	llvm::FunctionType* printf_type =
	llvm::FunctionType::get(
		llvm::Type::getInt32Ty(ctx), printf_arg_types, true);

	llvm::Function *func = llvm::Function::Create(
		printf_type, llvm::Function::ExternalLinkage,
		llvm::Twine("printf"),
								    mod
	);
	func->setCallingConv(llvm::CallingConv::C);
	return func;
}

int main(int argc, char *argv[]) {

	llvm::InitializeNativeTarget();
	
	if (argc < 2) {
		print_usage(argv[0]);
		return EXIT_FAILURE;
	}
	llvm::LLVMContext &context = llvm::getGlobalContext();
	llvm::Module *module = new llvm::Module("asdf", context);
	llvm::IRBuilder<> builder(context);

	llvm::Function *printf_func = printf_prototype(context, module);

	llvm::FunctionType *funcType = llvm::FunctionType::get(builder.getVoidTy(), false);
	llvm::Function *mainFunc = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "main", module);
	llvm::BasicBlock *entry = llvm::BasicBlock::Create(context, "entrypoint", mainFunc);
	builder.SetInsertPoint(entry);

	Lexer lexer(argv[1]);


	Parser p(&lexer);

	p.parse();


	p.emitCode(builder, *module);

	builder.CreateRet(ConstantInt::get(getGlobalContext(), APInt(32, 0)));
	module->dump();

	llvm::ExecutionEngine *engine = ExecutionEngine::create(module);

	if(engine) {
		printf("######### BEGIN \"%s\" OUTPUT #########\n", argv[1]);
		engine->runFunction(mainFunc, std::vector<llvm::GenericValue>());

		printf("\n######### END OUTPUT #########\n");
	} else {
		printf("Failed to initialize the execution engine");
	}
	
	delete module;

	return EXIT_SUCCESS;
}
