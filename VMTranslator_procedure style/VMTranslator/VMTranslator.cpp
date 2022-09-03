// VMTranslator.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stack>
#include "dirent.h"
using namespace std;

struct MACommand {
	string type;
	string segment;
	string value;
};

void getMACPart(MACommand &_lineData, string lineData) {
	int segmentStartIndex;
	int length = lineData.length();
	int segmentEndIndex =  length - 1;
	
	//get type
	if (lineData[3] == ' ') {
		_lineData.type = "pop";
		segmentStartIndex = 4;
	}
	else {
		_lineData.type = "push";
		segmentStartIndex = 5;
	}

	//get value
	while (lineData[segmentEndIndex] != ' ') --segmentEndIndex;
	_lineData.value = lineData.substr(segmentEndIndex + 1, length - segmentEndIndex - 1);
	--segmentEndIndex;
	
	//get segment;
	_lineData.segment = lineData.substr(segmentStartIndex, segmentEndIndex - segmentStartIndex + 1);
}

// Arithmatic and Logical process
void ALCommand(ofstream &outfile, string lineData, int &labelCounter) {
	

	// 1 agrument operator
	if (lineData == "neg") {
		outfile << "@SP\nA=M-1\nM=-M\n";
		return;
	}
	if (lineData == "not") {
		outfile << "@SP\nA=M-1\nM=!M\n";
		return;
	}
	
	// 2 agruments operator
	if (lineData == "add") {
		outfile << "@SP\nM=M-1\nA=M\nD=M\nA=A-1\nM=M+D\n";
		return;
	}
	if (lineData == "sub") {
		outfile << "@SP\nM=M-1\nA=M\nD=M\nA=A-1\nM=M-D\n";
		return;
	}
	if (lineData == "and") {
		outfile << "@SP\nM=M-1\nA=M\nD=M\nA=A-1\nM=M&D\n";
		return;
	}
	if (lineData == "or") {
		outfile << "@SP\nM=M-1\nA=M\nD=M\nA=A-1\nM=M|D\n";
		return;
	}
	if (lineData == "eq") {
		++labelCounter;
		outfile << "@SP\nM=M-1\nA=M\nD=M\nA=A-1\nM=M-D\nD=M\nM=0\n";

		//If (!eq), RAM[*SP-1]=0, else RAM[*SP-1]=-1
		outfile << "@EQ_YES." << labelCounter << "\nD;JEQ\n@EQ_DONE." << labelCounter << "\n0;JMP\n";
		outfile << "(EQ_YES." << labelCounter << ")\n@SP\nA=M-1\nM=-1\n@EQ_DONE." << labelCounter << "\n0;JMP\n";
		outfile << "(EQ_DONE." << labelCounter << ")\n";
		return;
	}
	if (lineData == "lt") {
		++labelCounter;
		outfile << "@SP\nM=M-1\nA=M\nD=M\nA=A-1\nM=M-D\nD=M\nM=0\n";

		//If (!lt), RAM[*SP-1]=0, else RAM[*SP-1]=-1
		outfile << "@LT_YES." << labelCounter << "\nD;JLT\n@LT_DONE." << labelCounter << "\n0;JMP\n";
		outfile << "(LT_YES." << labelCounter << ")\n@SP\nA=M-1\nM=-1\n@LT_DONE." << labelCounter << "\n0;JMP\n";
		outfile << "(LT_DONE." << labelCounter << ")\n";
		return;
	}
	if (lineData == "gt") {
		++labelCounter;
		outfile << "@SP\nM=M-1\nA=M\nD=M\nA=A-1\nM=M-D\nD=M\nM=0\n";

		//If (!gt), RAM[*SP-1]=0, else RAM[*SP-1]=-1
		outfile << "@GT_YES." << labelCounter << "\nD;JGT\n@GT_DONE." << labelCounter << "\n0;JMP\n";
		outfile << "(GT_YES." << labelCounter << ")\n@SP\nA=M-1\nM=-1\n@GT_DONE." << labelCounter << "\n0;JMP\n";
		outfile << "(GT_DONE." << labelCounter << ")\n";
		return;
	}
}

