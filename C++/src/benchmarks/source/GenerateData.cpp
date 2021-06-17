#include "rapidjson/document.h"
#include <iostream>
#include <fstream>

using namespace rapidjson;
using namespace std;

int main(int argc, char *argv[]) {

	if (argc < 3) {
		cout << "Requires Tweeter JSON file path!!" << endl;
		cout << "Requires Tweeter JSON out path" << endl;
		cout << "Run as: ./main <path/to/tweet.json>  <path/to/output/file>" << endl;
		return 0;
	}

	// Read line-by-line data from dataset and sent it to json parser:
	ifstream infile;
	//infile.open(argv[1]);
	string line;

	//Set output file path
	string outFile = argv[2];


	//Output Stream: For Index Writing:
	ofstream outfile;
	outfile.open(outFile.c_str());

	//Set number of repeats
	int numberOfRepeat = atoi(argv[3]);

	int l = 0;

	for (int i = 0; i < numberOfRepeat; ++i) {
		infile.open(argv[1]);
		while (getline(infile, line)) {
			outfile << line;
			outfile << "\n";
			l++;
		}
		infile.close();
		infile.clear();
	}


	outfile.close();
	outfile.clear();

	return 0;

}