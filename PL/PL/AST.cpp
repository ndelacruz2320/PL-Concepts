#include "AST.h"
#include "Type.h"

#include <iostream>
#include <string>
using namespace std;

string indentspace = "   ";

ASTNode::ASTNode()
{

}

void ASTNode::setup(int lineNumberin)
{
	lineNumber = lineNumberin;
}

int ASTNode::getLineNumber()
{
	return lineNumber;
}

void ASTProgram::addFunction(ASTNode * inNode)
{
	functions.push_back(inNode);
}

void ASTProgram::setSizes(string it, string x, string y)
{
	iterations = it;
	xsize = x;
	ysize = y;
}

void ASTProgram::print(int indent, ostream & out)
{
	out << iterations;
	out << " ";
	out << xsize;
	out << " ";
	out << ysize;
	out << "\n";

	for (unsigned int i = 0; i < functions.size(); i++)
	{
		functions[i]->print(0, out);
	}
}

string ASTFunction::getFunctionName()
{
	return functionName;
}

void ASTFunction::setFunctionName(string name)
{
	functionName = name;
}
void ASTFunction::setFunctionBody(ASTNode * body)
{
	functionBody = body;
}
void ASTFunction::setX(ASTNode * node)
{
	returnX = node;
}
void ASTFunction::setY(ASTNode * node)
{
	returnY = node;
}

void ASTFunction::print(int indent, ostream & out)
{
	out << functionName;
	out << "()\n-{\n";
	if (functionBody != 0)
	{
		functionBody->print(1, out);
	}
	out << "" << indentspace << "return ";
	returnX->print(0, out);
	out << ",";
	returnY->print(0, out);
	out << ";\n";
	out << "}-\n";
}



void ASTExpr::addOp(char op)
{
	ops.push_back(op);
}
void ASTExpr::addTerm(ASTNode * theTerm)
{
	terms.push_back(theTerm);
}

void ASTExpr::print(int indent, ostream & out)
{
	if (terms.size() > 1)
	{
		for (unsigned int i = 0; i < terms.size(); i++)
		{
			terms[i]->print(indent, out);
			if (terms.size() - 1 != i)
				out << " " << ops[i] << " ";
		}
	}
	else
	{
		terms[0]->print(indent, out);
	}
}

void ASTTerm::addOp(char op)
{
	ops.push_back(op);
}
void ASTTerm::addFactor(ASTNode * fact)
{
	facts.push_back(fact);
}

void ASTTerm::print(int indent, ostream & out)
{
	if (facts.size() > 1)
	{
		for (unsigned int i = 0; i < facts.size(); i++)
		{
			facts[i]->print(indent, out);
			if (facts.size() - 1 != i)
				out << " " << ops[i] << " ";
		}
	}
	else
	{
		facts[0]->print(indent, out);
	}
}

void ASTFactor::print(int indent, ostream & out)
{
	if (paren)
	{
		out << "(";
		node->print(indent, out);
		out << ")";
	}
	else
	{
		node->print(indent, out);
	}
}

void ASTFactor::setNode(ASTNode * theNode)
{
	node = theNode;
}
void ASTFactor::setParen(bool in)
{
	paren = in;
}



void ASTElement::setNode1(string theNode)
{
	left = theNode;
}

void ASTElement::setNode2(string theNode)
{
	right = theNode;
}

void ASTElement::setDot(bool in)
{
	isDot = in;
}

void ASTElement::print(int indent, ostream & out)
{
	if (!isDot)
	{
		out << left;
	}
	else
	{
		out << left;
		out << ".";
		out << right;
	}
}

string ASTElement::getLeft()
{
	return left;
}
string ASTElement::getRight()
{
	return right;
}


void ASTStatements::print(int indent, ostream & out)
{
	for (unsigned int i = 0; i < statements.size(); i++)
	{
		statements[i]->print(indent, out);
	}
}

void ASTStatements::addStatement(ASTNode * theNode)
{
	statements.push_back(theNode);
}




void ASTBlockStatement::print(int indent, ostream & out)
{
	for (int i = 0; i < indent; i++)
	{
		out << indentspace;
	}
	out << "-{\n";
	statements->print(indent + 1, out);
	for (int i = 0; i < indent; i++)
	{
		out << indentspace;
	}
	out << "}-\n";
}
void ASTBlockStatement::setStatement(ASTNode * theNode)
{
	statements = theNode;
}