void pushProcess(ofstream &outfile, MACommand _lineData, string fileName) {

	if (_lineData.segment == "local") {
		outfile << "@" << _lineData.value << "\nD=A\n";
		outfile << "@LCL\nA=M\nA=A+D\nD=M\n@SP\nA=M\nM=D\n";
		outfile << "@SP\nM=M+1\n";
		return;
	}

	if (_lineData.segment == "argument") {
		outfile << "@" << _lineData.value << "\nD=A\n";
		outfile << "@ARG\nA=M\nA=A+D\nD=M\n@SP\nA=M\nM=D\n";
		outfile << "@SP\nM=M+1\n";
		return;
	}
	
	if (_lineData.segment == "this") {
		outfile << "@" << _lineData.value << "\nD=A\n";
		outfile << "@THIS\nA=M\nA=A+D\nD=M\n@SP\nA=M\nM=D\n";
		outfile << "@SP\nM=M+1\n";
		return;
	}

	if (_lineData.segment == "that") {
		outfile << "@" << _lineData.value << "\nD=A\n";
		outfile << "@THAT\nA=M\nA=A+D\nD=M\n@SP\nA=M\nM=D\n";
		outfile << "@SP\nM=M+1\n";
		return;
	}

	if (_lineData.segment == "constant") {
		outfile << "@" << _lineData.value << "\nD=A\n";
		outfile << "@SP\nA=M\nM=D\n";
		outfile << "@SP\nM=M+1\n";
		return;
	}

	if (_lineData.segment == "static") {
		outfile << "@" << fileName << "." << _lineData.value << "\nD=M\n";
		outfile << "@SP\nA=M\nM=D\n";
		outfile << "@SP\nM=M+1\n";
		return;
	}

	if (_lineData.segment == "temp") {
		outfile << "@" << _lineData.value << "\nD=A\n@5\nA=A+D\nD=M\n";
		outfile << "@SP\nA=M\nM=D\n";
		outfile << "@SP\nM=M+1\n";
		return;
	}

	//Else, _linData.segment == "pointer"
	if (_lineData.value == "0") {
		outfile << "@THIS\nD=M\n";
	}
	else {
		outfile << "@THAT\nD=M\n";
	}
	outfile << "@SP\nA=M\nM=D\n";
	outfile << "@SP\nM=M+1\n";
}

void popProcess(ofstream &outfile, MACommand _lineData, string fileName) {

	if (_lineData.segment == "local") {
		outfile << "@" << _lineData.value << "\nD=A\n";
		outfile << "@LCL\nA=M\nD=A+D\n";
		outfile << "@SP\nM=M-1\nA=M\nD=D+M\nA=D-M\nD=D-A\nM=D\n";
		return;
	}

	if (_lineData.segment == "argument") {
		outfile << "@" << _lineData.value << "\nD=A\n";
		outfile << "@ARG\nA=M\nD=A+D\n";
		outfile << "@SP\nM=M-1\nA=M\nD=D+M\nA=D-M\nD=D-A\nM=D\n";
		return;
	}

	if (_lineData.segment == "this") {
		outfile << "@" << _lineData.value << "\nD=A\n";
		outfile << "@THIS\nA=M\nD=A+D\n";
		outfile << "@SP\nM=M-1\nA=M\nD=D+M\nA=D-M\nD=D-A\nM=D\n";
		return;
	}

	if (_lineData.segment == "that") {
		outfile << "@" << _lineData.value << "\nD=A\n";
		outfile << "@THAT\nA=M\nD=A+D\n";
		outfile << "@SP\nM=M-1\nA=M\nD=D+M\nA=D-M\nD=D-A\nM=D\n";
		return;
	}

	if (_lineData.segment == "static") {
		outfile << "@SP\nM=M-1\nA=M\nD=M\n";
		outfile << "@" << fileName << "." << _lineData.value << "\nM=D\n";
		return;
	}

	if (_lineData.segment == "temp") {
		outfile << "@" << _lineData.value << "\nD=A\n";
		outfile << "@5\nD=A+D\n";
		outfile << "@SP\nM=M-1\nA=M\nD=D+M\nA=D-M\nD=D-A\nM=D\n";
		return;
	}

	//Else, _linData.segment == "pointer"
	outfile << "@SP\nM=M-1\nA=M\nD=M\n";
	if (_lineData.value == "0") {
		outfile << "@THIS\nM=D\n";
	}
	else {
		outfile << "@THAT\nM=D\n";
	}
}

