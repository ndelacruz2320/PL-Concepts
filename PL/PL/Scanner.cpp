//it should be noted that my scanner has some extra code in it from pieces I chose not to give you. ex., the ; was originally goingto be a single #.


#include "Scanner.h"
#include <string>
#include <iostream>
using namespace std;

//enum TokenType {NAME,CONST,EQL,EE,GR,LT,MULTIPLY,DIVIDE,ADD,MINUS,LPAREN,RPAREN,LBRACE,RBRACE,EOL,COMMA,DOT, NONE /*this is for if the file is empty*/ };

string Scanner::toString(TokenType t)
{
	if (t == NONE)
		return "NONE";
	if (t == NAME)
		return "NAME";
	if (t == EQL)
		return "EQL";
	if (t == EE)
		return "EE";
	if (t == GR)
		return "GR";
	if (t == LT)
		return "LT";
	if (t == MULTIPLY)
		return "MULTIPLY";
	if (t == DIVIDE)
		return "DIVIDE";
	if (t == MINUS)
		return "MINUS";
	if (t == ADD)
		return "ADD";
	if (t == LPAREN)
		return "LPAREN";
	if (t == RPAREN)
		return "RPAREN";
	if (t == LBRACE)
		return "LBRACE";
	if (t == RBRACE)
		return "RBRACE";
	if (t == EOL)
		return "EOL";
	if (t == COMMA)
		return "COMMA";
	if (t == IF)
		return "IF";
	if (t == FOR)
		return "FOR";
	if (t == DOT)
		return "DOT";
	if (t == ERROR)
		return "ERROR: ";
	if (t == CONST)
		return "CONST";
	if (t == RETURN)
		return "RETURN";
	return "ERROR in tostring";
}


string Scanner::currentTokenString()
{
	return currents;
}

string Scanner::nextTokenString()
{
	return nexts;
}

TokenType Scanner::currentTokenType()
{
	return currenttt;
}

TokenType Scanner::nextTokenType()
{
	return nexttt;
}

Scanner::Scanner(string fname)
{
	filestream.open(fname);

	linenext = 1;
	column = 1;


	if (!filestream.good())
	{
		cout << "Could not open file: " << fname << "\n";
		return;
	}


	advance(); //fill up first slot
	advance(); //fill up second slot

			   /*while (currentTokenType() != NONE)
			   {
			   cout << toString(currentTokenType()) << " " << currentTokenString() << "\n";
			   advance();
			   }*/
}


void addToBuffer(string & buf, ifstream & stream)
{
	int next = stream.get();

	if (next == -1)
	{
		buf = buf + (char)0; //null signifies eof for today!
	}

	//cout << "nextchar: " << next << "\n";
	buf = buf + (char)next;

}


void removeFromBuffer(string & buf, ifstream & stream)
{
	char last = buf.back();
	stream.putback(last);
	buf = buf.substr(0, buf.size() - 1);

}


bool isNum(char test)
{
	return (test == '0' || test == '1' || test == '2' || test == '3' || test == '4' || test == '5' || test == '6' || test == '7' || test == '8' || test == '9');
}

bool isLowerCharacter(char test)
{
	return (test == 'a' || test == 'b' || test == 'c' || test == 'd' ||
		test == 'e' || test == 'f' || test == 'g' || test == 'h' ||
		test == 'i' || test == 'j' || test == 'k' || test == 'l' ||
		test == 'm' || test == 'n' || test == 'o' || test == 'p' ||
		test == 'q' || test == 'r' || test == 's' || test == 't' ||
		test == 'u' || test == 'v' || test == 'w' || test == 'x' || test == 'y' || test == 'z');
}



