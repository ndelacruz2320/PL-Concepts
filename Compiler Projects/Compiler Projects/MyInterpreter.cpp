#include "MyInterpreter.h"
#include <iostream>
#include <string>
using namespace std;


In_Statement::In_Statement(StatementType stin, string op1in, string  op2in, string op3in)
{
	st = stin;
	op1 = op1in;
	op2 = op2in;
	op3 = op3in;
}
//********************************************
//Statement Fuctions
StatementType In_Statement::getType() { return st; }
string In_Statement::getop1() { return op1; }
string In_Statement::getop2() { return op2; }
string In_Statement::getop3() { return op3; }


void In_Function::addStatement(In_Statement & statement)//adds statements to vector
{
	statements.push_back(statement);
}

In_Statement In_Function::getStatement(int i)//gets the statement at index i
{
	return statements[i];
}

int In_Function::size()//returns the size of the statements vector
{
	return statements.size();
}

string In_Function::getName()//returns name of fuction in statements vector
{
	return name;
}

void In_Function::setName(string namein)//sets the name of a function
{
	name = namein;
}
//********************************************
//Register Functions
In_Reg::In_Reg(bool isNumin)//checks if register has a number or an int
{
	isNum = isNumin;
	if (isNum)
		numValue = 0;
	else
		intValue = 0;
}

In_Reg::In_Reg(bool isStringin)
{
	isString = isStringin;
	if (isString) 
	{
		isString = "";
	}
	else
	{

	}

}

bool In_Reg::getIsNum()//checks if a register is a number
{
	return isNum;
}

void In_Reg::setIntValue(int newValue)//sets the int register to a new int value
{
	intValue = newValue;
}

void In_Reg::setNumValue(double newValue)
{
	numValue = newValue;
}

int In_Reg::getIntValue()
{
	return intValue;
}

double In_Reg::getNumValue()
{
	return numValue;
}
//********************************************
//Interpreter reading in fuctions and operands
Interpreter::Interpreter(string fname)
{
	ifstream istream(fname);

	In_Function currentFunction; 

	while (!istream.eof())
	{
		string statementtype, op1, op2, op3;

		istream >> statementtype;

		if (statementtype == "function") // if it is a function
		{
			//read in whatever operands come after it
			istream >> op1;


			In_Function func;

			if (currentFunction.size() > 0)
			{
				functions.push_back(currentFunction); // add complete functions
			}
			currentFunction = func;
			currentFunction.setName(op1);

		}
		else if (statementtype == "add")
		{
			istream >> op1 >> op2 >> op3;
			In_Statement statement(ADD, op1, op2, op3);
			currentFunction.addStatement(statement);

		}
		else if (statementtype == "set") // set constants
		{
			istream >> op1 >> op2;
			In_Statement statement(SET, op1, op2, "*");
			currentFunction.addStatement(statement);
		}
		else if (statementtype == "setreg") // set reg to be reg
		{
			istream >> op1 >> op2;
			In_Statement statement(SETREG, op1, op2, "*");
			currentFunction.addStatement(statement);
		}
		else if (statementtype == "print")
		{
			istream >> op1;
			In_Statement statement(PRINTREG, op1, "*", "*");
			currentFunction.addStatement(statement);
		}
		else if (statementtype == "functioncall")
		{
			istream >> op1;
			In_Statement statement(FUNCTIONCALL, op1, "*", "*");
			currentFunction.addStatement(statement);
		}
		else if (statementtype == "clear")
		{
			istream >> op1;
			In_Statement statement(CLEAR, op1, "*", "*");
			currentFunction.addStatement(statement);
		}
		else if (statementtype == "setstr")
		{
			istream >> op1 >> op2;
			In_Statement statement(SETSTR, op1, op2, "*");
			currentFunction.addStatement(statement);
		}

	}
	if (currentFunction.size() > 0)
	{
		functions.push_back(currentFunction);
	} //add last function
}

