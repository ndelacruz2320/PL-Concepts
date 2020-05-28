#include "Scanner.h"
#include "AST.h"
#include "Parser.h"
#include <string>

Parser::Parser(string fname)
{
	filename = fname;
}

//entry point to parse, calls the first recursive decent piece 
ASTNode * Parser::parse(bool & haderror)
{
	Scanner myscanner(filename);

	return rdpProgram(myscanner, haderror);
}

ASTNode * Parser::rdpProgram(Scanner & scan, bool & haderror)
{
	ASTProgram * prog = new ASTProgram();
	prog->setup(scan.getLine());

	string it, x, y;

	if (scan.currentTokenType() == CONST)
	{
		it = scan.currentTokenString();
		scan.advance();

	}
	else
	{
		if (scan.currentTokenType() == ERROR)
		{
			cout << scan.currentTokenString() << "\n";
			scan.advance();
			haderror = true;
			return 0;
		}

		cout << "error1: expecting CONST on line:" << scan.getLine() << " but received " << scan.toString(scan.currentTokenType()) << " \"" << scan.currentTokenString() << "\"" << "\n";
		scan.advance();
		haderror = true;
	}

	if (scan.currentTokenType() == CONST && !haderror)
	{
		x = scan.currentTokenString();
		scan.advance();
	}
	else if (!haderror)
	{
		if (scan.currentTokenType() == ERROR)
		{
			cout << scan.currentTokenString() << "\n";
			scan.advance();
			haderror = true;
			return 0;
		}

		cout << "error2: expecting CONST on line:" << scan.getLine() << " but received " << scan.toString(scan.currentTokenType()) << " \"" << scan.currentTokenString() << "\"" << "\n";
		scan.advance();
		haderror = true;
	}

	if (scan.currentTokenType() == CONST && !haderror)
	{
		y = scan.currentTokenString();
		scan.advance();
	}
	else if (!haderror)
	{
		cout << "error3: expecting CONST on line:" << scan.getLine() << " but received " << scan.toString(scan.currentTokenType()) << " \"" << scan.currentTokenString() << "\"" << "\n";
		scan.advance();
		haderror = true;
	}

	if (!haderror)
	{
		prog->setSizes(it, x, y);

		while (scan.currentTokenType() != NONE)
		{
			ASTNode * n = rdpFunction(scan, haderror);
			prog->addFunction(n);
		}
	}

	return prog;
}

