#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;

class Corpus {
public:

	string filename;
	ofstream file;

	Corpus(string filename_) {
		filename = filename_;
	}

	bool openFile() {
		file.open(filename);
		return not f.fail()
	}

	bool closeFile() {
		if (f.is_open()) {
			f.close()
			return not f.fail();
		}
		return true;
	}
}