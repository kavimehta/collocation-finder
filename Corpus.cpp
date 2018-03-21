#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;

/**
 * This class represents the text file that makes up a corpus.
 */
class Corpus {
public:

	string filename;
	ofstream file;

	/**
     * Constructor for the Corpus.
     *
     * @param filename_ The text file that contains the corpus.
     */
	Corpus(string filename_) {
		filename = filename_;
	}

	/**
     * Open the file for reading.
     *
     * @return true if the open succeeded, false if the open failed.
     */
	bool openFile() {
		file.open(filename);
		return not f.fail();
	}

    /**
     * Close the file if it was open.
     *
     * @return true if the file was already closed or the
     * operation closed it. false if the file is still
     * open after execution.
     */
	bool closeFile() {
		if (f.is_open()) {
			f.close()
			return not f.fail();
		}
		return true;
	}

    /**
     * Count all the lines in the corpus and print to cout.
     */
	void countLines() {
		int count = 0;
		string line;
		while (getline(file, line)) {
			count++;
		}
		cout << "Lines: " << count;
	}

    /**
     * This returns a Vector of Strings, where each String is a sentence in the
     * Corpus that contains the specified word.
     *
     * @param word_ The word that is searched for in the corpus.
     * @return The Vector of Strings with the sentences.
     */
	vector<string> getSentencesWith(string word_) {
		vector<string> foundSentences;
		openFile();
		string record;
		while (getline(myfile, record)) {
			// Add spaces so record.find catches word at beginning or end
			string tempRecord = " " + record + " ";
			if (tempRecord.find(" " + word_ + " ")) {
				foundSentences.push_back(record);
			}
		}
		closeFile();
		return foundSentences;
	}
}