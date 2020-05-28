#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include <unordered_map>
#include <string>


//think of enum as creating named constants. the first thing, technically, starts at 0. so set is 1 and setreg is 2, etc.
enum StatementType {ADD, SET, SETREG, PRINTREG, FUNCTIONCALL, CLEAR, SETSTR, OUTPUT, SUBTRACT, MULTIPLY, DIVIDE, LESS,
	GREATER, EQUALSBOOL, LESSE, GREATERE, NOT, INPUT, JUMP, JUMPIFN, LABEL, RETURN};

//a container for each statement of bytecode
class I_Statement
{
public:
	I_Statement(StatementType stin, string op1in, string  op2in, string op3in);

	StatementType getType();
	string getop1();
	string getop2();
	string getop3();

private:
	StatementType st;
	string op1;
	string op2;
	string op3;
};

//a container for each function of the bytecode. Each function contains many statements
class I_Function
{
public:
	void addStatement(I_Statement & statement);
	I_Statement getStatement(int i);
	int size(); //size of statements
	string getName();
	void setName(string namein);

private:
	vector<I_Statement> statements;
	string name;
};

//a class for the registers used in the bytecode
class I_Reg
{


public:

	I_Reg(bool isNumin, bool isStringin, bool isIntin, bool isBoolin);

	bool getIsNum();
	double getNumValue();
	void setNumValue(double newValue);

	bool getIsString();
	string getSValue();
	void setSValue(string newValue);

	bool getIsInt();
	int getIntValue();
	void setIntValue(int newValue);

	bool getIsBool();
	bool getbValue();
	void setbValue(bool newValue);

	

private:
	
	bool isString;
	bool isBool;
	bool isInt;
	bool isNum;
	int intValue;
	double numValue;
	string sValue;
	bool bValue;
	
};

class Interpreter
{
public:
	Interpreter(string fname); //setup and read in file
	void execute(); // run program
private:
	vector<I_Function> functions; //this would be better as a map, but i want you to see why.
	void executeFunction(I_Function & func);
};