// Memory access command
void MemoryAccessCommand(ofstream &outfile, string lineData, string fileName) {
	MACommand _lineData;
	getMACPart(_lineData, lineData);

	if (_lineData.type=="push") {
		pushProcess(outfile, _lineData, fileName);
	}
	else {
		popProcess(outfile, _lineData, fileName);
	}

}

void CallCommand(ofstream &outfile, string lineData) {

}

void commandPrint(ofstream &outfile, string lineData, int &labelCounter, string inFileName) {
	//Print command
	outfile << "//" << lineData << endl;

	//Arithmatic or logical process
	if (lineData.length() <= 3) {
		ALCommand(outfile, lineData, labelCounter);
	}
	else {
		//call command
		if (lineData[0]=='c') {

		}
		//Memory access command
		MemoryAccessCommand(outfile, lineData, inFileName);
	}
	outfile << endl;
}

void getVMFileinDir(string path, vector<string>& v) {
	// Populates v with all .vm files in the directory pointed at by path.
	// If it couldn't find any .vm files, it returns false.	
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(path.c_str())) != NULL) {
		// Scanning directory contents looking for .vm files...
		while ((ent = readdir(dir)) != NULL) {
			string entry_name = ent->d_name;
			if (entry_name.find(".vm") != string::npos) {
				string file_path = path;
				file_path.append(entry_name); // path/file.vm
				v.push_back(file_path);  // ... and adding them to vm_files.
			}
		}
		closedir(dir);
	}
}

void ignoreDoubleFSlash(unsigned int &lineLength, string &lineData) {
	if (lineLength) {
		for (unsigned int i = 0; i < lineLength - 1; ++i) {
			if (lineData[i] == '/' && lineData[i + 1] == '/') {
				if (i == 0 || i == 1) {
					lineData = "";
					lineLength = 0;
				}
				else {
					lineData = lineData.substr(0, i - 1);
					lineLength = i;
				}
				break;
			}
		}
	}
}

void ignoreWhiteSpace(unsigned int &lineLength, string &lineData) {
	if (lineLength) {

		//remove all the start space
		if (lineData[0] == ' ') {
			int pivot = 1;
			while (lineData[pivot] == ' ') ++pivot;
			lineData = lineData.substr(pivot, lineLength - pivot);
			lineLength -= pivot;
		}

		//revmove all the end space
		if (lineData[lineLength - 1] == ' ') {
			int pivot = lineLength - 2;
			while (lineData[pivot] == ' ') --pivot;
			lineData = lineData.substr(0, pivot);
			lineLength = pivot + 1;
		}
	}
}

void VMTranslator(string inFileName, string outFileName){
	ifstream infile(inFileName);
	ofstream outfile(outFileName);

	//if can't open the file
	if (!infile.is_open() || !outfile.is_open()) {
		cout << "ERROR: Can't open the file\n";
		if (infile.is_open()) infile.close();
		if (outfile.is_open()) outfile.close();
		return;
	}
	
	int fowardSlashIndex = inFileName.length() - 1;
	while (inFileName[fowardSlashIndex] != '/') --fowardSlashIndex;
	string fileName = inFileName.substr(fowardSlashIndex + 1, inFileName.length() - fowardSlashIndex - 1);

	//Line variable
	string lineData;
	unsigned int lineLength;
	int labelCounter = -1;

	//Line by line scan code
	while (getline(infile, lineData)) {
		lineLength = lineData.length();

		//Preprocess, if there is comment or space, ignore it
		ignoreDoubleFSlash(lineLength, lineData);
		ignoreWhiteSpace(lineLength, lineData);

		//if there is no empty line, process
		if (lineLength) commandPrint(outfile, lineData, labelCounter, fileName);
	}

	//End loop
	outfile << "(END)\n@END\n0;JMP\n";

	infile.close();
	outfile.close();
}

