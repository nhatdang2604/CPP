#include <iostream>
#include <dirent.h>
#include <vector>
#include "JackAnalyzer.h"
using namespace std;

/* Get all the ".jack" file in the path, and store into the list*/
/* This module uses <dirent.h> version for Windows, because submit in Linux*/
void getFileInDir(string path, vector<string> &list) {
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(path.c_str())) != NULL) {

		//Scanning directory contents looking for ".jack" file
		while ((ent = readdir(dir)) != NULL) {

			//Get a file in directory
			string entryName = ent->d_name;

			//If the extension is ".jack"
			if (entryName.find(".jack")!=string::npos) {

				//Add the path/file.hack into the list
				list.push_back(path + "/" + entryName);
			}
		}
		closedir(dir);
	}
	else {
		cout << "Cannot open the directory\n";
	}
}


int main(int argc, char *argv[]) {

	vector<string>fileList;			//Use to contain all the .jack file input
	string source = argv[1];		//Use to contain the input file
	string outputPath = "";	//Use to contain the current directory

	//if there is ".jack" in the source file
	if (source.find(".jack")!=string::npos) {
		fileList.push_back(source);	
	}
	else {
		//Else, this is a folder, get all the ".jack" file in the folder
		getFileInDir(source, fileList);

		//The output path become the input folder
		outputPath += "/" + source + "/";
	}

	//Translate all the "file.jack" contain in fileList

	//Testing
	for (string content : fileList) {
		JackAnalyzer* _jackAnalyzer = new JackAnalyzer(content, outputPath);
		_jackAnalyzer->translate();
	}

	system("PAUSE");
	return 0;
}