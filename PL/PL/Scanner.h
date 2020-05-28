#pragma once


#include <iostream>
#include <fstream>
using namespace std;

enum TokenType { RETURN, ERROR, IF, FOR, NAME, CONST, EQL, EE, GR, LT, MULTIPLY, DIVIDE, ADD, MINUS, LPAREN, RPAREN, LBRACE, RBRACE, EOL, COMMA, DOT, NONE /*this is for if the file is empty*/ };

class Scanner
{
public:
	Scanner(string filename);

	TokenType currentTokenType();
	TokenType nextTokenType();
	string currentTokenString();
	string nextTokenString();
	string toString(TokenType t);

	void advance();

	int getLine();
private:
	ifstream filestream;
	string currents;
	string nexts;
	TokenType currenttt;
	TokenType nexttt;

	int linenext;
	int linecurrent;

	int column;
};
