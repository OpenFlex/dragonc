#include "Function.h"
using namespace std;
namespace Dragonc 
{

Function::Function(string name, string returnType, map<string, string> arguments)
{

	mName = name;
	mReturnType = returnType;
	mArguments = arguments;
}

void Function::print()
{
	cout << mName << " " << mReturnType << endl; 
	map<string, string>::iterator it;
	for (it = mArguments.begin(); it != mArguments.end(); ++it) {
			cout << it->first << it->second << endl;
	}
}


}