void ASTFor::print(int indent, ostream & out)
{
	for (int i = 0; i < indent; i++)
	{
		out << indentspace;
	}
	out << "for\n";
	dec->print(indent + 1, out);
	for (int i = 0; i < indent + 1; i++)
	{
		out << indentspace;
	}
	cond->print(indent + 1, out);
	out << "\n";
	inc->print(indent + 1, out);
	statement->print(indent + 2, out);
}

void ASTFor::setData(ASTNode * dec_in, ASTNode * cond_in, ASTNode * inc_in, ASTNode * statement_in)
{
	dec = dec_in;
	cond = cond_in;
	inc = inc_in;
	statement = statement_in;
}

void ASTIf::print(int indent, ostream & out)
{
	for (int i = 0; i < indent; i++)
	{
		out << indentspace;
	}
	out << "if ";
	cond->print(indent, out);
	out << "\n";
	statement->print(indent + 1, out);
}
void ASTIf::setData(ASTNode * cond_in, ASTNode * statement_in)
{
	cond = cond_in;
	statement = statement_in;
}

void ASTDeclaration::print(int indent, ostream & out)
{
	for (int i = 0; i < indent; i++)
	{
		out << indentspace;
	}
	out << type;
	out << " ";
	out << name;
	out << ";\n";
}
void ASTDeclaration::setData(string type_in, string name_in)
{
	type = type_in;
	name = name_in;
}

void ASTAssign::print(int indent, ostream & out)
{
	for (int i = 0; i < indent; i++)
	{
		out << indentspace;
	}
	left->print(indent, out);
	out << " = ";
	right->print(indent, out);
	out << ";\n";
}

void ASTAssign::setData(ASTNode * left_in, ASTNode * right_in)
{
	left = left_in;
	right = right_in;
}

void ASTBooleanExpr::print(int indent, ostream & out)
{
	left->print(indent, out);
	out << " " << op << " ";
	right->print(indent, out);
}

void ASTBooleanExpr::setData(ASTNode * left_in, ASTNode * right_in, string op_in)
{
	left = left_in;
	right = right_in;
	op = op_in;
}


void printErrorHelper(ASTNode* node, string message, string number, bool & hadError)
{
	cout << "Error " << number << ": line: " << node->getLineNumber() << "   " << message << "\n";
	hadError = true;
}

string typeToString(Type type)
{
	if (type == T_NULLTYPE)
		return "T_NULLTYPE";
	if (type == T_ERROR)
		return "T_ERROR";
	if (type == T_INT)
		return "T_INT";
	if (type == T_NUMBER)
		return "T_NUMBER";
	if (type == T_BOOL)
		return "T_BOOL";
	if (type == T_VECTOR2)
		return "T_VECTOR2";
	if (type == T_NAME)
		return "T_NAME";

	return "ERROR IN TYPETOSTRING E102";
}

//http://www.cplusplus.com/reference/string/string/find/
bool contains(string s, char c)
{
	std::size_t found = s.find(c);
	if (found != std::string::npos)
	{
		return true;
	}
	return false;
}

double getNumberValue(string name)
{
	string s = name;
	int pos = s.find('#');
	s.erase(s.begin() + pos);
	return stod(s);
}
int getIntValue(string name)
{
	string s = name;
	int pos = s.find('#');
	s.erase(s.begin() + pos);
	return stoi(s);
}



int getType(string input)
{
	if ((!contains(input, '.')) && contains(input, '#'))
	{
		return T_INT;
	}
	else if ((contains(input, '.')) && contains(input, '#'))
	{
		return T_NUMBER;
	}
	else
	{
		return T_NAME;
	}

}

bool isNumber(string input)
{
	return (contains(input, '.')) && contains(input, '#');
}

bool isName(string input)
{
	return !contains(input, '#');
}


Type ASTProgram::typeCheck(TypeMap * map, bool & hadError)
{
	unordered_map<string, bool> funcMap;

	if (getType(iterations) != T_INT)
	{
		printErrorHelper(this, " Program iterations is not an integer!", "T02", hadError);
	}
	else if (getIntValue(iterations) < 1)
	{
		printErrorHelper(this, "Program iterations is not > 0!", "T03", hadError);
	}

	if (getType(xsize) != T_INT)
	{
		printErrorHelper(this, " Program sizex is not an integer!", "T04", hadError);
	}
	else if (getIntValue(xsize) < 1)
	{
		printErrorHelper(this, "Program sizex is not > 0!", "T05", hadError);
	}

	if (getType(xsize) != T_INT)
	{
		printErrorHelper(this, " Program sizex is not an integer!", "T06", hadError);
	}
	else if (getIntValue(xsize) < 1)
	{
		printErrorHelper(this, "Program sizex is not > 0!", "T07", hadError);
	}

	for (int i = 0; i < functions.size(); i++)
	{
		//if the function is not defined
		if (funcMap[((ASTFunction*)functions[i])->getFunctionName()] == false)
		{
			funcMap[((ASTFunction*)functions[i])->getFunctionName()] = true;
		}
		else //function already defined (i.e., duplicate function)
		{
			printErrorHelper(functions[i], "Function \"" + ((ASTFunction*)functions[i])->getFunctionName() + "\" is already defined", "T01", hadError);
		}
	}

	for (int i = 0; i < functions.size(); i++)
	{
		functions[i]->typeCheck(0, hadError);
	}

	return T_NULLTYPE;
}