ASTNode * Parser::rdpFunction(Scanner & scan, bool & haderror)
{
	ASTFunction * func = new ASTFunction();
	func->setup(scan.getLine());

	if (scan.currentTokenType() == NAME && !haderror)
	{
		string name = scan.currentTokenString();
		scan.advance();

		func->setFunctionName(name);
	}
	else if (!haderror)
	{
		cout << "error4: expecting NAME on line:" << scan.getLine() << " but received " << scan.toString(scan.currentTokenType()) << " \"" << scan.currentTokenString() << "\"" << "\n";
		scan.advance();
		haderror = true;
	}

	if (scan.currentTokenType() == LPAREN && !haderror)
	{
		scan.advance();
	}
	else if (!haderror)
	{
		cout << "error5: expecting LPAREN on line:" << scan.getLine() << " but received " << scan.toString(scan.currentTokenType()) << " \"" << scan.currentTokenString() << "\"" << "\n";
		scan.advance();
		haderror = true;
	}

	if (scan.currentTokenType() == RPAREN && !haderror)
	{
		scan.advance();
	}
	else if (!haderror)
	{
		cout << "error18: expecting RPAREN on line:" << scan.getLine() << " but received " << scan.toString(scan.currentTokenType()) << " \"" << scan.currentTokenString() << "\"" << "\n";
		scan.advance();
		haderror = true;
	}

	if (scan.currentTokenType() == LBRACE && !haderror)
	{
		scan.advance();
	}
	else if (!haderror)
	{
		cout << "error6: expecting LBRACE on line:" << scan.getLine() << " but received " << scan.toString(scan.currentTokenType()) << " \"" << scan.currentTokenString() << "\"" << "\n";
		scan.advance();
		haderror = true;
	}

	if (scan.currentTokenType() != RETURN && !haderror)
	{
		ASTNode * statements = rdpStatements(scan, haderror);
		func->setFunctionBody(statements);
	}
	if (scan.currentTokenType() == RETURN && !haderror)
	{
		scan.advance();
		ASTNode * left = rdpExpr(scan, haderror);
		func->setX(left);

		if (scan.currentTokenType() == COMMA && !haderror)
		{
			scan.advance();
			ASTNode * right = rdpExpr(scan, haderror);
			func->setY(right);
		}
		else if (!haderror)
		{
			cout << "error7: expecting COMMA on line:" << scan.getLine() << " but received " << scan.toString(scan.currentTokenType()) << " \"" << scan.currentTokenString() << "\"" << "\n";
			scan.advance();
			haderror = true;
		}
	}
	else if (!haderror)
	{
		cout << "error8: expecting RETURN on line:" << scan.getLine() << " but received " << scan.toString(scan.currentTokenType()) << " \"" << scan.currentTokenString() << "\"" << "\n";
		scan.advance();
		haderror = true;
	}

	if (scan.currentTokenType() == EOL && !haderror)
	{
		scan.advance();
	}
	else if (!haderror)
	{
		cout << "error9: expecting EOL on line:" << scan.getLine() << " but received " << scan.toString(scan.currentTokenType()) << " \"" << scan.currentTokenString() << "\"" << "\n";
		scan.advance();
		haderror = true;
	}

	if (scan.currentTokenType() == RBRACE && !haderror)
	{
		scan.advance();
	}
	else if (!haderror)
	{
		cout << "error17: expecting RBRACE on line:" << scan.getLine() << " but received " << scan.toString(scan.currentTokenType()) << " \"" << scan.currentTokenString() << "\"" << "\n";
		scan.advance();
		haderror = true;
	}
	return func;
}

ASTNode * Parser::rdpStatements(Scanner & scan, bool & haderror)
{
	ASTStatements * statements = new ASTStatements();
	statements->setup(scan.getLine());

	while (!haderror && (scan.currentTokenType() != RBRACE && scan.currentTokenType() != RETURN))
	{
		ASTNode * theNode = rdpStatement(scan, haderror);
		statements->addStatement(theNode);
	}
	return statements;
}


ASTNode * Parser::rdpExpr(Scanner & scan, bool & haderror)
{
	ASTExpr * expression = new ASTExpr();
	expression->setup(scan.getLine());

	if (scan.currentTokenType() == NAME || scan.currentTokenType() == CONST || scan.currentTokenType() == LPAREN)
	{
		ASTNode * left = rdpTerm(scan, haderror);
		expression->addTerm(left);
	}
	else if (!haderror)
	{
		cout << "error10: expecting NAME, CONST, or LPAREN on line : " << scan.getLine() << " but received " << scan.toString(scan.currentTokenType()) << " \"" << scan.currentTokenString() << "\"" << "\n";

		scan.advance();
		haderror = true;
	}


	while (scan.currentTokenType() == MULTIPLY || scan.currentTokenType() == DIVIDE)
	{
		char op = (scan.currentTokenType() == MULTIPLY) ? '*' : '/';
		expression->addOp(op);
		scan.advance();

		if (scan.currentTokenType() == NAME || scan.currentTokenType() == CONST || scan.currentTokenType() == LPAREN)
		{
			ASTNode * left = rdpTerm(scan, haderror);
			expression->addTerm(left);
		}
		else if (!haderror)
		{
			cout << "error11: expecting NAME, CONST, or LPAREN on line : " << scan.getLine() << " but received " << scan.toString(scan.currentTokenType()) << " \"" << scan.currentTokenString() << "\"" << "\n";

			scan.advance();
			haderror = true;
		}

	}

	return expression;
}


