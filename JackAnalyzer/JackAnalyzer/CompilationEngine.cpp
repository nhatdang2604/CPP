#include "CompilationEngine.h"

/* Constructor */
CompilationEngine::CompilationEngine(const string& _infile, const string& _outfile) {

	//open the input and output file
	infileStream.open(_infile, ios::in);
	outfileStream.open(_outfile, ios::out);

	//check if the input or output file is not open
	if (!infileStream.is_open() || !outfileStream.is_open()) {
		if (infileStream.is_open()) infileStream.close();
		if (outfileStream.is_open()) outfileStream.close();
	}

	//create tokenizer
	tokenizer = new Tokenizer(_infile, outfileStream);


	/*
	//get the first token
	tokenizer->advance();

	//compile a/more class
	while (tokenizer->getCurrentToken() == "class") compileClass()
	*/
}

/*------------------------------------Program structure------------------------------------*/

/* Compile a class*/
void CompilationEngine::compileClass() {

	//if the first keyword is not fit, return
	if (tokenizer->getCurrentToken() != "class") return;

	//print header
	printTab();
	outfileStream << "<class>" << endl;

	//increase the tab number;
	++tabNumber;

	//print "class"
	printTab();
	tokenizer->printToken();

	//print the class name 
	tokenizer->advance();
	//compileIdentifier("className");
	printTab();
	tokenizer->printToken();
	
	//print the first '{' 
	tokenizer->advance();
	printTab();
	tokenizer->printToken();

	//get the next token
	tokenizer->advance();

	//Process until we got the final '}'
	while (tokenizer->getCurrentToken() != "}") {

		//check if it is gonna a class variable declaration
		if (tokenizer->getCurrentToken() == "static" || tokenizer->getCurrentToken() == "field")
			compileClassVarDec();

		//else, it is gonna a subrountine
		else compileSubroutine();

	}

	//print the final '}'
	printTab();
	tokenizer->printToken();

	//decrease the tab number
	--tabNumber;

	//print footer
	printTab();
	outfileStream << "</class>" << endl;

	//get the next token
	tokenizer->advance();
}

/*Compile a class variable declaration*/
void CompilationEngine::compileClassVarDec() {

	//check if it is not a class variable declaration
	if (tokenizer->getCurrentToken() != "static" && tokenizer->getCurrentToken() != "field") return;

	//print the header
	printTab();
	outfileStream << "<classVarDec>" << endl;

	//increase tab number
	++tabNumber;

	//print "static"/"field"
	//tokenizer->advance();
	printTab();
	tokenizer->printToken();

	//print type
	tokenizer->advance();
	//compileType();
	printTab();
	tokenizer->printToken();

	//print the (first) variable name
	tokenizer->advance();
	//compileIdentifier("varName");
	printTab();
	tokenizer->printToken();

	//get the next token
	tokenizer->advance();

	//while get more var name
	while (tokenizer->getCurrentToken() == ",") {
		
		//print the ","
		printTab();
		tokenizer->printToken();

		//print the next var name
		tokenizer->advance();
		//compileIdentifier("varName");
		printTab();
		tokenizer->printToken();

		//get the next token
		tokenizer->advance();
	}

	//print the ';'
	printTab();
	tokenizer->printToken();

	//decrease tab number
	--tabNumber;

	//print the footer
	printTab();
	outfileStream << "</classVarDec>" << endl;

	//get the next token
	tokenizer->advance();
}

/* Compile parameter list*/
void CompilationEngine::compileParameterList() {

	/*Print header*/
	printTab();
	outfileStream << "<parameterList>" << endl;

	//increase tab number
	++tabNumber;

	//if the parameter is not null
	if (tokenizer->getCurrentToken() != ")") {

		//print type
		//tokenizer->advance();
		//compileType();
		printTab();
		tokenizer->printToken();

		//print varName
		tokenizer->advance();
		//compileIdentifier("varName");
		printTab();
		tokenizer->printToken();

		//check if there are parameters or a single parameter
		tokenizer->advance();
		while (tokenizer->getCurrentToken() == ",") {

			//print ','
			printTab();
			tokenizer->printToken();

			//print type
			tokenizer->advance();
			printTab();
			tokenizer->printToken();

			//get the next var name
			tokenizer->advance();
			//compileIdentifier("varName");
			printTab();
			tokenizer->printToken();

			//get the next token
			tokenizer->advance();
		}
	}

	//decrease tab number
	--tabNumber;

	/*Print footer*/
	printTab();
	outfileStream << "</parameterList>" << endl;
}

