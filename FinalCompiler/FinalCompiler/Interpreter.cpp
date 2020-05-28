#include "Interpreter.h"
#include <iostream>
#include <string>
using namespace std;


I_Statement::I_Statement(StatementType stin, string op1in, string  op2in, string op3in)
{
	st = stin;
	op1 = op1in;
	op2 = op2in;
	op3 = op3in;
}

StatementType I_Statement::getType() { return st; }
string I_Statement::getop1() { return op1; }
string I_Statement::getop2() { return op2; }
string I_Statement::getop3() { return op3; }



void I_Function::addStatement(I_Statement & statement)
{
	statements.push_back(statement);

}
I_Statement I_Function::getStatement(int i)
{
	return statements[i];
}
int I_Function::size()
{
	return statements.size();
}
string I_Function::getName()
{
	return name;
}
void I_Function::setName(string namein)
{
	name = namein;
}


I_Reg::I_Reg(bool isNumin, bool isStringin, bool isIntin, bool isBoolin)
{
	isNum = isNumin;
	if (isNum)//if reg is number
	{
		numValue = 0;
	}
		isString = isStringin;
		if (isString)//if reg is string
		{
			sValue = "";
		}
			isInt = isIntin;
			if (isInt)//if reg is int
			{
				intValue = 0;
			}
				isBool = isBoolin;
				if (isBool)//if reg is boolean
				{
					bValue = false;
				}
}


bool I_Reg::getIsNum()
{
	return isNum;
}

void I_Reg::setNumValue(double newValue)
{
	numValue = newValue;
}

double I_Reg::getNumValue()
{
	return numValue;
}
//***********************************
int I_Reg::getIntValue()
{
	return intValue;
}

void I_Reg::setIntValue(int newValue)
{
	intValue = newValue;
}

bool I_Reg::getIsInt()
{
	return isInt;
}
//**********************************
string I_Reg::getSValue()
{
	return sValue;
}

void I_Reg:: setSValue(string newS)
{
	sValue = newS;
}

bool I_Reg:: getIsString()
{
	return isString;
}
//**********************************
bool I_Reg::getbValue()
{
	return bValue;
}

void I_Reg::setbValue(bool newB)
{
	bValue = newB;
}

bool I_Reg::getIsBool()
{
	return isBool;
}