Type ASTFunction::typeCheck(TypeMap * map, bool & hadError)
{
	map = new TypeMap();
	(*map)["time"] = T_INT;

	if (functionBody != NULL)
		functionBody->typeCheck(map, hadError);

	Type x = returnX->typeCheck(map, hadError);
	Type y = returnY->typeCheck(map, hadError);
	if (x != T_INT && x != T_NUMBER && x != T_NULLTYPE)
	{
		printErrorHelper(returnX, "Return argument 1 not integer or number!", "T08", hadError);
	}
	if (y != T_INT && y != T_NUMBER && y != T_NULLTYPE)
	{
		printErrorHelper(returnY, "Return argument 2 not integer or number!", "T09", hadError);
	}

	return T_NULLTYPE;
}


Type ASTStatements::typeCheck(TypeMap * tm, bool & haderror)
{

	if (statements.empty())
	{
		return T_NULLTYPE;
		printErrorHelper(this, "Statements array is empty", "T05", haderror);
	}
	for (int i = 0; i < statements.size(); i++)
	{
		Type t = statements[i]->typeCheck(tm, haderror); //Everything essentially we need 
	}
}

Type ASTBlockStatement::typeCheck(TypeMap * tm, bool & haderror)
{

	statements->typeCheck(tm, haderror);

	return T_NULLTYPE;
}

Type ASTFor::typeCheck(TypeMap * tm, bool & haderror)
{
	dec->typeCheck(tm, haderror);
	cond->typeCheck(tm, haderror);
	inc->typeCheck(tm, haderror);
	statement->typeCheck(tm, haderror);

	return T_NULLTYPE;
}

Type ASTIf::typeCheck(TypeMap * tm, bool & haderror)
{
	cond->typeCheck(tm, haderror);
	statement->typeCheck(tm, haderror);

	return T_NULLTYPE;
}

Type ASTDeclaration::typeCheck(TypeMap * tm, bool & haderror)
{
	//check if variable exists
	if ((*tm)[name] != T_NULLTYPE)
	{
		printErrorHelper(this, "Variable \"" + name + "\" is already defined", "T10", haderror);
	}
	else if (type != "int" && type != "number" && type != "vector2")
	{
		printErrorHelper(this, "Type must be int, number, or vector2; received " + type, "T11", haderror);
	}
	else
	{
		Type ts;

		if (type == "int")
			ts = T_INT;
		else if (type == "number")
			ts = T_NUMBER;
		else if (type == "vector2")
			ts = T_VECTOR2;

		(*tm)[name] = ts;
	}


	return T_NULLTYPE;
}

Type ASTAssign::typeCheck(TypeMap * map, bool & hadError)
{

	Type first = left->typeCheck(map, hadError);
	Type second = right->typeCheck(map, hadError);


	if (first != T_INT && first != T_NUMBER && first != T_NULLTYPE && first != T_VECTOR2)
	{
		printErrorHelper(left, "Return argument 1 not integer or number!", " ASSIGN T12", hadError);
	}
	if (second != T_INT && second != T_NUMBER && second != T_NULLTYPE && second != T_VECTOR2)
	{
		printErrorHelper(right, "Return argument 2 not integer or number!", "ASSIGN T13", hadError);
	}


	if (first == T_NAME)
	{
		if (second == T_INT)
		{
			return T_INT;
		}
		else if (second == T_NUMBER)
		{
			return T_NUMBER;
		}
		else
		{
			printErrorHelper(this, "Name being assigned to invalid type; Assign Error: ", "T12", hadError);
			return T_NULLTYPE;
		}
	}
	else if (first == T_NUMBER)
	{
		if (second == T_NUMBER)
		{
			return T_NUMBER;
		}
		else if (second == T_INT)
		{
			return T_NUMBER;
		}
		else
		{
			printErrorHelper(this, "Number being assigned to invalid type; Assign Error:" , "T14", hadError);
			return T_NULLTYPE;
		}
	}
	else if (first == T_INT)
	{
		if (second == T_INT)
		{
			return T_INT;
		}
		else
		{
			printErrorHelper(this, "Int being assigned to invalid type; Assign Error:", "T15", hadError);
			return T_NULLTYPE;
		}
	}
	return T_NULLTYPE;
}



