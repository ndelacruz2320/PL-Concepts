#pragma once

#include <vector>
#include "Type.h"
#include "Scanner.h"
using namespace std;

class ASTNode
{
public:
	ASTNode();

	virtual void print(int indent, ostream & out) = 0;

	virtual Type typeCheck(TypeMap * map, bool & hadError) = 0;

	//virtual Register outputCode(ofstream & outputFile, VariableContext * vc) = 0;

	void setup(int lineNumberin);
	int getLineNumber();

private:
	int lineNumber;
};


class ASTProgram : public ASTNode
{
public:
	virtual void print(int indent, ostream & out);

	void addFunction(ASTNode * theNode);
	void setSizes(string it, string x, string y);
	Type typeCheck(TypeMap * map, bool & hadError);
private:
	vector<ASTNode *> functions;
	string  iterations;
	string  xsize;
	string  ysize;
};

class ASTFunction : public ASTNode
{
public:
	virtual void print(int indent, ostream & out);
	Type typeCheck(TypeMap * map, bool & hadError);
	void setFunctionName(string name);
	void setFunctionBody(ASTNode * body);
	void setX(ASTNode * node);
	void setY(ASTNode * node);

	string getFunctionName();

private:
	string functionName;
	ASTNode * functionBody = 0;
	ASTNode * returnX = 0;
	ASTNode * returnY = 0;
};

class ASTStatements : public ASTNode
{
public:
	virtual void print(int indent, ostream & out);
	Type typeCheck(TypeMap * map, bool & hadError);
	void addStatement(ASTNode * theNode);
private:
	vector<ASTNode *> statements;
};

class ASTBlockStatement : public ASTNode
{
public:
	virtual void print(int indent, ostream & out);
	Type typeCheck(TypeMap * map, bool & hadError);
	void setStatement(ASTNode * theNode);
private:
	ASTNode * statements;
};

class ASTFor : public ASTNode
{
public:
	virtual void print(int indent, ostream & out);
	Type typeCheck(TypeMap * map, bool & hadError);
	void setData(ASTNode * dec_in, ASTNode * cond_in, ASTNode * inc_in, ASTNode * statement_in);
private:
	ASTNode * dec, *cond, *inc, *statement;
};

class ASTIf : public ASTNode
{
public:
	virtual void print(int indent, ostream & out);
	Type typeCheck(TypeMap * map, bool & hadError);
	void setData(ASTNode * cond_in, ASTNode * statement_in);
private:
	ASTNode * cond, *statement;
};

class ASTDeclaration : public ASTNode
{
public:
	virtual void print(int indent, ostream & out);
	Type typeCheck(TypeMap * map, bool & hadError);
	void setData(string type_in, string name_in);
private:
	string type, name;
};

class ASTAssign : public ASTNode
{
public:
	virtual void print(int indent, ostream & out);
	Type typeCheck(TypeMap * map, bool & hadError);
	void setData(ASTNode * left_in, ASTNode * right_in);
private:
	ASTNode * left, *right;
};


class ASTBooleanExpr : public ASTNode
{
public:
	virtual void print(int indent, ostream & out);
	Type typeCheck(TypeMap * map, bool & hadError);
	void setData(ASTNode * left_in, ASTNode * right_in, string op);
private:
	ASTNode * left, *right;
	string op;
};


class ASTExpr : public ASTNode
{
public:
	virtual void print(int indent, ostream & out);
	Type typeCheck(TypeMap * map, bool & hadError);
	void addOp(char op);
	void addTerm(ASTNode * theTerm);
private:
	vector<ASTNode *> terms;
	vector<char> ops;
};

class ASTTerm : public ASTNode
{
public:
	virtual void print(int indent, ostream & out);
	Type typeCheck(TypeMap * map, bool & hadError);
	void addOp(char op);
	void addFactor(ASTNode * fact);
private:
	vector<ASTNode *> facts;
	vector<char> ops;
};

class ASTFactor : public ASTNode
{
public:
	virtual void print(int indent, ostream & out);
	Type typeCheck(TypeMap * map, bool & hadError);
	void setNode(ASTNode * theNode);
	void setParen(bool in);
private:
	ASTNode * node;
	bool paren = false;
};



class ASTElement : public ASTNode
{
public:
	virtual void print(int indent, ostream & out);
	Type typeCheck(TypeMap * map, bool & hadError);
	void setNode1(string theNode);
	void setNode2(string theNode);
	void setDot(bool in);

	string getLeft();
	string getRight();
private:
	string left;
	string right;
	bool isDot = false;
};

