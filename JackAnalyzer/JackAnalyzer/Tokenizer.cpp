#include "Tokenizer.h"
using namespace std;

/*Return false if there is no token*/
bool Tokenizer::hasMoreTokens() {
	return (!infileStream.eof() || currentLine!="");
}

/*Constructor*/
Tokenizer::Tokenizer(const string& _infile, ofstream& _outfile) {

	infileStream.open(_infile, ios::in);
	outfileStream = &_outfile;

	//If cannot open the input file and output file
	if (!infileStream.is_open() || !outfileStream->is_open()) {
		if (infileStream.is_open()) infileStream.close();
		if (outfileStream->is_open()) outfileStream->close();
	}

	//Get the first token
	//if (this->hasMoreTokens()) this->advance();

	/*
	//print the header
	cout << "<tokens>\n";

	//If there are more tokens, keep translate
	while (this->hasMoreTokens()) {
	this->advance();
	//this->tokenPrint();
	}

	//print the footer
	cout << "</tokens>\n";
	*/
}

/*Return the type of token*/
string Tokenizer::tokenType() {

	//If the token is a keyword
	for (int i = 0; i < NUMBER_OF_KEYWORD; ++i) {
		if (currentToken == this->keywords[i]) return "KEYWORD";
	}

	//If the token is a number
	if ('0' <= currentToken[0] && currentToken[0] <= '9') return "INT_CONST";

	//If the token is a symbol
	for (int i = 0; i < NUMBER_OF_SYMBOL; ++i) {
		if (currentToken[0] == this->symbols[i]) return "SYMBOL";
	}

	//If the token is a string
	if (currentToken[0] == '"') return "STRING_CONST";

	//Else => the token is identifier
	return "IDENTIFIER";
}


/*Gets the next token from the input and makes it the current token*/
void Tokenizer::advance() {
	string block;					//1 block = 1/more token which stick together, 2 block is seperate by a white space
	string token("");				//return the result of tokenType()

	

	//delete all the first space the old line
	while (currentLine[0] == ' ') {
		currentLine = currentLine.erase(0, 1);
	}

	//delete all the first tab
	while (currentLine[0] == '\t') {
		currentLine = currentLine.erase(0, 1);
	}

	/*
	while (currentLine == "") {
		if (!getline(infileStream, currentLine)) return;
		if (infileStream.eof()) return;

		//delete all the first space the new line
		while (currentLine[0] == ' ') {
			currentLine = currentLine.erase(0, 1);
		}

		//delete all the first tab
		while (currentLine[0] == '\t') {
			currentLine = currentLine.erase(0, 1);
		}
	}*/

	

	//ignore "//" and "/** */" and ""
	while ((currentLine == "") || (currentLine[0] == '/' && currentLine[1] == '/') || 
		(currentLine.length() > 2 && currentLine[0] == '/' && currentLine[1] == '*' && currentLine[2] == '*')) {

		//ignore "//" or ""
		if (currentLine == "" || (currentLine[0] == '/' && currentLine[1] == '/')) {
			//infileStream.seekg(-1 * signed(block.length()), ios_base::cur);

			//get the non-comment line
			if (!getline(infileStream, currentLine)) return;
			if (infileStream.eof()) return;

			//delete all the first space
			while (currentLine[0] == ' ') {
				currentLine = currentLine.erase(0, 1);
			}

			//delete all the first tab
			while (currentLine[0] == '\t') {
				currentLine = currentLine.erase(0, 1);
			}

		}
		else {

			//ignore "/** */"
			//infileStream.seekg(-1 * signed(block.length()), ios_base::cur);
			if (currentLine[currentLine.length() - 2] != '*' || currentLine[currentLine.length() - 1] != '/') {
				getline(infileStream, currentLine);
				while (currentLine[currentLine.length() - 2] != '*' || currentLine[currentLine.length() - 1] != '/') {
					getline(infileStream, currentLine);

				}
			}

			//get the non-comment line
			getline(infileStream, currentLine);

			//delete all the first space
			while (currentLine[0] == ' ') {
				currentLine = currentLine.erase(0, 1);
			}

			//delete all the first tab
			while (currentLine[0] == '\t') {
				currentLine = currentLine.erase(0, 1);
			}
		}
	}

	//get the first block
	block = getBlock(currentLine);

	//If the token is a keyword
	for (int i = 0; i < NUMBER_OF_KEYWORD; ++i) {
		if (block == this->keywords[i]) {
			this->currentToken = this->keywords[i];
			return;
		}
	}

	//If the token is a number
	if ('0' <= block[0] && block[0] <= '9') {
		token += block[0];
		int i = 0;
		while ('0' <= block[++i] && block[i] <= '9')
			token += block[i];
		this->currentToken = token;

		//infileStream.seekg(-1 * (signed(block.length()) - signed(token.length())), ios_base::cur);
		if (currentLine != "") currentLine = " " + currentLine;
		currentLine = block.substr(token.length(), block.length() - token.length()) + currentLine;

		return;
	}

	//If the token is a symbol
	for (int i = 0; i < NUMBER_OF_SYMBOL; ++i) {
		if (block[0] == this->symbols[i]) {
			if (block[0] == '<') this->currentToken = "&lt;";
			else if (block[0] == '>') this->currentToken = "&gt;";
			else if (block[0] == '&') this->currentToken = "&amp;";
			else this->currentToken = block[0];

			//infileStream.seekg(-1 * (signed(block.length()) - 1), ios_base::cur);
			if (currentLine != "") currentLine = " " + currentLine;
			currentLine = block.substr(1, block.length() - 1) + currentLine;

			return;
		}
	}
	//If the token is a string
	if (block[0] == '"') {

		//set the file pointer to the opened double quotes position

		//infileStream.seekg(-1 * (signed(block.length())), ios::cur);
		if (currentLine != "") currentLine = " " + currentLine;
		currentLine = block + currentLine;

		//get the line 
		block = currentLine;

		size_t closeDoubleQuotePos = block.find_last_of('"');		//the closed double quotes position

		//get the string, include 2 double quotes
		this->currentToken = block.substr(0, closeDoubleQuotePos + 1);
			
		int tokenLength = this->currentToken.length();
		for (int i = 1; i < tokenLength - 1; ++i) {

			//replace '&' by "&amp"
			if (this->currentToken[i] == '&') {
				this->currentToken.replace(i, 1, "&amp;");
				tokenLength += 3;
			}

			//replace '<' by "&lt"
			else if (this->currentToken[i] == '<') {
				this->currentToken.replace(i, 1, "&lt;");
				tokenLength += 2;		
			} 

			//replace '>' by "&gt"
			else if (this->currentToken[i] == '>') {
				this->currentToken.replace(i, 1, "&gt;");
				tokenLength += 2;
			
			} 
			//replace '"' by "&quot"
			else if (this->currentToken[i] == '"') {
				this->currentToken.replace(i, 1, "&quot;");
				tokenLength += 4;
			}	
		}

		//move the file pointer to the closed double quotes position + 1

		//infileStream.seekg(-1 * (signed(block.length()) - signed(closeDoubleQuotePos) + 1), ios_base::cur);
		if (currentLine != "") currentLine = " " + currentLine;
		currentLine = block.substr(closeDoubleQuotePos + 1, block.length() - closeDoubleQuotePos - 1);

		return;
	}

	//If it goes down here, the token is identifier
	int blockLength = block.length();
	token += block[0];
	for (int i = 1; i <= blockLength; ++i) {

		//Check if whole block is a identifier
		if (i == blockLength) {
			this->currentToken = token;
			return;
		}

		//Check if block[i] is a symbol
		for (int j = 0; j < NUMBER_OF_SYMBOL; ++j) {
			if (block[i] == this->symbols[j]) {
				this->currentToken = token;

				//infileStream.seekg(-1 * (signed(block.length()) - signed(token.length())), ios_base::cur);
				if (currentLine != "") currentLine = " " + currentLine;
				currentLine = block.substr(i, block.length() - i) + currentLine;

				return;
			}
		}
		token += block[i];
	}
}

