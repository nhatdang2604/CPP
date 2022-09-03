#pragma once
#ifndef _COMPilATION_ENGINE_H_
#define _COMPilATION_ENGINE_H_

#include <fstream>
#include "Tokenizer.h"
using namespace std;

class CompilationEngine {
private:
	
	ifstream infileStream;
	ofstream outfileStream;
	Tokenizer* tokenizer;
	int tabNumber = 0;	//them number of tab each sentence 

public:

	//Constructor
	CompilationEngine(const string&, const string&);

	void compileClass();
	void compileClassVarDec();
	void compileSubroutine();
	void compileParameterList();
	void compileVarDec();
	void compileStatements();
	void compileDo();
	void compileLet();
	void compileWhile();
	void compileReturn();
	void compileIf();
	void compileExpression();
	void compileTerm();
	void compileExpressionList();

	//Destructor
	~CompilationEngine() {
		if (tokenizer) delete tokenizer;
		if (infileStream.is_open()) infileStream.close();
		if (outfileStream.is_open()) outfileStream.close();
	}

	//Extension
	void compile();
	void printTab();
	//void compileType();
	/*void compileClassName();
	void compileSubroutineName();
	void compileVarName();*/
	//void compileIdentifier(const string&);
	void compileSubroutineBody();
	void compileSubroutineCall();
};

	
#endif // !1
