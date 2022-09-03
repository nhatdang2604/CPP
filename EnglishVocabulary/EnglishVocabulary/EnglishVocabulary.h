#pragma once
#ifndef _ENGLISH_VOCABULARY_H
#define _ENGLISH_VOCABULARY_H

#include<string>
#include<vector>
#include<time.h>
#include<iostream>
using namespace std;

#define NUMBER_OF_WORDS 10

vector<string> initVietnameseWords();
vector<string> initEnglishWords();
int randomizeIndex();
void getWord(const vector<string>&, const vector<string>&);
void runEnglishVocabulary(const vector<string>&, const vector<string>&);

#endif // 