/* Compile a subroutine */
void CompilationEngine::compileSubroutine() {
	
	//if the keyword is not fit, return;
	if (tokenizer->getCurrentToken() != "constructor" &&
		tokenizer->getCurrentToken() != "function" &&
		tokenizer->getCurrentToken() != "method")	return;

	//print header
	printTab();
	outfileStream << "<subroutineDec>" << endl;

	//increase tab number
	++tabNumber;

	//print "constructor"/"function"/"method"
	//tokenizer->advance();
	printTab();
	tokenizer->printToken();

	//print "void"/type
	tokenizer->advance();
	printTab();
	tokenizer->printToken();
	

	//print subroutine name
	tokenizer->advance();
	//compileIdentifier("subroutineName");
	printTab();
	tokenizer->printToken();

	//print '('
	tokenizer->advance();
	printTab();
	tokenizer->printToken();

	//decision parameter list empty or not
	tokenizer->advance();
	compileParameterList();
	
	//print ')'
	printTab();
	tokenizer->printToken();

	//print subroutine body
	tokenizer->advance();
	compileSubroutineBody();

	//decrease tab number
	--tabNumber;

	//print footer
	printTab();
	outfileStream << "</subroutineDec>" << endl;

}

/* Compile variable declaration */
void CompilationEngine::compileVarDec() {

	//if the format is not fit
	if (tokenizer->getCurrentToken() != "var") return;

	//print header
	printTab();
	outfileStream << "<varDec>" << endl;

	//increase tab number
	++tabNumber;

	//print "var"
	printTab();
	tokenizer->printToken();

	//print type
	tokenizer->advance();
	//compileType();
	printTab();
	tokenizer->printToken();

	//print the first variable name
	tokenizer->advance();
	//compileIdentifier("varName");
	printTab();
	tokenizer->printToken();

	//check if there are more variable names
	tokenizer->advance();
	while (tokenizer->getCurrentToken() == ",") {

		//print the ','
		printTab();
		tokenizer->printToken();

		//print the variable name
		tokenizer->advance();
		//compileIdentifier("varName");
		printTab();
		tokenizer->printToken();
		tokenizer->advance();
	}

	//print the ';'
	printTab();
	tokenizer->printToken();

	//decrease tab number
	--tabNumber;

	//print footer
	printTab();
	outfileStream << "</varDec>" << endl;

	//get the next token
	tokenizer->advance();
}

/*------------------------------------Statements------------------------------------*/

/* Compile statements*/
void CompilationEngine::compileStatements() {

	//if the format is not fitted
	if (tokenizer->getCurrentToken() != "let" &&
		tokenizer->getCurrentToken() != "if" && tokenizer->getCurrentToken() != "while" &&
		tokenizer->getCurrentToken() != "do" && tokenizer->getCurrentToken() != "return")
		return;

	//print header
	printTab();
	outfileStream << "<statements>" << endl;

	//increase tab number
	++tabNumber;

	while (tokenizer->getCurrentToken() == "let" ||
		tokenizer->getCurrentToken() == "if" || 
		tokenizer->getCurrentToken() == "while" ||
		tokenizer->getCurrentToken() == "do" || 
		tokenizer->getCurrentToken() == "return")
	{
		if (tokenizer->getCurrentToken() == "let") {
			compileLet();
		}
		else 
			if (tokenizer->getCurrentToken() == "if") {
				compileIf();
			}
			else 
				if (tokenizer->getCurrentToken() == "while") {
					compileWhile();
				}
				else 
					if (tokenizer->getCurrentToken() == "do") {
						compileDo();
					}
					else compileReturn();
	}
	//decrease tab number
	--tabNumber;

	//print footer
	printTab();
	outfileStream << "</statements>" << endl;
}

