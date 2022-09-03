#pragma once
#ifndef _JACKANALYZER_H_
#define _jACKANALYZER_H_

#include<string>
#include<fstream>
#include"Tokenizer.h"
#include"CompilationEngine.h"

using namespace std;

class JackAnalyzer {
private:
	string inFile;
	string outPath;
	CompilationEngine* compilationEngine;
	Tokenizer* tokenizer;
public:
	JackAnalyzer(const string&, const string&);	//Constructor
	string getOutName();						//Get the "file.xml" name from "file.hack"
	void translate();							//Start translate the "file.hack"
	~JackAnalyzer() {
		if (compilationEngine) delete compilationEngine;
		if (tokenizer) delete tokenizer;
	}
};

#endif

