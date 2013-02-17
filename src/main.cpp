#include <stdlib.h>
#include "DragonLexer.h"
#include "DragonParser.h"
using namespace llvm;
using namespace Dragonc;
using namespace std;

void print_usage(char *executable) 
{
	std::cout << "Usage: " << executable << " <source file> " << std::endl;
}

int main(int argc, char *argv[]) {
	
	if(argc < 2) {
		print_usage(argv[0]);
		return EXIT_FAILURE;
	}
	Lexer lexer(argv[1]);
	
	
	while(lexer.getToken() != TOKEN_EOF) {
		std::cout << lexer.getCurrentTokenValue() << std::endl;
	}
	
	return EXIT_SUCCESS;
}