/* Compile the let statement*/
void CompilationEngine::compileLet() {

	//check if the format is not fit
	if (tokenizer->getCurrentToken() != "let") return;

	//print header
	printTab();
	outfileStream << "<letStatement>" << endl;

	//increase the tab number
	++tabNumber;

	//print "let"
	printTab();
	tokenizer->printToken();

	//print variable name
	tokenizer->advance();
	//compileIdentifier("varName");
	printTab();
	tokenizer->printToken();

	//decide if the variable is a element of an array or not
	//if yes, it is an element of an array
	tokenizer->advance();
	if (tokenizer->getCurrentToken() == "[") {

		//print '['
		printTab();
		tokenizer->printToken();

		//print the epxression
		tokenizer->advance();
		compileExpression();

		//print ']'
		printTab();
		tokenizer->printToken();

		//get the next token
		tokenizer->advance();
	}
	
	//in both case, in this line, the token must be '='
	
	//print '='
	printTab();
	tokenizer->printToken();

	//print the expression
	tokenizer->advance();
	compileExpression();

	//print the ';'
	printTab();
	tokenizer->printToken();

	//decrease the tab number
	--tabNumber;

	//print footer
	printTab();
	outfileStream << "</letStatement>" << endl;

	//get the next token
	tokenizer->advance();
}

/*Compile the if statement*/
void CompilationEngine::compileIf() {

	//if the format is not fit, return;
	if (tokenizer->getCurrentToken() != "if") return;

	//print the header
	printTab();
	outfileStream << "<ifStatement>" << endl;

	//increase tab number
	++tabNumber;

	//print "if"
	printTab();
	tokenizer->printToken();

	//print '('
	tokenizer->advance();
	printTab();
	tokenizer->printToken();

	//print the expression
	tokenizer->advance();
	compileExpression();

	//print ')'
	printTab();
	tokenizer->printToken();

	//print '{'
	tokenizer->advance();
	printTab();
	tokenizer->printToken();

	//print yes statements
	tokenizer->advance();
	compileStatements();

	//print '}'
	printTab();
	tokenizer->printToken();

	//decide if there is an "else"
	tokenizer->advance();
	//if yes, there is an "else"
	if (tokenizer->getCurrentToken() == "else") {

		//print else
		printTab();
		tokenizer->printToken();

		//print '{'
		tokenizer->advance();
		printTab();
		tokenizer->printToken();

		//print statements
		tokenizer->advance();
		compileStatements();

		//print '}'
		printTab();
		tokenizer->printToken();

		//get the next token
		tokenizer->advance();
	}

	//decrease tab number
	--tabNumber;

	//print the footer
	printTab();
	outfileStream << "</ifStatement>" << endl;

	//get the next token? (No need, this state different than other compilation)
	//because we have to decide if there is an "else" or not, both of 2 case are
	//already get the next token
}

/* Compile the while statement*/
void CompilationEngine::compileWhile() {

	//if the format is not fit, return
	if (tokenizer->getCurrentToken() != "while") return;

	//print header
	printTab();
	outfileStream << "<whileStatement>" << endl;

	//increase tab number
	++tabNumber;

	//print "while"
	printTab();
	tokenizer->printToken();

	//print '('
	tokenizer->advance();
	printTab();
	tokenizer->printToken();

	//print the expression
	tokenizer->advance();
	compileExpression();

	//print ')'
	printTab();
	tokenizer->printToken();

	//print '{'
	tokenizer->advance();
	printTab();
	tokenizer->printToken();

	//print the statements
	tokenizer->advance();
	compileStatements();

	//print '}'
	printTab();
	tokenizer->printToken();

	//decrease tab number
	--tabNumber;

	//print footer
	printTab();
	outfileStream << "</whileStatement>" << endl;

	//get the next token
	tokenizer->advance();
}

/* Compile the do statement */
void CompilationEngine::compileDo() {

	//if the format is not fit, return;
	if (tokenizer->getCurrentToken() != "do") return;

	//print header
	printTab();
	outfileStream << "<doStatement>" << endl;

	//increase tab number
	++tabNumber;

	//print "do"
	printTab();
	tokenizer->printToken();

	//print subroutine call
	tokenizer->advance();
	//compileTerm();
	compileSubroutineCall();

	//print ';'
	printTab();
	tokenizer->printToken();

	//decrease tab number
	--tabNumber;

	//print footer
	printTab();
	outfileStream << "</doStatement>" << endl;

	//get the next token
	tokenizer->advance();

}

