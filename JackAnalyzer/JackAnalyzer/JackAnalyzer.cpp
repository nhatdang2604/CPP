#include "JackAnalyzer.h"

/* Constructor */
JackAnalyzer::JackAnalyzer(const string& file,const string& path) {
	this->inFile = file;
	this->outPath = path;
	compilationEngine = new CompilationEngine(inFile, getOutName());

	ofstream tok(inFile.substr(0, inFile.length() - 5) + "T.xml");
	tokenizer = new Tokenizer(inFile, tok);

	
	//print tokenize output
	if (tokenizer->hasMoreTokens()) tokenizer->advance();

	//print the header
	tok << "<tokens>" << endl;

	//If there are more tokens, keep translate
	while (tokenizer->hasMoreTokens()) {
		tokenizer->printToken();
		tokenizer->advance();
	}

	//print the footer
	tok << "</tokens>" << endl;	
	

}

/* From a file "file.hack", get the name "file.xml" */
string JackAnalyzer::getOutName() {
	return (inFile.substr(0, inFile.length() - 5) + ".xml");
}

/* Start translate*/
void JackAnalyzer::translate() {
	compilationEngine->compile();
}