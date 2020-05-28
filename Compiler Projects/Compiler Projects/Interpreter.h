#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include <unordered_map>
#include <string>


//think of enum as creating named constants. the first thing, technically, starts at 0. so set is 1 and setreg is 2, etc.
enum StatementType {ADD, SET, SETREG, PRINTREG, FUNCTIONCALL, CLEAR};

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

	I_Reg(bool isNumin);

	bool getIsNum();

	void setIntValue(int newValue);

	void setNumValue(double newValue);
	int getIntValue();
	double getNumValue();
	

private:
	int intValue;
	double numValue;
	bool isNum;
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