//The interpreter reads in the bytecode from the file on creation
Interpreter::Interpreter(string fname)
{
	ifstream istream(fname);

	I_Function currentFunction; //it might be a better idea to use pointers... less mistake prone.

	while (!istream.eof())
	{
		string statementtype, op1,op2,op3;

		istream >> statementtype;

		if (statementtype == "function") // if it is a function
		{
			//read in whatever operands come after it
			istream >> op1;

			
			I_Function func;

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
			I_Statement statement(ADD,op1,op2,op3);
			currentFunction.addStatement(statement);
			
		}
		else if (statementtype == "set") // set constants
		{
			istream >> op1 >> op2;
			I_Statement statement(SET, op1, op2, "*");
			currentFunction.addStatement(statement);
		}
		else if (statementtype == "setreg") // set reg to be reg
		{
			istream >> op1 >> op2;
			I_Statement statement(SETREG, op1, op2, "*");
			currentFunction.addStatement(statement);
		}
		else if (statementtype == "print") 
		{
			istream >> op1;
			I_Statement statement(PRINTREG, op1, "*", "*");
			currentFunction.addStatement(statement);
		}
		else if (statementtype == "functioncall")
		{
			istream >> op1;
			I_Statement statement(FUNCTIONCALL, op1, "*", "*");
			currentFunction.addStatement(statement);
		}
		else if (statementtype == "clear")
		{
			istream >> op1;
			I_Statement statement(CLEAR, op1, "*", "*");
			currentFunction.addStatement(statement);
		}
		else if (statementtype == "setstr")
		{
			istream >> op1 >> op2;
			I_Statement statement(SETSTR, op1, op2, "*");
			currentFunction.addStatement(statement);
		}
		else if (statementtype == "subtract")
		{
			istream >> op1 >> op2 >> op3;
			I_Statement statement(SUBTRACT, op1, op2, op3);
			currentFunction.addStatement(statement);

		}
		else if (statementtype == "multiply")
		{
			istream >> op1 >> op2 >> op3;
			I_Statement statement(MULTIPLY, op1, op2, op3);
			currentFunction.addStatement(statement);

		}
		else if (statementtype == "divide")
		{
			istream >> op1 >> op2 >> op3;
			I_Statement statement(DIVIDE, op1, op2, op3);
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


I_Reg * getRegister(unordered_map<string, I_Reg *> & registers, string name)//@@@@@@@@@@@ UNSURE HOW THIS WORKS 
{

	//if not present create and init to 0
	if (registers[name] == 0)
	{
		if (name[0] == 'n')
		{
			registers[name] = new I_Reg(true);
		}
		else
		{
			registers[name] = new I_Reg(false);
		}

		return registers[name];
	}
	else //otherwise return the found reg
	{
		return registers[name];
	}
}

void Interpreter::executeFunction(I_Function & currentFunction)
{
	unordered_map<string, I_Reg *> registers; // since this is only local, then each function has its own pool and can use the same names.

	//loops over each statement in "current function", executing that particular statement; each statement is implemented differently. For instance, print prints things, a function call calls a function, add adds two numbers, etc.
	for (int i = 0; i < currentFunction.size(); i++)
	{
		if (currentFunction.getStatement(i).getType() == PRINTREG)
		{
			I_Reg * reg = getRegister(registers,currentFunction.getStatement(i).getop1());

			if (reg->getIsNum())
			{
				cout << reg->getNumValue()<<"\n";
			}
			else
			{
				cout << reg->getIntValue() << "\n";
			}
		}
		if (currentFunction.getStatement(i).getType() == FUNCTIONCALL)
		{
			for (int j=0; j < functions.size(); j++)
			{
				if (currentFunction.getStatement(i).getop1() == functions[j].getName())
				{
					executeFunction(functions[j]);
				}
			}
		}
		if (currentFunction.getStatement(i).getType() == ADD)
		{
			I_Reg * reg1 = getRegister(registers, currentFunction.getStatement(i).getop1());
			I_Reg * reg2 = getRegister(registers, currentFunction.getStatement(i).getop2());
			I_Reg * reg3 = getRegister(registers, currentFunction.getStatement(i).getop3());

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
			I_Reg * reg1 = getRegister(registers, currentFunction.getStatement(i).getop1());
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
			I_Reg * reg1 = getRegister(registers, currentFunction.getStatement(i).getop1());
			I_Reg * reg2 = getRegister(registers, currentFunction.getStatement(i).getop2());

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
			I_Reg * reg1 = getRegister(registers, currentFunction.getStatement(i).getop1());
			if (reg1->getIsNum())
			{
				reg1->setNumValue(0);
			}
			if (!reg1->getIsNum())
			{
				reg1->setIntValue(0);
			}
		}

		/*if (currentFunction.getStatement(i).getType() == SETSTR)
		{
			I_Reg * reg1 = getRegister(registers, currentFunction.getStatement(i).getop1());
			ifstream in;
			string s;
			in >> s;
			char c;
			c = in.get();
			s = +c;
			reg1->setSValue(s);
		}*/
		if (currentFunction.getStatement(i).getType() == SUBTRACT)
		{
			I_Reg * reg1 = getRegister(registers, currentFunction.getStatement(i).getop1());
			I_Reg * reg2 = getRegister(registers, currentFunction.getStatement(i).getop2());
			I_Reg * reg3 = getRegister(registers, currentFunction.getStatement(i).getop3());

			if (reg1->getIsNum())
			{
				reg1->setNumValue(reg2->getNumValue() - reg3->getNumValue());
			}
			if (!reg1->getIsNum())
			{
				reg1->setIntValue(reg2->getIntValue() - reg3->getIntValue());
			}
		}

		if (currentFunction.getStatement(i).getType() == MULTIPLY)
		{
			I_Reg * reg1 = getRegister(registers, currentFunction.getStatement(i).getop1());
			I_Reg * reg2 = getRegister(registers, currentFunction.getStatement(i).getop2());
			I_Reg * reg3 = getRegister(registers, currentFunction.getStatement(i).getop3());

			if (reg1->getIsNum())
			{
				reg1->setNumValue(reg2->getNumValue() * reg3->getNumValue());
			}
			if (!reg1->getIsNum())
			{
				reg1->setIntValue(reg2->getIntValue() * reg3->getIntValue());
			}
		}
		if (currentFunction.getStatement(i).getType() == DIVIDE)
		{
			I_Reg * reg1 = getRegister(registers, currentFunction.getStatement(i).getop1());
			I_Reg * reg2 = getRegister(registers, currentFunction.getStatement(i).getop2());
			I_Reg * reg3 = getRegister(registers, currentFunction.getStatement(i).getop3());

			if (reg1->getIsNum())
			{
				reg1->setNumValue(reg2->getNumValue() / reg3->getNumValue());
			}
			if (!reg1->getIsNum())
			{
				reg1->setIntValue(reg2->getIntValue() / reg3->getIntValue());
			}
		}
	}

}