ASTNode * Parser::rdpTerm(Scanner & scan, bool & haderror)
{
	ASTTerm * term = new ASTTerm();
	term->setup(scan.getLine());


	if (scan.currentTokenType() == NAME || scan.currentTokenType() == CONST || scan.currentTokenType() == LPAREN)
	{
		ASTNode * left = rdpFactor(scan, haderror);
		term->addFactor(left);
	}
	else if (!haderror)
	{
		cout << "error12: expecting NAME, CONST, or LPAREN on line : " << scan.getLine() << " but received " << scan.toString(scan.currentTokenType()) << " \"" << scan.currentTokenString() << "\"" << "\n";

		scan.advance();
		haderror = true;
	}


	while (scan.currentTokenType() == ADD || scan.currentTokenType() == MINUS)
	{
		char op = (scan.currentTokenType() == ADD) ? '+' : '-';
		term->addOp(op);
		scan.advance();

		if (scan.currentTokenType() == NAME || scan.currentTokenType() == CONST || scan.currentTokenType() == LPAREN)
		{
			ASTNode * left = rdpFactor(scan, haderror);
			term->addFactor(left);
		}
		else if (!haderror)
		{
			cout << "error13: expecting NAME, CONST, or LPAREN on line : " << scan.getLine() << " but received " << scan.toString(scan.currentTokenType()) << " \"" << scan.currentTokenString() << "\"" << "\n";

			scan.advance();
			haderror = true;
		}
	}

	return term;
}


ASTNode * Parser::rdpFactor(Scanner & scan, bool & haderror)
{
	ASTFactor * fact = new ASTFactor();
	fact->setup(scan.getLine());

	if (scan.currentTokenType() == LPAREN)
	{
		scan.advance();
		ASTNode * n = rdpExpr(scan, haderror);
		fact->setNode(n);

		if (scan.currentTokenType() == RPAREN)
		{
			scan.advance();
		}
		else if (!haderror)
		{
			cout << "error14: expecting RPAREN on line : " << scan.getLine() << " but received " << scan.toString(scan.currentTokenType()) << " \"" << scan.currentTokenString() << "\"" << "\n";
			scan.advance();
			haderror = true;
		}
	}
	else if (scan.currentTokenType() == NAME || scan.currentTokenType() == CONST)
	{
		ASTNode * n = rdpElement(scan, haderror);
		fact->setNode(n);
	}
	else if (!haderror)
	{
		cout << "error15: expecting NAME, CONST, or LPAREN on line : " << scan.getLine() << " but received " << scan.toString(scan.currentTokenType()) << " \"" << scan.currentTokenString() << "\"" << "\n";
		scan.advance();
		haderror = true;
	}
	return fact;
}



/*ASTNode * Parser::rdpNAMEID(Scanner & scan, bool & haderror)
{
ASTNAMEID * namenode = new ASTNAMEID();
namenode->setup(scan.getLine());

if (scan.currentTokenType() == NAME || scan.currentTokenType() == CONST)
{
string name = scan.currentTokenString();

namenode->setType(scan.currentTokenType());
scan.advance();

namenode->setName(name);

}
else
{
cout << "error16: expecting NAME or CONST on line : " << scan.getLine() << " but received " << scan.toString(scan.currentTokenType()) << " \"" << scan.currentTokenString() << "\"" << "\n";
scan.advance();
haderror = true;
}

return namenode;
}*/

