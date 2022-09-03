#include "EnglishVocabulary.h"

int main() {
	vector<string> english = initEnglishWords();
	vector<string> vietnamese = initVietnameseWords();
	runEnglishVocabulary(english, vietnamese);
	return 0;
}