void Interpreter::execute()
{
	//A map here is O(1); a vector is O(N) here.
	for (int i = 0; i < functions.size(); i++)
	{
		if (functions[i].getName() == "main")
		{
			executeFunction(functions[i]);

		}
	}
}

In_Reg * getRegister(unordered_map<string, In_Reg *> & registers, string name)
{

	//if not present create and init to 0
	if (registers[name] == 0)
	{
		if (name[0] == 'n')
		{
			registers[name] = new In_Reg(true);
		}
		else
		{
			registers[name] = new In_Reg(false);
		}

		return registers[name];
	}
	else //otherwise return the found reg
	{
		return registers[name];
	}
}
//********************************
//Fuctionalities of Functions
void Interpreter::executeFunction(In_Function & currentFunction)
{
	unordered_map<string, In_Reg *> registers; // since this is only local, then each function has its own pool and can use the same names.

											  //loops over each statement in "current function", executing that particular statement; each statement is implemented differently. For instance, print prints things, a function call calls a function, add adds two numbers, etc.
	for (int i = 0; i < currentFunction.size(); i++)
	{
		if (currentFunction.getStatement(i).getType() == PRINTREG)
		{
			In_Reg * reg = getRegister(registers, currentFunction.getStatement(i).getop1());

			if (reg->getIsNum())
			{
				cout << reg->getNumValue() << "\n";
			}
			else
			{
				cout << reg->getIntValue() << "\n";
			}
		}
		if (currentFunction.getStatement(i).getType() == FUNCTIONCALL)
		{
			for (int j = 0; j < functions.size(); j++)
			{
				if (currentFunction.getStatement(i).getop1() == functions[j].getName())
				{
					executeFunction(functions[j]);
				}
			}
		}
		if (currentFunction.getStatement(i).getType() == ADD)
		{
			In_Reg * reg1 = getRegister(registers, currentFunction.getStatement(i).getop1());
			In_Reg * reg2 = getRegister(registers, currentFunction.getStatement(i).getop2());
			In_Reg * reg3 = getRegister(registers, currentFunction.getStatement(i).getop3());

			if (reg1->getIsNum())
			{
				reg1->setNumValue(reg2->getNumValue() + reg3->getNumValue());
			}
			if (!reg1->getIsNum())
			{
				reg1->setIntValue(reg2->getIntValue() + reg3->getIntValue());
			}
		}
		if (currentFunction.getStatement(i).getType() == SET)
		{
			In_Reg * reg1 = getRegister(registers, currentFunction.getStatement(i).getop1());
			if (reg1->getIsNum())
			{
				reg1->setNumValue(stod(currentFunction.getStatement(i).getop2()));
			}
			if (!reg1->getIsNum())
			{
				reg1->setIntValue(stoi(currentFunction.getStatement(i).getop2()));
			}
		}
		if (currentFunction.getStatement(i).getType() == SETREG)
		{
			In_Reg * reg1 = getRegister(registers, currentFunction.getStatement(i).getop1());
			In_Reg * reg2 = getRegister(registers, currentFunction.getStatement(i).getop2());

			if (reg1->getIsNum())
			{
				reg1->setNumValue(reg2->getNumValue());
			}
			if (!reg1->getIsNum())
			{
				reg1->setIntValue(reg2->getIntValue());
			}
		}
		if (currentFunction.getStatement(i).getType() == CLEAR)
		{
			In_Reg * reg1 = getRegister(registers, currentFunction.getStatement(i).getop1());
			if (reg1->getIsNum())
			{
				reg1->setNumValue(0);
			}
			if (!reg1->getIsNum())
			{
				reg1->setIntValue(0);
			}
		}

		if (currentFunction.getStatement(i).getType() == SETSTR)
		{
			ifstream in;
			string s;
			in >> s;
			char c;
			c = in.get();
			s = +c;
		}
	}

}