Type ASTExpr::typeCheck(TypeMap * map, bool & hadError)
{
	//single term
	if (terms.size() == 1)
	{
		Type t = terms[0]->typeCheck(map, hadError);
		return t;
	}


	//more than 1 term
	{
		bool error = false;
		Type t = terms[0]->typeCheck(map, hadError);

		for (int i = 1; i < terms.size(); i++)
		{
			Type nextType = terms[i]->typeCheck(map, hadError);


			if (t == T_INT && nextType == T_NUMBER || nextType == T_INT && t == T_NUMBER)
			{
				t = T_NUMBER;
			}
			else if ((t != nextType || t == T_VECTOR2) && t != T_NULLTYPE && nextType != T_NULLTYPE)
			{
				printErrorHelper(terms[i], "Left and right of operators must be of arithmetic types. Left is " + typeToString(t) + "; right is " + typeToString(nextType) + ".", "T14", hadError);
				error = true;
			}
		}
		return error ? T_NULLTYPE : t;
	}

	return T_NULLTYPE;
}

Type ASTTerm::typeCheck(TypeMap * map, bool & hadError)
{
	// single term
		if (facts.size() == 1)
		{
			Type t = facts[0]->typeCheck(map, hadError);
			return t;
		}


	//more than 1 term
	{
		bool error = false;
		Type t = facts[0]->typeCheck(map, hadError);

		for (int i = 1; i < facts.size(); i++)
		{
			Type nextType = facts[i]->typeCheck(map, hadError);


			if (t == T_INT && nextType == T_NUMBER || nextType == T_INT && t == T_NUMBER)
			{
				t = T_NUMBER;
			}
			else if ((t != nextType || t == T_VECTOR2) && t != T_NULLTYPE && nextType != T_NULLTYPE)
			{
				printErrorHelper(facts[i], "Left and right of operators must be of arithmetic types. Left is " + typeToString(t) + "; right is " + typeToString(nextType) + ".", "T14", hadError);
				error = true;
			}
		}
		return error ? T_NULLTYPE : t;
	}

	return T_NULLTYPE;
}

Type ASTFactor::typeCheck(TypeMap * tm, bool & haderror)
{

	Type t = node->typeCheck(tm, haderror); //if an element calls element typecheck and same for expression
	return t;
}

Type ASTElement::typeCheck(TypeMap * tm, bool & haderror)
{
	if (!isDot)
	{
		if (getType(left) == T_NAME)
		{

			if ((*tm)[left] == T_NULLTYPE)
			{
				printErrorHelper(this, "" + left + " is not defined", "T00", haderror);
				return T_NULLTYPE;
			}
			else
			{
				return (*tm)[left];
			}
		}
		else
		{
			if (contains(left, '.'))
			{
				return T_NUMBER;
			}
			else
			{
				return T_INT;
			}
		}
	}
	else
	{
		Type leftt = T_NULLTYPE;

		if (getType(left) == T_NAME)
		{
			if ((*tm)[left] == T_NULLTYPE)
			{
				printErrorHelper(this, "" + left + " is not defined", "T00", haderror);
				leftt = T_NULLTYPE;
			}
			else
			{
				leftt = (*tm)[left];
			}
		}
		if (leftt != T_VECTOR2 && leftt != T_NULLTYPE)
		{
			printErrorHelper(this, "Dot operator requires vector2 on left side. Left is " + typeToString(leftt) + ".", "T16", haderror);

		}
		if (right != "x" && right != "y")
		{
			printErrorHelper(this, "Dot operator requires right is either x or y. Right is " + right + ".", "T17", haderror);
		}

		return T_NUMBER;
	}
}

Type ASTBooleanExpr::typeCheck(TypeMap * tm, bool & haderror)
{
	Type lType = left->typeCheck(tm, haderror);
	Type rType = right->typeCheck(tm, haderror);

	if (lType == T_NULLTYPE)
	{
		return T_NULLTYPE;
	}
	if ((lType) != T_INT && (lType != T_NUMBER))
	{
		printErrorHelper(this, "BOOLEAN ERROR:  Left variables is not a Number or an Int", "T23", haderror);
	}
	else if ((rType) != T_INT && (rType != T_NUMBER))
	{
		printErrorHelper(this, "BOOLEAN ERROR:  Right variables is not a Number or an Int", "T24", haderror);
	}

	return T_BOOL;
}
