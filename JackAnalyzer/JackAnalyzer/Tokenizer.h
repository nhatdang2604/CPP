#pragma once
#ifndef _TOKENIZER_H_
#define _TOkENIZER_H_

#define NUMBER_OF_KEYWORD 21
#define NUMBER_OF_SYMBOL 19
#define WINDOWS_EOL_CHARACTER_NUMBER 2
#define UNIX_EOL_CHARACTER_NUMBER 1
#define EOL_CHARACTER_NUMBER WINDOWS_EOL_CHARACTER_NUMBER

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

class Tokenizer {
public:
	string keywords[NUMBER_OF_KEYWORD] = { "class", "constructor", "function",
		"method", "field", "static", "var", "int", "char", "boolean",
		"void", "true", "false", "null", "this", "let", "do", "if",
		"else", "while", "return" };

	char symbols[NUMBER_OF_SYMBOL] = { '{', '}', '(', ')', '[', ']', '.', ',',
		';', '+', '-', '*', '/', '&', '|', '<', '>', '=', '~' };

	//Constructor
	Tokenizer(const string&, ofstream&);

	bool hasMoreTokens();
	void advance();
	string tokenType();
	string keyWord();
	char symbol();
	string identifier();
	int intVal();
	string stringVal();

	//Destructor
	~Tokenizer() {
		if (infileStream.is_open()) infileStream.close();
		if (outfileStream->is_open()) outfileStream->close();
	}

	//Extension
	void printToken();
	string getCurrentToken();
	string getBlock(string&);

private:
	//string infile;
	ifstream infileStream;
	ofstream* outfileStream;
	string currentToken = "";
	string currentLine ="";
};

#endif 