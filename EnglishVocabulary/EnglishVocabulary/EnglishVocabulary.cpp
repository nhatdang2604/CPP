#include "EnglishVocabulary.h"


vector<string> initVietnameseWords() {
	vector<string>result;
	result.push_back("Con cho");
	result.push_back("Con meo");
	result.push_back("Con tho");
	result.push_back("Con ga");
	result.push_back("Con heo");
	result.push_back("Con bo");
	result.push_back("Con buom");
	result.push_back("Con ong");
	result.push_back("Con chim");
	result.push_back("Con chuot");
	return result;
}

vector<string> initEnglishWords() {
	vector<string> result;
	result.push_back("Dog");
	result.push_back("Cat");
	result.push_back("Rabbit");
	result.push_back("Chicken");
	result.push_back("Pig");
	result.push_back("Cow");
	result.push_back("Butterfly");
	result.push_back("Bee");
	result.push_back("Bird");
	result.push_back("Mouse");
	return result;
}

int randomizeIndex() {
	return rand() % NUMBER_OF_WORDS;
}

void getWord(const vector<string>& english, const vector<string>& vietnamese) {
	int index = randomizeIndex();
	cout << "English: " << english[index] << " -> Vietnamese: " << vietnamese[index] << endl;
}

void runEnglishVocabulary(const vector<string>& english, const vector<string>& vietnamese) {
	srand(unsigned int(time(NULL)));
	string buffer;
	do {
		system("CLS");
		cout << "**Huong dan: De dung chuong trinh, hay nhap ki tu bat ki, sau day nhan Enter\n";
		cout << "- Tu vung ta nhan duoc la:\n\n";
		getWord(english, vietnamese);
		cout << endl;
		cout << "Nhan Enter de tiep tuc gieo ra tu moi...\n";
		getline(cin, buffer);
	} while (buffer == "");
}