/*Compile the return statement*/
void CompilationEngine::compileReturn() {

	//if the format is not fit, return
	if (tokenizer->getCurrentToken() != "return") return;

	//print header
	printTab();
	outfileStream << "<returnStatement>" << endl;

	//inrcrease tab number
	++tabNumber;

	//print "return"
	printTab();
	tokenizer->printToken();

	//decide if there is an expression
	tokenizer->advance();
	//if the current token is not ";" => there is an expression
	if (tokenizer->getCurrentToken() != ";") {
		compileExpression();

	}
	
	//print ";"
	printTab();
	tokenizer->printToken();

	//decrease tab number
	--tabNumber;

	//print footer
	printTab();
	outfileStream << "</returnStatement>" << endl;

	//get the next token
	tokenizer->advance();
}

/*------------------------------------Expressions------------------------------------*/

/*Compile term*/
void CompilationEngine::compileTerm() {

	//print header
	printTab();
	outfileStream << "<term>" << endl;

	//increase tab number
	++tabNumber;


	//if the first token is unary operator => unaryOp term case
	if (tokenizer->getCurrentToken() == "-" || tokenizer->getCurrentToken() == "~") {

		//print the unary operator
		printTab();
		tokenizer->printToken();

		//print the term
		tokenizer->advance();
		compileTerm();
	}
	else {

		//if the first token is '(' => the case is: '(' expression ')'
		if (tokenizer->getCurrentToken() == "(") {

			//print '('
			printTab();
			tokenizer->printToken();

			//print expression
			tokenizer->advance();
			compileExpression();

			//print ')'
			printTab();
			tokenizer->printToken();

			//get the next token
			tokenizer->advance();
		}
		else {

			//print the first (or only) token
			printTab();
			tokenizer->printToken();

			//check if there are more tokens
			tokenizer->advance();

			//if the case is varName'['expression'] => an array element
			if (tokenizer->getCurrentToken() == "[") {

				//print '['
				printTab();
				tokenizer->printToken();

				//print expression
				tokenizer->advance();
				compileExpression();

				//print ']'
				printTab();
				tokenizer->printToken();

				//get the next token
				tokenizer->advance();
			}
			else {

				//if the case is subroutineName'(' expressionList ')'
				if (tokenizer->getCurrentToken() == "(") {

					//we already print subroutine name

					//print '('
					printTab();
					tokenizer->printToken();

					//print expression list
					tokenizer->advance();
					compileExpressionList();

					//print ')'
					printTab();
					tokenizer->printToken();

					//get the next token
					tokenizer->advance();
				}
				else {

					//if the case is (className | varName)'.'subroutineName'('expressionList')'
					if (tokenizer->getCurrentToken() == ".") {

						//we already print (className | varName)

						//print '.'
						printTab();
						tokenizer->printToken();

						//print subroutineName
						tokenizer->advance();
						printTab();
						tokenizer->printToken();

						//print '('
						tokenizer->advance();
						printTab();
						tokenizer->printToken();

						//print expressionList
						tokenizer->advance();
						compileExpressionList();

						//print ')'
						printTab();
						tokenizer->printToken();

						//get the next token
						tokenizer->advance();
					}
				}
			}
		}
	}

	//decrease tab number
	--tabNumber;

	//print footer
	printTab();
	outfileStream << "</term>" << endl;

	//get the next token? (No need, this state different than other compilation)
	//Every case is implemented to already get the next token
}

/*compile expression*/
void CompilationEngine::compileExpression() {

	//the current token must be a term
	
	//print header
	printTab();
	outfileStream << "<expression>" << endl;

	//increase tab number
	++tabNumber;

	//print the first (or only) term
	compileTerm();

	//decide if there is an operator or not
	while (tokenizer->getCurrentToken() == "+" || tokenizer->getCurrentToken() == "-"
		|| tokenizer->getCurrentToken() == "*" || tokenizer->getCurrentToken() == "/"
		|| tokenizer->getCurrentToken() == "&amp;" || tokenizer->getCurrentToken() == "|"
		|| tokenizer->getCurrentToken() == "&lt;" || tokenizer->getCurrentToken() == "&gt;"
		|| tokenizer->getCurrentToken() == "=") {

		//print the operator
		printTab();
		tokenizer->printToken();

		//print the term
		tokenizer->advance();
		compileTerm();
	}

	//decrease tab number
	--tabNumber;

	//print footer
	printTab();
	outfileStream << "</expression>" << endl;

	//get the next token? 
	//No need, because we have got the next token in the loop (if the loop doesn't run, it already gets before the loop)
}