void addBoostrapCode(ofstream &outfile) {
	outfile << "//Boostrap code\n";
	outfile << "@256\nD=A\n@SP\nM=D\n";

	//blah blah blah
}

void labelProcess(string _lineData, string fileName, string currentFunction, ofstream &outfile) {

	//find " " in _lineData
	int spacePos;
	int lineLength = _lineData.length();
	for (int i = 0; i < lineLength; ++i) {
		if (_lineData[i] == ' ') {
			spacePos = i;
			break;
		}
	}

	string labelName = _lineData.substr(spacePos + 1, lineLength - 1);
	outfile << "(" << fileName << "." << currentFunction << "$" << labelName << ")\n";
}

void gotoProcess(string _lineData, ofstream &outfile) {
	int spacePos;
	int lineLength = _lineData.length();
	for (int i = 0; i < lineLength; ++i) {
		if (_lineData[i] == ' ') {
			spacePos = i;
			break;
		}
	}

	string destination = _lineData.substr(spacePos + 1, lineLength - 1);
	outfile << "@" << destination << "\n0;JMP\n";
}

void ifProcess(string _lineData, ofstream &outfile) {
	int spacePos;
	int lineLength = _lineData.length();
	for (int i = 0; i < lineLength; ++i) {
		if (_lineData[i] == ' ') {
			spacePos = i;
			break;
		}
	}

	string destination = _lineData.substr(spacePos + 1, lineLength - 1);

	outfile << "@SP\nM=M-1\nA=M\nD=M\n";
	outfile << "@" << destination << "D;JNE\n";
}

void functionProcess(string _lineData, ofstream &outfile, string &currentFunction, string fileName) {
	int firstSpace;
	int secondSpace;
	int lineLength = _lineData.length();

	for (int i = 0; i < lineLength; ++i) {
		if (_lineData[i] == ' ') {
			firstSpace = i;
			break;
		}
	}
	for (int i = firstSpace + 1; i < lineLength; ++i) {
		if (_lineData[i] == ' ') {
			secondSpace = i;
			break;
		}
	}

	string functionName = _lineData.substr(firstSpace + 1, secondSpace - 1);

}

void callProcess() {

}



void VMTranslator(string inFileName, string outFileName, vector<string> vmfile) {
	ifstream infile(inFileName);
	ofstream outfile(outFileName);

	//if can't open the file
	if (!infile.is_open() || !outfile.is_open()) {
		cout << "ERROR: Can't open the file\n";
		if (infile.is_open()) infile.close();
		if (outfile.is_open()) outfile.close();
		return;
	}

	int fowardSlashIndex = inFileName.length() - 1;
	while (inFileName[fowardSlashIndex] != '/') --fowardSlashIndex;
	string fileName = inFileName.substr(fowardSlashIndex + 1, inFileName.length() - fowardSlashIndex - 1);

	//Line variable
	string lineData;
	unsigned int lineLength;
	int labelCounter = -1;

	//Line by line scan code
	while (getline(infile, lineData)) {
		lineLength = lineData.length();

		//Preprocess, if there is comment or space, ignore it
		ignoreDoubleFSlash(lineLength, lineData);
		ignoreWhiteSpace(lineLength, lineData);

		//if there is no empty line, process
		if (lineLength) commandPrint(outfile, lineData, labelCounter, fileName);
	}

	//End loop
	outfile << "(END)\n@END\n0;JMP\n";

	infile.close();
	outfile.close();
}

int main(int argc, char* argv[]) {

	string input_filename = argv[2];

	// if the input is a .vm file
	if (argv[2][input_filename.length() - 2] == '.') {
		string output_filename = input_filename.substr(0, input_filename.length() - 2) + "asm";
		VMTranslator(input_filename, output_filename);
	}
	else {
		// the input is a directory
		string output_filename = input_filename.substr(0, input_filename.length()) + ".asm";
		if (input_filename.back() != '/') input_filename.append("/");
		vector<string> vmfile;
		getVMFileinDir(input_filename, vmfile);
	}
    return 0;
}

