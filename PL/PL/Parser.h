#pragma once

#include "Scanner.h"
#include "AST.h"

class Parser
{
public:
	Parser(string fname);

	ASTNode * parse(bool & haderror);

	ASTNode * rdpProgram(Scanner & scan, bool & haderror);
	ASTNode * rdpFunction(Scanner & scan, bool & haderror);
	ASTNode * rdpStatements(Scanner & scan, bool & haderror);
	ASTNode * rdpExpr(Scanner & scan, bool & haderror);
	ASTNode * rdpTerm(Scanner & scan, bool & haderror);
	ASTNode * rdpFactor(Scanner & scan, bool & haderror);
	ASTNode * rdpElement(Scanner & scan, bool & haderror);
	//ASTNode * rdpNAMEID(Scanner & scan, bool & haderror);

	ASTNode * rdpStatement(Scanner & scan, bool & haderror);
	ASTNode * rdpBlockStatement(Scanner & scan, bool & haderror);
	ASTNode * rdpFor(Scanner & scan, bool & haderror);
	ASTNode * rdpIf(Scanner & scan, bool & haderror);
	ASTNode * rdpDeclaration(Scanner & scan, bool & haderror);
	ASTNode * rdpAssign(Scanner & scan, bool & haderror);
	ASTNode * rdpBooleanExpr(Scanner & scan, bool & haderror);

private:
	string filename;
	Scanner * scan;

	ASTNode * root;
};