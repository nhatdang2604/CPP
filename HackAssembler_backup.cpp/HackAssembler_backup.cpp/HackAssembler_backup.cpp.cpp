// HackAssembler.cpp : Defines the entry point for the console application.
//

#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <fstream>
#include <iostream>
using namespace std;

#define INPUT "Pong.asm"
#define OUTPUT "Pong.hack"
#define MAX_CHARACTER 32767

struct Row {
	string symbolName;
	int value;
};

struct SymbolTable {
	Row *row;
	int numberOfRow;
	int ramAvailableIndex;
};

void initST(SymbolTable &table) {
	table.row = new Row[MAX_CHARACTER];
	table.numberOfRow = 23;
	table.ramAvailableIndex = 16;
	table.row[0].symbolName = "SP"; table.row[0].value = 0;
	table.row[1].symbolName = "LCL"; table.row[1].value = 1;
	table.row[2].symbolName = "ARG"; table.row[2].value = 2;
	table.row[3].symbolName = "THIS"; table.row[3].value = 3;
	table.row[4].symbolName = "THAT"; table.row[4].value = 4;
	table.row[5].symbolName = "R0"; table.row[5].value = 0;
	table.row[6].symbolName = "R1"; table.row[6].value = 1;
	table.row[7].symbolName = "R2"; table.row[7].value = 2;
	table.row[8].symbolName = "R3"; table.row[8].value = 3;
	table.row[9].symbolName = "R4"; table.row[9].value = 4;
	table.row[10].symbolName = "R5"; table.row[10].value = 5;
	table.row[11].symbolName = "R6"; table.row[11].value = 6;
	table.row[12].symbolName = "R7"; table.row[12].value = 7;
	table.row[13].symbolName = "R8"; table.row[13].value = 8;
	table.row[14].symbolName = "R9"; table.row[14].value = 9;
	table.row[15].symbolName = "R10"; table.row[15].value = 10;
	table.row[16].symbolName = "R11"; table.row[16].value = 11;
	table.row[17].symbolName = "R12"; table.row[17].value = 12;
	table.row[18].symbolName = "R13"; table.row[18].value = 13;
	table.row[19].symbolName = "R14"; table.row[19].value = 14;
	table.row[20].symbolName = "R15"; table.row[20].value = 15;
	table.row[21].symbolName = "SCREEN"; table.row[21].value = 16384;
	table.row[22].symbolName = "KBD"; table.row[22].value = 24576;
}

void addLabel(SymbolTable &table, string label, int line_index) {
	//table.row = new Row[++table.numberOfRow];
	++table.numberOfRow;
	table.row[table.numberOfRow - 1].symbolName = label;
	table.row[table.numberOfRow - 1].value = line_index + 1;
}

void addLabel(SymbolTable &table, string label) {
	//table.row = new Row[++table.numberOfRow];
	++table.numberOfRow;
	table.row[table.numberOfRow - 1].symbolName = label;
	table.row[table.numberOfRow - 1].value = table.ramAvailableIndex;
	++table.ramAvailableIndex;
}

void releaseST(SymbolTable &table) {
	delete[]table.row;
}

//return the index label if there are already in symbol table, else return -1
int findLabel(string line_data, SymbolTable table) {
	for (int i = 0; i < table.numberOfRow; ++i) if (line_data == table.row[i].symbolName) return i;
	return -1;
}

//modify @stringName -> @value (value is a decimal number in string)
void modify(string &line_data, SymbolTable &table) {

	string value;
	string stringName = line_data.substr(1, line_data.length() - 1);
	int index = findLabel(stringName, table);

	//if stringName is already in the symbolic table
	if (index >= 0) value = to_string(table.row[index].value);
	else {
		addLabel(table, stringName);
		value = to_string(table.ramAvailableIndex - 1);
	}
	line_data = "@" + value;
}

string String2AInstruction_L(string input) {
	string result = "0000000000000000";
	int digit = 1;
	int value = 0; // decimal form of input

				   //Convert input into decimal number
	for (int i = input.length() - 1; i >= 1; --i) {
		value += digit*((int)input[i] - (int)'0');
		digit *= 10;
	}

	digit = 15; //index of most right bit of result

				//Convert value into string binary form
	while (value > 0) {
		result[digit] = char(value % 2 + (int)'0');
		value = value / 2;
		--digit;
	}
	return result;
}