/*Compile expression list*/
void CompilationEngine::compileExpressionList() {

	//print header
	printTab();
	outfileStream << "<expressionList>" << endl;

	//increase tab number
	++tabNumber;

	//if the current token is ')' => the expression list is null
	if (tokenizer->getCurrentToken() != ")") {
		//the current token here must be expression
		compileExpression();

		//decide if there are more expression
		//if the current token is an "," => more expression
		while (tokenizer->getCurrentToken() == ",") {

			//print ","
			printTab();
			tokenizer->printToken();

			//print expression
			tokenizer->advance();
			compileExpression();
		}
	}
	//decrease tab number
	--tabNumber;

	//print footer
	printTab();
	outfileStream << "</expressionList>" << endl;

	//get the next token? 
	//No need, because we have got the next token in the loop (if the loop doesn't run, it already gets before the loop)
}

/*------------------------------------Extension------------------------------------*/
void CompilationEngine::printTab() {
	for (int i = 0; i < tabNumber; ++i)	outfileStream << " ";
}

/*void CompilationEngine::compileType() {
	printTab();
	outfileStream << "<type>\n";
	++tabNumber;
	//if type is int, char or boolean
	if (tokenizer->getCurrentToken == "int" ||
		tokenizer->getCurrentToken() == "char" ||
		tokenizer->getCurrentToken() == "boolean") {
		printTab();
		tokenizer->printToken();
		tokenizer->advance();
	}
	else {
		//type is class name
		compileIdentifier("className");
	}
	--tabNumber;
	printTab();
	outfileStream << "</type>\n";
}*/

/*void CompilationEngine::compileIdentifier(const string& content) {
	printTab();
	outfileStream << "<" << content << ">\n";
	++tabNumber;
	printTab();
	tokenizer->printToken();
	--tabNumber;
	printTab();
	outfileStream << "</" << content << ">\n";

	//get the next token
	tokenizer->advance();
}*/

void CompilationEngine::compileSubroutineBody() {

	//if the format is not fit
	if (tokenizer->getCurrentToken() != "{") return;

	//print header
	printTab();
	outfileStream << "<subroutineBody>" << endl;

	//increase tab number
	++tabNumber;

	//print the '{'
	printTab();
	tokenizer->printToken();

	//decision of there is a variable declaration(s) or not
	tokenizer->advance();
	//while the current token is "var" => there is a variable declaration
	while (tokenizer->getCurrentToken() == "var") {
		compileVarDec();
	}

	//compile statements
	compileStatements();

	//print the '}'
	printTab();
	tokenizer->printToken();

	//decrease tab number
	--tabNumber;

	//print footer
	printTab();
	outfileStream << "</subroutineBody>" <<endl;

	//get the next token
	tokenizer->advance();
}

/*Compile the call of subroutine */
void CompilationEngine::compileSubroutineCall() {

	/*print header
	printTab();
	outfileStream << "<subroutineCall>\n";

	//increase tab number
	++tabNumber;*/

	//print the first identifier
	printTab();
	tokenizer->printToken();

	//decide if the next token is '(' or '.'
	tokenizer->advance();
	//if it is '(' => it is subroutineName '(' expressionList ')'
	if (tokenizer->getCurrentToken() == "(") {

		//print '('
		printTab();
		tokenizer->printToken();

		//print the expressionList
		tokenizer->advance();
		compileExpressionList();

		//print the ')'
		printTab();
		tokenizer->printToken();

	}
	else {

		//else => the case is (className|varName)'.'subroutineName'('expressionList')'
	
		//print '.'
		printTab();
		tokenizer->printToken();

		//print subroutineName
		tokenizer->advance();
		printTab();
		tokenizer->printToken();

		//print '('
		tokenizer->advance();
		printTab();
		tokenizer->printToken();

		//print expression list
		tokenizer->advance();
		compileExpressionList();

		//print ')'
		printTab();
		tokenizer->printToken();
	}




	/*//decrease tab number
	--tabNumber;

	//print footer
	printTab();
	outfileStream << "</subroutineCall>\n";*/

	//get the next token
	tokenizer->advance();
}

void CompilationEngine::compile() {
	while (tokenizer->hasMoreTokens()) {
		//get the first token of the class
		tokenizer->advance();
		compileClass();
	}
}

