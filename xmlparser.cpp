#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "rapidxml.hpp"


using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ofstream;
using std::ifstream;
using namespace rapidxml;
using std::vector;
using std::istreambuf_iterator;


string GetSentrixID(string url);
string GetSentrixPosition(string url);
string GetGroup(string Group);
string NameExcelFile();

int main(void)
{

	xml_document<> doc;
	xml_node<> * root_node;
	// Read the xml file into a vector
	string file;
	cout << "Enter the name of the file(including the .xml extension): ";
	getline(cin, file);

	ifstream theFile(file);

	if (theFile.is_open()) {

		vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
		buffer.push_back('\0');
		// Parse the buffer using the xml file parsing library into doc 
		doc.parse<0>(&buffer[0]);
		root_node = doc.first_node("MINiML");

		//create and open the and excel file for output
		string outputFile = NameExcelFile();

		ofstream outfile(outputFile); // RENAME THE OUTPUT FILE FOR THE EXCEL SHEET
		outfile << "[Header]" << endl;


		// get the instigator name
		/*xml_node<>* Contributor_node = root_node->first_node("Contributor");
		xml_node<>* Person_node = Contributor_node->first_node("Person");
		xml_node<>* Firstname_node = Person_node->first_node("First");
		xml_node<>* Lastname_node = Person_node->first_node("Last");

		outfile << "Instigator Name" << "\t" << Firstname_node->value() << " " << Lastname_node->value() << endl;*/


		outfile << "Instigator Name" << "\t" << endl;
		outfile << "Project Name" << endl;
		outfile << "Experiment Name" << endl;
		outfile << "Date" << endl;

		outfile << endl; // skip a row

		outfile << "[Data]" << endl;
		outfile << "Sample_Name" << "\t"
			<< "Sample_Plate" << "\t"
			<< "Sample_Group" << "\t"
			<< "Pool_ID" << "\t"
			<< "Project" << "\t"
			<< "Sample_Well" << "\t"
			<< "Sentrix_ID" << "\t"
			<< "Sentrix_Position" << "\t" << endl;


		//Creating text file for get
		ofstream Getfile("GetFile.txt");

		// find each sample node
		for (xml_node<>* Sample_node = root_node->first_node("Sample"); Sample_node; Sample_node = Sample_node->next_sibling())
		{

			cout << Sample_node->first_attribute("iid")->value() << endl;

			//get source 
			xml_node<>* Channel_node = Sample_node->first_node("Channel");

			if (Channel_node != nullptr) { // checks to make sure a soure can be found for the sample
				//xml_node<>* Source_node = Channel_node->first_node("Source");


				outfile << Sample_node->first_node("Title")->value() << "\t" // Sample name
					<< "\t"; // Sample plate
				
				
				// get the group
				string Group = GetGroup(Channel_node->first_node("Source")->value());
				outfile << Group << "\t"; // Sample group

				outfile << "\t" // Pool ID
					<< "\t" // Project
					<< "\t"; // Sample well
				
				string attribute = Sample_node->first_node("Supplementary-Data")->first_attribute("type")->value(); // Check for an IDAT link

				if (attribute == "IDAT") {

					// get the sentrix id
					string SentrixID = GetSentrixID(Sample_node->first_node("Supplementary-Data")->value());
					outfile << SentrixID << "\t"; //Sentrix ID


					// get the sentrix position
					string SentrixPosition = GetSentrixPosition(Sample_node->first_node("Supplementary-Data")->value());
					outfile << SentrixPosition << endl; //Sentrix position
			
				}
				else {

					outfile << "\t";
					outfile << endl;


				}




				// get each url and store it in a text file
				string dataAttribute; //= Sample_node->first_node("Supplementary-Data")->first_attribute("type")->value();

					for (xml_node<>* Data_node = Sample_node->first_node("Supplementary-Data"); Data_node; Data_node = Data_node->next_sibling()) {
						
						if (Data_node->next_sibling() != nullptr) {

							dataAttribute = Data_node->first_attribute("type")->value(); // checking for an IDAT link
						}
						else {
							
							dataAttribute = "";

						}

						if (dataAttribute == "IDAT") {

							cout << "IDAT" << endl;


							//Getfile << Data_node->value() << endl;


							for (xml_node<>* Data_node = Sample_node->first_node("Supplementary-Data"); Data_node; Data_node = Data_node->next_sibling()) {

									Getfile << Data_node->value() << endl;


							}

						}


						

					}


			}


		}



		outfile.close();
		Getfile.close();
	}
	else {

		cout << "Could not locate file" << endl;


	}
	
	//system("pause");

	return 0;
}


string GetSentrixID(string url) {

	string ID;
	bool gotId = false;
	int index = 0;
	char temp;

	char* IDHolder = nullptr; // making a character array to hold the url
	int length = url.length(); // getting the length of the url

	if (length > 0) {

		IDHolder = &url[index];

		//cout << "1\n";

		
		do {
			
	
			temp = IDHolder[index];
			//cout << "2\n";

			

			if (temp == '_') {
				//cout << "3\n";

				index++; // move to the next index in the array

				temp = IDHolder[index];
				while (temp != '_' && isdigit(temp)) {
					//cout << "4\n";

					ID = ID + temp;

					index++;

					temp = IDHolder[index];

				}


				gotId = true;

			}



			index++;
		} while (!gotId && index < length);


		IDHolder = nullptr;
		delete IDHolder;


		
	}
	
	return ID;
}

string GetSentrixPosition(string url) {

	string Position;
	bool gotPos = false;
	int index = 0;
	char temp;

	char* PositionHolder = nullptr; // making a character array to hold the url
	int length = url.length(); // getting the length of the url

	if (length > 0) {

		PositionHolder = &url[index];

		//cout << "1\n";


		do {


			temp = PositionHolder[index];
			//cout << "2\n";



			if (temp == 'R') {
				//cout << "3\n";

				//index++; // move to the next index in the array

				temp = PositionHolder[index];
				while (temp != '_') {
					//cout << "4\n";

					Position = Position + temp;

					index++;

					temp = PositionHolder[index];

				}


				gotPos = true;

			}



			index++;
		} while (!gotPos && index < length);


		PositionHolder = nullptr;
		delete PositionHolder;


		
	}
	
	return Position;
}


string GetGroup(string Group) {

	string SampleGroup;

	char* GroupHolder = nullptr;
	char temp;
	int length = Group.length();
	int index = 0;

	

	if (Group != " ") {

		GroupHolder = &Group[index];

		temp = GroupHolder[index];

		while (index < length) {

			SampleGroup = SampleGroup + temp;

			index++;

			temp = GroupHolder[index];
			
			
		}


	}




	GroupHolder = nullptr;
	delete GroupHolder;

	return SampleGroup;
}


string NameExcelFile() {

	string fileName;

	cout << "What do you want to name the excel file? or press enter to default name to projectData(do NOT include the file extension): ";
	getline(cin, fileName, '\n'); // using a new line buffer so the user can default the file name


	if (fileName == "") { // checking if the user wants to default the file name

		fileName = "projectData";

	}


	return fileName + ".xls";
}