/* print keyword*/
string Tokenizer::keyWord() {
	*outfileStream << "<keyword> " << currentToken << " </keyword>" << endl;
	return currentToken;
}

/* print symbol*/
char Tokenizer::symbol() {
	*outfileStream << "<symbol> " << currentToken[0] << " </symbol>" << endl;
	return currentToken[0];
}

/* print identifier*/
string Tokenizer::identifier() {
	*outfileStream << "<identifier> " << currentToken << " </identifier>" << endl;
	return currentToken;
}

/* print integer value*/
int Tokenizer::intVal() {
	*outfileStream << "<integerConstant> " << stoi(currentToken) << " </integerConstant>" << endl;
	return stoi(currentToken);
}

/* print string const */
string Tokenizer::stringVal() {
	string content = currentToken.substr(1, currentToken.length() - 2);
	*outfileStream << "<stringConstant> " << content << " </stringConstant>" << endl;
	return content;
}

//------------------------------------Extension------------------------------------

/* Print token of any type to screen*/
void Tokenizer::printToken() {
	string type = tokenType();

	//print keyword
	if (type == "KEYWORD") {
		string KEYWORD = keyWord();
		return;
	}

	//print symbol
	if (type == "SYMBOL") {
		char SYMBOL = symbol();
		return;
	}

	//print identifier
	if (type == "IDENTIFIER") {
		string IDENTIFIER = identifier();
		return;
	}

	//print integer constant
	if (type == "INT_CONST") {
		int INT_CONST = intVal();
		return;
	}

	//print string constant
	if (type == "STRING_CONST") {
		string STRING_CONST = stringVal();
		return;
	}
}

/* Get the current token*/
string Tokenizer::getCurrentToken() {
	return currentToken;
}

/* Get a block from a line*/
string Tokenizer::getBlock(string& currentLine) {
	string block;		//the result
	size_t spacePos;	//position of the first space / the newline 

	//while some first tokens are " "
	while (currentLine[0] == ' ') {
		currentLine = currentLine.erase(0, 1);
	}

	//delete all the first tab
	while (currentLine[0] == '\t') {
		currentLine = currentLine.erase(0, 1);
	}

	//if the current line is content only 1 block (block is a sequence of characters which don't have a space)
	if ((spacePos = currentLine.find_first_of(" ")) == string::npos) {
		block = currentLine;
		currentLine = "";
	}
	else {

		//if current line content more than 1 block
		block = currentLine.substr(0, currentLine.find_first_of(" "));
		currentLine = currentLine.erase(0, block.length() + 1);	//delete the first (sizeof(block) + sizeof(" ")) character
	}
	
	return block;
}