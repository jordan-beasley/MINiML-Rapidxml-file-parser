#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::ifstream;
using std::endl;
using std::string;

int main() {

	string url;
	int counter = 0;

	ifstream infile("GetFile.txt");

	if (infile.is_open()) {

		while (!infile.eof()) {

			if (infile.bad()) {

				infile.clear();

			}

			infile >> url;
			string command = "wget " + url + " &"; // make the command a standard string to be casted to a c style string
			//string command = "echo " + url;
			system((const char*)command.c_str());

			//cout << "the Url " << counter << " is: " << url << endl;

			counter++;

		}



	}
	else {
		cout << "Could not locate file" << endl;


	}



	//system("pause");
	return 0;
}
