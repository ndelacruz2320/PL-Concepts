//#include "Scanner.h"
#//include "Parser.h"
#include "Interpreter.h"


//this code will be discussed in class during each part of the project


#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
	/*if (argc < 2)
	{
		cout << "Usage: <executable name> <filename>";
	}
	//this was for testing part II -> i commented some other code out in the constructor to test it.
	//Scanner scan(argv[1]);
	

	//Part III
	Parser theParser(argv[1]);

	bool haderror = false;
	ASTNode * root = theParser.parse(haderror);
	if (haderror)
	{
		cout << "Errors in program. Exiting...\n";
		cin.ignore();
		return 0;
	}

	root->print(0);

	//part IV
	root->typeCheck(0, haderror);

	if (haderror)
	{
		cout << "Errors in program. Exiting...\n";
		cin.ignore();
		return 0;
	}

	//part V
	string outfile = argv[1];
	outfile += ".out";

	ofstream output(outfile);

	
	root->outputCode(output,0);

	delete root;

	output.close();*/

	//Part I
	string outfile = argv[1];
	outfile += ".out";
	Interpreter theInterpreter(outfile);
	theInterpreter.execute();


	cin.ignore();

}