string String2AInstruction_L(int input) {
	string result = "0000000000000000";
	int digit = 15;  //index of most right bit of result

					 //Convert value into string binary form
	while (input > 0) {
		result[digit] = char(input % 2 + (int)'0');
		input = input / 2;
		--digit;
	}
	return result;
}

string AInstruction_L(string line_data, SymbolTable &table) {
	if (line_data[0] != '@') return NULL; //if it is not A instruction, exit
	if (line_data[1] > '9' || line_data[1] < '0') modify(line_data, table);
	return String2AInstruction_L(line_data);
}

void CInstructionCombination(string &line_data, string comp, string dest, string jump) {

	for (int i = 3; i <= 9; ++i) line_data[i] = comp[i - 3];
	for (int i = 10; i <= 12; ++i) line_data[i] = dest[i - 10];
	for (int i = 13; i <= 15; ++i) line_data[i] = jump[i - 13];
}

void DestProcess(string &dest, string line_data, int equal_sign_index) {
	string destString = line_data.substr(0, equal_sign_index);
	int pivot = 0;
	for (int i = 0; i < 3; ++i) {
		if (pivot == equal_sign_index) break;
		char character = destString[pivot];
		if (character == 'M') dest[2] = '1';
		else if (character == 'D') dest[1] = '1';
		else dest[0] = '1';
		++pivot;
	}
}

void CompProcess(string &comp, string line_data, int equal_sign_index, int semicolon_index) {
	int comp_end_index = semicolon_index - 1;
	int comp_start_index = equal_sign_index + 1;
	if (semicolon_index == -1) comp_end_index = line_data.length() - 1; //If there is no semicolon
	string compString = line_data.substr(comp_start_index, comp_end_index - comp_start_index + 1);

	//Brute force :(((
	if (compString == "0") comp = "0101010";
	else if (compString == "1") comp = "0111111";
	else if (compString == "-1") comp = "0111010";
	else if (compString == "D") comp = "0001100";
	else if (compString == "A") comp = "0110000";
	else if (compString == "M") comp = "1110000";
	else if (compString == "!D") comp = "0001101";
	else if (compString == "!A") comp = "0110001";
	else if (compString == "!M") comp = "1110001";
	else if (compString == "-D") comp = "0001111";
	else if (compString == "-A") comp = "0110011";
	else if (compString == "-M") comp = "1110011";
	else if (compString == "D+1") comp = "0011111";
	else if (compString == "A+1") comp = "0110111";
	else if (compString == "M+1") comp = "1110111";
	else if (compString == "D-1") comp = "0001110";
	else if (compString == "A-1") comp = "0110010";
	else if (compString == "M-1") comp = "1110010";
	else if (compString == "D+A") comp = "0000010";
	else if (compString == "D+M") comp = "1000010";
	else if (compString == "D-A") comp = "0010011";
	else if (compString == "D-M") comp = "1010011";
	else if (compString == "A-D") comp = "0000111";
	else if (compString == "M-D") comp = "1000111";
	else if (compString == "D&A") comp = "0000000";
	else if (compString == "D&M") comp = "1000000";
	else if (compString == "D|A") comp = "0010101";
	else if (compString == "D|M") comp = "1010101";
}

void JumpProcess(string &jump, string line_data, int semicolon_index) {
	if (semicolon_index == -1) return;
	int jump_start_index = semicolon_index + 1;
	string jumpString = line_data.substr(jump_start_index + 1, 2);

	//Brute force :(((
	if (jumpString == "GT") jump = "001";
	else if (jumpString == "EQ") jump = "010";
	else if (jumpString == "GE") jump = "011";
	else if (jumpString == "LT") jump = "100";
	else if (jumpString == "NE") jump = "101";
	else if (jumpString == "LE") jump = "110";
	else if (jumpString == "MP") jump = "111";
}