ASTNode * Parser::rdpStatement(Scanner & scan, bool & haderror)
{
	if (scan.currentTokenType() == FOR)
	{
		return rdpFor(scan, haderror);
	}
	else if (scan.currentTokenType() == IF)
	{
		return rdpIf(scan, haderror);
	}
	else if (scan.currentTokenType() == NAME && scan.nextTokenType() == NAME)
	{
		return rdpDeclaration(scan, haderror);
	}
	else if (scan.currentTokenType() == NAME)
	{
		return rdpAssign(scan, haderror);
	}
	else if (scan.currentTokenType() == LBRACE)
	{
		return rdpBlockStatement(scan, haderror);
	}
	else
	{
		cout << "error20: expecting For, If, Declaration, Assign, or Block statement on line : " << scan.getLine() << " but received " << scan.toString(scan.currentTokenType()) << " \"" << scan.currentTokenString() << "\"" << "\n";
		scan.advance();
		haderror = true;
	}
	return 0;
}

ASTNode * Parser::rdpBlockStatement(Scanner & scan, bool & haderror)
{
	ASTBlockStatement * block = new ASTBlockStatement();
	block->setup(scan.getLine());

	if (scan.currentTokenType() == LBRACE)
	{
		scan.advance();
	}
	else if (!haderror)
	{
		cout << "error21: expecting LBRACE on line : " << scan.getLine() << " but received " << scan.toString(scan.currentTokenType()) << " \"" << scan.currentTokenString() << "\"" << "\n";
		scan.advance();
		haderror = true;
	}

	ASTNode * statements = (rdpStatements(scan, haderror));
	block->setStatement(statements);

	if (scan.currentTokenType() == RBRACE)
	{
		scan.advance();
	}
	else if (!haderror)
	{
		cout << "error22: expecting RBRACE on line : " << scan.getLine() << " but received " << scan.toString(scan.currentTokenType()) << " \"" << scan.currentTokenString() << "\"" << "\n";
		scan.advance();
		haderror = true;
	}

	return block;
}

ASTNode * Parser::rdpFor(Scanner & scan, bool & haderror)
{
	ASTFor * forstatement = new ASTFor();
	forstatement->setup(scan.getLine());

	if (scan.currentTokenType() == FOR)
	{
		scan.advance();
	}
	else if (!haderror)
	{
		cout << "error23: expecting FOR on line : " << scan.getLine() << " but received " << scan.toString(scan.currentTokenType()) << " \"" << scan.currentTokenString() << "\"" << "\n";
		scan.advance();
		haderror = true;
	}

	ASTNode * dec = rdpDeclaration(scan, haderror);
	ASTNode * boo = rdpBooleanExpr(scan, haderror);
	ASTNode * inc = rdpAssign(scan, haderror);
	ASTNode * statement = rdpStatement(scan, haderror);

	forstatement->setData(dec, boo, inc, statement);

	return forstatement;
}

ASTNode * Parser::rdpIf(Scanner & scan, bool & haderror)
{
	ASTIf * ifstatement = new ASTIf();
	ifstatement->setup(scan.getLine());

	if (scan.currentTokenType() == IF)
	{
		scan.advance();
	}
	else if (!haderror)
	{
		cout << "error24: expecting IF on line : " << scan.getLine() << " but received " << scan.toString(scan.currentTokenType()) << " \"" << scan.currentTokenString() << "\"" << "\n";
		scan.advance();
		haderror = true;
	}

	ASTNode * boo = rdpBooleanExpr(scan, haderror);
	ASTNode * statement = rdpStatement(scan, haderror);

	ifstatement->setData(boo, statement);

	return ifstatement;
}

ASTNode * Parser::rdpDeclaration(Scanner & scan, bool & haderror)
{
	ASTDeclaration * dec = new ASTDeclaration();
	dec->setup(scan.getLine());

	string type, name;

	if (scan.currentTokenType() == NAME)
	{
		type = scan.currentTokenString();
		scan.advance();
	}
	else if (!haderror)
	{
		cout << "error25: expecting NAME on line : " << scan.getLine() << " but received " << scan.toString(scan.currentTokenType()) << " \"" << scan.currentTokenString() << "\"" << "\n";
		scan.advance();
		haderror = true;
	}

	if (scan.currentTokenType() == NAME)
	{
		name = scan.currentTokenString();
		scan.advance();
	}
	else if (!haderror)
	{
		cout << "error26: expecting NAME on line : " << scan.getLine() << " but received " << scan.toString(scan.currentTokenType()) << " \"" << scan.currentTokenString() << "\"" << "\n";
		scan.advance();
		haderror = true;
	}

	if (scan.currentTokenType() == EOL)
	{
		scan.advance();
	}
	else if (!haderror)
	{
		cout << "error31: expecting EOL on line : " << scan.getLine() << " but received " << scan.toString(scan.currentTokenType()) << " \"" << scan.currentTokenString() << "\"" << "\n";
		scan.advance();
		haderror = true;
	}

	dec->setData(type, name);

	return dec;
}

