#include <fstream>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

struct Examinee {
	string id;
	float math;
	float literary;
	float physic;
	float chemistry;
	float biology;
	float history;
	float geography;
	float civic_education;
	float natural_science;
	float social_science;
	float foreign_language;
};

bool openInput(ifstream& infile) {
	infile.open("data.txt", ifstream::in);
	if (infile.is_open()) return true;
	else return false;
}

void closeInput(ifstream& infile) {
	if (infile.is_open()) infile.close();
}

string getOutfileName() {
	string name;
	cout << "\nMoi thay nhap ten file output (khong bao gom extension)\n";
	cout << "Moi thay nhap: ";
	getline(cin, name);
	cout << "File output luc nay la: " << name << ".txt\n";
	name.append(".txt");
	return name;
}

void getPoint(string& lineData, float& point) {
	int pos = lineData.find_first_of(',');
	point = 0;
	string _point = lineData.substr(0, pos);
	if (_point != "") {
		point = stof(_point);
	}
	lineData = lineData.erase(0, pos + 1);
}

Examinee ReadExaminee(string line_info) {
	Examinee data;
	string lineData = line_info;

	//get id
	int pos = lineData.find_first_of(',');
	data.id = line_info.substr(0, pos);
	lineData = lineData.erase(0, pos + 1);

	//get point
	getPoint(lineData, data.math);
	getPoint(lineData, data.literary);
	getPoint(lineData, data.physic);
	getPoint(lineData, data.chemistry);
	getPoint(lineData, data.biology);
	getPoint(lineData, data.history);
	getPoint(lineData, data.geography);
	getPoint(lineData, data.civic_education);
	getPoint(lineData, data.natural_science);
	getPoint(lineData, data.social_science);
	getPoint(lineData, data.foreign_language);

	return data;
}

vector<Examinee> ReadExamineeList(string file_name) {
	vector<Examinee> result;
	ifstream infile;
	if (openInput(infile)) {
		string lineData;
		Examinee examinee;

		//ignore the first line, control the input file pointer to the next line
		getline(infile, lineData, '\n');

		while (!infile.eof()) {
			getline(infile, lineData, '\n');
			examinee = ReadExaminee(lineData);
			result.push_back(examinee);
		}
	}

	return result;
}

void WriteSumOfScore(vector<Examinee> examinee_list, string out_file_name) {
	ofstream outfile(out_file_name);

	if (!outfile) {
		cout << "Khong the mo duoc file " << out_file_name << ".txt\n";
		return;
	}

	//Output each of examinee's sum of score to out_file_name.txt
	for (Examinee content : examinee_list) {
		content.natural_science = content.physic + content.chemistry + content.biology;
		content.social_science = content.history + content.geography + content.civic_education;
		float sum = content.math + content.literary + content.foreign_language
			+ content.natural_science + content.social_science;
		outfile << content.id << " ";
		outfile << sum << "\n";
	}

	outfile.close();
	
}

int run() {
	ifstream infile;
	if (!openInput(infile)) {
		cout << "Khong the mo file data.txt de doc\n";
		cout << "Se ket thuc chuong trinh\n";
		return -1;
	}
	else {
		string outfileName = getOutfileName();
		vector<Examinee> list = ReadExamineeList("data.txt");
		WriteSumOfScore(list, outfileName);
		closeInput(infile);
	}
	return 0;
}

int main() {	
	int errorCode = run();
	return 0;
}
