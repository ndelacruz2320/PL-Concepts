//#include "Scanner.h"
//#include "Interpreter.h"
#include "Parser.h"
#include <fstream>

#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		cout << "Usage: <executable name> <filename>";
	}

	//Scanner scan(argv[1]);


	Parser p(argv[1]);

	bool haderror = false;
	ASTNode * prog = p.parse(haderror);
	if (!haderror)
	{
		cout << "printing out  to file\n";
		ofstream file("out.txt");

		prog->print(0, file);
		file.close();
		cout << "reading from file and printing out:\n\n";

		Parser p2("out.txt");
		ASTNode * prog2 = p2.parse(haderror);
		prog2->print(0, cout);



		prog->typeCheck(0, haderror);
	}




	/*string s = argv[1];
	Interpreter i(s+".out");
	i.printProgram();*/


		cin.ignore();
}