ASTNode * Parser::rdpAssign(Scanner & scan, bool & haderror)
{
	ASTAssign * assign = new ASTAssign();
	assign->setup(scan.getLine());

	ASTNode * var = 0, *expr = 0;

	if (scan.currentTokenType() == NAME)
	{
		var = rdpElement(scan, haderror);
	}
	else if (!haderror)
	{
		cout << "error27: expecting NAME on line : " << scan.getLine() << " but received " << scan.toString(scan.currentTokenType()) << " \"" << scan.currentTokenString() << "\"" << "\n";
		scan.advance();
		haderror = true;
	}

	if (scan.currentTokenType() == EQL)
	{
		scan.advance();
	}
	else if (!haderror)
	{
		cout << "error28: expecting EQL on line : " << scan.getLine() << " but received " << scan.toString(scan.currentTokenType()) << " \"" << scan.currentTokenString() << "\"" << "\n";
		scan.advance();
		haderror = true;
	}

	expr = rdpExpr(scan, haderror);

	if (scan.currentTokenType() == EOL)
	{
		scan.advance();
	}
	else if (!haderror)
	{
		cout << "error31: expecting EOL on line : " << scan.getLine() << " but received " << scan.toString(scan.currentTokenType()) << " \"" << scan.currentTokenString() << "\"" << "\n";
		scan.advance();
		haderror = true;
	}

	assign->setData(var, expr);
	return assign;
}

ASTNode * Parser::rdpBooleanExpr(Scanner & scan, bool & haderror)
{
	ASTBooleanExpr * boole = new ASTBooleanExpr();
	boole->setup(scan.getLine());

	ASTNode * left = rdpExpr(scan, haderror);
	string op;

	if (scan.currentTokenType() == EE || scan.currentTokenType() == GR || scan.currentTokenType() == LT)
	{
		switch (scan.currentTokenType())
		{
		case EE:
			op = "==";
			break;
		case GR:
			op = ">";
			break;
		case LT:
			op = "<";
			break;
		}

		scan.advance();
	}
	else if (!haderror)
	{
		cout << "error29: expecting EE or LT or GR on line : " << scan.getLine() << " but received " << scan.toString(scan.currentTokenType()) << " \"" << scan.currentTokenString() << "\"" << "\n";
		scan.advance();
		haderror = true;
	}

	ASTNode * right = rdpExpr(scan, haderror);

	boole->setData(left, right, op);
	return boole;
}

ASTNode * Parser::rdpElement(Scanner & scan, bool & haderror)
{
	ASTElement * element = new ASTElement();
	element->setup(scan.getLine());

	string nameOrConst = scan.currentTokenString();
	scan.advance();

	element->setDot(false);
	element->setNode1(nameOrConst);

	if (scan.currentTokenType() == DOT)
	{
		element->setDot(true);
		scan.advance();

		if (scan.currentTokenType() == NAME)
		{
			string n = scan.currentTokenString();
			scan.advance();
			element->setNode2(n);
		}
		else if (!haderror)
		{
			cout << "error30: expecting NAME after DOT on line : " << scan.getLine() << " but received " << scan.toString(scan.currentTokenType()) << " \"" << scan.currentTokenString() << "\"" << "\n";
			scan.advance();
			haderror = true;
		}
	}
	return element;
}