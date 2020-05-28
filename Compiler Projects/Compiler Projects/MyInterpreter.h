#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

enum StatementType { ADD, SET, SETREG, PRINTREG, FUNCTIONCALL, CLEAR, SETSTR, OUTPUT, FUNCTIONCALL,	SUBTRACT, MULTIPLY, DIVIDE, LESS,
GREATER, EQUALSBOOL, LESSE, GREATERE, NOT, INPUT, JUMP, JUMPIFN, LABEL, RETURN};

class In_Statement
{
public:
	In_Statement(StatementType stin, string op1in, string  op2in, string op3in);

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


class In_Function
{

public:

	void addStatement(In_Statement & statement);
	In_Statement getStatement(int i);
	int size();
	string getName();
	void setName(string nName);

private:
	vector<In_Statement> statements;
	string name;


};

class In_Reg
{
public:

	In_Reg(bool isNumin);

	bool getIsNum();

	void setIntValue(int newValue);

	void setNumValue(double newValue);
	int getIntValue();
	double getNumValue();


private:
	int intValue;
	bool isString;
	double numValue;
	bool isNum;
};

class Interpreter
{
public:
	Interpreter(string fname); //setup and read in file
	void execute(); // run program
private:
	vector<In_Function> functions; //vector of functions
	void executeFunction(In_Function & func);
};