//advance places whatever is in the next variables into the current variables and finds what the next variables are supposed to be
void Scanner::advance()
{
	currents = nexts;
	currenttt = nexttt;
	linecurrent = linenext;

	string buffer;

	addToBuffer(buffer, filestream);


	bool shouldbenumber = false;

	addToBuffer(buffer, filestream);
	if (buffer[0] == '-' && buffer[1] == '#')
	{
		shouldbenumber = true;
	}
	if (buffer[0] == '#' && isNum(buffer[1]))
	{
		shouldbenumber = true;
	}
	removeFromBuffer(buffer, filestream);

	if (buffer[0] == '=')
	{
		addToBuffer(buffer, filestream);

		if (buffer[1] == '=')
		{

			nexttt = EE;
			nexts = "==";
		}
		else
		{
			removeFromBuffer(buffer, filestream);

			nexttt = EQL;
			nexts = "=";
		}
	}
	else if (buffer[0] == '>')
	{
		nexttt = GR;
		nexts = ">";
	}
	else if (buffer[0] == '<')
	{
		nexttt = LT;
		nexts = "<";
	}
	else if (buffer[0] == '*')
	{
		nexttt = MULTIPLY;
		nexts = "*";
	}
	else if (buffer[0] == '/')
	{
		nexttt = DIVIDE;
		nexts = "/";
	}
	else if (buffer[0] == '+')
	{
		nexttt = ADD;
		nexts = "+";
	}
	else if (buffer[0] == ';' && !shouldbenumber)
	{
		nexttt = EOL;
		nexts = ";";
	}
	else if (buffer[0] == ',')
	{
		nexttt = COMMA;
		nexts = ",";
	}
	else if (buffer[0] == '.')
	{
		nexttt = DOT;
		nexts = ".";
	}
	else if (buffer[0] == '-' && !shouldbenumber)
	{
		addToBuffer(buffer, filestream);

		if (buffer[1] == '{')
		{
			nexttt = LBRACE;
			nexts = "-{";
		}
		else
		{
			removeFromBuffer(buffer, filestream);

			nexttt = MINUS;
			nexts = "-";
		}
	}
	else if (buffer[0] == '(')
	{
		nexttt = LPAREN;
		nexts = "(";
	}
	else if (buffer[0] == ')')
	{
		nexttt = RPAREN;
		nexts = ")";
	}
	else if (buffer[0] == '}')
	{
		addToBuffer(buffer, filestream);

		if (buffer[1] == '-')
		{
			nexttt = RBRACE;
			nexts = "}-";
		}
		else
		{
			nexttt = ERROR;
			while ((buffer[buffer.size() - 1] != ' ' && buffer[buffer.size() - 1] != '\n' && buffer[buffer.size() - 1] != '\t' && buffer[buffer.size() - 1] != 0))
			{
				addToBuffer(buffer, filestream);
			}
			removeFromBuffer(buffer, filestream);
			nexts = "Invalid Token detected: \"" + buffer + "\" on line: " + to_string(linenext);
		}
	}
	else if (buffer[0] == 0)
	{
		nexttt = NONE;
		nexts = "eof";
	}
	else
	{


		/*if (isNum(buffer[0]))
		{
		//addToBuffer(buffer, filestream);

		while (isNum(buffer[buffer.size() - 1]))
		{
		addToBuffer(buffer, filestream);
		}

		if (buffer[buffer.size() - 1] == '.')
		{
		addToBuffer(buffer, filestream);
		}
		while (isNum(buffer[buffer.size() - 1]))
		{
		addToBuffer(buffer, filestream);
		}

		removeFromBuffer(buffer, filestream);
		nexttt = NUMBER;
		nexts = buffer;

		}
		else if (isLowerCharacter(buffer[0]))
		{
		while (isNum(buffer[buffer.size() - 1]) || isLowerCharacter(buffer[buffer.size() - 1]))
		{
		addToBuffer(buffer, filestream);
		}
		removeFromBuffer(buffer, filestream);

		nexttt = NAME;
		nexts = buffer;

		if (buffer == "print")
		{
		nexttt = PRINT;
		nexts = buffer;
		}


		}
		else*/
		if (isLowerCharacter(buffer[0]))
		{
			while (isNum(buffer[buffer.size() - 1]) || isLowerCharacter(buffer[buffer.size() - 1]))
			{
				addToBuffer(buffer, filestream);
			}
			removeFromBuffer(buffer, filestream);

			nexttt = NAME;
			nexts = buffer;

			if (buffer == "for")
			{
				nexttt = FOR;
				nexts = buffer;
			}
			if (buffer == "if")
			{
				nexttt = IF;
				nexts = buffer;
			}
			if (buffer == "return")
			{
				nexttt = RETURN;
				nexts = buffer;
			}

		}
		else if (buffer[0] == '-' || buffer[0] == '#')
		{
			bool error = false;

			if (buffer[0] == '-')
			{
				addToBuffer(buffer, filestream);
			}

			//here: # is the last thing added
			addToBuffer(buffer, filestream);

			if (!isNum(buffer[buffer.size() - 1]))
			{
				nexttt = ERROR;
				while ((buffer[buffer.size() - 1] != ' ' && buffer[buffer.size() - 1] != '\n' && buffer[buffer.size() - 1] != '\t' && buffer[buffer.size() - 1] != 0))
				{
					addToBuffer(buffer, filestream);
				}
				removeFromBuffer(buffer, filestream);
				nexts = "Invalid Token detected: \"" + buffer + "\" on line: " + to_string(linenext);
				error = true;
			}
			if (!error)
			{
				while (isNum(buffer[buffer.size() - 1]))
				{
					addToBuffer(buffer, filestream);
				}

				if (buffer[buffer.size() - 1] == '.')
				{
					addToBuffer(buffer, filestream);
				}
				while (isNum(buffer[buffer.size() - 1]))
				{
					addToBuffer(buffer, filestream);
				}

				if (!isNum(buffer[buffer.size() - 2]))
				{
					nexttt = ERROR;
					while ((buffer[buffer.size() - 1] != ' ' && buffer[buffer.size() - 1] != '\n' && buffer[buffer.size() - 1] != '\t' && buffer[buffer.size() - 1] != 0))
					{
						addToBuffer(buffer, filestream);
					}
					removeFromBuffer(buffer, filestream);
					nexts = "Invalid Token detected: \"" + buffer + "\" on line: " + to_string(linenext);
					error = true;
				}
				else
				{
					removeFromBuffer(buffer, filestream);
					nexttt = CONST;
					nexts = buffer;
				}
			}
		}
		else
		{
			//white space
			bool temp = buffer[0] == ' ';
			if (temp || buffer[0] == '\n' || buffer[0] == '\t')
			{
				if (buffer[0] == '\n')
				{
					linenext++;

				}
				advance();
			}
			else
			{
				nexttt = ERROR;
				while ((buffer[buffer.size() - 1] != ' ' && buffer[buffer.size() - 1] != '\n' && buffer[buffer.size() - 1] != '\t' && buffer[buffer.size() - 1] != 0))
				{
					addToBuffer(buffer, filestream);
				}
				removeFromBuffer(buffer, filestream);
				nexts = "Invalid Token detected: \"" + buffer + "\" on line: " + to_string(linenext);
			}
		}
	}
}





int Scanner::getLine()
{
	return linecurrent;
}