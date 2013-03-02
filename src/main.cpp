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
#include <vector>
#include <string>
using namespace llvm;
using namespace Dragonc;
using namespace std;

void print_usage(char *executable)
{
	std::cout << "Usage: " << executable << " <source file> " << std::endl;
}

int main(int argc, char *argv[]) {

	if (argc < 2) {
		print_usage(argv[0]);
		return EXIT_FAILURE;
	}
	
	llvm::LLVMContext &context = llvm::getGlobalContext();
	llvm::Module *module = new llvm::Module("asdf", context);
	llvm::IRBuilder<> builder(context);

	llvm::FunctionType *funcType = llvm::FunctionType::get(builder.getVoidTy(), false);
	llvm::Function *mainFunc = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "main", module);
	llvm::BasicBlock *entry = llvm::BasicBlock::Create(context, "entrypoint", mainFunc);
	builder.SetInsertPoint(entry);

	Lexer lexer(argv[1]);


	Parser p(&lexer);

	p.parse();


	p.emitCode(builder, *module);

	builder.CreateRetVoid();
	module->dump();

	delete module;

	return EXIT_SUCCESS;
}