string CInstruction(string line_data) {
	if (line_data[0] == '@') return NULL;
	string result = "111accccccdddjjj";
	string comp = "0000000";
	string dest = "000";
	string jump = "000";

	//find comp, dest and jump part
	unsigned int lineLength = line_data.length();
	int	equal_sign_index = -1;
	int semicolon_index = -1;
	for (unsigned int i = 0; i < lineLength; ++i) {
		char character = line_data[i];
		if (character == '=') equal_sign_index = i;
		else if (character == ';') semicolon_index = i;
	}

	if (equal_sign_index != -1) DestProcess(dest, line_data, equal_sign_index);
	CompProcess(comp, line_data, equal_sign_index, semicolon_index);
	if (semicolon_index != -1) JumpProcess(jump, line_data, semicolon_index);

	//combination comp, dest, jump into result
	CInstructionCombination(result, comp, dest, jump);
	return result;
}

void InstructionPrint(ofstream &outfile, string infile_line_data, SymbolTable &table) {
	if (infile_line_data[0] == '@') outfile << AInstruction_L(infile_line_data, table) << endl;
	else outfile << CInstruction(infile_line_data) << endl;
}

void IOProcessing() {

	//IO variable
	ifstream infile(INPUT);
	ofstream outfile(OUTPUT);

	//Symbol table variable
	SymbolTable table;
	initST(table);

	//If can not open both input file and output file, exit
	if (!infile.is_open() || !outfile.is_open() || !table.row) {
		cout << "Mo file hoac thiet lap Symbol Table that bai!\n";
		system("PAUSE");
		if (table.row) delete[]table.row;
		if (infile.is_open()) infile.close();
		if (outfile.is_open()) outfile.close();
		return;
	}

	//Line variable
	string infile_line_data;
	char firstChar = '[';
	unsigned int lineIndex = -1;
	unsigned int lineLength;
	bool secondScanYet = false;

	//Line by line process first scan
	while (getline(infile, infile_line_data)) {
		++lineIndex;
		//Preprocess, if there is command...
		lineLength = infile_line_data.length();
		if (lineLength) {
			for (unsigned int i = 0; i < lineLength - 1; ++i) {
				if (infile_line_data[i] == '/' && infile_line_data[i + 1] == '/') {
					if (i == 0 || i == 1) infile_line_data = "";
					else infile_line_data = infile_line_data.substr(0, i - 1);
					lineLength = infile_line_data.length();
					break;
				}
			}
		}
		//...or space, ignore it
		if (lineLength) {
			for (unsigned int i = 0; i < lineLength; ++i) {
				if (infile_line_data[i] == ' ') {
					if (i == 0) {
						infile_line_data = infile_line_data.substr(i + 1, lineLength - 1);
						--i;
						--lineLength;
					}
					else {
						infile_line_data = infile_line_data.substr(0, i);
						lineLength = i;
						break;
					}
				}
			}
		}

		//if there is no empty line, process
		if (lineLength) firstChar = infile_line_data[0];
		else --lineIndex;
		if (!secondScanYet && firstChar == '(') {
			--lineIndex;
			string labelName = infile_line_data.substr(1, lineLength - 2);
			addLabel(table, labelName, lineIndex);
		}
	}

	//Finsh the first scan, prepare for the second
	secondScanYet = true;
	infile.clear();
	infile.seekg(0, ios::beg);
	lineIndex = -1;
	firstChar = ']';

	//Line by line second scan
	while (getline(infile, infile_line_data)) {
		++lineIndex;
		//Preprocess, if there is command...
		lineLength = infile_line_data.length();
		if (lineLength) {
			for (unsigned int i = 0; i < lineLength - 1; ++i) {
				if (infile_line_data[i] == '/' && infile_line_data[i + 1] == '/') {
					if (i == 0 || i == 1) infile_line_data = "";
					else infile_line_data = infile_line_data.substr(0, i - 1);
					lineLength = infile_line_data.length();
					break;
				}
			}
		}
		//...or space, ignore it
		if (lineLength) {
			for (unsigned int i = 0; i < lineLength; ++i) {
				if (infile_line_data[i] == ' ') {
					if (i == 0) {
						infile_line_data = infile_line_data.substr(i + 1, lineLength - 1);
						--i;
						--lineLength;
					}
					else {
						infile_line_data = infile_line_data.substr(0, i);
						lineLength = i;
						break;
					}
				}
			}
		}

		//if there is no empty line, process
		
		if (lineLength && infile_line_data[0] != '(') InstructionPrint(outfile, infile_line_data, table);
	}

	//relase symbol table and close file 
	infile.close();
	outfile.close();
	releaseST(table);
}

int main()
{
	IOProcessing();
	return 0;
}

